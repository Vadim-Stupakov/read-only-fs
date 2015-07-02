
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
MODULE_DESCRIPTION("Character device for research");

#define BUF_LEN 255

int roflt_init_char_dev(const char* roflt_file_name, const char* device_name);
void roflt_clean_char_dev(void);
int roflt_open(struct inode *i, struct file *f);
int roflt_close(struct inode *i, struct file *f);
ssize_t roflt_read(struct file *f, char __user *buf, size_t len, loff_t *off);

//redirfs_filter roflt_flt;
static struct cdev char_dev;
static dev_t first = 0;
static struct class* cl = NULL;
static atomic_t device_open = ATOMIC_INIT(0);
//static char kernel_buf[BUF_LEN];
//static int kernel_buf_size = 0;
static const char* roflt_dev_name = "roflt_dev";
static const char* roflt_file_name = "roflt_file";

static struct file_operations fops =
{
    .owner    = THIS_MODULE,
    .open     = roflt_open,
    .release  = roflt_close,
    .read     = roflt_read
};

int roflt_init_char_dev(const char* file_name, const char* device_name){
    long retval = 0;
    retval = alloc_chrdev_region(&first, 0, 1, file_name);
    if ( retval < 0){
        FILTER_LOG_CRIT("alloc_chrdev_region() error! Return value = %ld", retval);
        return (-1);
    }

    if ((cl = class_create(THIS_MODULE, device_name)) == NULL ){
        unregister_chrdev_region(first, 1);
        FILTER_LOG_CRIT("%s", "class_create() error!");
        return (-1);
    }

    if (!PTR_ERR(device_create(cl, NULL, first, NULL, file_name)) ){
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        FILTER_LOG_CRIT("%s", "device_create() error!");
        return (-1);
    }

    cdev_init(&char_dev, &fops);

    if (cdev_add(&char_dev, first, 1) == -1){
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        FILTER_LOG_CRIT("%s", "cdev_add() Return value = -1");
        return (-1);
    }

    return (0);
}

void roflt_clean_char_dev(void){
    cdev_del(&char_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
}

int roflt_open(struct inode *i, struct file *f){
    if (atomic_add_return(1, &device_open) > 2) {
        atomic_dec(&device_open);
        printk("device busy\n");
        return -EBUSY;
    }

    printk("device is opened\n");
    try_module_get(THIS_MODULE );
    return (0);
}

int roflt_close(struct inode *i, struct file *f){
    printk("device is closed\n");
    atomic_dec(&device_open);
    module_put(THIS_MODULE );
    return (0);
}

ssize_t roflt_read(struct file *f, char __user *buf, size_t len, loff_t *off){
    printk("Read\n");
    return (1);
}

int init_module(void){ /* Constructor */

    int err = 0;

    err = roflt_init_rfs();
    if(err){
        FILTER_LOG_CRIT("Error. Error code = %d", err);
        return err;
    }
//    if(!roflt_init_char_dev(roflt_file_name, roflt_dev_name)){
//        FILTER_LOG_INFO(KERN_INFO "%s: registered", roflt_dev_name);
//    }
//    else{
//        FILTER_LOG_INFO(KERN_INFO "%s: not registered", roflt_dev_name);
//    }
    return (0);
}

void cleanup_module(void){ /* Destructor */
//    redirfs_delete_filter(roflt_flt);
    FILTER_LOG_INFO(KERN_INFO "%s: unregistered", roflt_dev_name);
    roflt_unregister();
//    roflt_clean_char_dev();
}

