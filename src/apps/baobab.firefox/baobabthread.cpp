#include "baobabthread.h"

#undef _STDLIB_H
#include <stdlib.h>

uint32 BaobabThread::run(void)
{
    TNString string(getenv("HOME"));

    string+="/baobab.firefox.script ";
    string+=_ip;
    tnlog(LE_Info,"Executing: [ %s ]",string.c_str(),(const char *)_ip);
    system(string.c_str());
    return(0);
}
