# On Memory: Paging 

1. Paging - show_mem: To help you understand the buddy system, you will do two small experiments with the kernel source code. First, insert show_mem()</br> 
somewhere in your kernel so that you will get all the info show_mem() provides. Remember to put your name before each printk. Note that show_mem</br> 
calls show_free_areas which will in turn call show_node. You will have to go down a few levels to insert your name before each printk.
2. Paging - /proc/buddyinfo: Second, implement your own kernel function that prints /proc/buddyinfo.

	Recompile the kernel and load the latest version. The new kernel version will print the information in dmesg (/var/log/messages)</br> 
along with other standard messages.
