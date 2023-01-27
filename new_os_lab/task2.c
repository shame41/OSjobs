#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include<stddef.h>
#include<linux/kfifo.h>

dev_t devno;
int ma = 255;
const char DEVNAME[] = "task2_device";

DEFINE_KFIFO(BUFFER_NAME,char,64);

wait_queue_head_t read_queue;
wait_queue_head_t write_queue;



char data[64]  = "Hello world!";


int hello_open(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    return 0;
}

int hello_close(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    return 0;
}

ssize_t hello_read(struct file * file, char __user * buf, size_t count, loff_t * loff)
{
       unsigned r=0;
	unsigned ro=0;
	if(kfifo_is_empty(&BUFFER_NAME))
	{
		if(file->f_flags & O_NONBLOCK)
		{
		printk(KERN_EMERG "EAGAIN IS %d.\n",EAGAIN);
		return -EAGAIN;
		}
		
		wait_event_interruptible(read_queue,!kfifo_is_empty(&BUFFER_NAME));
	}
	r=kfifo_to_user(&BUFFER_NAME,buf,count,&ro);
	if(r)
	{
	 	printk(KERN_EMERG "failed to kfifo_to_user.\n");
	 	return r;
	}
	
	if(!kfifo_is_full(&BUFFER_NAME))
		wake_up_interruptible(&write_queue);
		return ro;
}

ssize_t hello_write(struct file * file, const char __user * buf, size_t count, loff_t * loff)
{
        unsigned r=0;
	unsigned wi=0;
	if(kfifo_is_full(&BUFFER_NAME))
	{
		if(file->f_flags & O_NONBLOCK)
		return -EAGAIN;
		
		
		wait_event_interruptible(write_queue,!kfifo_is_full(&BUFFER_NAME));
	}
	r=kfifo_from_user(&BUFFER_NAME,buf,count,&wi);
	if(r)
	{
	 	printk(KERN_EMERG "failed to kfifo_from_user.\n");
	 	return r;
	}
	
	if(!kfifo_is_empty(&BUFFER_NAME))
		wake_up_interruptible(&read_queue);
		return wi;
}


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
    int r;
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 1. 生成并注册设备号 */
    devno = MKDEV(ma, 0);
    r  = register_chrdev_region(devno, 1, DEVNAME);
    if (r != 0)
    {
        printk("%s : %d fail to register_chrdev_region\n", __func__, __LINE__);
        return -1;
    }
    

    cdev.owner = THIS_MODULE;
    r = cdev_add(&cdev, devno, 1);
    cdev_init(&cdev, &hello_fops);
    if (r < 0)
    {
        printk("%s : %d fail to cdev_add\n", __func__, __LINE__);
        return -1;
    }
    printk("success!\n");
    init_waitqueue_head(&read_queue);
    init_waitqueue_head(&write_queue);
    
    return 0;
}

static void hello_exit(void)
{
    printk("%s : %d\n", __func__, __LINE__);
      

    cdev_del(&cdev);
    unregister_chrdev_region(devno, 1);
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

