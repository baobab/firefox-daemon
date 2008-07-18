#define TNC_EXPOSE_TNCSTRING
#include "tnclib/tncstring.h"
#include "tnclib/tnclib.h"

TNCString *tncstring_create(void)
{
    TNCString *string=(TNCString *)tnmalloc(sizeof(TNCString));

    if(string)
    {
        if((string->_buffer=tncbuffer_create(256))==0)
        {
            tnlog(LE_Error,_tnoom);
            tnfree(string);
            string=0;
        }
    }
    else
    {
        tnlog(LE_Error,_tnoom);
    }
    return(string);
}

void tncstring_destroy(TNCString *string)
{
    if(string)
    {
        tncbuffer_destroy(string->_buffer);
        tnfree(string);
    }
}

const char *tncstring_assign(TNCString *string,const char *text)
{
    if(string)
    {
        tncbuffer_reset(string->_buffer);
        if(text)
        {
            tncbuffer_write(string->_buffer,
                            (const uint8 *)text,
                            tnstrlen(text)+1);
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return((const char *)(string?tncbuffer_buffer(string->_buffer):0));
}

const char *tncstring_assignn(TNCString *string,const char *text,uint32 n)
{
    if(string)
    {
        tncbuffer_reset(string->_buffer);
        if(text)
        {
            tncbuffer_write(string->_buffer,
                            (const uint8 *)text,
                            n);
            if(*(text+n-1))
            {
                uint8 z=0;
                tncbuffer_write(string->_buffer,&z,1);
            }
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return((const char *)(string?tncbuffer_buffer(string->_buffer):0));
}

const char *tncstring_append(TNCString *string,const char *text)
{
    if(string)
    {
        if(text)
        {
            if(tncbuffer_size(string->_buffer)>1)
            {
                tncbuffer_trunc(string->_buffer,1);
            }
            tncbuffer_write(string->_buffer,
                            (const uint8 *)text,
                            tnstrlen(text)+1);
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
    return((const char *)(string?tncbuffer_buffer(string->_buffer):0));
}

const char *tncstring_appendc(TNCString *string,const char ch)
{
    uint8 data[2];

    if(string)
    {
        if(tncbuffer_size(string->_buffer)>1)
        {
            tncbuffer_trunc(string->_buffer,1);
        }
        *(data+0)=ch;
        *(data+1)=0;
        tncbuffer_write(string->_buffer,data,2);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return((const char *)(string?tncbuffer_buffer(string->_buffer):0));
}

const char *tncstring_text(TNCString *string)
{
    return((const char *)(string
                          ?tncbuffer_size(string->_buffer)
                                ?tncbuffer_buffer(string->_buffer)
                                :0
                          :0));
}

uint32 tncstring_length(TNCString *string)
{
    uint32 len=string?tncbuffer_size(string->_buffer):0;

    if(string)
    {
        if(len)
        {
            len-=1;
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(len);
}

