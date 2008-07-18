#ifndef TNCLIST_H

#   define TNCLIST_H

#   include "tnlib/tncnode.h"
#   include "tnlib/tnlist.h"

    class TNCList : protected TNList
    {
        private:
            TNCList(const TNList&);
            TNCList& operator=(const TNList&);

        public:
            TNCList(bool should_delete_on_destroy = true)
                :TNList(should_delete_on_destroy){}
            virtual ~TNCList(void){}
            TNCNode *remove(TNCNode *n)
                            {return((TNCNode *)TNList::remove(n));}
            TNCNode *find(TNCNode *n){return((TNCNode *)TNList::find(n));}
    };

#   define TNCList(Type)            \
        TNCNode(Type);              \
        class Type##CList : public TNCList                              \
        {                                                               \
            private:                                                    \
                Type##CList(const Type##CList&);                        \
                Type##CList& operator=(const Type##CList&);             \
                                                                        \
            public:                                                     \
                Type##CList(bool should_delete_on_destroy = true)       \
                    :TNCList(should_delete_on_destroy){}                \
                virtual ~Type##CList(void){}                            \
                bool append(const Type& t)                              \
                    {return(TNList::append(                             \
                            (TNNode *)tnnew(TNC##Type##Node(t))));}     \
        }

#endif

