KERNEL_VERS = `uname -r`
KERNEL_BUILDDIR = /lib/modules/$(KERNEL_VERS)/build
ROOT_PATH=`pwd`
FILTER_DIR="$(ROOT_PATH)/roflt"
REDIRFS_DIR="$(ROOT_PATH)/redirfs"

ifndef EXCHANGE
	EXTRA_CFLAGS=-DRFS_EXCHANGE_D_CHILD=0
else
	EXTRA_CFLAGS=-DRFS_EXCHANGE_D_CHILD=1
endif

all:
	make -C $(KERNEL_BUILDDIR) M=$(REDIRFS_DIR) EXTRA_CFLAGS=$(EXTRA_CFLAGS) modules
	cp $(REDIRFS_DIR)/Module.symvers $(FILTER_DIR)
	make -C $(KERNEL_BUILDDIR) M=$(FILTER_DIR) EXTRA_CFLAGS=-I$(REDIRFS_DIR) modules

install:
	make -C $(KERNEL_BUILDDIR) M=$(REDIRFS_DIR) modules_install
	make -C $(KERNEL_BUILDDIR) M=$(FILTER_DIR) EXTRA_CFLAGS=-I$(REDIRFS_DIR) modules_install

clean:
	make -C $(KERNEL_BUILDDIR) M=$(FILTER_DIR) EXTRA_CFLAGS=-I$(REDIRFS_DIR) clean
	make -C $(KERNEL_BUILDDIR) M=$(REDIRFS_DIR) clean
	# remove all exept *.c and
	find $(FILTER_DIR)/ $(REDIRFS_DIR)/ -mindepth 1 ! -name "*.c" ! -name "*.h" ! -name "Makefile" ! -name "README" | \
    xargs -I {} -t rm -rf {}
