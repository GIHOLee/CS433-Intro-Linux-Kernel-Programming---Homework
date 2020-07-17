// SPDX-License-Identifier: GPL-2.0-only
/*
 * Generic show_mem() implementation
 *
 * Copyright (C) 2008 Johannes Weiner <hannes@saeurebad.de>
 */

#include <linux/mm.h>
#include <linux/cma.h>

void show_mem(unsigned int filter, nodemask_t *nodemask)
{
	pg_data_t *pgdat;
	unsigned long total = 0, reserved = 0, highmem = 0;

	/*********************************************************************************
	 * add some params of printk function by Giho Lee
	 *********************************************************************************/
	printk("%s - Mem-Info:\n", OH_MY_NAME);
	//printk("Mem-Info:\n");
	show_free_areas(filter, nodemask);

	for_each_online_pgdat(pgdat) {
		int zoneid;

		for (zoneid = 0; zoneid < MAX_NR_ZONES; zoneid++) {
			struct zone *zone = &pgdat->node_zones[zoneid];
			if (!populated_zone(zone))
				continue;

			total += zone->present_pages;
			reserved += zone->present_pages - zone_managed_pages(zone);

			if (is_highmem_idx(zoneid))
				highmem += zone->present_pages;
		}
	}

	printk("%s - %lu pages RAM\n", OH_MY_NAME, total);
	//printk("%lu pages RAM\n", total);
	printk("%s - %lu pages HighMem/MovableOnly\n", OH_MY_NAME, highmem);
	//printk("%lu pages HighMem/MovableOnly\n", highmem);
	printk("%s %lu pages reserved\n", OH_MY_NAME, reserved);
	//printk("%lu pages reserved\n", reserved);
#ifdef CONFIG_CMA
	printk("%s %lu pages cma reserved\n", OH_MY_NAME, totalcma_pages);
	//printk("%lu pages cma reserved\n", totalcma_pages);
#endif
#ifdef CONFIG_MEMORY_FAILURE
	printk("%s %lu pages hwpoisoned\n", OH_MY_NAME, atomic_long_read(&num_poisoned_pages));
	//printk("%lu pages hwpoisoned\n", atomic_long_read(&num_poisoned_pages));
#endif
}
