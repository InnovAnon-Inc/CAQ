AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libcaq.la
libcaq_la_CPPFLAGS = $(GLITTER_CFLAGS) $(MMALLOC_CFLAGS) $(ARRAY_CFLAGS)
libcaq_la_LIBADD   = $(GLITTER_LIBS)   $(MMALLOC_LIBS)   $(ARRAY_LIBS)
include_HEADERS = caq.h

bin_PROGRAMS += caq-test
caq_test_CPPFLAGS =       $(MMALLOC_CFLAGS) $(ARRAY_CFLAGS) $(SIMON_CFLAGS)
caq_test_LDADD    = -lcaq $(MMALLOC_LIBS)   $(ARRAY_LIBS)   $(SIMON_LIBS)
EXTRA_caq_test_DEPENDENCIES = libcaq.la

