# Scheduling Kernel Threads


In this homework, you will trace the life cycle of kernel threads by following creation and switching. Print the time, thread numbers, and names before and after creation and switch. There are two places you need to look: kernel_thread() and schedule(). There will be many switches and try to limit the number of switches to, say 100, using a global switch counter.

1. KERNEL_SRC/kernel/fork.c: Print the time, thread numbers, and names in 'kernel_thread' function.

``` c
/*
 * Create a kernel thread.
 */
pid_t kernel_thread(int (*fn)(void *), void *arg, unsigned long flags)
{
	long nr; // ++
	struct task_struct *task;
	struct kernel_clone_args args = {
		.flags		= ((flags | CLONE_VM | CLONE_UNTRACED) & ~CSIGNAL),
		.exit_signal	= (flags & CSIGNAL),
		.stack		= (unsigned long)fn,
		.stack_size	= (unsigned long)arg,
	};
	nr = _do_fork(&args); // ++
	task = find_task_by_pid_ns(nr, &init_pid_ns); // ++
	pr_info("GIHO Lee - %s %s time: %lld pid:%ld comm:%s\n", __FILE__, __func__, ktime_get(), nr, task->comm); // ++
	return nr; // ++
//	return _do_fork(&args); // --
}
```

2. KERNEL_SRC/kernel/sched/core.c: Print the time, thread numbers, and names in 'context_switch' function.

``` c
atomic_t kerthread_switch_count = ATOMIC_INIT(0); // ++

static __always_inline struct rq *
context_switch(struct rq *rq, struct task_struct *prev,
	       struct task_struct *next, struct rq_flags *rf)
{
	...
	if (!next->mm) {                                // to kernel
		...
		if (100 > atomic_read(&kerthread_switch_count)) { // ++
			pr_info("Giho Lee - %s %s time: %lld pid: %d comm:%s\n", __FILE__, __func__, ktime_get(), next->pid, next->comm); // ++
			atomic_add(1, &kerthread_switch_count); // ++
		} // ++
	} 
	...
}

```

