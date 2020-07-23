# Creating and Destroying Kernel Threads

* Print some information of all the processes pointed by init_task, something similiar to "ps -ef", including UID, PID, PPID, thread name, etc.
* Create five kernel threads using the following methods:
	a) Create 2 threads using kernel_thread()
	b) Create 2 threads on a dual-core machine (4 on a quad-core machine) using smpboot_register_percpu_thread() which creates kthread place holder through kthread_creat_list which kthreadd periodically checks
  to create a kernel thread eventually using kernel_thread().
* Print some information of all the processes including the five threads. The output will be part of dmesg or messages. Again, try to follow the "ps -ef" format when printing all the processes including your
  own threads.

1. KERNEL_SRC/init/main.c: declare and define the function that will create threads and those threads that will actually do something.

``` c
/*********************************************************************************
 * declare the funtions that will create threads and those threads that will
 * actually do something by Giho Lee
 ********************************************************************************/

static void my_kernel_thread_create_1(void);
static void my_kernel_thread_create_2(void);

static int m_k_t_do_something_1(void *);
static int m_k_t_do_something_2(void *);

static void print_info_of_all_task(void);

/*********************************************************************************
 * end
 ********************************************************************************/

```

``` c
/*********************************************************************************
 * define the funtions that will create threads and those threads that will
 * actually do something by Giho Lee
 ********************************************************************************/

static void my_kernel_thread_create_1(void)
{
	int mypid;
	struct task_struct *task;

	printk(KERN_NOTICE "%s: Calling kernel_thread(my_ker_thd_1)\n", OH_MY_NAME);
	mypid = kernel_thread(m_k_t_do_something_1, NULL, (CLONE_FS | CLONE_FILES | CLONE_SIGHAND));
	task = find_task_by_vpid(mypid);
	set_task_comm(task, "my_ker_thd_1");
	printk(KERN_NOTICE "%s: my_ker_thd_1 = %d\n", OH_MY_NAME, mypid);
}

static void my_kernel_thread_create_2(void)
{
	int mypid;
	struct task_struct *task;

	printk(KERN_NOTICE "%s: Calling kernel_thread(my_ker_thd_2)\n", OH_MY_NAME);
	mypid = kernel_thread(m_k_t_do_something_2, NULL, (CLONE_FS | CLONE_FILES | CLONE_SIGHAND));
	task = find_task_by_vpid(mypid);
	set_task_comm(task, "my_ker_thd_2");
	printk(KERN_NOTICE "%s: my_ker_thd_2 = %d\n", OH_MY_NAME, mypid);
}

static int m_k_t_do_something_1(void *data)
{
	struct task_struct *curtask = current;
	(void)data;

	curtask->state = TASK_RUNNING;
	printk(KERN_NOTICE "%s: m_k_t_do_something_1 is about to be scheduled.\n", OH_MY_NAME);
	schedule();
	printk(KERN_NOTICE "%s: m_k_t_do_something_1 is now scheduled.\n", OH_MY_NAME);

	return 0;
}

static int m_k_t_do_something_2(void *data)
{
	struct task_struct *curtask = current;
	(void)data;

	curtask->state = TASK_RUNNING;
	printk(KERN_NOTICE "%s: m_k_t_do_something_2 is about to be scheduled.\n", OH_MY_NAME);
	schedule();
	printk(KERN_NOTICE "%s: m_k_t_do_something_2 is now scheduled.\n", OH_MY_NAME);

	return 0;
}

static void print_info_of_all_task(void)
{
	struct task_struct *task;

	printk(KERN_NOTICE "PID  PPID  STIME          TIME CMD\n");
	for_each_process(task) {
		printk(KERN_NOTICE "%d  %d  %llu          %llu %s\n",
			task->pid, task->real_parent->pid, task->start_boottime, (task->utime + task->stime) / HZ, task->comm);
	}
}

/*********************************************************************************
 * end
 ********************************************************************************/

```

2. KERNEL_SRC/kernel/softirq.c: declare and define *struct smp_hotplug_thread my_hotplug_threads* and callback functions.

``` c
/*********************************************************************************
 * Declare and define  smp_hotplug_thread my_hotplug_threads
 ********************************************************************************/

DEFINE_PER_CPU(struct task_struct *, my_hotplugd);
static DEFINE_PER_CPU(int, should_run);

static void my_hotplugd_setup(unsigned int cpu)
{
	__this_cpu_write(should_run, 1);
}

static void run_my_hotplugd(unsigned int cpu)
{
	printk(KERN_NOTICE "[my_hotplugd/%u] is up and runing\n", cpu);
	__this_cpu_write(should_run, 0);
}

static int my_hotplugd_should_run(unsigned int cpu)
{
	return __this_cpu_read(should_run);
}

static struct smp_hotplug_thread my_hotplug_threads = {
	.store                  = &my_hotplugd,
	.setup                  = my_hotplugd_setup,
	.thread_should_run      = my_hotplugd_should_run,
	.thread_fn              = run_my_hotplugd,
	.thread_comm            = "my_hotplugd/%u",
};

static __init int spawn_my_hotplugd(void)
{
	BUG_ON(smpboot_register_percpu_thread(&my_hotplug_threads));

	return 0;
}
early_initcall(spawn_my_hotplugd);

/*********************************************************************************
 * end
 ********************************************************************************/

```

