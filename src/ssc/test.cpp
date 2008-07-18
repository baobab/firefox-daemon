#include "tnclib/tncbuffer.h"

extern "C" void tncbuffer_unit_test(void);

int main(void)
{
    TNCBuffer *buffer=tncbuffer_create(253);

    if(buffer)
    {
        tncbuffer_destroy(buffer);
        tncbuffer_unit_test();
    }
    else
    {
        tnlog(LE_Error,_tnoom);
    }
    return(0);
}
