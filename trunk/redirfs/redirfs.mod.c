#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb89a34a1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x964b601a, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xd5d786e, __VMLINUX_SYMBOL_STR(kset_create_and_add) },
	{ 0x123467c8, __VMLINUX_SYMBOL_STR(d_path) },
	{ 0xdff77dda, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x16e17547, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xda3e43d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0xcd2ce252, __VMLINUX_SYMBOL_STR(__mark_inode_dirty) },
	{ 0x10078068, __VMLINUX_SYMBOL_STR(mntget) },
	{ 0x754d539c, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x7ce330eb, __VMLINUX_SYMBOL_STR(dget_parent) },
	{ 0xb0758883, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x52cbb014, __VMLINUX_SYMBOL_STR(lockref_get) },
	{ 0xf1ab8913, __VMLINUX_SYMBOL_STR(dput) },
	{ 0xf84f8e94, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x703dfdb2, __VMLINUX_SYMBOL_STR(kobject_del) },
	{ 0xb29c0a66, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x64aa2bb6, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x9868dd1, __VMLINUX_SYMBOL_STR(kern_path) },
	{ 0xad1540f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x9166fada, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x5562fca3, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0xcc759d9e, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xfe36e18c, __VMLINUX_SYMBOL_STR(setattr_copy) },
	{ 0x95eb8512, __VMLINUX_SYMBOL_STR(kobject_add) },
	{ 0x36df0732, __VMLINUX_SYMBOL_STR(mntput) },
	{ 0x1aa0bab6, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xe3164779, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x433a8ace, __VMLINUX_SYMBOL_STR(fs_kobj) },
	{ 0x555fabf4, __VMLINUX_SYMBOL_STR(sysfs_remove_file_ns) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xbac21420, __VMLINUX_SYMBOL_STR(inode_change_ok) },
	{ 0x9483706f, __VMLINUX_SYMBOL_STR(path_put) },
	{ 0x3b88f3a0, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd52bf1ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x87550437, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x2897571f, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb4fed763, __VMLINUX_SYMBOL_STR(generic_permission) },
	{ 0x56777a, __VMLINUX_SYMBOL_STR(kobject_init) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xb0e602eb, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xd2f0ff32, __VMLINUX_SYMBOL_STR(sysfs_create_file_ns) },
	{ 0x5c39a5c4, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "684E8D500B022B049E7898F");
