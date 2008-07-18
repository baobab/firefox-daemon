#ifndef TNCLIB_H

#   define TNCLIB_H

#   include "tnos/tnos.h"
#   include "tnclib/tnprintf.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   define TNCCreate(type,var) \
        if((var=(TNC##type *)tnmalloc(sizeof(TNC##type)))!=0)   \
        { ZEROn(var,sizeof(TNC##type)); }

    // defines
#   define tnsrandom    tnos_srandom
#   define tnrandom     tnos_random

#   define tnisupper(a) ((a)>='A'&&(a)<='Z')
#   define tnislower(a) ((a)>='a'&&(a)<='z')
#   define tntoupper(a) (tnislower(a)?((a)-0x20):(a))
#   define tntolower(a) (tnisupper(a)?((a)+0x20):(a))

    // returns number of bytes coppied
    uint32 tnmemcpy(void *dst,const void *src,uint32 n);
    // returns number of bytes set
    uint32 tnmemset(void *dst,uint8 c,uint32 n);
    // compares memory
    int tnmemcmp(const void *dst,const void *src,uint32 n);

    // string length
    uint32 tnstrlen(const char *);
    // string cmp
    int tnstrcmp(const char *,const char *);
    int tnstrcmpi(const char *,const char *);
    // string cpy
    char *tnstrcpy(char *,const char *);
    // char in string?
    tnbool tnstrchr(const char *str,char ch);
    // cut a string up
    const char *tncut(char *dst,const char *str,char delim,uint32 n);

#   ifdef __cplusplus
        }
#   endif

#endif
