#include "tnos/tnos.h"
#include "tnos/tnosstdio.h"

const uint8 tnfalse=0;
const uint8 tntrue=1;

const char _tnnull[] = {"null"};
const char _tnoom[] = {"oom"};
const char _tnempty[] = {""};
const char _tndashes[] = {"----------------------------------------"};
const char _tnplusses[] = {"++++++++++++++++++++++++++++++++++++++++"};


void tncore(void)
{
    tnfflush(0);
    _tncore;
}
