
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/fs.h>

#include <linux/kthread.h>
#include <linux/moduleparam.h>
#include <linux/version.h>
#include <linux/kernel.h>

#include "roflt_util.h"
#include "roflt_rfs.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vadim Stupakov");
MODULE_DESCRIPTION("Read only VFS filter for redirfs");

static char* roflt_dev_name = "roflt";

int init_module(void){ /* Constructor */
    int err = 0;

    err = roflt_init_rfs();
    if(err){
        FILTER_LOG_CRIT("Error. Error code = %d", err);
        return err;
    }

    return (0);
}

void cleanup_module(void){ /* Destructor */
    FILTER_LOG_INFO(KERN_INFO "%s: unregistered", roflt_dev_name);
    roflt_unregister();
}

