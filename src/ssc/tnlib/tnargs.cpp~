#include "tnlib/tnargs.h"
#include "tnlib/tnstringto.h"
#include "tnclib/tnclib.h"

TNArg *tnargs_find(const char *text,TNArg *args,uint32 nargs)
{
    TNArg *found(0);

    if(text)
    {
        for(uint32 i=0;!found&&i<nargs;++i,++args)
        {
            if(text)
            {
                if(!tnstrcmp(text,args->_name))
                {
                    found=args;
                }
            }
        }
    }
    return(found);
}

bool tnargs_process
(
    TNArg *args,
    uint32 n,
    char **argv,
    uint32 argc,
    bool silent,
    bool ignore_unknowns
)
{
    bool status(true);
    TNArg *arg;

    for(uint32 i=1;status&&i<argc;++i)
    {
        status=false;
        if(*(argv+i))
        {
            if(**(argv+i)=='-')
            {
                if(*((*(argv+i))+1)=='-')
                {
                    if((arg=tnargs_find((*(argv+i))+2,args,n))!=0)
                    {
                        // next arg..
                        if(++i<argc)
                        {
                            if(arg->_arg)
                            {
                                switch(arg->_type)
                                {
                                    case TNAT_uint32:
                                    {
                                        status=tnstringto(*(argv+i),
                                                        (uint32 *)arg->_arg);
                                        break;
                                    }
                                    case TNAT_TNString:
                                    {
                                        status=tnstringto(*(argv+i),
                                                      (TNString *)arg->_arg);
                                        break;
                                    }
                                    default:
                                    {
                                        if(!silent)
                                        {
                                            tnlog(LE_Error,
                                                  "No type 0x%0x",
                                                  arg->_type);
                                        }
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                if(!silent)
                                {
                                    tnlog(LE_Error,"No arg");
                                }
                            }
                        }
                        else
                        {
                            // check if bool/just it exits
                            // if(arg->_type==TNAT_Bool
                            //  ||arg->_type==TNAT_Just_Exists_On_CmdLine)
                            if(!silent)
                            {
                                tnlog(LE_Error,"Out of args");
                            }
                        }
                    }
                    else
                    {
                        if(!silent)
                        {
                            tnlog(LE_Error,"Unknown arg (%s)",*(argv+i));
                        }
                        if(ignore_unknowns)
                        {
                            status=true;
                        }
                    }
                }
                else if(!silent)
                {
                    tnlog(LE_Error,"Invalid arg %s",*(argv+i));
                }
            }
            else if(!silent)
            {
                tnlog(LE_Error,"Invalid arg %s",*(argv+i));
            }
        }
        else
        {
            tnlog(LE_Error,_tnnull);
        }
    }
    return(status);
}
