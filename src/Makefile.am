AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../Array
#AM_CPPFLAGS += -I $(top_srcdir)/Array/src
#endif

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libcaq_config caq_test_config

lib_LTLIBRARIES = libcaq.la
#libcaq_la_LIBADD = $(LIBCAQ_LIBADD)
libcaq_la_LIBADD = @LIBCAQ_LIBADD@
include_HEADERS = caq.h

#include ../../StD/src/Makefile-LIBADD.inc
bin_PROGRAMS = caq-test
#caq_test_LDADD = libcaq.la $(LIBCAQ_LIBADD) -lsimon $(LIBSIMON_LIBADD)
#caq_test_LDADD = $(CAQ_TEST_LIBADD)
caq_test_LDADD = @CAQ_TEST_LIBADD@
EXTRA_caq_test_DEPENDENCIES = libcaq.la
