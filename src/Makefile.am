AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libcaq.la
libcaq_la_CPPFLAGS = $(MMALLOC_CFLAGS)
libcaq_la_LIBADD   = $(MMALLOC_LIBS)
include_HEADERS = caq.h

bin_PROGRAMS += caq-test
caq_test_CPPFLAGS =       $(MMALLOC_CFLAGS) $(ARRAY_CFLAGS) $(SIMON_CFLAGS)
caq_test_LDADD    = -lcaq $(MMALLOC_LIBS)   $(ARRAY_LIBS)   $(SIMON_LIBS)
EXTRA_caq_test_DEPENDENCIES = libcaq.la

