#include "roflt_rfs.h"

redirfs_filter roflt_flt;

#define MODULE_NAME     "roflt"
#define MODULE_PRIORITY 60321
#define MODULE_STATUS   1

static int roflt_create (struct inode* inode, struct dentry* dentry, umode_t mode, bool flag){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_mkdir (struct inode* inode, struct dentry* dentry, umode_t mode){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_link (struct dentry* dentry1, struct inode* inode, struct dentry* dentry2){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_unlink (struct inode* inode, struct dentry* dentry){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static ssize_t roflt_write (struct file* file, const char __user * data, size_t size, loff_t* offset){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");

    if(rargs->args.i_create.dir->i_op->create != roflt_create){
        FILTER_LOG_DEBUG("\t%s", "create");

        struct inode_operations* i_op = (struct inode_operations*)(rargs->args.i_create.dir->i_op);
        if(i_op){
            i_op->create = roflt_create;
        }
        else{
            FILTER_LOG_CRIT("%s", "Error! i_op = NULL");
        }
        return REDIRFS_STOP;
    }
    else if(rargs->args.i_mkdir.dir->i_op->mkdir != roflt_mkdir){
        FILTER_LOG_DEBUG("\t%s", "mkdir");

        struct inode_operations* i_op = (struct inode_operations*)(rargs->args.i_mkdir.dir->i_op);
        if(i_op){
            i_op->mkdir = roflt_mkdir;
        }
        else{
            FILTER_LOG_CRIT("%s", "Error! i_op = NULL");
        }
        return REDIRFS_STOP;
    }
    else if(rargs->args.i_link.dir->i_op->link != roflt_link){
        FILTER_LOG_DEBUG("\t%s", "link");

        struct inode_operations* i_op = (struct inode_operations*)(rargs->args.i_link.dir->i_op);
        if(i_op){
            i_op->link = roflt_link;
        }
        else{
            FILTER_LOG_CRIT("%s", "Error! i_op = NULL");
        }
        return REDIRFS_STOP;
    }
    else if(rargs->args.i_unlink.dir->i_op->unlink != roflt_unlink){
        FILTER_LOG_DEBUG("\t%s", "unlink");

        struct inode_operations* i_op = (struct inode_operations*)(rargs->args.i_unlink.dir->i_op);
        if(i_op){
            i_op->unlink = roflt_unlink;
        }
        else{
            FILTER_LOG_CRIT("%s", "Error! i_op = NULL");
        }
        return REDIRFS_STOP;
    }
    else if(rargs->args.f_open.file->f_op->write != roflt_write){
        FILTER_LOG_DEBUG("\t%s", "unlink");

        struct file_operations* f_op = (struct file_operations*)(rargs->args.f_open.file->f_op);
        if(f_op){
            f_op->write = roflt_write;
        }
        else{
            FILTER_LOG_CRIT("%s", "Error! f_op = NULL");
        }
        return REDIRFS_STOP;
    }
    return REDIRFS_CONTINUE;
}

static struct redirfs_op_info roflt_op_info[] =
{
    {REDIRFS_DIR_IOP_CREATE,    roflt_pre_callback, NULL},
    {REDIRFS_DIR_IOP_MKDIR,     roflt_pre_callback, NULL},
    {REDIRFS_DIR_IOP_LINK,      roflt_pre_callback, NULL},
    {REDIRFS_DIR_IOP_UNLINK,    roflt_pre_callback, NULL},
    {REDIRFS_DIR_FOP_OPEN,      roflt_pre_callback, NULL},
    {REDIRFS_OP_END,            NULL,               NULL}
};

static struct redirfs_filter_operations roflt_ops =
{
    .activate   = roflt_activate,
    .add_path   = roflt_add_path,
    .unregister = roflt_unregister
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
