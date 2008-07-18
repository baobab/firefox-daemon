#ifndef TNLIST_H

#   define TNLIST_H

#   include "tnlib/tnnode.h"

    class TNList : public TNNode
    {
        protected:
            TNNode *_head;
            TNNode *_tail;
            bool _should_delete;

        private:
            TNList(const TNList&);
            TNList& operator=(const TNList&);

        public:
            TNList(bool should_delete_on_destroy = true);
            virtual ~TNList(void);

            virtual bool append(TNNode *);
            TNNode *remove(TNNode *);
            TNNode *find(TNNode *);
            uint32 size(void);
    };

#endif

