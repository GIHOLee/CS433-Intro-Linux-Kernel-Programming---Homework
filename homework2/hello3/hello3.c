#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/param.h>

#define P_MODULE_LICENSE "GPL"
#define P_MODULE_AUTHOR "Giho Lee"
#define P_MODULE_DESCRIPTION "Print Some Msg V3"

#define MODULE_STR "hello3"

/*
 * __initdata will release after init function done.
 * __exitdata will release after exit function done.
 */
static int v_init __initdata = 3;
static int v_exit __exitdata = 3;

#define PARAM_LEN 64

static char name[PARAM_LEN] __initdata;
static char street[PARAM_LEN] __initdata;
static char city[PARAM_LEN] __initdata;
static char zip_code[PARAM_LEN] __initdata;

module_param_string(name, name, PARAM_LEN, 0);
module_param_string(street, street, PARAM_LEN,  0);
module_param_string(city, city, PARAM_LEN, 0);
module_param_string(zip_code, zip_code, PARAM_LEN, 0);

static int __init hello3_init(void)
{
  printk(KERN_INFO "Loading %s module - Hello World %d\n", MODULE_STR, v_init);
  printk(KERN_INFO "==================================\n");
  printk(KERN_INFO "Name : %s\n", name);
  printk(KERN_INFO "Street : %s\n", street);
  printk(KERN_INFO "City : %s\n", city);
  printk(KERN_INFO "Zip Code : %s\n", zip_code);
    
  return 0;
}

static void __exit hello3_exit(void)
{
  printk(KERN_INFO "Exiting %s module - Hello World %d\n", MODULE_STR, v_exit);
}

module_init(hello3_init);
module_exit(hello3_exit);

MODULE_LICENSE(P_MODULE_LICENSE);
MODULE_AUTHOR(P_MODULE_AUTHOR);
MODULE_DESCRIPTION(P_MODULE_DESCRIPTION);

