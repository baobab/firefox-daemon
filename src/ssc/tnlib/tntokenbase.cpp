#include "tnlib/tntokenbase.h"

const char TNTokenBase::_default_seps[] = {" ,={}\n\r\t"};
const char TNTokenBase::_default_igns[] = {" \n\r\t"};

TNTokenBase::TNTokenBase
(
    const char *seps,
    const char *igns
):
_seps(seps?seps:_default_seps),
_igns(igns?igns:_default_igns),
_pos(0)
{
}
 
TNTokenBase::~TNTokenBase(void)
{
}

TNTokenBase& TNTokenBase::operator=(const TNString& s)
{
    return(operator=(s.c_str()));
}

TNTokenBase& TNTokenBase::operator=(const char *ptr)
{
    _line=ptr;
    _pos=0;
    return(*this);
}

const char *TNTokenBase::next_token(void)
{
    _pos+=_line.next_token(_pos,_token,_seps,_igns);
    return(_token.c_str());
}

const char *TNTokenBase::rest_of_line(void)
{
    const char *ptr(0);
    
    if(_pos<_line.size())
    {
        ptr=_line.c_str()+_pos;
    }
    return(ptr);
}

