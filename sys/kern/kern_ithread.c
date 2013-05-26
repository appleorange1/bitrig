#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/ithread.h>
#include <sys/kthread.h>

#include <uvm/uvm_extern.h>

#include <machine/intr.h> 	/* XXX */

/*
 * ITHREADS
 */

#define ITHREAD_DEBUG
#ifdef ITHREAD_DEBUG
int ithread_debug = 10;
#define DPRINTF(l, x...)	do { if ((l) <= ithread_debug) printf(x); } while (0)
#else
#define DPRINTF(l, x...)
#endif	/* ITHREAD_DEBUG */

void
ithread(void *v_is)
{
	struct intrsource *is = v_is;
	struct pic *pic = is->is_pic;
	struct intrhand *ih;
	int rc, s;

	sched_peg_curproc(&cpu_info_primary);
	KERNEL_UNLOCK();

	DPRINTF(1, "ithread %p pin %d started\n",
	    curproc->p_pid, is->is_pin);

	for (; ;) {
		rc = 0;

		s = splraise(is->is_maxlevel);
		for (ih = is->is_handlers; ih != NULL; ih = ih->ih_next) {
			is->is_scheduled = 0; /* protected by is->is_maxlevel */

			if ((ih->ih_flags & IPL_MPSAFE) == 0)
				KERNEL_LOCK();

			KASSERT(ih->ih_level <= is->is_maxlevel);
			rc |= (*ih->ih_fun)(ih->ih_arg);

			if ((ih->ih_flags & IPL_MPSAFE) == 0)
				KERNEL_UNLOCK();
		}
		splx(s);

		if (!rc)
			printf("stray interrupt pin %d ?\n", is->is_pin);

		pic->pic_hwunmask(pic, is->is_pin);

		s = splraise(is->is_maxlevel);
		/*
		 * Since we do splx, we might have just run the handler which
		 * wakes us up, therefore, is_scheduled might be set now, in the
		 * future we should have 3 values, so that the handler could
		 * save the wakeup() but still set is_scheduled. We need to
		 * raise the IPL again so that the check for is_scheduled and
		 * the tsleep call is atomic.
		 */
		if (!is->is_scheduled) {
			ithread_sleep(is);
			DPRINTF(20, "ithread %p woke up\n", curproc->p_pid);
		}
		splx(s);
	}
}


/* XXX intr_shared_edge totalmente ignorado */
/*
 * We're called with interrupts disabled, so no need to protect anything. This
 * is the code that gets called when get a real interrupt, it's sole purpose is
 * to schedule the interrupt source to run.
 */
int
ithread_handler(struct intrsource *is)
{
	struct cpu_info *ci = curcpu();
	struct schedstate_percpu *spc = &ci->ci_schedstate;
	struct proc *p = is->is_proc;

	splassert(is->is_maxlevel);

	DPRINTF(10, "ithread accepted interrupt pin %d "
	    "(ilevel = %d, maxlevel = %d)\n",
	    is->is_pin, ci->ci_ilevel, is->is_maxlevel);

	is->is_scheduled = 1;

	switch (p->p_stat) {
	case SRUN:
	case SONPROC:
		break;
	case SSLEEP:
		TAILQ_REMOVE(&spc->spc_ithread_slpq, p, p_runq);
		p->p_wmesg   = NULL;
		p->p_stat    = SRUN;
		p->p_slptime = 0;
		/*
		 * Setting the thread to runnable is cheaper than a normal
		 * process since the process state can be protected by blocking
		 * interrupts. There is also no need to choose a cpu since we're
		 * pinned. XXX we're not there yet and still rely on normal
		 * SCHED_LOCK crap.
		 */
		TAILQ_INSERT_TAIL(&spc->spc_ithread_runq, p, p_runq);
		break;
	default:
		panic("ithread_handler: unexpected thread state %d\n", p->p_stat);
	}

	return (0);
}

void
ithread_sleep(struct intrsource *is)
{
	struct proc *p = curproc;
	struct schedstate_percpu *spc = &curcpu()->ci_schedstate;
	int s;

	KASSERT(p == is->is_proc);
	KASSERT(p->p_stat == SONPROC);
	splassert(is->is_maxlevel);

	p->p_wmesg = "interrupt";
	p->p_stat = SSLEEP;

	TAILQ_INSERT_TAIL(&spc->spc_ithread_slpq, p, p_runq);

	/*
	 * XXX mi_switch() still wants SCHED_LOCK, we must zefix it.
	 */
	SCHED_LOCK(s);
	mi_switch();
	SCHED_UNLOCK(s);
}

void
ithread_create(struct intrsource *is)
{
	struct intrhand *ih;

	/* Make sure all handlers are marked as IPL_THREAD */
	for (ih = is->is_handlers; ih != NULL; ih = ih->ih_next)
		KASSERT(ih->ih_flags & IPL_THREAD);

	if (is->is_proc)
		return;

	DPRINTF(1, "ithread_create for cpu %d pin %d\n",
	    curcpu()->ci_cpuid, is->is_pin);

	kthread_create_deferred(ithread_create2, is);
}

void
ithread_create2(void *v_is)
{
	struct intrsource *is = v_is;

	DPRINTF(1, "ithread_create2 for cpu %d pin %d\n",
	    curcpu()->ci_cpuid, is->is_pin);

	if (kthread_create(ithread, is, &is->is_proc,
	    "ithread%d", is->is_idtvec))
		panic("ithread create2");
}
