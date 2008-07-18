#ifndef TNLCRITICALSECTION_H

#   define TNLCRITICALSECTION_H

#   include "tnlib/tncriticalsection.h"
#   include <pthread.h>

    class TNLCriticalSection : public TNCriticalSection
    {
        protected:
            pthread_mutex_t _mutex;

        private:
            TNLCriticalSection(const TNLCriticalSection&);
            TNLCriticalSection& operator=(const TNLCriticalSection&);

        public:
            TNLCriticalSection(void);
            virtual ~TNLCriticalSection(void);
            bool enter(void);
            bool exit(void);
    };

    extern TNCriticalSection *tncriticalsection(void);

#endif
