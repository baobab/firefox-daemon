#ifndef TNTHREAD_H

#   define TNTHREAD_H

#   include "tnlib/tnilist.h"
#   include "tnlib/tncriticalsection.h"
#   include <pthread.h>

    TNIList(TNThread);
    class TNThread : public TNNode
    {
        protected:
            bool _done;
            pthread_t _thread;

            static TNThreadList _threads;
            static TNCriticalSection *_lock;

        private:
            TNThread(const TNThread&);
            TNThread& operator=(const TNThread&);

        protected:
            TNThread(void);
            static void *start_thread(void *node);
            static bool enter(void);
            static bool exit(void);

            virtual uint32 run(void) = 0;

        public:
            virtual ~TNThread(void);

            bool start(void);

            bool done(void){return(_done);}
    };

#endif

