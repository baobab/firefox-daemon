#ifndef TNPRINTF_H

#   define TNPRINTF_H

#   include "tnos/tnosstdio.h"
#   include "tnos/tnosstdarg.h"
#   include "tnclib/tncstring.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   define printf tnprintf

    extern int tnprintf(const char *fmt,...);
    extern int tnvprintf(const char *fmt,va_list args);
    extern int tnfprintf(TNFILE *,const char *fmt,...);
    extern int tnvfprintf(TNFILE *,const char *fmt,va_list args);
    extern int tnsprintf(TNCString *string,const char *fmt,...);
    extern int tnsprintfc(char *,const char *fmt,...);
    extern int tnvsprintf(TNCString *string,const char *fmt,va_list args);

    extern int tnsscanf(const char *buff,const char *fmt,...);

#   ifdef __cplusplus
        }
#   endif

#endif

