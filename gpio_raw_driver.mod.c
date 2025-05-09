#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xefd817eb, "__platform_driver_register" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xe26aae7b, "_dev_info" },
	{ 0x4fb5886b, "devm_kmalloc" },
	{ 0xcb5a3e32, "platform_get_resource" },
	{ 0x4b3a9263, "devm_ioremap_resource" },
	{ 0x9053e613, "of_property_read_variable_u32_array" },
	{ 0x730f5d6e, "_dev_err" },
	{ 0xc02e8507, "platform_driver_unregister" },
	{ 0x4048dc1b, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cmy,gpio-raw");
MODULE_ALIAS("of:N*T*Cmy,gpio-rawC*");

MODULE_INFO(srcversion, "E6B7FE4763EF9ACBB006809");
