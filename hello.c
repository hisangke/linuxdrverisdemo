#include<linux/init.h>
#include<linux/module.h>

#include<linux/miscdevice.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
static char buffer[256]={0x00};
// int (*open) (struct inode *, struct file *);
int misc_open(struct inode * pInode, struct file * pFile)
{
    printk("int misc_open(struct inode * pInode, struct file * pFile\n)");
    memcpy(buffer,"init buffer",sizeof("init buffer"));
    printk("buffer = %s\n",buffer);
    return 0;
}

// int (*release) (struct inode *, struct file *);
int misc_release(struct inode * pInde, struct file * pFile)
{
    printk("int misc_release(struct inode * pInde, struct file * pFile)");

    return 0;
}

// ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
ssize_t misc_read(struct file * pFile, char __user * pUser, size_t size, loff_t *pLofft)
{
    printk("ssize_t misc_read(struct file * pFile, char __user * pUser, size_t size, loff_t *pLofft)\n");
        if (copy_to_user(pUser,buffer,strlen(buffer))!=0)
    {
        printk("copy_to_user Failed");
        return -1;
    }
    printk("copy_to_user success");
    return 0;
}

// ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
ssize_t misc_write(struct file * pFile, const char __user * pUser, size_t size, loff_t *pLofft)
{
    printk("ssize_t misc_write(struct file * pFile, const char __user * pUser, size_t size, loff_t *pLofft)\n");
    if (copy_from_user(buffer,pUser,size)!=0)
    {
        printk("copy_from_user failed");
        return -1;
    }
    
    printk("copy_from_user success");
    return 0;
}

struct file_operations misc_fops = {
  .owner = THIS_MODULE,
  .open = misc_open,
  .release = misc_release,
  .read = misc_read,
  .write = misc_write,
};


struct miscdevice misc_dev={
    .minor=MISC_DYNAMIC_MINOR,
    .name="register_hisangke_misc",
    .fops=&misc_fops,
};


static int hello_init(void)
{
    int ret=0;
    // 在内核里面无法使用基础c库printf，需要使用内核库printk
    printk("Hello, I’m hisangke misc\n");
    ret=misc_register(&misc_dev);
    if (ret<0)
    {
       printk("failed to misc_register(misc_dev)n");
       return -1;
    }
    
    return 0;
}

static void hello_exit(void)
{
    printk("bye-bye!!!\n");
    misc_deregister(&misc_dev);
}




MODULE_LICENSE("GPL");

module_init(hello_init);
module_exit(hello_exit);

