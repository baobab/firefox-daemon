#include "tnlib/tntokenfile.h"
#include "tnclib/tnclib.h"

TNTokenFile::TNTokenFile
(
    const char *filename,
    const char *seps,
    const char *igns
):
TNTokenBase(seps,igns),
_filename(filename),
_file(0)
{
}
            
TNTokenFile::~TNTokenFile(void)
{
    if(_file)
    {
        tnlog(LE_Info,
              "Auto closing token file (%s), don't be lazy!",
              _filename.c_str());
        close();
    }
}
 
bool TNTokenFile::open(void)
{
    if(_file)
    {
        tnlog(LE_Info,"File already open? (%s)",_filename.c_str());
        close();
    }
    _file=tnfopen(_filename.c_str(),"rt");
    return(_file);
}

void TNTokenFile::close(void)
{
    if(_file)
    {
        tnfclose(_file);
        _file=0;
    }
    else
    {
        tnlog(LE_Error,"Already closed (%s)",_filename.c_str());
    }
}
 
const char *TNTokenFile::next_token(void)
{
    if(_file)
    {
        if(!TNTokenBase::next_token())
        {
            // we failed to get a token, so we need another line..
            if(next_line())
            {
                // get the next token
                next_token();
            }
            else
            {
                // we are out of data, thus we are done.
                close();
            }
        }
    }
    return(token());
}

const char *TNTokenFile::next_line(void)
{
    char buffer[128];
    bool again;
    TNString string;

    if(_file)
    {
        do{
            again=false;
            if(tnfgets(buffer,sizeof(buffer)-1,_file))
            {
                // make sure we are null termed
                *(buffer+sizeof(buffer)-1)=0;
                if(*(buffer+tnstrlen(buffer)-1)!='\n')
                {
                    again=true;
                    *(buffer+sizeof(buffer)-1)=0;
                }
                string+=buffer;
            }
        }while(again);
        TNTokenBase::operator=(string);
    }
    else
    {
        _line=0;
    }
    return(_line.c_str());
}
