# Compiling the kernel and printing messages and Implementing system calls

1. Compiling the kernel and printing messages
   Inside start_kernel(), go to the first level of at least five functions of your choosing and print their names along with the contents of the parameters that are passed if any.
   Start with setup_arch(). For example, for "setup_arch(&command_line);" in start_kernel(), you would insert the following line in source/arch/x86/kernel/setup.c:
   

		printk(KERN_INFO "my_name (put your name here): setup_arch(): command_line=%s\n",*command_line);
		
   which would print
   	 my real name: setup_arch(): first_value_of_command_line
   in /var/log/messages. setup_arch() already has the following line but you may still modify it:
   0691         printk(KERN_INFO "Command line: %s\n", boot_command_line);
   
   You may encounter kernel panic.

2. Implementing system calls
	Add the following line at the end of common system calls in arch/x86/entry/syscalls/syscall_64.tbl
	333     common  my_name_call                   sys_my_name_call
	Write the function

		SYSCALL_DEFINE1(my_name_call, char *, message)	{
		/* Print your name here, 
		indicating that your syscall is indeed called
		You may also print the message you supply as a parameter
		This type of macros are used to implement system calls with
        varying number of parameters.
		*/
		return 0;
		}
		
3. Compile the kernel and boot
