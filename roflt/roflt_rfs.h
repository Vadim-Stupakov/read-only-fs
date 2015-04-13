#ifndef ROFLT_RFS_H
#define ROFLT_RFS_H

#include "rfs.h"
#include "redirfs.h"

enum redirfs_rv roflt_pre_callback(redirfs_context cont, struct redirfs_args *rargs);
int roflt_init_rfs(void);
void roflt_cleanup_rfs(void);
int roflt_add_path(struct redirfs_path_info *info);
int roflt_activate(void);

#endif // ROFLT_RFS_H
