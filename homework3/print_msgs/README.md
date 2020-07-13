# Compiling the kernel and printing messages

1. modify KERNEL_SRC/arch/x86/kernel/setup.c:

``` c

void __init setup_arch(char **cmdline_p)
{
	...

	strlcpy(command_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = command_line;
	
	/*********************************************************************************
	 * debug by Giho Lee
	 *********************************************************************************/
	
	printk (KERN_INFO "I'm %s: setup_arch(): command_line=%s\n", "Giho Lee", command_line);
	
	/*********************************************************************************
	 * debug end
	 *********************************************************************************/
	 
	...
}
```

2. Compile the kernel and boot

3. shell exec cmd and verify:
   
		$sudo dmesg | grep command_line
