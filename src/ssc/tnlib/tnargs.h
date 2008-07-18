#ifndef TNARGS_H

#   define TNARGS_H

#   include "tnlib/tnstring.h"

    typedef enum {
        TNAT_None,
        TNAT_TNString,
        TNAT_uint32,
    } TNArgType;

    typedef struct {
        TNArgType _type;
        const char *_name;
        void *_arg;
    } TNArg;

    bool tnargs_process(TNArg *args,
                        uint32 n,
                        char **argv,
                        uint32 argc,
                        bool silent = false,
                        bool ignore_unknown = false);

#endif

