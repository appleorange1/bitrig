/*	$OpenBSD: biosvar.h,v 1.13 1997/09/29 03:42:28 mickey Exp $	*/

/*
 * Copyright (c) 1997 Michael Shalayeff
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
 *	This product includes software developed by Michael Shalayeff.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _I386_BIOSVAR_H_
#define _I386_BIOSVAR_H_

#define	BOOT_APIVER	0x00000001

#define BIOSNHEADS(d)	(((d)>>24)+1)
#define BIOSNSECTS(d)	((d)&0x3f)	/* sectors are 1-based */
#define BIOSNDRIVES(d)	((((d)>>16)&0x0f)+1)
#define BIOSNTRACKS(d)	(( (((d)>>8)&0xff) | (((d)&0xc0)<<2) ) +1)

/* BIOS media ID */
#define BIOSM_F320K	0xff	/* floppy ds/sd  8 spt */
#define	BIOSM_F160K	0xfe	/* floppy ss/sd  8 spt */
#define	BIOSM_F360K	0xfd	/* floppy ds/sd  9 spt */
#define	BIOSM_F180K	0xfc	/* floppy ss/sd  9 spt */
#define	BIOSM_ROMD	0xfa	/* ROM disk */
#define	BIOSM_F120M	0xf9	/* floppy ds/hd 15 spt 5.25" */
#define	BIOSM_F720K	0xf9	/* floppy ds/dd  9 spt 3.50" */
#define	BIOSM_HD	0xf8	/* hard drive */
#define	BIOSM_F144K	0xf0	/* floppy ds/hd 18 spt 3.50" */
#define	BIOSM_OTHER	0xf0	/* any other */

/* 
 * CTL_BIOS definitions.
 */
#define	BIOS_DEV		1	/* int: BIOS boot device */
#define	BIOS_GEOMETRY		2	/* int: BIOS boot device geometry */
#define	BIOS_CNVMEM		3	/* int: amount of conventional memory */
#define	BIOS_EXTMEM		4	/* int: amount of extended memory */
#define	BIOS_MAXID		5	/* number of valid machdep ids */

#define	CTL_BIOS_NAMES { \
	{ 0, 0 }, \
	{ "biosdev", CTLTYPE_INT }, \
	{ "biosgeo", CTLTYPE_INT }, \
	{ "cnvmem", CTLTYPE_INT }, \
	{ "extmem", CTLTYPE_INT }, \
}

#if defined(_KERNEL) || defined (_STANDALONE)

#ifdef _LOCORE
#define	DOINT(n)	int	$0x20+(n)
#else
#define	DOINT(n)	"int $0x20+(" #n ")"

extern struct BIOS_vars {
	/* XXX filled in assumption that last file opened is kernel */
	int	bios_dev;
	int	bios_geometry;

	u_int	bios_apm_detail;
	u_int	bios_apm_code32_base;
	u_int	bios_apm_code16_base;
	u_int	bios_apm_code_len;
	u_int	bios_apm_data_base;
	u_int	bios_apm_data_len;
	u_int	bios_apm_entry;

}	BIOS_vars;

extern struct BIOS_regs {
	u_int32_t	biosr_ax;
	u_int32_t	biosr_cx;
	u_int32_t	biosr_dx;
	u_int32_t	biosr_bx;
	u_int32_t	biosr_bp;
	u_int32_t	biosr_si;
	u_int32_t	biosr_di;
	u_int32_t	biosr_ds;
	u_int32_t	biosr_es;
}	BIOS_regs;

struct EDD_CB {
	u_int8_t  edd_len;   /* size of packet */
	u_int8_t  edd_res;   /* reserved */
	u_int16_t edd_nblk;  /* # of blocks to transfer */
	u_int32_t edd_buf;   /* address of buffer */
	u_int64_t edd_daddr; /* starting block */
};

#ifdef _KERNEL
#include <machine/bus.h>

struct bios_attach_args {
	char *bios_dev;
	union {
		struct {
			bus_space_tag_t _bios_iot;
			bus_space_tag_t _bios_memt;
		} bios;
		struct {
			u_int	_apm_detail;
			u_int	_apm_code32_base;
			u_int	_apm_code16_base;
			u_int	_apm_code_len;
			u_int	_apm_data_base;
			u_int	_apm_data_len;
			u_int	_apm_entry;
		} apm;
	} _;
};

#define	bios_iot	_.bios._bios_iot
#define	bios_memt	_.bios._bios_memt
#define	apm_detail	_.apm._apm_detail
#define	apm_code32_base	_.apm._apm_code32_base
#define	apm_code16_base	_.apm._apm_code16_base
#define	apm_code_len	_.apm._apm_code_len
#define	apm_data_base	_.apm._apm_data_base
#define	apm_data_len	_.apm._apm_data_len
#define	apm_entry	_.apm._apm_entry

struct consdev;
struct proc;

int bios_sysctl
	__P((int *, u_int, void *, size_t *, void *, size_t, struct proc *));

void bioscnprobe __P((struct consdev *));
void bioscninit __P((struct consdev *));
void bioscnputc __P((dev_t, int));
int bioscngetc __P((dev_t));
void bioscnpollc __P((dev_t, int));

#endif /* _KERNEL */
#endif /* _LOCORE */
#endif /* _KERNEL || _STANDALONE */

#endif /* _I386_BIOSVAR_H_ */
