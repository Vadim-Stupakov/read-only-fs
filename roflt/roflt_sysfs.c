





//look here rfs_sysfs.c





#include "hnfsflt.h"

static ssize_t hnfsflt_device_major_show(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%d", atomic_read(&hnfsflt_device_major));
}

static ssize_t hnfsflt_device_major_store(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, const char *buf, size_t count)
{
    return -EPERM;
}


static ssize_t hnfsflt_ll_dropped_show(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, char *buf)
{
    int val = test_and_clear_ll_dropped();
    if (val) {
        buf[0] = '1';
    }
    else {
        buf[0] = '0';
    }
    return 1;
}

static ssize_t hnfsflt_ll_dropped_store(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, const char *buf, size_t count)
{
    return -EPERM;
}


static ssize_t hnfsflt_noll_show(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%d", atomic_read(&hnfsflt_noll));
}

static ssize_t hnfsflt_noll_store(redirfs_filter filter,
    struct redirfs_filter_attribute *attr, const char *buf, size_t count)
{
    return -EPERM;
}


static struct redirfs_filter_attribute hnfsflt_device_major_attr =
    REDIRFS_FILTER_ATTRIBUTE(device_major, 0400, hnfsflt_device_major_show,
    hnfsflt_device_major_store);

static struct redirfs_filter_attribute hnfsflt_ll_dropped_attr =
    REDIRFS_FILTER_ATTRIBUTE(ll_dropped, 0400, hnfsflt_ll_dropped_show,
    hnfsflt_ll_dropped_store);

static struct redirfs_filter_attribute hnfsflt_noll_attr =
    REDIRFS_FILTER_ATTRIBUTE(noll, 0444, hnfsflt_noll_show,
    hnfsflt_noll_store);

int hnfsflt_sys_init(void)
{
    int ret;

    ret = redirfs_create_attribute(hnfsflt, &hnfsflt_device_major_attr);
    if (ret)
        goto fail_device_major;

    ret = redirfs_create_attribute(hnfsflt, &hnfsflt_ll_dropped_attr);
    if (ret)
        goto fail_ll_dropped;

    ret = redirfs_create_attribute(hnfsflt, &hnfsflt_noll_attr);
    if (ret)
        goto fail_noll;

    return 0;

fail_noll:
    redirfs_remove_attribute(hnfsflt, &hnfsflt_ll_dropped_attr);
fail_ll_dropped:
    redirfs_remove_attribute(hnfsflt, &hnfsflt_device_major_attr);
fail_device_major:
    return ret;
}


void hnfsflt_sys_cleanup(void)
{
    redirfs_remove_attribute(hnfsflt, &hnfsflt_noll_attr);
    redirfs_remove_attribute(hnfsflt, &hnfsflt_ll_dropped_attr);
    redirfs_remove_attribute(hnfsflt, &hnfsflt_device_major_attr);
}

