#include "tnlib/tnsocketip4.h"

TNSocketIP4::TNSocketIP4(const char *host,uint16 port):
TNSocket(host,port)
{
}

TNSocketIP4::TNSocketIP4
(
    TNOSSocket sock,
    struct sockaddr_in *in,
    socklen_t len
):
TNSocket(sock,in,len)
{
}

TNSocketIP4::~TNSocketIP4(void)
{
}

TNSocketIP4 *TNSocketIP4::create(const char *host,uint16 port)
{
    return((TNSocketIP4 *)tnnew(TNSocketIP4(host,port)));
}

TNSocket *TNSocketIP4::create
(
    TNOSSocket sock,
    struct sockaddr_in *in,
    socklen_t len
)
{
    return((TNSocketIP4 *)tnnew(TNSocketIP4(sock,in,len)));
}

bool TNSocketIP4::v_connect(sockaddr_in *sa)
{
    bool ok(::connect(_socket,(struct sockaddr *)sa,sizeof(struct sockaddr))
                   !=TNOSError);

    if(ok)
    {
        nagle(1);
    }
    return(ok);
}

bool TNSocketIP4::nagle(bool nag)
{
    int flag(nag?1:0);

    nag=setsockopt(_socket,
                   IPPROTO_TCP,
                   TCP_NODELAY,
                   (char *)&flag,
                   sizeof(flag))==0;
    return(nag);
}

uint32 TNSocketIP4::write(const uint8 *data,uint32 length)
{
    int i;
    if(connected())
    {
        switch(i=send(_socket,data,length,0))
        {
            case -1:
            case 0:
            {
                if(!length)
                {
                    tnlog(LE_Error,"Zero write?");
                }
                length=0;
                disconnect();
                break;
            }
            default:
            {
                length=i;
                break;
            }
        }
    }
    else
    {
        length=0;
    }
    return(length);
}

int32 TNSocketIP4::poll(void)
{
    int32 i(-1);
    uint8 buffer[1024];
    
    for(uint32 n=0;available()>0&&n<10;++n)
    {
        if(n) tnlog(LE_Info,"#@#@ FIXME #@#@ -- looping %d",(int)n);
        switch(i=recv(_socket,buffer,sizeof(buffer),0))
        {
            case -1:
            case 0:
            {
                disconnect();
                break;
            }
            default:
            {
                store(buffer,i);
                break;
            }
        }
    }
    return(i);
}
