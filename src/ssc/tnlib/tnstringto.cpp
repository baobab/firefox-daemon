#include "tnlib/tnstringto.h"
#include "tnclib/tnclib.h"

bool tnstringto(const char *string,uint32 *dest)
{
    bool ok(string&&dest);
    
    if(ok)
    {
        if(*string!='0')
        {
            ok=tnsscanf(string,"%lu",dest)==1;
        }
        else if(tntoupper(*(string+1))=='X')
        {
            ok=tnsscanf(string,"%0x",dest)==1;
        }
        else
        {
            ok=tnsscanf(string,"%lu",dest)==1;
        }
    }
    return(ok);
}

bool tnstringto(const char *string,TNString *dest)
{
    bool ok(string&&dest);

    if(ok)
    {
        dest->operator=(string);
    }
    return(ok);
}

