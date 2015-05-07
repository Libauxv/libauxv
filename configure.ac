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
# Enable the use of non-default location of system headers
AC_ARG_WITH([headers],
            AC_HELP_STRING([--with-headers=PATH],
                           [location of system headers to use (for example /usr/src/linux/include) @<:@default=compiler default@:>@]),
            [sysheaders=$withval],
            [sysheaders=])
AC_SUBST(sysheaders, [])

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
