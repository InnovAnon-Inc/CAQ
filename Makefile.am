# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libcaq.pc src/caq-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libcaq.pc.in src/caq-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

