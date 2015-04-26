#include "roflt_rfs.h"

redirfs_filter roflt;

enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");
    PRINT_DUMP_STACK;
    rargs->rv.rv_int = EROFS;
    return REDIRFS_STOP;
}

enum redirfs_rv roflt_post_callback(redirfs_context cont, struct redirfs_args *rargs){
    FILTER_LOG_DEBUG("%s", "");
    PRINT_DUMP_STACK;
    rargs->rv.rv_int = EROFS;
    return REDIRFS_STOP;
}

static struct redirfs_op_info roflt_op_info[] =
{
    {REDIRFS_REG_FOP_OPEN,      roflt_pre_callback, NULL},
    {REDIRFS_DIR_IOP_MKDIR,     roflt_pre_callback, NULL},
    {REDIRFS_OP_END,            NULL,               NULL}
};

static struct redirfs_filter_operations roflt_ops =
{
    .activate =     roflt_activate,
    .add_path =     roflt_add_path,
    .unregister =   roflt_unregister
};

static struct redirfs_filter_info roflt_info =
{
    .owner =    THIS_MODULE,
    .name =     "roflt",
    .priority = 60321,
    .active =   1,
    .ops =      &roflt_ops
};

//Registration, activation and operation settings
int roflt_init_rfs(void){
    int err = 0;
    int rv = 0;

    roflt = redirfs_register_filter(&roflt_info);
    if (IS_ERR(roflt)) {
        rv = PTR_ERR(roflt);
        FILTER_LOG_CRIT("register filter failed(%d)\n", rv);
        return rv;
    }

    rv = redirfs_set_operations(roflt, roflt_op_info);
    if (rv) {
        FILTER_LOG_CRIT("set operations failed(%d)\n", rv);
        goto error;
    }

    FILTER_LOG_DEBUG("%s", "successful!");
    return 0;
error:
    err = redirfs_unregister_filter(roflt);
    if (err) {
        FILTER_LOG_CRIT("unregister filter failed(%d)\n", err);
        return 0;
    }

    redirfs_delete_filter(roflt);
    FILTER_LOG_CRIT("%s", "unsuccessful!");
    return rv;
}

void roflt_unregister(void){
    int rv = redirfs_unregister_filter(roflt);
    if(rv){
        FILTER_LOG_CRIT("redirfs_unregister_filter() Error! Error code = %d", rv);
    }
    else{
        redirfs_delete_filter(roflt);
        FILTER_LOG_DEBUG("%s", "successful!");
    }
}

int roflt_add_path(struct redirfs_path_info *info)
{
    redirfs_path path = {0};
    redirfs_root root = {0};

    path = redirfs_add_path(roflt, info);
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
    int rv = redirfs_activate_filter(roflt);

    if(!rv){
        FILTER_LOG_DEBUG("%s", "successful!");
    }
    else{
        FILTER_LOG_DEBUG("%s", "successful!");
    }

    return rv;
}
