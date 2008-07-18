#ifndef TNOSSTDIO_H

#   define TNOSSTDIO_H

#   include "tnos/tnos.h"

#   ifdef TNOS_OS_IS_LINUX
#       define TNOS_USE_STDIO
#   else
#       error stdio unsupported
#   endif

#   ifdef TNOS_USE_STDIO

#   ifdef __cplusplus
        extern "C" {
#   endif

        typedef void TNFILE;
        typedef uint32 tntime_t;
        typedef long int tnsize_t;

        TNFILE *tnfopen(const char *,const char *);
        int tnfclose(TNFILE *);
        int tnfflush(TNFILE *);
        tnsize_t tnfread(void *,tnsize_t,tnsize_t,TNFILE *);
        tnsize_t tnfwrite(void *,tnsize_t,tnsize_t,TNFILE *);
        long tnftell(TNFILE *);
        int tnfseek(TNFILE *,long offset,int whence);
        char *tnfgets(char *,uint32,TNFILE *);

        void tnos_sleep(uint32);

#   ifdef __cplusplus
        }
#   endif

#   endif

#endif

