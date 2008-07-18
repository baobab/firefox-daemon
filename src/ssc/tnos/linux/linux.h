#ifndef _TN_LINUX_H

#   define _TN_LINUX_H

#   define TNOS_OS_IS_LINUX

    // don't allow these libraries
#   define _STDIO_H
#   define _STDLIB_H
#   define _STRING_H
#   define _TIME_H

    // system types
#   include <stdint.h>

    //
    // types
    //
    typedef int8_t int8;
    typedef uint8_t uint8;
    typedef int16_t int16;
    typedef uint16_t uint16;
    typedef int32_t int32;
    typedef uint32_t uint32;

    typedef int TNOSSocket;

#endif
