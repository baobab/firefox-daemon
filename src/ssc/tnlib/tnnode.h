#ifndef TNNODE_H

#   define TNNODE_H

#   include "tnos/tnos.h"

    class TNNode
    {
        protected:
            TNNode *_next;
            TNNode *_last;

        private:
            TNNode(const TNNode&);
            TNNode& operator=(const TNNode&);

        public:
            TNNode(void){reset();}
            virtual ~TNNode(void){}
            TNNode *next(void){return(_next);}
            TNNode *last(void){return(_last);}
            void next(TNNode *next){_next=next;}
            void last(TNNode *last){_last=last;}
            void reset(void){_next=_last=0;}
    };

#endif

