#include "tnlib/tnstring.h"
#include "tnclib/tnclib.h"

TNString::TNString(void):
TNNode()
{
    init();
}

TNString::TNString(const TNString& string):
TNNode()
{
    init();
    operator=(string);
}

TNString::TNString(const char *string):
TNNode()
{
    init();
    operator=(string);
}

TNString::TNString(const char *string,uint32 n):
TNNode()
{
    init();
    if(_string)
    {
        tncstring_assignn(_string,string,n);
    }
}

TNString::~TNString(void)
{
    if(_string)
    {
        tncstring_destroy(_string);
    }
}

void TNString::init(void)
{
    if((_string=tncstring_create())==0)
    {
        tnlog(LE_Error,_tnoom);
    }
}

TNString& TNString::operator=(const TNString& src)
{
    return(operator=(src.c_str()));
}

TNString& TNString::operator=(const char *src)
{
    if(_string)
    {
        tncstring_assign(_string,src);
    }
    else
    {
        tnlog(LE_Error,"No string?");
    }
    return(*this);
}

TNString& TNString::operator+=(const char *src)
{
    if(_string)
    {
        tncstring_append(_string,src);
    }
    else
    {
        tnlog(LE_Error,"No string?");
    }
    return(*this);
}

TNString& TNString::operator+=(const char src)
{
    if(_string)
    {
        tncstring_appendc(_string,src);
    }
    else
    {
        tnlog(LE_Error,"No string?");
    }
    return(*this);
}

uint32 TNString::size(void) const
{
    return(_string?tncstring_length(_string):0);
}

const char *TNString::c_str(void) const
{
    return(tncstring_text(_string));
}

uint32 TNString::next_token
(
    uint32 start,
    TNString& token,
    const char *seps,
    const char *igns
)
{
    uint32 length(size()),skip(0);
    const char *ptr(c_str());

    token=0;
    if(start<length)
    {
        ptr+=start;
        if(!tnstrchr(seps,*ptr)||tnstrchr(igns,*ptr))
        {
            while(*ptr&&tnstrchr(igns,*ptr))
            {
                ++ptr;
                ++skip;
            }
            if(!tnstrchr(seps,*ptr))
            {
                while(*ptr&&!tnstrchr(seps,*ptr))
                {
                    token+=*ptr++;
                    ++skip;
                }
            }
            else
            {
                token+=*ptr;
                ++skip;
            }
        }
        else
        {
            token+=*ptr;
            ++skip;
        }
    }
    return(skip);
}



