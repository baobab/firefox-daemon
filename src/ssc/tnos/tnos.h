#ifndef TNOS_H

#   define TNOS_H

    // specific project config
#   include "tnos_config.h"

#   if defined(linux)
#       include "tnos/linux/linux.h"
#   elif defined(__CYGWIN32__)
#       define linux
#       include "tnos/linux/linux.h"
#   elif defined(__WIN32__)
#       include "tnos/win32/win32.h"
#   else
#       error TN does not support your platform
#   endif

#   include "tnos/tnlog.h"
#   include "tnos/tnmem.h"
#   include "tnos/tnmacros.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   define GET_BYTE(i,n)    ((uint8)(((i)&(0x00ff<<(n<<3)))>>(n<<3)))
#   define _tncore          {char *ptr=0;*ptr=0;}
#   define SIZE(x)          (sizeof(*x)/sizeof(x))

    typedef uint8 tnbool;
    extern const uint8 tnfalse;
    extern const uint8 tntrue;

    extern const char _tnnull[];
    extern const char _tnoom[];
    extern const char _tndashes[];
    extern const char _tnplusses[];
    extern const char _tnempty[];

    extern void tnos_srandom(uint32 seed);
    extern uint32 tnos_random(void);

    extern void tncore(void);

#   ifdef __cplusplus
        }
#   endif

#endif

