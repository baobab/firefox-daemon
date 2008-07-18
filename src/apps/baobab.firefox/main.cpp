/*
 * baobab firefox daemon...
 */
#include "tnos/tnosstdio.h"
#include "tnlib/tndaemon.h"
#include "baobabthread.h"

void start(const TNIP&);

int main(int argc,char *argv[])
{
    bool done(false);
    TNDaemon *daemon(TNDaemon::create(5840));
    TNSocket *socket;

    if(daemon)
    {
        if(daemon->connect())
        {
            tnlog(LE_Info,"Connected to port %d",(int)daemon->port());
            while(!done)
            {
                // sockets knocking?
                if(daemon->available())
                {
                    if((socket=daemon->accept())!=0)
                    {
                        tnlog(LE_Info,
                              "Accepted: %s:%lu",
                              socket->hostname(),
                              (uint32)socket->port());
                        start(socket->ip());
                        socket->disconnect();
                    }
                    else
                    {
                        tnlog(LE_Error,"Accept error.");
                    }
                }
                daemon->purge();
                tnos_sleep(100);
            }
            daemon->disconnect();
        }
        else
        {
            tnlog(LE_Error,"Unable to connect to port %d",(int)daemon->port());
        }
    }
    else
    {
        tnlog(LE_Error,"Cannot allocate.");
    }
    return(0);
}

void start(const TNIP& ip)
{
    BaobabThread *thread((BaobabThread *)tnnew(BaobabThread(ip)));

    if(thread)
    {
        thread->start();
    }
    else
    {
        tnlog(LE_Error,"Cannot start thread.");
    }
}

/*
void socket_test(void)
{
    TNSocket *socket(TNSocket::create("mars.switch.com",22));

    if(socket)
    {
        if(socket->connect())
        {
            tnlog(LE_Error,
                  "Connected to %s:%d",
                  socket->hostname(),
                  socket->port());
            while(socket->connected())
            {
                socket->poll();
                if(socket->size())
                {
                    uint8 buff[1024];
                    uint32 n;

                    n=socket->read(buff,n);
                    if(n)
                    {
                        TNString s((char *)buff,n);

                        tnlog(LE_Error,"%s",s.c_str());
                    }

                }
                tnos_sleep(20);
            }
            socket->disconnect();
        }
        else
        {
            tnlog(LE_Error,"Unable to connect.");
        }
        tndelete(socket);
    }
    else
    {
        tnlog(LE_Error,"Unable to create socket.");
    }
}
*/
