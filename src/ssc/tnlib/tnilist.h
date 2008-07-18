#ifndef TNILIST_H

#   define TNILIST_H

#   include "tnlib/tniterator.h"
#   include "tnlib/tnlist.h"

#   define TNIList(Type)                                \
        class Type;                                     \
        class Type##List : public TNList                \
        {                                               \
            TNIterator(Type);                           \
            public:                                     \
                Type##List(void):TNList(){}             \
                virtual ~Type##List(void){}             \
                Type *head(void)                        \
                    {return((Type *)_head);}            \
                Type *begin(void)                       \
                    {return((Type *)_head);}            \
                Type *end(void){return(0);}             \
                Type *get(TNNode *n)                    \
                 {return((Type *)TNList::find(n));}     \
        }

#endif

