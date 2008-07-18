#ifndef TNOSSTDARG_H

#   define TNOSSTDARG_H

#   ifdef __GNUC__
        typedef __builtin_va_list va_list;
#       define va_start(a,b)    __builtin_va_start(a,b)
#       define va_end(a)      __builtin_va_end(a)
#       define va_arg(a,b)      __builtin_va_arg(a,b)
#   else
#       error stdargs not supported
#   endif

#endif
