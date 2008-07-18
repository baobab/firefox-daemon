#ifndef TNMEM_H

#   define TNMEM_H

#   ifdef __cplusplus
        extern "C" {
#   endif

#   ifndef TNMEM_DEBUG
#       define tnmalloc(a)    malloc(a)
#       define tnfree(a)      free(a)
#       define tnnew(a)       new a
#       define tndelete(a)    delete a
#       define tndeletera(a)  delete[] a
#   else
        extern void *_tnmalloc(const char *,int,void *,uint32);
        extern void _tnfree(const char *,int,void *);
        extern void _tndelete(const char *,int,void *);
        extern void *_tnmalloc_real(uint32);

#       define tnmalloc(a)    _tnmalloc(__FILE__,__LINE__,_tnmalloc_real(a),a)
#       define tnfree(a)      _tnfree(__FILE__,__LINE__,a);
#       define tnnew(a)       _tnmalloc(__FILE__,__LINE__,new a,0)
#       define tndelete(a)    _tndelete(__FILE__,__LINE__,a);delete a
#       define tndeletera(a)  _tndelete(__FILE__,__LINE__,a);delete[] a
#       define tndeletearray(a)  _tndelete(__FILE__,__LINE__,a);delete[] a
#   endif

        extern void tnm_dump(void);

#   ifdef __cplusplus
        }
#   endif

#endif
