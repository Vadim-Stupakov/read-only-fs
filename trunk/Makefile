KERNEL_VERS = `uname -r`
KERNEL_BUILDDIR = /lib/modules/$(KERNEL_VERS)/build
ROOT_PATH=`pwd`

all:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/redirfs modules
	cp $(ROOT_PATH)/redirfs/Module.symvers $(ROOT_PATH)/avflt
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs modules

install:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/redirfs modules_install
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs modules_install

clean:
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs clean
	make -C $(KERNEL_BUILDDIR) M=$(ROOT_PATH)/redirfs clean
	rm -rf ./*/Module*.symvers ./*/Module*.symvers rm -rf ./*/*.mod.c ./*/*.mod.c
	
