#include "tnos/tnos.h"

#undef _TIME_H
#include <time.h>
#undef _STDLIB_H
#include <stdlib.h>

void tnos_sleep(uint32 l)
{
    struct timespec spec,rem;

    spec.tv_sec=l/1000;
    spec.tv_nsec=(l-(spec.tv_sec*1000))*1000000;
    nanosleep(&spec,&rem);
}

void tnos_nsleep(uint32 l)
{
    struct timespec spec,rem;

    spec.tv_sec=0;
    spec.tv_nsec=l;
    nanosleep(&spec,&rem);
}

void tnos_srandom(uint32 seed)
{
    srandom(seed);
}

uint32 tnos_random(void)
{
    return(random());
}
