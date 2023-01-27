/* 源代码文件名为：firstmod.c */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
 
static int __init firstmod_init(void)    //驱动入口函数
{
    printk(KERN_EMERG "firstmod_init\r\n");
    return ;
}

static void firstmod_write()
{

}

static void __exit firstmod_exit(void)    //驱动出口函数
{
    printk(KERN_EMERG "firstmod_exit\r\n");
}
 
module_init(firstmod_init);    //注册入口函数
module_exit(firstmod_exit);    //注册出口函数
