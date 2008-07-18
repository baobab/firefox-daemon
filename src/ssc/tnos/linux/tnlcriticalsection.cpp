#include "tnos/linux/tnlcriticalsection.h"

TNLCriticalSection::TNLCriticalSection(void):
TNCriticalSection()
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&_mutex, &attr);
}

TNLCriticalSection::~TNLCriticalSection(void)
{
    pthread_mutex_destroy(&_mutex);
}

bool TNLCriticalSection::enter(void)
{
    bool status;

    if(!(status=!pthread_mutex_lock(&_mutex)))
    {
        tnlog(LE_Error,"Unable to lock the mutex!");
    }
    return(status);
}

bool TNLCriticalSection::exit(void)
{
    bool status;

    if(!(status=!pthread_mutex_unlock(&_mutex)))
    {
        tnlog(LE_Error,"Unable to unlock the mutex!");
    }
    return(status);
}

TNCriticalSection *tncriticalsection(void)
{
    return((TNCriticalSection *)tnnew(TNLCriticalSection()));
}

