#ifndef ROFLT_UTIL_H
#define ROFLT_UTIL_H

#include <linux/kernel.h>

#define GET_FILE_LINE_FUNC_ARG __FILE__, __LINE__, __FUNCTION__

#define DEBUG 3

#ifdef DEBUG

#define PRINT_DUMP_STACK\
    do{\
        printk("\n\nDump stack begin:\n\n");\
        dump_stack();\
        printk("\n\nDump stack end:\n\n");\
    }while(0);

#if DEBUG > 0
#define FILTER_LOG_INFO(format, args...)\
    printk(KERN_INFO "File:(%s), Line:(%u), Function:(%s)\n\tMessage: "format"\n", GET_FILE_LINE_FUNC_ARG, args);
#endif

#if DEBUG > 1
#define FILTER_LOG_DEBUG(format, args...)\
    printk(KERN_DEBUG "File:(%s), Line:(%u), Function:(%s)\n\tMessage: "format"\n", GET_FILE_LINE_FUNC_ARG, args);
#endif

#if DEBUG > 2
#define FILTER_LOG_CRIT(format, args...)\
    printk(KERN_CRIT "File:(%s), Line:(%u), Function:(%s)\n\tMessage: "format"\n", GET_FILE_LINE_FUNC_ARG, args);
#endif

#endif //#ifdef DEBUG


#endif // ROFLT_UTIL_H
