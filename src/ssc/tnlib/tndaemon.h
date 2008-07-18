#ifndef TNDAEMON_H

#   define TNDAEMON_H

#   include "tnlib/tnsocket.h"

    typedef enum {
        TNDT_None   = 0,
        TNDT_IP4    = 1,
        TNDT_UDP    = 2,
    } TNDaemonType;

    class TNDaemon : public TNSocket
    {
        protected:
            TNSocketList _clients;

        private:
            TNDaemon(const TNDaemon&);
            TNDaemon& operator=(const TNDaemon&);

        protected:
            TNDaemon(uint16 port);

            virtual bool v_connect(struct sockaddr_in *sa);
            virtual TNSocket *create(TNOSSocket sock,
                                     struct sockaddr_in *sa,
                                     socklen_t len);

        public:
            virtual ~TNDaemon(void);
            static TNDaemon *create(uint16 port,TNDaemonType = TNDT_IP4);

            virtual uint32 write(const uint8*,uint32);
            virtual int32 poll(void);
            virtual void purge(void);

            TNSocketList& clients(void){return(_clients);}
            virtual TNSocket *accept(void);
    };

#endif
