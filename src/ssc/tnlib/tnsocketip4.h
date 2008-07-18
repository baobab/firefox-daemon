#ifndef TNSOCKETIP4_H

#   define TNSOCKETIP4_H

#   include "tnlib/tnsocket.h"

    class TNSocketIP4 : public TNSocket
    {
        protected:

        private:
            TNSocketIP4(const TNSocketIP4&);
            TNSocketIP4& operator=(const TNSocketIP4&);

        protected:
            TNSocketIP4(const char *,uint16);
            TNSocketIP4(TNOSSocket,struct sockaddr_in *,socklen_t);

            virtual bool v_connect(struct sockaddr_in *sa);

        public:
            virtual ~TNSocketIP4(void);
            static TNSocketIP4* create(const char *,uint16);
            static TNSocket *create(TNOSSocket,
                                    struct sockaddr_in *,
                                    socklen_t);

            virtual uint32 write(const uint8*,uint32);
            virtual int32 poll(void);

            bool nagle(bool);
    };

#endif
