#ifndef TNCBUFFER_H

#   define TNCBUFFER_H

#   include "tnos/tnos.h"

#   ifdef __cplusplus
            extern "C" {
#   endif

#   ifdef TNC_EXPOSE_TNCBUFFER
        struct s_TNCBuffer
        {
            uint8 *_buffer;
            uint32 _length;
            uint32 _size;
        };
#   else
        struct s_TNCBuffer;
#   endif

        typedef struct s_TNCBuffer TNCBuffer;

        TNCBuffer *tncbuffer_create(uint32 length);
        void tncbuffer_destroy(TNCBuffer *);

        uint32 tncbuffer_write(TNCBuffer *t,const uint8 *data,uint32 len);
        uint32 tncbuffer_read(TNCBuffer *t,uint8 *data,uint32 len);
        void tncbuffer_purge(TNCBuffer *);
        void tncbuffer_reset(TNCBuffer *);
        uint32 tncbuffer_resize(TNCBuffer *,uint32);

        uint8 *tncbuffer_buffer(TNCBuffer *);
        uint32 tncbuffer_size(TNCBuffer *);
#       define tncbuffer_length tncbuffer_size
        uint32 tncbuffer_actual_size(TNCBuffer *);
        uint32 tncbuffer_trunc(TNCBuffer *,uint32);

#   ifdef __cplusplus
            }
#   endif

#endif

