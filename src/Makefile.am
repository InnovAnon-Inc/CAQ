AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

SUBDIRS += ../Array
AM_CPPFLAGS += -I $(top_srcdir)/Array/src

LIBCAQ_LIBADD = ../Array/src/.libs/libarray.la $(LIBARRAY_LIBADD)

lib_LTLIBRARIES = libcaq.la
libcaq_la_LIBADD = $(LIBCAQ_LIBADD)
include_HEADERS = caq.h

bin_PROGRAMS = caq-test
caq_test_LDADD = libcaq.la $(LIBCAQ_LIBADD)
