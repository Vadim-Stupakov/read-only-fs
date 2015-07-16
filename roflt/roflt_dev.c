#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "roflt_util.h"
#include "roflt_rfs.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vadim Stupakov");
MODULE_DESCRIPTION("Read only VFS filter for redirfs");

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
    FILTER_LOG_INFO(KERN_INFO "%s: unregistered", MODULE_NAME);
    roflt_unregister();
}

