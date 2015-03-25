#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(auxv, 1.0.0, rsa@us.ibm.com)
AC_CONFIG_SRCDIR([lsauxv.c])
AC_CONFIG_HEADER([config.h])

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



AC_SUBST(sysheaders, [])
AC_ARG_WITH([headers], AC_HELP_STRING([--with-headers=PATH], [location of system headers to use (for example /usr/src/linux/include) 
	@<:@default=compiler default@:>@]), [sysheaders=$withval], [sysheaders=])

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_RANLIB

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h malloc.h strings.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getpagesize strcasecmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
