#ifndef TNCNODE_H

#   define TNCNODE_H

#   include "tnlib/tnnode.h"

    class TNCNode : public TNNode
    {
        private:
            TNCNode(const TNCNode *);
            TNCNode& operator=(const TNCNode&);
        public:
            TNCNode(void):TNNode(){}
            virtual ~TNCNode(void){}
    };

#define  TNCNode(Type)  class TNC##Type##Node : public TNCNode             \
                        {                                                   \
                            protected:                                      \
                                Type _object;                               \
                                                                            \
                            private:                                        \
                                TNC##Type##Node(const TNC##Type##Node&);    \
                                TNC##Type##Node& operator=(                 \
                                            const TNC##Type##Node&);        \
                                                                            \
                            public:                                         \
                                TNC##Type##Node(const Type& t)              \
                                    :TNCNode(),_object(t){}                 \
                                virtual ~TNC##Type##Node(void){}            \
                                operator Type&(){return(_object);}          \
                                Type& object(void){return(_object);}        \
                                Type& operator=(const Type& t)              \
                                    {_object=t;return(_object);}            \
                        }

#endif

