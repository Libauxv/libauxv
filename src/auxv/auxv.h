/* Prototypes for the Auxiliary Vector Library

   Author(s): Sean Curry <spcurry@us.ibm.com>
              Ryan S. Arnold <rsa@us.ibm.com>

   Copyright (c) 2010, IBM Corporation
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
	 * Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	 * Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	 * Neither the name of the IBM Corporation nor the names of its
	   contributors may be used to endorse or promote products derived from
	   this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL IBM CORPORATION BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
   DAMAGE.
 */

/* If your system is old enough that it doesn't have /proc/self/auxv then you'll
 * sufferer the consequences if you're an ingenious fool and dlopen this library
 * after you've moved the env via a call to setenv!  Just don't do it.  */

#ifndef _AUXV_H
#define _AUXV_H

#include <elf.h>
#include <link.h>

/* We aren't going to assume that the system elf.h has the latest information
 * on all AUXV additions.  */
#ifndef AT_BASE_PLATFORM
#define AT_BASE_PLATFORM 24		/* String identifying real platforms.*/
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  /* Function: prefetch_auxv
   * -------------------------------------------------------------------------
   *
   *  The aux vector will be loaded into application addressable memory.
   *  If available, the aux vector will be read from /proc/self/auxv file.
   *  Older kernels may not have this feature, in which case it will try to
   *  find the Aux Vector info in the process address space immediately
   *  following the env table.   If the caller's application has done a
   *  setenv() the  __environ pointer may have been moved and the
   *  assumption that the auxv follows is not true.
   *
   *  Parameters: None
   *
   *  Returns: On success '0' is returned.  On failure '-1' is returned and
   *  errno is set:
   *
   *  Errors:
   *
   * 	ENOENT: /proc/self/auxv was not found and the auxv was not found
   * 	following the env variable.
   *
   * 	OTHER: Errnos related to pthread_once, file read, or malloc
   * 	failure may be returned.
   *
   *   Note: On failure, no memory is allocated.
   *
   */
  extern int prefetch_auxv(void)
  __attribute__ ((deprecated ("Warning: libauxv is going to be discontinued. "
  "Please use glibc's getauxval() instead.")));

  /* Function: get_auxv
   * -------------------------------------------------------------------------
   *
   *  Returns a pointer to the aux vector that has been read into memory.
   *
   *  Parameters: None.
   *
   *  Returns: If the aux vector has been read into memory this function will
   *  return the address of that memory.  If memory has not been allocated it
   *  will return zero.
   */
  extern ElfW(auxv_t) * get_auxv(void)
  __attribute__ ((deprecated ("Warning: libauxv is going to be discontinued. "
  "Please use glibc's getauxval() instead.")));

  /* Function: query_auxv
   * -------------------------------------------------------------------------
   *
   *  Queries the aux vector for an auxv_t struct where that auxv_t
   *  struct's a_type member variable matches the int argument.
   *
   *  Parameters: 'int': the a_type of the auxv_t struct that needs to be
   *  searched for in the aux vector.  This should correspond to the AT_*
   *  a_types defined in elf.h
   *
   *  Note: As an optimization, this function fetches the aux vector once
   *  and caches it in memory for reuse.  If the aux vector has been
   *  prefetched (using the prefetch_auxv() function), prior to calling
   *  query_auxv() the first time, then the cached aux vector is checked
   *  immediately.  Otherwise the first call to query_auxv() will also
   *  fetch the auxv into memory.
   *
   *  Returns: On success the a_val member variable of the auxv_t struct
   *  that has an a_type matching the argument will be returned.
   *
   *  The value 0 is returned if NO auxv_t struct with an a_type matching
   *  the argument could be found.
   *
   *  The value -1 is returned if there was a failure fetching the aux
   *  vector the first time query_auxv() is called.
   *
   */

  extern ElfW(Addr) query_auxv(ElfW(Addr))
  __attribute__ ((deprecated ("Warning: libauxv is going to be discontinued. "
  "Please use glibc's getauxval() instead.")));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AUXV_H */
