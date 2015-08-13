#include <linux/limits.h>
#include <linux/dcache.h>

#include "roflt_rfs.h"

redirfs_filter roflt_flt;

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

static int roflt_permission (struct inode* inode, int flags){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_mknod (struct inode* inode, struct dentry* dentry, umode_t mode, dev_t dev){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_rename (struct inode* inode, struct dentry* dentry1, struct inode* dentry2,
                         struct dentry* dentry3){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_rmdir (struct inode* inode, struct dentry* dentry){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_setattr (struct dentry* dentry, struct iattr* attr){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

static int roflt_symlink (struct inode* inode, struct dentry* dentry, const char* name){
    FILTER_LOG_DEBUG("%s", "");
    return -EROFS;
}

enum redirfs_rv roflt_post_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");
    return REDIRFS_STOP;
}

enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs){
    struct inode_operations* i_op = NULL;
    int id = 0;

    id = rargs->type.id;

    switch (id) {
    case REDIRFS_DIR_IOP_CREATE:
        if(rargs->args.i_create.dir->i_op->create != roflt_create){
            FILTER_LOG_DEBUG("\t%s", "create");

            i_op = (struct inode_operations*)(rargs->args.i_create.dir->i_op);
            if(i_op){
                i_op->create = roflt_create;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;

        }
        break;

    case REDIRFS_DIR_IOP_MKDIR:
        if(rargs->args.i_mkdir.dir->i_op->mkdir != roflt_mkdir){
            FILTER_LOG_DEBUG("\t%s", "mkdir");

            i_op = (struct inode_operations*)(rargs->args.i_mkdir.dir->i_op);
            if(i_op){
                i_op->mkdir = roflt_mkdir;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_LINK:
        if(rargs->args.i_link.dir->i_op->link != roflt_link){
            FILTER_LOG_DEBUG("\t%s", "link");

            i_op = (struct inode_operations*)(rargs->args.i_link.dir->i_op);
            if(i_op){
                i_op->link = roflt_link;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_UNLINK:
        if(rargs->args.i_unlink.dir->i_op->unlink != roflt_unlink){
            FILTER_LOG_DEBUG("\t%s", "unlink");

            i_op = (struct inode_operations*)(rargs->args.i_unlink.dir->i_op);
            if(i_op){
                i_op->unlink = roflt_unlink;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_PERMISSION:
        if(rargs->args.i_permission.inode->i_op->permission != roflt_permission){
            FILTER_LOG_DEBUG("\t%s", "permission");

            i_op = (struct inode_operations*)(rargs->args.i_permission.inode->i_op);
            if(i_op){
                i_op->permission = roflt_permission;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_REG_IOP_PERMISSION:
        if(rargs->args.i_permission.inode->i_op->permission != roflt_permission){
            FILTER_LOG_DEBUG("\t%s", "permission");

            i_op = (struct inode_operations*)(rargs->args.i_permission.inode->i_op);
            if(i_op){
                i_op->permission = roflt_permission;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_MKNOD:
        if(rargs->args.i_mknod.dir->i_op->mknod != roflt_mknod){
            FILTER_LOG_DEBUG("\t%s", "mknod");

            i_op = (struct inode_operations*)(rargs->args.i_mknod.dir->i_op);
            if(i_op){
                i_op->mknod = roflt_mknod;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_RENAME:
        if(rargs->args.i_rename.old_dir->i_op->rename != roflt_rename){
            FILTER_LOG_DEBUG("\t%s", "rename");

            i_op = (struct inode_operations*)(rargs->args.i_rename.old_dir->i_op);
            if(i_op){
                i_op->rename = roflt_rename;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_RMDIR:
        if(rargs->args.i_rmdir.dir->i_op->rmdir != roflt_rmdir){
            FILTER_LOG_DEBUG("\t%s", "rmdir");

            i_op = (struct inode_operations*)(rargs->args.i_rmdir.dir->i_op);
            if(i_op){
                i_op->rmdir = roflt_rmdir;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_SETATTR:
        if(rargs->args.i_setattr.dentry->d_inode->i_op->setattr != roflt_setattr){
            FILTER_LOG_DEBUG("\t%s", "setattr");

            i_op = (struct inode_operations*)(rargs->args.i_setattr.dentry->d_inode->i_op);
            if(i_op){
                i_op->setattr = roflt_setattr;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_REG_IOP_SETATTR:
        if(rargs->args.i_setattr.dentry->d_inode->i_op->setattr != roflt_setattr){
            FILTER_LOG_DEBUG("\t%s", "setattr");

            i_op = (struct inode_operations*)(rargs->args.i_setattr.dentry->d_inode->i_op);
            if(i_op){
                i_op->setattr = roflt_setattr;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;

    case REDIRFS_DIR_IOP_SYMLINK:
        if(rargs->args.i_symlink.dir->i_op->symlink != roflt_symlink){
            FILTER_LOG_DEBUG("\t%s", "symlink");

            i_op = (struct inode_operations*)(rargs->args.i_symlink.dir->i_op);
            if(i_op){
                i_op->symlink = roflt_symlink;
            }
            else{
                goto error;
            }
            return REDIRFS_STOP;
        }
        break;
    }

    return REDIRFS_CONTINUE;

error:

    FILTER_LOG_CRIT("%s", "Error! i_op = NULL");
    return REDIRFS_CONTINUE;
}

static struct redirfs_op_info roflt_op_info[] =
{
    {REDIRFS_DIR_IOP_CREATE,     roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_MKDIR,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_LINK,       roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_UNLINK,     roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_PERMISSION, roflt_pre_callback, roflt_post_callback},
    {REDIRFS_REG_IOP_PERMISSION, roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_MKNOD,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_RENAME,     roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_RMDIR,      roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_SETATTR,    roflt_pre_callback, roflt_post_callback},
    {REDIRFS_REG_IOP_SETATTR,    roflt_pre_callback, roflt_post_callback},
    {REDIRFS_DIR_IOP_SYMLINK,    roflt_pre_callback, roflt_post_callback},

    {REDIRFS_OP_END,             NULL,               NULL}
};

static struct redirfs_filter_info roflt_info =
{
    .owner    = THIS_MODULE,
    .name     = MODULE_NAME,
    .priority = MODULE_PRIORITY,
    .active   = MODULE_STATUS
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

    FILTER_LOG_INFO("%s", "successful!");
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

