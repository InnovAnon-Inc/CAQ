lib_LTLIBRARIES = libcaq.la
libcaq_la_LIBADD = -larray
libcaq_la_SOURCES = caq.c
include_HEADERS	= caq.h
#libcaq_la_CFLAGS =

bin_PROGRAMS = caq-test
caq_test_SOURCES = caq-test.c
caq_test_LDADD = libcaq.la -larray
#caq_test_CFLAGS =

AM_CPPFLAGS = -D__STDC_INT64__
AM_CPPFLAGS += -I $(srcdir)/../glitter/src
AM_CPPFLAGS += -I $(srcdir)/../Array/src
