#ifndef ROFLT_UTIL_H
#define ROFLT_UTIL_H

#include <linux/kernel.h>

#define DEBUG 3

#ifdef DEBUG

#if DEBUG > 0
#define FILTER_LOG_INFO(format, args...) printk(KERN_INFO "%s(%u): "format"\n", (__FUNCTION__), (__LINE__), args )
#endif

#if DEBUG > 1
#define FILTER_LOG_DEBUG(format, args...) printk(KERN_DEBUG "%s(%u): "format"\n", (__FUNCTION__), (__LINE__), args )
#endif

#if DEBUG > 2
#define FILTER_LOG_CRIT(format, args...) printk(KERN_CRIT "%s(%u): "format"\n", (__FUNCTION__), (__LINE__), args )
#endif

#endif //#ifdef DEBUG


#endif // ROFLT_UTIL_H
