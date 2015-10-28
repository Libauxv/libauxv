# Libauxv
#### The "Auxiliary Vector Library" User & Developer Guide

===========================================================================
  **Libauxv**
    The "Auxiliary Vector Library" User & Developer Guide
    For the GNU/Linux OS
    Contributed by IBM Corporation
    Copyright (C) 2010, 2011 IBM Corporation


===========================================================================
Permission is granted to copy, distribute and/or modify this document under
the terms of the GNU Free Documentation License, Version 1.3 or any later
version published by the Free Software Foundation; with no Invariant
Sections, no Front-Cover Texts, and no Back-Cover Texts.  A copy of the
license is included in the file entitled "GFDLv1.3.txt"


===========================================================================
NOTE:Eight space tabs are the optimum editor setting for reading this file.
===========================================================================
WARNING: This library is going to be discontinued. Please use glibc's
getauxval () function for similar functionality instead.
===========================================================================

		Author(s) : Ryan S. Arnold <rsa@us.ibm.com>
		      Date Created: January 29, 2010
			  Last Updated: Oct 28, 2015

===========================================================================

Table of Contents:

	1.  Introduction
	  1.1. Rationale
	2.  License
	3.  Supported Platforms
	4.  Dependencies
	  4.1  GNU/Linux OS
	  4.2  GLIBC Minimum Version
	5.  Configuration
	6.  Make Rules
	7.  Use
	8.  Contributing

	A.  History
	B.  Acknowledgements

---------------------------------------------------------------------------
1.  Introduction

---------------------------------------------------------------------------
1.1.  Rationale

The functionality in Libauxv was originally proposed for GLIBC but was
rejected:

http://sources.redhat.com/ml/libc-alpha/2006-01/msg00051.html

The reason this library is necessary is as follows:

1.) GLIBC won't provide access to the 5th process variable, which is the
auxiliary vector (see the link above).

2.) Libraries may need access to the auxv information but only 'main' can find
it.

3.) Libraries may try to find the auxv after the env, but as a library you
can't guarantee that a user application hasn't mangled the environment.

4.) Given that the most reliable method for querying the aux vector is through
/proc/self/auxv a reusable library is useful.

5.) There is an automatic fallback to attempting to read the aux vector from
the env if the /proc/self/auxv isn't supported by the kernel.

---------------------------------------------------------------------------
2.  License

Libauxv is released under the "New BSD License" as indicated by the file
COPYING.txt.

---------------------------------------------------------------------------
3.  Supported Platforms

Currently Libauxv has only been tested on the Power Architecture POWER
platforms.  The maintainer will accept patches for other architectures.  The
principle should work for other architectures and platforms.

---------------------------------------------------------------------------
4.  Dependencies
---------------------------------------------------------------------------
4.1  GNU/Linux OS

Libauxv is designed to query /proc/self/auxv for the auxiliary vector.
Sufficiently old kernels may not have support for this.  In this case Libauxv
will attempt to use a fallback mechanism and locate the auxiliary vector in
the process environment.

---------------------------------------------------------------------------
4.2  GLIBC Minimum Version

Applications which intend to use libauxv must link against libpthread.so
(-lpthread) because libauxv uses pthread_once () to enforce threadsafe
singleton creation.  This of course requires a version of glibc with NPTL
support (GLIBC 2.5)

---------------------------------------------------------------------------
5.  Configuration

Libauxv must be built in a directory that is not the base level source
directory.

  CC=/opt/at4.0/bin/gcc CFLAGS="-m32 -g -O2" ../libauxv/configure \
  --build=powerpc-linux --host=powerpc-linux --enable-shared \
  --enable-static 2>&1 | tee _configure32

  CC=/opt/at4.0/bin/gcc CFLAGS="-m64 -g -O2" ../libauxv/configure \
  --build=powerpc64-linux --host=powerpc64-linux --enable-shared \
  --enable-static 2>&1 | tee _configure64

---------------------------------------------------------------------------
6.  Make Rules

  make all:
    Build libauxv-X.Y.Z.so, libauxv.so, libauxv.so.1, and lsauxv.

  make check:
    The libauxv test suite tests the primary auxv fetching method as well as
    the fallback method.  In order to test the fallback method a version of
    the library is built which globalizes the __auxv_fallback symbol.  This
    is libauxv_test-0.0.9.so, libauxv_test.so, and libauxv_test.so.1.  These
    libraries never get installed.

  make install:
    Results in the installation of libauxv-X.Y.Z.so, libauxv.so, libauxv.so.1
    into @libdir@ as specified by configure.

    Results in the installation of lsauxv into @bindir@ as specified by
    configure.

    Results in the installation of <auxv/auxv.h> and <auxv/hwcap.h> into the
    @includedir@ specified by configure.

    Results in the installation of man/auxv.3 and man/lsauxv.1 into @mandir@
    as specified by configure.  Also results in the creation of man/lsauxv.3
    which points to man/auxv.3

    install_root=<new_top_level>
      This causes the aforementioned libraries, applications, and header files
      to be installed into <new_top_level>/@libdir@ <new_top_level>/@bindir@,
      <new_top_level>/@includedir@, and <new_top_level>/@mandir@

  make uninstall:
    Results in all installed files being removed.

  make install-headers:
    Results in the installation of <auxv/auxv.h> and <auxv/hwcap.h> into the
    @includedir@ specified by configure.

---------------------------------------------------------------------------
7. Use

It should be noted that use of Libauxv will most likely result in the mapping
of a page of memorty that is not able to be reclaimed or freed until the
parent process exits.

For information on how to use the facilities provided by Libauxv please read
the man pages auxv.3 and lsauxv.c included with this source code.

---------------------------------------------------------------------------
8. Contributing

We simply ask that you contribute modifications back to the community as a
gesture of goodwill.

In order to contribute as an individual please fill out the ICLA.txt file,
sign, date, scan, and email to the maintainer.

In order to contribute as a corporate entit please fill out the CCLA.txt file,
sign, date, scan, and email to the maintainer.

Individual contributions should use the signed-off method as indicated in the
CONTRIBUTIONS file.

---------------------------------------------------------------------------
A. History

 - Libauxv was originally written and packaged by Sean Curry
   <spcurry5@linux.vnet.ibm.com>

 - It was modified for performance by Steve Munroe <munroesj@us.ibm.com>

 - It was updated for breadth and packaged for community consumption by Ryan
   S. Arnold <rsa@us.ibm.com>
