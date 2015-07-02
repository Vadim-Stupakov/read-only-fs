#include "roflt_rfs.h"

redirfs_filter roflt_flt;

#define MODULE_NAME     "roflt"
#define MODULE_PRIORITY 60321
#define MODULE_STATUS   1

ssize_t roflt_write(struct file* file, const char __user * buf, size_t size, loff_t * offset){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static struct file_operations roflt_fops;

enum redirfs_rv roflt_post_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");
    if(rargs->args.f_open.file->f_op->write != roflt_write){


        printk("Before\n");
        printk("\trargs->args.f_open.file = %p\n", rargs->args.f_open.file);
        if(rargs->args.f_open.file)
        {
            printk("\trargs->args.f_open.file->f_op = %p\n", rargs->args.f_open.file->f_op);
            if(rargs->args.f_open.file->f_op)
            {
                printk("\trargs->args.f_open.file->f_op->write = %p\n", rargs->args.f_open.file->f_op->write);
                printk("\trargs->args.f_open.file->f_op->open = %p\n", rargs->args.f_open.file->f_op->open);
            }
        }

//        memcpy(&roflt_fops, rargs->args.f_open.file->f_op, sizeof(roflt_fops));
//        roflt_fops.owner = THIS_MODULE;
//        roflt_fops.write = roflt_write;

//        rargs->args.f_open.file->f_op = &roflt_fops;

        struct file_operations* fop = (struct file_operations*)(rargs->args.f_open.file->f_op);
        fop->write = roflt_write;


        printk("After\n");
        printk("\trargs->args.f_open.file = %p\n", rargs->args.f_open.file);
        if(rargs->args.f_open.file)
        {
            printk("\trargs->args.f_open.file->f_op = %p\n", rargs->args.f_open.file->f_op);
            if(rargs->args.f_open.file->f_op)
            {
                printk("\trargs->args.f_open.file->f_op->write = %p\n", rargs->args.f_open.file->f_op->write);
                printk("\trargs->args.f_open.file->f_op->open = %p\n", rargs->args.f_open.file->f_op->open);
            }
        }

        return REDIRFS_CONTINUE;
    }
    return REDIRFS_CONTINUE;
}

enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");
    return REDIRFS_CONTINUE;
}

static struct redirfs_op_info roflt_op_info[] =
{
    {REDIRFS_REG_FOP_OPEN,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_FOP_OPEN,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_LNK_FOP_OPEN,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_CHR_FOP_OPEN,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_BLK_FOP_OPEN,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_FIFO_FOP_OPEN,     roflt_pre_callback, roflt_post_callback},
    {REDIRFS_OP_END,            NULL,               NULL}
};

static struct redirfs_filter_operations roflt_ops =
{
//    .activate   = roflt_activate,
//    .add_path   = roflt_add_path,
//    .unregister = roflt_unregister,
    .pre_rename = roflt_pre_callback,
    .post_rename = roflt_post_callback
};

static struct redirfs_filter_info roflt_info =
{
    .owner    = THIS_MODULE,
    .name     = MODULE_NAME,
    .priority = MODULE_PRIORITY,
    .active   = MODULE_STATUS,
    .ops      = &roflt_ops
};


//Registration, activation and operation settings
int roflt_init_rfs(void){
    int err = 0;
    int rv = 0;

    roflt_flt = redirfs_register_filter(&roflt_info);
    if (IS_ERR(roflt_flt)) {
        rv = PTR_ERR(roflt_flt);
        FILTER_LOG_CRIT("register filter failed(%d)\n", rv);
        return rv;
    }

    rv = redirfs_set_operations(roflt_flt, roflt_op_info);
    if (rv) {
        FILTER_LOG_CRIT("set operations failed(%d)\n", rv);
        goto error;
    }

    FILTER_LOG_DEBUG("%s", "successful!");
    return 0;
error:
    err = redirfs_unregister_filter(roflt_flt);
    if (err) {
        FILTER_LOG_CRIT("unregister filter failed(%d)\n", err);
        return 0;
    }

    redirfs_delete_filter(roflt_flt);
    FILTER_LOG_CRIT("%s", "unsuccessful!");
    return rv;
}

int roflt_unregister(void){
    int rv = redirfs_unregister_filter(roflt_flt);
    if(rv){
        FILTER_LOG_CRIT("redirfs_unregister_filter() Error! Error code = %d", rv);
    }
    else{
        redirfs_delete_filter(roflt_flt);
        FILTER_LOG_DEBUG("%s", "successful!");
    }
    return rv;
}

int roflt_add_path(struct redirfs_path_info *info)
{
    redirfs_path path = {0};
    redirfs_root root = {0};

    path = redirfs_add_path(roflt_flt, info);
    if (IS_ERR(path)){
        FILTER_LOG_CRIT("%s", "reditfs_add_path() error!");
        return PTR_ERR(path);
    }

    root = redirfs_get_root_path(path);
    redirfs_put_path(path);
    if (!root){
        FILTER_LOG_CRIT("%s", "redirfs_put_path() error!");
        return 0;
    }

    redirfs_put_root(root);

    FILTER_LOG_DEBUG("%s", "successful!");
    return 0;
}


int roflt_activate(void)
{
    int rv = redirfs_activate_filter(roflt_flt);

    if(!rv){
        FILTER_LOG_DEBUG("%s", "successful!");
    }
    else{
        FILTER_LOG_DEBUG("%s", "successful!");
    }

    return rv;
}
