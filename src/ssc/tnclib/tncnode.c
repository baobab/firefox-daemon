#define TNC_EXPOSE_TNCNODE
#include "tnclib/tncnode.h"
#include "tnclib/tnclib.h"
TNCNode *tncnode_create(void)
{
    TNCNode *node=(TNCNode *)tnmalloc(sizeof(TNCNode));

    if(node)
    {
        tncnode_reset(node);
    }
    else
    {
        tnlog(LE_Error,_tnoom);
    }
    return(node);
}

void tncnode_destroy(TNCNode *node)
{
    if(node)
    {
        tnfree(node);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

void tncnode_reset(TNCNode *node)
{
    if(node)
    {
        tnmemset(node,0,sizeof(TNCNode));
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

TNCNode *tncnode_next(TNCNode *node)
{
    if(node)
    {
        node=node->_next;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(node);
}

TNCNode *tncnode_last(TNCNode *node)
{
    if(node)
    {
        node=node->_last;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(node);
}

void tncnode_set_next(TNCNode *node,TNCNode *n)
{
    if(node)
    {
        node->_next=n;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

void tncnode_set_last(TNCNode *node,TNCNode *l)
{
    if(node)
    {
        node->_last=l;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

