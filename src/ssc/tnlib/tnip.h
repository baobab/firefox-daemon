#ifndef TNIP_H

#   define TNIP_H

#   include "tnlib/tnstring.h"
#   include <netinet/in.h>

    class TNIP
    {
        protected:
            TNString _ip;
            uint8 _a;
            uint8 _b;
            uint8 _c;
            uint8 _d;

        public:
            TNIP(void);
            TNIP(const TNIP&);
            TNIP(struct sockaddr_in *);
            virtual ~TNIP(void);

            TNIP& operator=(uint32);
            TNIP& operator=(const TNIP&);
            operator const char *() const;

            void set(uint32 ip);
            uint32 ip(void){return((_a<<24)|(_b<<16)|(_c<<8)|_d);}
    };

#endif

