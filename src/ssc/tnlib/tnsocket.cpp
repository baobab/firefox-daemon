#include "tnlib/tnsocket.h"
#include "tnlib/tnsocketip4.h"
#include "tnclib/tnclib.h"

TNIP TNSocket::_local_ip;

TNSocket::TNSocket(const char *host,uint16 port):
TNNode(),
_socket(TNOSInvalidSocket),
_hostname(host),
_port(port)
{
    init();
}

TNSocket::TNSocket
(
    TNOSSocket sock,
    struct sockaddr_in *sa,
    socklen_t len
):
TNNode(),
_socket(sock),
_ip(sa)
{
    _hostname=_ip;
    _port=ntohs(sa->sin_port);
    init();
}

TNSocket::~TNSocket(void)
{
    if(connected())
    {
        TNOSClose(_socket);
    }
}

void TNSocket::init(void)
{
    if(!_local_ip.ip())
    {
        set_local_ip();
    }
    _select=&TNSocket::select;
}

uint32 TNSocket::store(const uint8 *data,uint32 length)
{
    return(_buffer.write(data,length));
}

uint32 TNSocket::read(uint8 *data,uint32 length)
{
    return(_buffer.read(data,length));
}

TNSocket *TNSocket::create
(
    const char *host,
    uint16 port,
    TNSocketType type
)
{
    TNSocket *socket(0);

    switch(type)
    {
        case TNST_IP4:
        {
            socket=TNSocketIP4::create(host,port);
            break;
        }
        default:
        {
            tnlog(LE_Error,"Invalid type %d",(int)type);
            break;
        }
    }
    return(socket);
}

bool TNSocket::connect(void)
{
    struct hostent *he;
    struct sockaddr_in sa;

    if(!connected())
    {
        tnmemset(&sa,0,sizeof(struct sockaddr_in));
        if(_hostname.size())
        {
            he=gethostbyname(_hostname.c_str());
            if(he)
            {
                _hostname=he->h_name;
                _ip=htonl(*((uint32 *)he->h_addr));
                tnmemcpy(&sa.sin_addr,he->h_addr,he->h_length);
                sa.sin_family=he->h_addrtype;
                sa.sin_port=htons(_port);
                _socket=socket(he->h_addrtype,SOCK_STREAM,0);
                if(_socket!=TNOSInvalidSocket)
                {
                    if(!v_connect(&sa))
                    {
                        disconnect();
                    }
                }
            }
            else
            {
                tnlog(LE_Error,"No host (%s)",_hostname.c_str());
            }
        }
        else if(_ip.ip())
        {
            _hostname=_ip;
            sa.sin_addr.s_addr=htonl(_ip.ip());
            sa.sin_family=AF_INET;
            sa.sin_port=htons(_port);
            _socket=socket(PF_INET,SOCK_STREAM,0);
            if(_socket!=TNOSInvalidSocket)
            {
                if(!v_connect(&sa))
                {
                    disconnect();
                }
            }
            else
            {
                tnlog(LE_Error,"Cannot create socket");
            }
        }
        else
        {
            tnlog(LE_Error,"No hostname!");
        }
    }
    else
    {
        tnlog(LE_Error,"Socket already connected");
    }
    return(connected());
}

bool TNSocket::disconnect(void)
{
    bool ret(false);

    if(connected())
    {
        ret=true;
        v_disconnect();
        if(connected())
        {
           TNOSClose(_socket);
           _socket=TNOSInvalidSocket;
        }
    }
    return(ret);
}

bool TNSocket::connected(void)
{
    return(_socket!=TNOSInvalidSocket);
}

int32 TNSocket::available(void)
{
    int32 i(TNOSError);

    if(connected())
    {
        switch(i=(this->*_select)(_socket))
        {
            case -1:        // error...
            {
                disconnect();
                break;
            }
            case 0:         // nothing going on...
            default:        // and the data
            {
                break;
            }
        }
    }
    return(i);
}

uint32 TNSocket::size(void)
{
    return(_buffer.size());
}

int TNSocket::select(TNOSSocket socket)
{
    struct timeval to={0,0};
    fd_set fds;
    int i(-1);

    if(_socket!=TNOSInvalidSocket)
    {
        FD_ZERO(&fds);
        FD_SET(socket,&fds);
        i=::select(socket+1,&fds,NULL,NULL,&to);
    }
    return(i);
}

void TNSocket::set_local_ip(void)
{
    char buff[512];
    struct hostent *he;

    gethostname(buff,sizeof(buff)-1);
    *(buff+sizeof(buff)-1)='\0';
    if((he=gethostbyname(buff))!=0)
    {
        _local_ip=htonl(*((uint32 *)he->h_addr));
    }
    else
    {
        tnlog(LE_Error,"Cannot set local ip!");
    }
}

TNSocket *TNSocket::create
(
    TNOSSocket sock,
    struct sockaddr_in *in,
    socklen_t len
)
{
    return(TNSocketIP4::create(sock,in,len));
}
