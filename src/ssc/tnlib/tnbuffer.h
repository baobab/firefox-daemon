#ifndef TNBUFFER_H

#   define TNBUFFER_H

#   include "tnclib/tncbuffer.h"
#   include "tnlib/tnnode.h"

    class TNBuffer : public TNNode
    {
        protected:
            TNCBuffer *_buffer;

        private:
            TNBuffer(const TNBuffer&);
            TNBuffer& operator=(const TNBuffer&);

        public:
            TNBuffer(uint32 length = 1024);
            virtual ~TNBuffer(void);
            uint32 write(const uint8 *,uint32);
            uint32 read(uint8 *,uint32);
            uint32 size(void);
    };

#endif

