KERNEL_VERS = `uname -r`
KERNEL_BUILDDIR = /lib/modules/$(KERNEL_VERS)/build
ROOT_PATH=`pwd`
FILTER_DIR="roflt"
REDIRFS_DIR="redirfs"

all:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) modules
	cp $(ROOT_PATH)/$(REDIRFS_DIR)/Module.symvers $(ROOT_PATH)/$(FILTER_DIR)
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) modules

install:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) modules_install
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) modules_install

clean:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) clean
	 make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) clean
	rm -rf ./*/Module*.symvers ./*/Module*.symvers rm -rf ./*/*.mod.c ./*/*.mod.c
	