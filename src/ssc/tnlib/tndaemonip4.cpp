#include "tnlib/tndaemonip4.h"

TNDaemonIP4::TNDaemonIP4(uint16 port):
TNDaemon(port)
{
}

TNDaemonIP4::~TNDaemonIP4(void)
{
}

TNDaemon *TNDaemonIP4::create(uint16 port)
{
    return((TNDaemon *)tnnew(TNDaemonIP4(port)));
}

