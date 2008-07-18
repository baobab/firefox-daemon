#ifndef TNCNODE_H

#   define TNCNODE_H

#   include "tnos/tnos.h"

#   ifdef __cplusplus
        extern "C" {
#   endif

#   ifdef TNC_EXPOSE_TNCNODE
        struct s_TNCNode
        {
            struct s_TNCNode *_next;
            struct s_TNCNode *_last;
        };
#   else
        struct s_TNCNode
#   endif

        typedef struct s_TNCNode TNCNode;

        TNCNode *tncnode_create(void);
        void tncnode_destroy(TNCNode *);
        void tncnode_reset(TNCNode *);
        TNCNode *tncnode_next(TNCNode *);
        TNCNode *tncnode_last(TNCNode *);
        void tncnode_set_next(TNCNode *,TNCNode *);
        void tncnode_set_last(TNCNode *,TNCNode *);

#   ifdef __cplusplus
        }
#   endif

#endif
