#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3d45854, "module_layout" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x9588e3b5, "cdev_del" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xc29f23e0, "cdev_init" },
	{ 0x32ed180f, "cdev_add" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x30a80826, "__kfifo_from_user" },
	{ 0xc959d152, "__stack_chk_fail" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x4578f528, "__kfifo_to_user" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2321FB32875D97F4D52E7DD");
