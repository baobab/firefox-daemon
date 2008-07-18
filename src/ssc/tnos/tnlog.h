#ifndef TNLOG_H

#   define TNLOG_H

#   include "tnos/tnos.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   define LE_Error     __FILE__,__LINE__,TNLL_Error
#   define LE_Info      __FILE__,__LINE__,TNLL_Info
#   define LE_Debug     __FILE__,__LINE__,TNLL_Debug

    typedef enum {
        TNLL_None = 0,
        TNLL_Error,
        TNLL_Info,
        TNLL_Debug,
    } TNLogLevel;

    extern void tnlog(const char *file,
                      uint32 line,
                      TNLogLevel level,
                      const char *fmt,
                      ...);

#   ifdef __cplusplus
        }
#   endif

#endif
