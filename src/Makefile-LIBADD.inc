#include $(top_srcdir)/Array/src/Makefile-LIBADD.inc
#include $(top_srcdir)/StD/src/Makefile-LIBADD.inc

#if USE_SUBMODULES
#LIBCAQ_LIBADD = ../Array/src/.libs/libarray.la $(LIBARRAY_LIBADD)
#else
LIBCAQ_LIBADD = -larray $(LIBARRAY_LIBADD)
#endif
