# User program
bin_PROGRAMS = lsauxv
lsauxv_SOURCES = lsauxv.c
lsauxv_LDADD = libauxv.la -lpthread

# Library
lib_LTLIBRARIES = libauxv.la
libauxv_la_SOURCES = auxv.c auxv.map
libauxv_la_LDFLAGS = -Wl,--version-script=$(top_srcdir)/src/auxv.map \
                     -version-info 1:0:0
nobase_include_HEADERS = auxv/auxv.h auxv/hwcap.h
