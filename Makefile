KERNEL_VERS = `uname -r`
#KERNEL_VERS = 3.13.0-24-generic
KERNEL_BUILDDIR = /lib/modules/$(KERNEL_VERS)/build
ROOT_PATH=`pwd`
FILTER_DIR="roflt"
REDIRFS_DIR="redirfs"

ifndef EXCHANGE
	EXTRA_CFLAGS=-DRFS_EXCHANGE_D_CHILD=0
else
	EXTRA_CFLAGS=-DRFS_EXCHANGE_D_CHILD=1
endif

all:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) EXTRA_CFLAGS=$(EXTRA_CFLAGS) modules
	cp $(ROOT_PATH)/$(REDIRFS_DIR)/Module.symvers $(ROOT_PATH)/$(FILTER_DIR)
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) modules

install:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) modules_install
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) modules_install

clean:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(FILTER_DIR) EXTRA_CFLAGS=-I$(ROOT_PATH)/$(REDIRFS_DIR) clean
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/$(REDIRFS_DIR) clean
	rm -rf ./*/Module*.symvers ./*/Module*.symvers rm -rf ./*/*.mod.c ./*/*.mod.c ./*/*.o ./*/*.cmd
