#ifndef TNSOCKET_H

#   define TNSOCKET_H

#   include "tnlib/tnbuffer.h"
#   include "tnlib/tnstring.h"
#   include "tnlib/tnip.h"
#   include "tnlib/tnilist.h"

#   if defined(linux) 
#       include <unistd.h>
#       include <netdb.h>
#       include <sys/socket.h>
#       include <sys/time.h>
#       include <netinet/in.h>
#	    include <arpa/inet.h>
#	    include <netinet/tcp.h>
#	    include <ctype.h>
#       define TNOSError            -1
#       define TNOSInvalidSocket    -1
#       define TNOSioctl            ioctl
#       define TNOSClose            close
        typedef int TNOSSocket;
#   elif defined(__WIN32__)
#       include <winsock.h>
#       define TNOSErrVal           SOCKET_ERROR
#       define TNOSBadSocket        INVALID_SOCKET
#       define TNOSioctl            ioctlsocket
#       define TNOSClose            closesocket
        typedef SOCKET TNOSSocket;
        typedef int socklen_t;
#   endif


    typedef enum {
        TNST_None   = 0,
        TNST_IP4    = 1,
        TNST_UDP    = 2,
    } TNSocketType;

    TNIList(TNSocket);
    class TNSocket : public TNNode
    {
        protected:
            TNOSSocket _socket;
            TNString _hostname;
            uint32 _port;
            TNIP _ip;
            TNBuffer _buffer;
            int (TNSocket::*_select)(TNOSSocket);

            static TNIP _local_ip;

        private:
            TNSocket(const TNSocket&);
            TNSocket& operator=(const TNSocket&);
            void set_local_ip(void);

        protected:
            TNSocket(const char *host,uint16 port);
            TNSocket(TNOSSocket,struct sockaddr_in *,socklen_t);

            void init(void);

            uint32 store(const uint8 *data,uint32 length);

            int select(TNOSSocket);

            virtual bool v_connect(struct sockaddr_in *sa) = 0;
            virtual void v_disconnect(void){}

        public:
            virtual ~TNSocket(void);

            bool connect(void);
            bool disconnect(void);
            bool connected(void);

            virtual uint32 write(const uint8 *data,uint32 length) = 0;
            virtual int32 poll(void) = 0;

            uint32 read(uint8 *data,uint32 length);

            int32 available(void);
            uint32 size(void);
            const TNIP& ip(void) const {return(_ip);}

            const char *hostname(void){return(_hostname.c_str());}
            int16 port(void){return(_port);}

            static const TNIP& local_ip(void){return(_local_ip);}

            // create routine
            static TNSocket *create(const char *host,
                                    uint16 port,
                                    TNSocketType type = TNST_IP4);
            static TNSocket *create(TNOSSocket,
                                    struct sockaddr_in *,
                                    socklen_t);
    };

#endif

