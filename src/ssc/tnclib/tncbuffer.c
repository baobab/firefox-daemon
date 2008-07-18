#define TNC_EXPOSE_TNCBUFFER
#include "tnclib/tncbuffer.h"
#include "tnclib/tnclib.h"

TNCBuffer *tncbuffer_create(uint32 length)
{
    TNCBuffer *buffer;
    
    TNCCreate(Buffer,buffer);
    if(buffer)
    {
        if(!tncbuffer_resize(buffer,length))
        {
            tnfree(buffer);
            buffer=0;
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(buffer);
}

void tncbuffer_destroy(TNCBuffer *buffer)
{
    if(buffer)
    {
        if(buffer->_buffer)
        {
            tnfree(buffer->_buffer);
        }
        else
        {
            tnlog(LE_Error,_tnnull);
        }
        tnfree(buffer);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

void tncbuffer_reset(TNCBuffer *buffer)
{
    if(buffer)
    {
        buffer->_length=0;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

uint32 tncbuffer_resize(TNCBuffer *this,uint32 size)
{
    uint8 *buffer;
    uint32 sz=0;

    if(this)
    {
        if((buffer=(uint8 *)tnmalloc(size))!=0)
        {
            if(this->_buffer)
            {
                // copy buffer and set length
                tnmemcpy(buffer,
                         this->_buffer,
                         this->_length=MIN(this->_length,size));
                // free
                tnfree(this->_buffer);
            }
            else
            {
                this->_length=0;
            }
            // set new buffer
            this->_buffer=buffer;
            sz=this->_size=size;
        }
        else
        {
            tnlog(LE_Error,_tnoom);
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(sz);
}

uint32 tncbuffer_write(TNCBuffer *this,const uint8 *data,uint32 len)
{
    if(this&&data)
    {
        // too small?
        if(this->_length+len>=this->_size)
        {
            // resize buffer (cheap size)
            tncbuffer_resize(this,(this->_length+len)<<1);
        }
        if(this->_length+len<this->_size)
        {
            tnmemcpy(this->_buffer+this->_length,data,len);
            this->_length+=len;
        }
        else
        {
            tnlog(LE_Error,_tnoom);
            len=0;
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
        len=0;
    }
    return(len);
}

uint32 tncbuffer_read(TNCBuffer *this,uint8 *data,uint32 len)
{
    if(this&&data)
    {
        // get maximum length of copy (minimum of two lengths)
        len=MIN(len,this->_length);
        tnmemcpy(data,this->_buffer,len);
        tnmemcpy(this->_buffer,this->_buffer+len,this->_length-=len);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
        len=0;
    }
    return(len);
}

void tncbuffer_purge(TNCBuffer *this)
{
    if(this)
    {
        this->_length=0;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

uint8 *tncbuffer_buffer(TNCBuffer *this)
{
    return(this?this->_buffer:0);
}

uint32 tncbuffer_size(TNCBuffer *this)
{
    uint32 size=0;
    if(this)
    {
        size=this->_length;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(size);
}

uint32 tncbuffer_trunc(TNCBuffer *this,uint32 length)
{
    uint32 r=0;
    if(this)
    {
        this->_length-=r=MIN(length,this->_length);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(r);
}

uint32 tncbuffer_actual_size(TNCBuffer *this)
{
    uint32 size=0;
    if(this)
    {
        size=this->_size;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(size);
}

void tncbuffer_unit_test(void)
{
    uint8 *check,*u8;
    uint32 check_len,chunk_len,r;
    uint32 i,in,pos,sz;
    TNCBuffer *buffer;

    tnlog(LE_Debug,"TNCBuffer...");
    for(i=0,in=1+tnrandom()%2000;i<in;++i)
    {
        if(!(i%500))
        {
            tnlog(LE_Debug,"   %d of %d",i,in);
        }
        check_len=tnrandom()%204803; // little prime number //
        if((check=(uint8 *)tnmalloc(check_len))!=0)
        {
            for(pos=0;pos<check_len;*(check+pos++)=tnrandom());
            if((buffer=tncbuffer_create(sz=tnrandom()%10))!=0)
            {
                for(pos=0;
                    pos<check_len;
                    pos+=tncbuffer_write(buffer,
                                         check+pos,
                                         tnrandom()%(check_len-pos)+1));
                // check size mismatch
                if(tncbuffer_size(buffer)!=check_len)
                {
                    tnlog(LE_Error,
                          "[TNCBuffer] Size mismatch %d != %d",
                          tncbuffer_size(buffer),
                          check_len);
                }
                else 
                {
                    if(tnmemcmp(check,tncbuffer_buffer(buffer),check_len)
                     ||tnmemcmp(check,
                                tncbuffer_buffer(buffer),
                                tncbuffer_size(buffer)))
                    {
                        tnlog(LE_Error,"Buffer failed");
                    }
                    for(pos=0;pos<check_len;pos+=chunk_len)
                    {
                        chunk_len=tnrandom()%(check_len-pos)+1;
                        if((u8=tnmalloc(chunk_len))!=0)
                        {
                            if((r=tncbuffer_read(buffer,u8,chunk_len))
                                    ==chunk_len)
                            {
                                if(!tnmemcmp(check+pos,u8,chunk_len))
                                {
                                }
                                else
                                {
                                    tnlog(LE_Error,"Data mismatch");
                                    pos=check_len;
                                }
                            }
                            else
                            {
                                tnlog(LE_Error,
                                      "Short read? (%d - %d != %d)",
                                      pos,
                                      r,
                                      chunk_len);
                                pos=check_len;
                            }
                            tnfree(u8);
                        }
                        else
                        {
                            tnlog(LE_Error,_tnoom);
                        }
                    }
                }
                tncbuffer_destroy(buffer);
            }
            else
            {
                if(sz)
                {
                    tnlog(LE_Error,_tnoom);
                }
            }
            tnfree(check);
        }
        else
        {
            tnlog(LE_Error,_tnoom);
        }
    }
}


