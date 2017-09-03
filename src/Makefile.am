lib_LTLIBRARIES = libcaq.la
libcaq_la_SOURCES = caq.c
include_HEADERS	= caq.h

libcaq_la_CFLAGS = -Wextra -pedantic -ansi

bin_PROGRAMS = caq-test laden
caq_test_SOURCES = caq-test.c
caq_test_LDADD = libcaq.la

caq_test_CFLAGS = -Wextra -pedantic -ansi -Wconversion -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self -Wcast-qual  -Wsign-promo -Wcast-align -Wstrict-null-sentinel -Wstrict-overflow
