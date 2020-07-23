1. KERNEL_SRC/include/linux/vmstat.h: add buddy_info_show function declare

``` c
/*********************************************************************************
* add function declare by Giho Lee
*********************************************************************************/

extern void buddy_info_show(void);

/*********************************************************************************
* end
*********************************************************************************/
```

2. KERNEL_SRC/mm/vmstat.c: add buddy_info_show function define

``` c
/*********************************************************************************
 * add buddy info show function by Giho Lee
 *********************************************************************************/

void buddy_info_show(void)
{
	unsigned int order;
	struct zone *zone;

	for_each_zone(zone) {
		printk(KERN_CONT "%s - Node %d, zone %8s ", OH_MY_NAME, zone->zone_pgdat->node_id, zone->name);
		for (order = 0; order < MAX_ORDER; ++order)
			printk(KERN_CONT "%6lu ", zone->free_area[order].nr_free);
		printk(KERN_CONT "\n");
	}
}

/*********************************************************************************
 * end
 *********************************************************************************/

```

3. KERNEL_SRC/kernel/smpboot.c: call buddy_info show function

``` c
/**
 * idle_threads_init - Initialize idle threads for all cpus
 */
void __init idle_threads_init(void)
{
	unsigned int cpu, boot_cpu;

	/*********************************************************************************
	 * add call buddy_info_show function by Giho Lee
	 *********************************************************************************/

	buddy_info_show();
	
	/*********************************************************************************
	 * end
	 *********************************************************************************/

	boot_cpu = smp_processor_id();

	for_each_possible_cpu(cpu) {
		if (cpu != boot_cpu)
			idle_init(cpu);
	}
}

```

