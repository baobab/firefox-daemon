#ifndef TNCSTRING_H

#   define TNCSTRING_H

#   include "tnos/tnos.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   ifdef TNC_EXPOSE_TNCSTRING
#       include "tnclib/tncbuffer.h"
        struct s_TNCString
        {
            TNCBuffer *_buffer;
        };
#   else
        struct s_TNCString;
#   endif

        typedef struct s_TNCString TNCString;

        TNCString *tncstring_create(void);
        void tncstring_destroy(TNCString *);
        const char *tncstring_assign(TNCString *,const char *);
        const char *tncstring_assignn(TNCString *,const char *,uint32);
        const char *tncstring_append(TNCString *,const char *);
        const char *tncstring_appendc(TNCString *,const char);
        const char *tncstring_text(TNCString *);
        uint32 tncstring_length(TNCString *);

#   ifdef __cplusplus
        }
#   endif

#endif
