
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#define P_MODULE_LICENSE "GPL"
#define P_MODULE_AUTHOR "Giho Lee"
#define P_MODULE_DESCRIPTION "Print Some Msg V2"

#define MODULE_STR "hello2"

static int v_init __initdata = 2;
static int v_exit __exitdata = 2;

static int __init hello2_init(void)
{
  printk(KERN_INFO "My Name: Loading %s module - Hello World %d\n", MODULE_STR, v_init);

  return 0;
}

static void __exit hello2_exit(void)
{
  printk(KERN_INFO "My Name: Exiting %s module - Hello World %d\n", MODULE_STR, v_exit);
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_LICENSE(P_MODULE_LICENSE);
MODULE_AUTHOR(P_MODULE_AUTHOR);
MODULE_DESCRIPTION(P_MODULE_DESCRIPTION);
