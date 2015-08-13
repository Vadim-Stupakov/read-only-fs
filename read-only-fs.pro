TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    redirfs/rfs.c \
    redirfs/rfs_chain.c \
    redirfs/rfs_data.c \
    redirfs/rfs_dcache.c \
    redirfs/rfs_dentry.c \
    redirfs/rfs_file.c \
    redirfs/rfs_flt.c \
    redirfs/rfs_info.c \
    redirfs/rfs_inode.c \
    redirfs/rfs_ops.c \
    redirfs/rfs_path.c \
    redirfs/rfs_root.c \
    redirfs/rfs_sysfs.c \
    roflt/roflt_dev.c \
    roflt/roflt_rfs.c \
    roflt/roflt_sysfs.c

HEADERS += \
    redirfs/redirfs.h \
    redirfs/rfs.h \
    roflt/roflt_rfs.h \
    roflt/roflt_util.h

LINUX_HEADERS_INCLUDE_PATH = $$system(find -L /usr/src/linux-headers-link/ -type d)

INCLUDEPATH += $$LINUX_HEADERS_INCLUDE_PATH redirfs roflt

OTHER_FILES += \
    Makefile \
    roflt/Makefile \
    redirfs/Makefile


