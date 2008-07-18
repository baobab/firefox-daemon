#ifndef TNDAEMONIP4_H

#   define TNDAEMONIP4_H

#   include "tnlib/tndaemon.h"

    class TNDaemonIP4 : public TNDaemon
    {
        protected:

        private:
            TNDaemonIP4(const TNDaemonIP4&);
            TNDaemonIP4& operator=(const TNDaemonIP4&);

        protected:
            TNDaemonIP4(uint16 port);

        public:
            virtual ~TNDaemonIP4(void);

            static TNDaemon *create(uint16 port);
    };

#endif
