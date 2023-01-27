#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

dev_t devno;
int major = 255;
const char DEVNAME[] = "hello_device";
char data[64]  = "";
char data2[64] = "";

int hello_open(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 一般用来做初始化设备的操作 */
    return 0;
}

int hello_close(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 一般用来做和open相反的操作，open申请资源，close释放资源 */
    return 0;
}

ssize_t hello_read(struct file * fp, char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    
    int *datan = (int*)data;
    int *data2n = (int*)data2;
    data2n[0] = datan[0]+datan[1];
    /* 将用户需要的数据从内核空间copy到用户空间(buf) */
    printk("%s : %d\n", __func__, __LINE__);
    if ((ret = copy_to_user(buf, data2, count)))
    {
        printk("copy_to_user err\n");
        return -1;
    }
    return count;
}

ssize_t hello_write(struct file * fp, const char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    /* 将用户需要的数据从内核空间copy到用户空间(buf) */
    printk("%s : %d\n", __func__, __LINE__);
    if ((ret = copy_from_user(data, buf, count)))
    {
        printk("copy_from_user err\n");
        return -1;
    }
    return count;
}

/* 2. 分配file_operations结构体 */
struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open  = hello_open,
    .release = hello_close,
    .read = hello_read,
    .write = hello_write
};
struct cdev cdev;

static int hello_init(void)
{
    int ret;
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 1. 生成并注册设备号 */
    devno = MKDEV(major, 0);
    ret  = register_chrdev_region(devno, 1, DEVNAME);
    if (ret != 0)
    {
        printk("%s : %d fail to register_chrdev_region\n", __func__, __LINE__);
        return -1;
    }
    
    /* 3. 分配、设置、注册cdev结构体 */
    cdev.owner = THIS_MODULE;
    ret = cdev_add(&cdev, devno, 1);
    cdev_init(&cdev, &hello_fops);
    if (ret < 0)
    {
        printk("%s : %d fail to cdev_add\n", __func__, __LINE__);
        return -1;
    }
    printk("success!\n");
    return 0;
}

static void hello_exit(void)
{
    printk("%s : %d\n", __func__, __LINE__);
      
    /* 释放资源 */
    cdev_del(&cdev);
    unregister_chrdev_region(devno, 1);
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
