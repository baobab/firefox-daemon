#ifndef TNITERATOR_H

#   define TNITERATOR_H

#   define TNIterator(Type)                                                 \
        public:                                                             \
        class iterator                                                      \
        {                                                                   \
            protected:                                                      \
                TNNode *_node;                                              \
                uint32 _position;                                           \
            public:                                                         \
                iterator(TNNode *n):_node(n),_position(0){}                 \
                iterator(const iterator& i):                                \
                    _node(i._node),_position(i._position){}                 \
                iterator(void):_node(0){}                                   \
                iterator& operator++(void)                                  \
                    {_node=_node?_node->next():0;++_position;return(*this);}\
                iterator& operator--(void)                                  \
                    {_node=_node->last();--_position;return(*this);}        \
                iterator& operator=(TNNode *n){_node=n;return(*this);}      \
                iterator& operator=(const iterator& i)                      \
                        {_node=i._node;return(*this);}                      \
                bool operator!=(const TNNode *n) const {return(_node!=n);}  \
                bool operator==(const TNNode *n) const {return(_node==n);}  \
                Type *operator*(){return((Type *)_node);}                   \
                Type *operator->(){return((Type *)_node);}                  \
                Type *type(void){return((Type *)_node);}                    \
                uint32 position(void){return(_position);}                   \
        }                                                                   \

#endif

