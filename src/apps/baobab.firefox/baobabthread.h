#ifndef BAOBABTHREAD_H

#   define BAOBABTHREAD_H

#   include "tnlib/tnthread.h"
#   include "tnlib/tnip.h"

    class BaobabThread : public TNThread
    {
        protected:
            TNIP _ip;

        private:
            BaobabThread(const BaobabThread&);
            BaobabThread& operator=(const BaobabThread&);

        protected:
            uint32 run(void);

        public:
            BaobabThread(const TNIP& ip):TNThread(),_ip(ip){}
            virtual ~BaobabThread(void){}
    };

#endif

