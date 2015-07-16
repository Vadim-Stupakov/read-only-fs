#ifndef ROFLT_RFS_H
#define ROFLT_RFS_H

#include "rfs.h"
#include "roflt_util.h"

#define MODULE_NAME     "roflt"
#define MODULE_PRIORITY 60321
#define MODULE_STATUS   1

//enum redirfs_rv roflt_post_callback(redirfs_context cont, struct redirfs_args *rargs);
enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs);
int roflt_init_rfs(void);
int roflt_unregister(void);
int roflt_add_path(struct redirfs_path_info *info);
int roflt_activate(void);

extern redirfs_filter roflt_flt;

#endif // ROFLT_RFS_H
