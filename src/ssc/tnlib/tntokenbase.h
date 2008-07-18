#ifndef TNTOKENBASE_H

#   define TNTOKENBASE_H

#   include "tnlib/tnstring.h"

    class TNTokenBase
    {
        protected:
            TNString _seps;
            TNString _igns;
            TNString _token;
            TNString _line;
            uint32 _pos;

            static const char _default_seps[];  // default seperators
            static const char _default_igns[];  // default ignoreables

        private:
            TNTokenBase(const TNTokenBase&);
            TNTokenBase& operator=(const TNTokenBase&);

        public:
            TNTokenBase(const char *seps = TNTokenBase::_default_seps,
                        const char *igns = TNTokenBase::_default_igns);
            virtual ~TNTokenBase(void);

            TNTokenBase& operator=(const TNString&);
            TNTokenBase& operator=(const char *);

            virtual const char *next_token(void);
            const char *token(void){return(_token.c_str());}
            const char *rest_of_line(void);
    };

#endif

