//First module creation

#include <linux/init.h>
#include <linux/module.h>

static int __init aufs_init(void){
	pr_debug("module initialised\n\n");
	return 0;
}

static void _exit aufs_exit(void){
	pr_debug("module exiting\n\n");
}

module_init(aufs_init);
module_exit(aufs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("niks");

