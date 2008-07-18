#ifndef TNTOKENFILE_H

#   define TNTOKENFILE_H

#   include "tnlib/tntokenbase.h"
#   include "tnos/tnosstdio.h"

    class TNTokenFile : public TNTokenBase
    {
        protected:
            TNString _filename;
            TNFILE *_file;

        private:
            TNTokenFile(const TNTokenFile&);
            TNTokenFile& operator=(const TNTokenFile&);

        public:
            TNTokenFile(const char *filename,
                        const char *seps = 0,
                        const char *igns = 0);
            virtual ~TNTokenFile(void);

            bool open(void);
            void close(void);
            virtual const char *next_token(void);
            const char *next_line(void);
    };

#endif

