#include "tnclib/tnprintf.h"

#undef _STDIO_H
#include <stdio.h>

#include "tnos/tnosstdarg.h"

int tnprintf(const char *fmt,...)
{
    int i;
    va_list va;
    
    va_start(va,fmt);
    i=tnvfprintf(stdout,fmt,va);
    va_end(va);
    return(i);
}

int tnsscanf(const char *buff,const char *fmt,...)
{
    int i;
    va_list va;
    
    va_start(va,fmt);
    i=vsscanf(buff,fmt,va);
    va_end(va);
    return(i);
}

int tnvprintf(const char *fmt,va_list args)
{
    int i;
    
    i=tnvfprintf(stdout,fmt,args);
    return(i);
}

int tnsprintf(TNCString *string,const char *fmt,...)
{
    int i=-1;
    va_list va;
    
    if(string)
    {
        va_start(va,fmt);
        i=tnvsprintf(string,fmt,va);
        va_end(va);
    }
    return(i);
}


int tnfprintf(TNFILE *fp,const char *fmt,...)
{
    int i;
    va_list va;
    
    va_start(va,fmt);
    i=tnvfprintf(fp,fmt,va);
    va_end(va);
    return(i);
}

int tnsprintfc(char *buff,const char *fmt,...)
{
    int i;
    va_list va;
    
    va_start(va,fmt);
    i=vsprintf(buff,fmt,va);
    va_end(va);
    return(i);

}
int tnvsprintf(TNCString *string,const char *fmt,va_list args)
{
    int i=-1;

    if(string&&fmt)
    {
        while(*fmt)
        {
            if(*fmt!='%')
            {
                // append
            }
            else
            {
                switch(*fmt)
                {
                    case '%':
                    default:
                    {
                        // append
                        break;
                    }
                }
            }
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(i);
}

int tnvfprintf(TNFILE *fp,const char *fmt,va_list args)
{
    // #@#@ FIXME #@#@//
    return(vfprintf(fp,fmt,args));
}


