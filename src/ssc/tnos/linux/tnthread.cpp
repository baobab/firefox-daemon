#include "tnlib/tnthread.h"

TNThreadList TNThread::_threads;
TNCriticalSection *TNThread::_lock=0;

TNThread::TNThread(void):
_done(false),
_thread(0)
{
    if(!_lock)
    {
        if((_lock=TNCriticalSection::create())==0)
        {
            // #@#@ FIXME #@#@
            tnlog(LE_Error,"Cannot create critical section...");
            // #@#@ FIXME #@#@
        }
    }
    if(enter())
    {
        _threads.append(this);
        exit();
    }
    else
    {
        tnlog(LE_Error,"Rouge thread.");
    }
}

TNThread::~TNThread(void)
{
    bool destroy(false);

    if(_lock)
    {
        if(enter())
        {
            if(!_threads.remove(this))
            {
                tnlog(LE_Error,"Cannot remove thread");
            }
            if(!_threads.size())
            {
                destroy=true;
            }
            exit();
        }
        else
        {
            tnlog(LE_Error,"Cannot lock");
        }
        if(destroy)
        {
            tndelete(_lock);
        }
    }
    else
    {
        tnlog(LE_Error,"No lock?");
    }
}

bool TNThread::enter(void)
{
    bool locked(false);

    if(_lock)
    {
        locked=_lock->enter();
    }
    else
    {
        tnlog(LE_Error,"No lock");
    }
    return(locked);
}

bool TNThread::exit(void)
{
    bool locked(false);

    if(_lock)
    {
        locked=_lock->exit();
    }
    else
    {
        tnlog(LE_Error,"No lock");
    }
    return(locked);
}

bool TNThread::start(void)
{
    bool ok(false);
    
    if(!_thread)
    {
        if(!pthread_create(&_thread,0,start_thread,this))
        {
            ok=true;
        }
        else
        {
            tnlog(LE_Error,"Unable to create thread!");
        }
    }
    else
    {
        tnlog(LE_Error,"Thread already running!");
    }
    return(ok);
}

void *TNThread::start_thread(void *node)
{
    if(node)
    {
        TNThread *thread;

        if(enter())
        {
            thread=_threads.get((TNNode *)node);
            exit();
            if(thread)
            {
                thread->run();
                enter();
                thread->_done=true;
                exit();
            }
            else
            {
                tnlog(LE_Error,"Cannot find thread (start) (%p)",node);
            }
	        thread->_thread=0;
        }
        else
        {
            tnlog(LE_Error,"Cannot lock");
        }
    }
    pthread_exit(0);
    return(0);
}

