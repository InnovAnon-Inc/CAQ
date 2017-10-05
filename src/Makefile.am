AM_CPPFLAGS = -D__STDC_INT64__

if USE_SUBMODULES
SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

SUBDIRS += ../Array
AM_CPPFLAGS += -I $(top_srcdir)/Array/src
endif

include Makefile-LIBADD.inc

lib_LTLIBRARIES = libcaq.la
libcaq_la_LIBADD = $(LIBCAQ_LIBADD)
include_HEADERS = caq.h

bin_PROGRAMS = caq-test
caq_test_LDADD = libcaq.la $(LIBCAQ_LIBADD) -lsimon $(LIBSIMON_LIBADD)
