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
AC_INIT(libauxv, 1.1.0, tulioqm@br.ibm.com)
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
AM_CONDITIONAL([SYSHEADERS_SET], [test "x$sysheaders" != "x"])

# Section: Programs
#
# Compilers
AC_PROG_CC
AC_PROG_CXX
#
# We now require at least GCC-4.5 to build libauxv.
#
AC_CACHE_CHECK([if $CC is sufficient to build libauxv], libauxv_cv_compiler_ok, [
AC_TRY_COMPILE([], [
#if !defined __GNUC__ || __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5)
#error insufficient compiler
#endif],
	       [libauxv_cv_compiler_ok=yes],
	       [libauxv_cv_compiler_ok=no])])
AS_IF([test $libauxv_cv_compiler_ok != yes],
      [critic_missing="$critic_missing gcc"])
#
test -n "$critic_missing" && AC_MSG_ERROR([
*** These critical programs are missing or too old:$critic_missing
*** Check the README file for required versions.])
# Library tools (note: ranlib is deprecated by libtool)
AC_PROG_RANLIB
AC_PROG_LN_S
AM_PROG_AR
AM_PROG_LIBTOOL
LT_INIT
#
# Pass libtool options to automake
AM_CONDITIONAL([TEST_SHARED], [test "x$enable_shared" = "xyes"])
AM_CONDITIONAL([TEST_STATIC], [test "x$enable_static" = "xyes"])

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
  man/Makefile
  test/Makefile
])
AC_OUTPUT
