#ifndef TNSTRING_H

#   define TNSTRING_H

#   include "tnclib/tncstring.h"
#   include "tnlib/tnnode.h"

    class TNString : public TNNode
    {
        protected:
            TNCString *_string;

        protected:
            void init(void);

        public:
            TNString(void);
            TNString(const TNString&);
            TNString(const char *);
            TNString(const char *,uint32 n);
            virtual ~TNString(void);

            TNString& operator=(const TNString&);
            TNString& operator=(const char *);
            TNString& operator+=(const TNString&);
            TNString& operator+=(const char *);
            TNString& operator+=(const char);
            const char *c_str(void) const;
            operator const char *() const {return(c_str());}
            uint32 size(void) const;

            uint32 next_token(uint32 start,
                              TNString& token,
                              const char *seps,
                              const char *igns);

    };

#endif

