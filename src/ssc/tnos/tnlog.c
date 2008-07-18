#include "tnos/tnlog.h"
#include "tnclib/tnprintf.h"

typedef struct {
    TNLogLevel _level;
    const char *_name;
} TNLLInfo;

const char *tnlog_level(TNLogLevel level)
{
    static const TNLLInfo _info[] = {
        { TNLL_Error, "ERROR" },
        { TNLL_Info, "INFO" },
        { TNLL_Debug, "DEBUG" },
    };
    static const uint32 _n_info=ARRAY_SIZE(_info);
    const TNLLInfo *found=0;
    const TNLLInfo *check;
    uint32 n;

    for(check=_info,n=0;!found&&n<_n_info;++n,++check)
    {
        if(check->_level==level)
        {
            found=check;
        }
    }
    return(found?found->_name:_tnnull);
}

void tnlog(const char *file,uint32 line,TNLogLevel level,const char *fmt,...)
{
    va_list va;
    tnprintf("[%s] [%s:%d]: ",tnlog_level(level),file,line);
    
    va_start(va,fmt);
    tnvprintf(fmt,va);
    va_end(va);
    tnprintf("\n");
}


