#ifndef TNCRITICALSECTION_H

#   define TNCRITICALSECTION_H

#   include "tnos/tnos.h"

    class TNCriticalSection
    {
        protected:

        private:
            TNCriticalSection(const TNCriticalSection&);
            TNCriticalSection& operator=(const TNCriticalSection&);

        protected:
            TNCriticalSection(void);

        public:
            virtual ~TNCriticalSection(void);
            virtual bool enter(void);
            virtual bool exit(void);
            // create method
            static TNCriticalSection *create(void);
    };

#endif

