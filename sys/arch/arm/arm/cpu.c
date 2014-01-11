/*	$OpenBSD: cpu.c,v 1.17 2013/08/06 23:15:43 jsg Exp $	*/
/*	$NetBSD: cpu.c,v 1.56 2004/04/14 04:01:49 bsh Exp $	*/


/*
 * Copyright (c) 1995 Mark Brinicombe.
 * Copyright (c) 1995 Brini.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Brini.
 * 4. The name of the company nor the name of the author may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BRINI ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL BRINI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * RiscBSD kernel project
 *
 * cpu.c
 *
 * Probing and configuration for the master CPU
 *
 * Created      : 10/10/95
 */

#include <sys/param.h>

#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/device.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <uvm/uvm_extern.h>
#include <machine/cpu.h>

#include <arm/cpuconf.h>
#include <arm/undefined.h>
#include <arm/vfp.h>

char cpu_model[256];

/* Prototypes */
void identify_arm_cpu(struct device *dv, struct cpu_info *);

/*
 * Identify the master (boot) CPU
 */
  
void
cpu_attach(struct device *dv)
{
	curcpu()->ci_dev = dv;

	/* Get the CPU ID from coprocessor 15 */

	curcpu()->ci_arm_cpuid = cpu_id();
	curcpu()->ci_arm_cputype = curcpu()->ci_arm_cpuid & CPU_ID_CPU_MASK;
	curcpu()->ci_arm_cpurev =
	    curcpu()->ci_arm_cpuid & CPU_ID_REVISION_MASK;

	identify_arm_cpu(dv, curcpu());

	vfp_init();
}

enum cpu_class {
	CPU_CLASS_NONE,
	CPU_CLASS_ARMv7
};

static const char * const generic_steppings[16] = {
	"rev 0",	"rev 1",	"rev 2",	"rev 3",
	"rev 4",	"rev 5",	"rev 6",	"rev 7",
	"rev 8",	"rev 9",	"rev 10",	"rev 11",
	"rev 12",	"rev 13",	"rev 14",	"rev 15"
};

struct cpuidtab {
	u_int32_t	cpuid;
	enum		cpu_class cpu_class;
	const char	*cpu_name;
	const char * const *cpu_steppings;
};

const struct cpuidtab cpuids[] = {
	{ CPU_ID_CORTEX_A5,	CPU_CLASS_ARMv7,	"ARM Cortex A5",
	  generic_steppings },
	{ CPU_ID_CORTEX_A7,	CPU_CLASS_ARMv7,	"ARM Cortex A7",
	  generic_steppings },
	{ CPU_ID_CORTEX_A8,	CPU_CLASS_ARMv7,	"ARM Cortex A8",
	  generic_steppings },
	{ CPU_ID_CORTEX_A8_R1,	CPU_CLASS_ARMv7,	"ARM Cortex A8 R1",
	  generic_steppings },
	{ CPU_ID_CORTEX_A8_R2,	CPU_CLASS_ARMv7,	"ARM Cortex A8 R2",
	  generic_steppings },
	{ CPU_ID_CORTEX_A8_R3,	CPU_CLASS_ARMv7,	"ARM Cortex A8 R3",
	  generic_steppings },
	{ CPU_ID_CORTEX_A9,	CPU_CLASS_ARMv7,	"ARM Cortex A9",
	  generic_steppings },
	{ CPU_ID_CORTEX_A9_R1,	CPU_CLASS_ARMv7,	"ARM Cortex A9 R1",
	  generic_steppings },
	{ CPU_ID_CORTEX_A9_R2,	CPU_CLASS_ARMv7,	"ARM Cortex A9 R2",
	  generic_steppings },
	{ CPU_ID_CORTEX_A9_R3,	CPU_CLASS_ARMv7,	"ARM Cortex A9 R3",
	  generic_steppings },
	{ CPU_ID_CORTEX_A9_R4,	CPU_CLASS_ARMv7,	"ARM Cortex A9 R4",
	  generic_steppings },
	{ CPU_ID_CORTEX_A15,	CPU_CLASS_ARMv7,	"ARM Cortex A15",
	  generic_steppings },
	{ CPU_ID_CORTEX_A15_R1,	CPU_CLASS_ARMv7,	"ARM Cortex A15 R1",
	  generic_steppings },
	{ CPU_ID_CORTEX_A15_R2,	CPU_CLASS_ARMv7,	"ARM Cortex A15 R2",
	  generic_steppings },
	{ CPU_ID_CORTEX_A15_R3,	CPU_CLASS_ARMv7,	"ARM Cortex A15 R3",
	  generic_steppings },
	{ CPU_ID_CORTEX_A15_R4,	CPU_CLASS_ARMv7,	"ARM Cortex A15 R4",
	  generic_steppings },

	{ 0, CPU_CLASS_NONE, NULL, NULL }
};

struct cpu_classtab {
	const char	*class_name;
	const char	*class_option;
};

const struct cpu_classtab cpu_classes[] = {
	{ "unknown",	NULL },			/* CPU_CLASS_NONE */
	{ "ARMv7",	"CPU_ARMv7" }		/* CPU_CLASS_ARMv7 */

};

/*
 * Report the type of the specified arm processor. This uses the generic and
 * arm specific information in the cpu structure to identify the processor.
 * The remaining fields in the cpu structure are filled in appropriately.
 */

static const char * const wtnames[] = {
	"wr-thru",
	"wr-back",
	"wr-back",
	"**unknown 3**",
	"**unknown 4**",
	"wr-back-lock",		/* XXX XScale-specific? */
	"wr-back-lock-A",
	"wr-back-lock-B",
	"**unknown 8**",
	"**unknown 9**",
	"**unknown 10**",
	"**unknown 11**",
	"**unknown 12**",
	"**unknown 13**",
	"**unknown 14**",
	"**unknown 15**"
};

void
identify_arm_cpu(struct device *dv, struct cpu_info *ci)
{
	u_int cpuid;
	enum cpu_class cpu_class = CPU_CLASS_NONE;
	int i;

	cpuid = ci->ci_arm_cpuid;

	if (cpuid == 0) {
		printf("Processor failed probe - no CPU ID\n");
		return;
	}

	for (i = 0; cpuids[i].cpuid != 0; i++)
		if (cpuids[i].cpuid == (cpuid & CPU_ID_CPU_MASK)) {
			cpu_class = cpuids[i].cpu_class;
			snprintf(cpu_model, sizeof(cpu_model),
			    "%s %s (%s core)", cpuids[i].cpu_name,
			    cpuids[i].cpu_steppings[cpuid &
						    CPU_ID_REVISION_MASK],
			    cpu_classes[cpu_class].class_name);
			break;
		}

	if (cpuids[i].cpuid == 0)
		snprintf(cpu_model, sizeof(cpu_model),
		    "unknown CPU (ID = 0x%x)", cpuid);

	printf(": %s\n", cpu_model);

	printf("%s:", dv->dv_xname);

	switch (cpu_class) {
	case CPU_CLASS_ARMv7:
		if ((ci->ci_ctrl & CPU_CONTROL_DC_ENABLE) == 0)
			printf(" DC disabled");
		else
			printf(" DC enabled");
		if ((ci->ci_ctrl & CPU_CONTROL_IC_ENABLE) == 0)
			printf(" IC disabled");
		else
			printf(" IC enabled");
		break;
	default:
		break;
	}
	if ((ci->ci_ctrl & CPU_CONTROL_WBUF_ENABLE) == 0)
		printf(" WB disabled");
	else
		printf(" WB enabled");

	if (ci->ci_ctrl & CPU_CONTROL_LABT_ENABLE)
		printf(" LABT");
	else
		printf(" EABT");

	if (ci->ci_ctrl & CPU_CONTROL_BPRD_ENABLE)
		printf(" branch prediction enabled");

	printf("\n");

	/* Print cache info. */
	if (arm_picache_line_size == 0 && arm_pdcache_line_size == 0)
		goto skip_pcache;

	if (arm_pcache_unified) {
		printf("%s: %dKB/%dB %d-way %s unified cache\n",
		    dv->dv_xname, arm_pdcache_size / 1024,
		    arm_pdcache_line_size, arm_pdcache_ways,
		    wtnames[arm_pcache_type]);
	} else {
		printf("%s: %dKB(%db/l,%dway) I-cache, %dKB(%db/l,%dway) %s D-cache\n",
		    dv->dv_xname, arm_picache_size / 1024,
		    arm_picache_line_size, arm_picache_ways,
		    arm_pdcache_size / 1024, arm_pdcache_line_size, 
		    arm_pdcache_ways, wtnames[arm_pcache_type]);
	}

 skip_pcache:

	switch (cpu_class) {
	case CPU_CLASS_ARMv7:
		break;
	default:
		if (cpu_classes[cpu_class].class_option != NULL)
			printf("%s: %s does not fully support this CPU."
			       "\n", dv->dv_xname, ostype);
		else {
			printf("%s: This kernel does not fully support "
			       "this CPU.\n", dv->dv_xname);
			printf("%s: Recompile with \"options %s\" to "
			       "correct this.\n", dv->dv_xname,
			       cpu_classes[cpu_class].class_option);
		}
		break;
	}
			       
}
#ifdef MULTIPROCESSOR
void
cpu_boot_secondary_processors(void)
{
	struct cpu_info *ci;
	u_long i;

	for (i=0; i < MAXCPUS; i++) {
		ci = cpu_info[i];
		if (ci == NULL)
			continue;
		if (ci->ci_idle_pcb == NULL)
			continue;
		if ((ci->ci_flags & CPUF_PRESENT) == 0)
			continue;
		if (ci->ci_flags & (CPUF_BSP|CPUF_SP|CPUF_PRIMARY))
			continue;
		ci->ci_randseed = random();
		/* XXX: Not yet, my dear. */
		//cpu_boot_secondary(ci);
	}
}

int
cpu_alloc_idle_pcb(struct cpu_info *ci)
{
	vaddr_t uaddr;
	struct pcb *pcb;
	struct trapframe *tf;

	/*
	 * Generate a kernel stack and PCB (in essence, a u-area) for the
	 * new CPU.
	 */
	uaddr = (vaddr_t)km_alloc(USPACE, &kv_any, &kp_zero, &kd_nowait);
	if (uaddr == 0) {
		printf("%s: unable to allocate idle stack\n",
		    __func__);
		return 1;
	}
	ci->ci_idle_pcb = pcb = (struct pcb *)uaddr;

	/*
	 * This code is largely derived from cpu_fork(), with which it
	 * should perhaps be shared.
	 */

	/* Copy the pcb */
	*pcb = proc0.p_addr->u_pcb;

	/* Set up the undefined stack for the process. */
	pcb->pcb_un.un_32.pcb32_und_sp = uaddr + USPACE_UNDEF_STACK_TOP;
	pcb->pcb_un.un_32.pcb32_sp = uaddr + USPACE_SVC_STACK_TOP;

#ifdef STACKCHECKS
	/* Fill the undefined stack with a known pattern */
	memset(((u_char *)uaddr) + USPACE_UNDEF_STACK_BOTTOM, 0xdd,
	    (USPACE_UNDEF_STACK_TOP - USPACE_UNDEF_STACK_BOTTOM));
	/* Fill the kernel stack with a known pattern */
	memset(((u_char *)uaddr) + USPACE_SVC_STACK_BOTTOM, 0xdd,
	    (USPACE_SVC_STACK_TOP - USPACE_SVC_STACK_BOTTOM));
#endif	/* STACKCHECKS */

	pcb->pcb_tf = tf =
	    (struct trapframe *)pcb->pcb_un.un_32.pcb32_sp - 1;
	*tf = *proc0.p_addr->u_pcb.pcb_tf;
	return 0;
}
#endif /* MULTIPROCESSOR */

/*
 * eventually it would be interesting to have these functions
 * support the V6/V7+ atomic instructions ldrex/strex if available
 * on the CPU.
 */
void
atomic_setbits_int(__volatile unsigned int *uip, unsigned int v)
{
	int oldirqstate;
	oldirqstate = disable_interrupts(I32_bit|F32_bit);
	*uip |= v;
	restore_interrupts(oldirqstate);
}

void
atomic_clearbits_int(__volatile unsigned int *uip, unsigned int v)
{
	int oldirqstate;
	oldirqstate = disable_interrupts(I32_bit|F32_bit);
	*uip &= ~v;
	restore_interrupts(oldirqstate);
}

/* End of cpu.c */
