#include "tnlib/tndaemon.h"
#include "tnlib/tndaemonip4.h"

TNDaemon::TNDaemon(uint16 port):
TNSocket("",port)
{
    _ip=local_ip();
}

TNDaemon::~TNDaemon(void)
{
}

TNDaemon *TNDaemon::create(uint16 port,TNDaemonType type)
{
    TNDaemon *daemon(0);

    switch(type)
    {
        case TNDT_IP4:
        {
            daemon=TNDaemonIP4::create(port);
            break;
        }
        default:
        {
            tnlog(LE_Error,"Invalid daemon type %d",(int)type);
            break;
        }
    }
    return(daemon);
}

bool TNDaemon::v_connect(struct sockaddr_in *sa)
{
        bool ok(false);
    int opt(1);
    
    if(!setsockopt(_socket,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   (char *)&opt,
                   sizeof(opt)))
    {
        // bind to all interfaces
        sa->sin_addr.s_addr=INADDR_ANY;
        if(!bind(_socket,
                 (struct sockaddr *)sa,
                 sizeof(struct sockaddr_in)))
        {
            if(!listen(_socket,2048))
            {
                ok=true;
            }
            else
            {
                tnlog(LE_Error,"Failed to listen");
            }
        }
        else
        {
            tnlog(LE_Error,"Failed to bind");
        }
    }
    else
    {
        tnlog(LE_Error,"Failed to set options");
    }
    return(ok);
}

uint32 TNDaemon::write(const uint8*,uint32)
{
    // broad cast?
    return(0);
}

int32 TNDaemon::poll(void)
{
    // not listening right now..
    return(0);
}

TNSocket *TNDaemon::create
(
    TNOSSocket sock,
    struct sockaddr_in *sa,
    socklen_t len
)
{
    return(TNSocket::create(sock,sa,len));
}

TNSocket *TNDaemon::accept(void)
{
    TNSocket *sock(0);
    struct sockaddr_in in;
    socklen_t len(sizeof(sockaddr_in));
    int fd;

    if(connected())
    {
        if((fd=::accept(_socket,(sockaddr *)&in,&len))>=0)
        {
            if((sock=TNSocket::create(fd,&in,len))!=0)
            {
                _clients.append(sock);
            }
            else
            {
                tnlog(LE_Error,"Cannot create socket.");
            }
        }
        else
        {
            tnlog(LE_Error,"Accept error.");
        }
    }
    return(sock);
}

void TNDaemon::purge(void)
{
    TNSocket *sock;

    for(TNSocketList::iterator i=_clients.begin();i!=_clients.end();++i)
    {
        if(!i->connected())
        {
            if((sock=(TNSocket *)_clients.remove(i.type()))!=0)
            {
                tndelete(sock);
                i=_clients.begin();
            }
            else
            {
                tnlog(LE_Error,"oops");
            }
        }
    }
}

