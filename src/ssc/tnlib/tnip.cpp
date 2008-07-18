#include "tnlib/tnip.h"
#include "tnlib/tnprintf.h"

TNIP::TNIP(void):
_a(0),
_b(0),
_c(0),
_d(0)
{
}

TNIP::TNIP(const TNIP& ip)
{
    operator=(ip);
}

TNIP::TNIP(struct sockaddr_in *in)
{
    set(ntohl(in->sin_addr.s_addr));
}

TNIP::~TNIP(void)
{
}

TNIP& TNIP::operator=(uint32 ip)
{
    set(ip);
    return(*this);
}

TNIP::operator const char *() const
{
    return(_ip.c_str());
}

void TNIP::set(uint32 ip)
{
    char buffer[128];
    
    _a=GET_BYTE(ip,3);
    _b=GET_BYTE(ip,2);
    _c=GET_BYTE(ip,1);
    _d=GET_BYTE(ip,0);
    tnsprintfc(buffer,
            "%d.%d.%d.%d",
            (unsigned int)_a,
            (unsigned int)_b,
            (unsigned int)_c,
            (unsigned int)_d);
    _ip=(buffer);
}

TNIP& TNIP::operator=(const TNIP& ip)
{
    char buffer[128];
    
    _a=ip._a;
    _b=ip._b;
    _c=ip._c;
    _d=ip._d;
    tnsprintfc(buffer,
            "%d.%d.%d.%d",
            (unsigned int)_a,
            (unsigned int)_b,
            (unsigned int)_c,
            (unsigned int)_d);
    _ip=(buffer);
    return(*this);
}

