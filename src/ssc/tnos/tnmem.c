#include "tnos/tnos.h"
#include "tnclib/tnclib.h"

#undef _STDLIB_H
#include <stdlib.h>

typedef struct tnmemnode {
    struct tnmemnode *_next;
    uint32 _alloc_id;
    char *_file;
    int _line;
    void *_ptr;
    uint32 _size;
} TNMemNode;

uint32 _tnm_alloc_id = 0;
TNMemNode *_tnm_head = 0;

#define tnmdealloc(ptr) if(ptr){free(ptr);}else tnlog(LE_Error,_tnnull);

TNMemNode *tnm_new_node(const char *file,int line,void *ptr,uint32 size)
{
    TNMemNode *node=(TNMemNode *)malloc(sizeof(TNMemNode));

    if(node)
    {
        ZEROn(node,sizeof(TNMemNode));
        if((node->_file=(char *)malloc(tnstrlen(file)+1))!=0)
        {
            tnstrcpy(node->_file,file);
            node->_alloc_id=_tnm_alloc_id++;
            node->_line=line;
            node->_ptr=ptr;
            node->_size=size;
        }
        else
        {
            free(node);
            node=0;
            tnlog(LE_Error,_tnoom);
        }
    }
    else
    {
        tnlog(LE_Error,_tnoom);
    }
    return(node);
}

void tnm_free_node(TNMemNode *node)
{
    if(node)
    {
        tnmdealloc(node->_file);
        tnmdealloc(node);
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
}

void *_tnmalloc_real(uint32 i)
{
    return(malloc(i));
}

void *_tnmalloc(const char *file,int line,void *ptr,uint32 size)
{
    TNMemNode *node=tnm_new_node(file,line,ptr,size);

    if(node)
    {
        node->_next=_tnm_head;
        _tnm_head=node;
    }
    else
    {
        tnlog(LE_Error,_tnnull);
    }
    return(ptr);
}

void _tnfree(const char *file,int line,void *ptr)
{
    _tndelete(file,line,ptr);
    if(ptr)
    {
        free(ptr);
    }
    else
    {
        tnlog(LE_Error,"FREEING NULL PTR");
    }
}

void _tndelete(const char *file,int line,void *ptr)
{
    TNMemNode *last=0,*node=0,*check=_tnm_head;

    while(check&&(!node))
    {
        if(check->_ptr!=ptr)
        {
            last=check;
            check=check->_next;
        }
        else
        {
            node=check;
        }
    }

    if(node)
    {
        if(last)
        {
            last->_next=node->_next;
        }
        else
        {
            _tnm_head=node->_next;
        }
        tnm_free_node(node);
    }
    else
    {
        tnlog(LE_Error,_tndashes);
        tnlog(LE_Error,"Invalid free/delete");
        tnlog(LE_Error,"0x%0x",ptr);
        tnlog(LE_Error,"File: %s:%d",file,line);
        tnlog(LE_Error,_tndashes);
#       ifdef TNMEM_CORE_ON_ERROR
        tncore();
#       endif
    }
}

void tnm_dump(void)
{
    uint32 n=0;
    TNMemNode *node;

    tnlog(LE_Info,_tndashes);
    tnlog(LE_Info,"tnm_dump():");
    for(node=_tnm_head;node;node=node->_next,++n)
    {
        tnlog(LE_Info,
              "%05lu [0x%0x %05lu bytes] %s:%d",
              node->_alloc_id,
              node->_ptr,
              node->_size,
              node->_file,
              node->_line);
    }
    tnlog(LE_Info,_tndashes);
    tnlog(LE_Info,"%lu of %lu allocs",n,_tnm_alloc_id);
    if(n)
    {
        tnlog(LE_Info,_tnempty);
        tnlog(LE_Info,"DIRTY  DIRTY  DIRTY  DIRTY");
        tnlog(LE_Info,_tnempty);
    }
    tnlog(LE_Info,_tndashes);
}

