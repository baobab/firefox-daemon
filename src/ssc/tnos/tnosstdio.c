#include "tnos/tnosstdio.h"

#ifdef TNOS_USE_STDIO
#undef _STDIO_H
#include <stdio.h>

TNFILE *tnfopen(const char *name,const char *mode)
{
    return(fopen(name,mode));
}

int tnfclose(TNFILE *fp)
{
    return(fclose(fp));
}

int tnfflush(TNFILE *fp)
{
    return(fflush(fp));
}

tnsize_t tnfread(void *ptr,tnsize_t sz,tnsize_t n,TNFILE *fp)
{
    return(fread(ptr,sz,n,fp));
}

tnsize_t tnfwrite(void *ptr,tnsize_t sz,tnsize_t n,TNFILE *fp)
{
    return(fwrite(ptr,sz,n,fp));
}

char *tnfgets(char *buffer,uint32 length,TNFILE *fp)
{
    char *ret=0;

    if(buffer)
    {
        if(fp)
        {
            ret=fgets(buffer,length,fp);
        }
        else
        {
            tnlog(LE_Error,_tnnull);
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(ret);
}

#endif
