# Implementing system calls

1. modify KERNEL_SRC/arch/x86/entry/syscalls/syscall_64.tbl, append content:

``` c
...

#################################################################################
# Add custom systemcalls by Giho Lee
#################################################1
################################

548	common	my_name_call	__x64_sys_my_name_call

#################################################################################
# end
#################################################################################

```

2. modify KERNEL_SRC/include/linux/syscalls.h, **add content before the last "#endif"**:

``` c
...

/*********************************************************************************
* add custom syscall function declare
*********************************************************************************/

asmlinkage long sys_my_name_call (const char __user *name);

/*********************************************************************************
* end
*********************************************************************************/

```

3. modify KERNEL_SRC/kernel/sys.c, **add content before the last "#endif"**:

``` c
...

/*********************************************************************************
 * add custom syscall function define by Giho Lee
 *********************************************************************************/

SYSCALL_DEFINE1(my_name_call, const char __user *, name)
{
  long nb_symbols;
  char *name_internal;
  long i;

  /*
   * Estimate the buffer length sufficient to accommodate the string
   */
  for (i = 1; ;i++) {
    nb_symbols = strnlen_user(name, i);
    if (nb_symbols <= 0)
      return -EFAULT;

    /* with enough length */
    if (nb_symbols < i)
      break;
  }

  /* Allocate the storage */
  name_internal = kmalloc(nb_symbols + 1, GFP_KERNEL);
  if (NULL == name_internal)
    return -ENOMEM;

  /* long strncpy (char *dst, const char __user *src, long count) 
   * Copies a NUL-terminated string from userspace to kernel space.
   * On success, returns the length of the string (not including the trailing NUL).
   */  
  if (strncpy_from_user(name_internal, name, nb_symbols) != nb_symbols - 1) {
    kfree(name_internal);
    return -EFAULT;
  }

  printk(KERN_INFO "Your 'name' is '%s'\n", name_internal);
  
  kfree(name_internal);

  return 0;
}

/*********************************************************************************
 * end
 *********************************************************************************/

```

4. Compile the kernel and boot

5. userspace code call **"my_name_call"** system call.

``` c

#include <stdio.h>

#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>

#define __NR_MY_NAME_CALL 548
#define MY_NAME "Giho Lee"

static long my_name_call(char *name)
{
  return syscall(__NR_MY_NAME_CALL, name);
}

int main(int argc, char **argv)
{
  long ret = my_name_call(MY_NAME);
  printf ("System call returned %ld\n", ret);
  
  return 0;
}
```

