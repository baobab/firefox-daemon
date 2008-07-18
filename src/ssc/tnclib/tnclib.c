#include "tnclib.h"

uint32 tnmemset(void *p,uint8 c,uint32 n)
{
    uint32 count=0;
    uint8 *ptr=(uint8 *)p;

    if(ptr)
    {
        for(;count++<n;*ptr++=c);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(count);
}

uint32 tnmemcpy(void *vdst,const void *vsrc,uint32 n)
{
    register uint8 *dst=(uint8 *)vdst;
    register const uint8 *src=(const uint8 *)vsrc;
    uint32 count=0;

    if(dst&&src)
    {
        for(;count++<n;*dst++=*src++);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(count);
}

int tnmemcmp(const void *vdst,const void *vsrc,uint32 n)
{
    register const uint8 *dst=(const uint8 *)dst;
    register const uint8 *src=(const uint8 *)vsrc;
    register int i,r=1;

    if(dst&&src)
    {
        for(i=0;i<n&&(!(r=*dst-*src));++i,++dst,++src);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(r);
}

char *tnstrcpy(register char *dst,register const char *src)
{
    char *r=dst;

    if(src&&dst)
    {
        while((*dst++=*src++)!=0);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(r);
}


uint32 tnstrlen(const char *string)
{
    uint32 length=0;

    if(string)
    {
        while(*string++)
        {
            ++length;
        }
    }
    return(length);
}

tnbool tnstrchr(const char *str,char ch)
{
    tnbool found=tnfalse;

    if(str)
    {
        while(!found&&*str)
        {
            if(*str++==ch)
            {
                found=tntrue;
            }
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(found);
}

int tnstrcmp(const char *a,const char *b)
{
    int r=0;

    if(a&&b)
    {
        while(*a&&*a==*b)
        {
            ++a;
            ++b;
        }
        r=*a-*b;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(r);
}

int tnstrcmpi(const char *a,const char *b)
{
    int r=0;

    if(a&&b)
    {
        while(*a&&tntoupper(*a)==tntoupper(*b))
        {
            ++a;
            ++b;
        }
        r=*a-*b;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(r);
}

const char *tncut(char *dst,const char *str,char delim,uint32 n)
{
    const char *ptr=0;
    char *dptr=dst;
    uint32 i;

    if(dst&&str)
    {
        *dst=0;
        for(i=0;*str&&i<n;)
        {
            if(*str!=delim)
            {
                *dptr++=*str++;
            }
            else
            {
                if(++i<n)
                {
                    dptr=dst;
                    *dst=0;
                    ++str;
                }
                else
                {
                    *dptr=0;
                    ptr=dst;
                }
            }
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(ptr);
}

