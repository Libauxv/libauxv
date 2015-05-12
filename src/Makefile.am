# Check if system headers were defined during configure
if SYSHEADERS_SET
include_sysheaders=-I$(sysheaders)
else
include_sysheaders=
endif

# User program
bin_PROGRAMS = lsauxv
lsauxv_SOURCES = lsauxv.c
lsauvx_CFLAGS = $(include_sysheaders)
lsauxv_LDADD = libauxv.la -lpthread

# Library
lib_LTLIBRARIES = libauxv.la
libauxv_la_SOURCES = auxv.c auxv.map
libauxv_la_CFLAGS = $(include_sysheaders)
libauxv_la_LDFLAGS = -Wl,--version-script=$(top_srcdir)/src/auxv.map \
                     -version-info 1:0:0
nobase_include_HEADERS = auxv/auxv.h auxv/hwcap.h
