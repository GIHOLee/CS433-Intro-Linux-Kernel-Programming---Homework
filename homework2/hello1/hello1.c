#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#define P_MODULE_LICENSE "GPL"
#define P_MODULE_AUTHOR "Giho Lee"
#define P_MODULE_DESCRIPTION "Print Some Msg"

#define MODULE_STR "hello1"

static int hello1_init(void)
{
  printk(KERN_INFO "My Name: Loading %s module - Hello World 1\n", MODULE_STR);
  return 0;
}

static void hello1_exit(void)
{
  printk(KERN_INFO "My Name: Exiting %s module - Goodbye World 1\n", MODULE_STR);
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE(P_MODULE_LICENSE);
MODULE_AUTHOR(P_MODULE_AUTHOR);
MODULE_DESCRIPTION(P_MODULE_DESCRIPTION); 

