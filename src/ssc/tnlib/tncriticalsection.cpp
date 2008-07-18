#include "tnlib/tncriticalsection.h"
            
extern TNCriticalSection *tncriticalsection(void);

TNCriticalSection::TNCriticalSection(void)
{
}

TNCriticalSection::~TNCriticalSection(void)
{
}

bool TNCriticalSection::enter(void)
{
    return(false);
}

bool TNCriticalSection::exit(void)
{
    return(false);
}

TNCriticalSection *TNCriticalSection::create(void)
{
    return(tncriticalsection());
}

