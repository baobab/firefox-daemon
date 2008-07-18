#include "tnlib/tnbuffer.h"

TNBuffer::TNBuffer(uint32 length):
TNNode(),
_buffer(tncbuffer_create(length))
{
    if(!_buffer)
    {
        tnlog(LE_Error,_tnoom);
    }
}

TNBuffer::~TNBuffer(void)
{
    if(_buffer)
    {
        tncbuffer_destroy(_buffer);
    }
}

uint32 TNBuffer::write(const uint8 *data,uint32 length)
{
    return(tncbuffer_write(_buffer,data,length));
}

uint32 TNBuffer::read(uint8 *data,uint32 length)
{
    return(tncbuffer_read(_buffer,data,length));
}

uint32 TNBuffer::size(void)
{
    return(tncbuffer_size(_buffer));
}


