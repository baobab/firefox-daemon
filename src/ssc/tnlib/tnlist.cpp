#include "tnlib/tnlist.h"
#include "tnos/tnos.h"
//#@#@ #include "tnos/tnmem.h"

TNList::TNList(bool sd):
TNNode(),
_head(0),
_tail(0),
_should_delete(sd)
{
}

TNList::~TNList(void)
{
    if(_should_delete)
    {
        while(_head)
        {
            _tail=_head;
            _head=_head->next();
            tndelete(_tail);
        }
    }
}

bool TNList::append(TNNode *node)
{
    if(node)
    {
        if(_tail)
        {
            _tail->next(node);
            node->last(_tail);
            _tail=node;
            _tail->next(0);
        }
        else
        {
            node->reset();
            _head=_tail=node;
        }
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(node);
}

TNNode *TNList::remove(TNNode *node)
{
    TNNode *n;
#   ifdef TNPARANOID
    node=find(node);
#   endif
    if(node)
    {
        if((n=node->last())!=0)
        {
            n->next(node->next());
        }
        else
        {
            _head=node->next();
        }
        if((n=node->next())!=0)
        {
            n->last(node->next());
        }
        else
        {
            _tail=node->last();
        }
    }
    else
    {
        tnlog(LE_Error,"Invalid node");
    }
    return(node);
}

TNNode *TNList::find(TNNode *node)
{
    TNNode *found(0);

    for(TNNode *check=_head;!found&&check;check=check->next())
    {
        if(node==check)
        {
            found=node;
        }
    }
    return(found);
}

uint32 TNList::size(void)
{
    uint32 n(0);

    for(TNNode *node=_head;node;++n,node=node->next());
    return(n);
}

