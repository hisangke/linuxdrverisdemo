#include<linux/init.h>
#include<linux/module.h>
static int hello_init(void)
{
    // 在内核里面无法使用基础c库printf，需要使用内核库printk
    printk("Hello, I’m hisangke\n");
    return 0;
}

static void hello_exit(void)
{
    printk("bye-bye!!!\n");
}

MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);

