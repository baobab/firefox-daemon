#ifndef TNMACROS_H

#   define TNMACROS_H

#   ifndef ARRAY_SIZE
#       define ARRAY_SIZE(a) (sizeof(a)/sizeof(*a))
#   endif

#   ifndef ZERO
#      define  ZERO(x) tnmemset((uint8 *)((void *)x),0,sizeof(x))
#   endif

#   ifndef ZEROn
#      define  ZEROn(x,n) tnmemset((uint8 *)((void *)x),0,n)
#   endif

#   ifndef MIN
#       define MIN(a,b)  (((a)<(b))?(a):(b))
#   endif

#   ifndef MAX
#       define MAX(a,b)  (((a)>(b))?(a):(b))
#   endif

#endif

