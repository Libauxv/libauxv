# This file is organized in the sections recommended by Gary V. Vaughan et al.
# in their book, The Goat Book.
#
# The entire book is available online at www.sourceware.org/autobook
#
# For detailed explanations about each section, please visit:
# www.sourceware.org/autobook/autobook/autobook_32.html#SEC32

# Section: Boilerplate
#
# Autoconf initialization
AC_PREREQ(2.61)
AC_INIT(auxv, 1.0.0, rsa@us.ibm.com)
AC_CONFIG_MACRO_DIR([m4])
#
# Automake initialization
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_MAINTAINER_MODE([disable])
#
# Enable GNU extensions, e.g. glibc extensions.
AC_GNU_SOURCE

# Section: Options
#
# XXX: Aren't these options (shared, static) enabled by default?
#
# Enable shared switch
AC_ARG_ENABLE([shared],
	      AS_HELP_STRING([--enable-shared],
			     [build shared library @<:@default@:>@]),
	      [case "$enableval" in
  yes)
       enable_shared=shared
       AC_MSG_NOTICE(enabling support for a shared library.);;
   no)
       enable_shared=
       AC_MSG_NOTICE(disabling support for a shared library.);;
    *)
       enable_shared=
       AC_MSG_NOTICE(enabling support for a shared library.);;
  esac],
	      enable_shared=shared )
AC_SUBST(enable_shared)
#
# Enable static switch
AC_ARG_ENABLE([static],
	      AS_HELP_STRING([--enable-static],
			     [build static library @<:@not default@:>@]),
	      [case "$enableval" in
  yes)
       enable_static=static
       AC_MSG_NOTICE(enabling support for a static library.);;
   no)
       enable_static=
       AC_MSG_NOTICE(disabling support for a static library.);;
    *)
       enable_static=static
       AC_MSG_NOTICE(enabling support for a static library.);;
 esac],
	      enable_static=)
AC_SUBST(enable_static)
#
# Enable non-default package installs
AC_SUBST(sysheaders, [])
AC_ARG_WITH([headers], AC_HELP_STRING([--with-headers=PATH], [location of system headers to use (for example /usr/src/linux/include) 
	@<:@default=compiler default@:>@]), [sysheaders=$withval], [sysheaders=])

# Section: Programs
#
# Compilers
AC_PROG_CC
AC_PROG_CXX
#
# Library tools (note: ranlib is deprecated by libtool)
AC_PROG_RANLIB
AM_PROG_AR
AM_PROG_LIBTOOL
LT_INIT

# Section: Libraries
#
# No libraries required

# Section: Headers
#
# Checks for header files
AC_CHECK_HEADERS([fcntl.h malloc.h strings.h unistd.h])

# Section: Typedefs and structures
#
# Checks for typedefs, structures, and compiler characteristics.
AC_C_VOLATILE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Section: Functions
#
# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getpagesize strcasecmp setenv])

# Section: Output
#
# Produce the output files
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
