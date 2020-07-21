# On memory - caching: kmalloc()

Implement a kernel routine that prints kernel cache-slubs with the fields described in /proc/slabinfo. Use kmalloc_caches[] for general purpose caches such as kmalloc-96, kmalloc-192, kmalloc-8, kmalloc-16,...,
kmalloc-2048, kmalloc-4096. You may skip special purpose caches but for those of you who are determined to print all caches as shown in /proc/slabinfo, use slab_caches(/mm/slub.c) to trace special caches such
as file_cachep, signal_cachep, dentry_cache, etc.

Note: This routine needs to be inserted towards the end of kernel_init(PID 1) so that a lot of caches will have created by then.

1. KERNEL_SRC/include/linux/slab.h: add show_slabinfo function declare.

``` c
/*********************************************************************************
 * add show_slabinfo function decalre by Giho Lee
 ********************************************************************************/

void show_slabinfo(void);

/*********************************************************************************
 * end
 ********************************************************************************/
 
```

2. KERNEL_SRC/mm/slab_common.c: add show_slabinfo function and some intenal function define.

``` c
/*********************************************************************************
 * add show_slabinfo function define by Giho Lee
 ********************************************************************************/

static void my_print_slabinfo_header(void)
{
	printk("%s\n", OH_MY_NAME);
	printk(KERN_CONT "# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab>");
	printk(KERN_CONT " : tunables <limit> <batchcount> <sharedfactor>");
	printk(KERN_CONT " : slabdata <active_slabs> <num_slabs> <sharedavail>");
}

/* skip special purpose caches */
static int is_special_purpose_caches(struct kmem_cache *s)
{
	int i;
	for (i = 1; i <= KMALLOC_SHIFT_HIGH; i++) {
		if (s == kmalloc_caches[KMALLOC_NORMAL][i])
			return 1;
	}

	return 0;
}

void show_slabinfo(void)
{
	struct kmem_cache *s;
	struct slabinfo sinfo;

	my_print_slabinfo_header();

	mutex_lock(&slab_mutex);

	list_for_each_entry(s, &slab_caches, list) {
		if (!is_root_cache(s) || is_special_purpose_caches(s))
			continue;

		memset(&sinfo, 0, sizeof(sinfo));
		get_slabinfo(s, &sinfo);

		printk(KERN_CONT "%-17s %6lu %6lu %6u %4u %4d",
			cache_name(s), sinfo.active_objs, sinfo.num_objs, s->size,
			sinfo.objects_per_slab, (1 << sinfo.cache_order));

		printk(KERN_CONT " : tunables %4u %4u %4u",
			sinfo.limit, sinfo.batchcount, sinfo.shared);
		printk(KERN_CONT " : slabdata %6lu %6lu %6lu",
			sinfo.active_slabs, sinfo.num_slabs, sinfo.shared_avail);
		printk(KERN_CONT "\n");
	}

	mutex_unlock(&slab_mutex);
}

/*********************************************************************************
 * end
 ********************************************************************************/

```

3. KERNEL_SRC/init/main.c: call show_slabinfo function.

``` c
static int __ref kernel_init(void *unused)
{
	int ret;

	kernel_init_freeable();
	/* need to finish all async __init code before freeing the memory */
	async_synchronize_full();
	ftrace_free_init_mem();
	free_initmem();
	mark_readonly();

	/*
	 * Kernel mappings are now finalized - update the userspace page-table
	 * to finalize PTI.
	 */
	pti_finalize();

	system_state = SYSTEM_RUNNING;
	numa_default_policy();
	/*********************************************************************************
	 * add call show_slabinfo function by Giho Lee
	 ********************************************************************************/
	show_slabinfo();
	/*********************************************************************************
	 * end
	 ********************************************************************************/
	rcu_end_inkernel_boot();
	...
}
	
```

