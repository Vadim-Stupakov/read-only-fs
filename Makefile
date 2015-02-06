
all:
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/redirfs modules
	cp $(ROOT_PATH)/redirfs/Module.symvers $(ROOT_PATH)/avflt
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs modules

install:
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/redirfs modules_install
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs modules_install

clean:
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/avflt EXTRA_CFLAGS=-I$(ROOT_PATH)/redirfs clean
	make -C /lib/modules/`uname -r`/build M=$(ROOT_PATH)/redirfs clean
	