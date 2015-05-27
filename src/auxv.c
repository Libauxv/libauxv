/* This file is part of The AuxV Library

   Author(s): Sean Curry <spcurry@us.ibm.com>
              Steve Munroe <munroesj@us.ibm.com>
              Ryan S. Arnold <rsa@us.ibm.com>
              Peter Bergner <bergner@linux.vnet.ibm.com>

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
 * suffer the consequences if you're an ingenious fool and dlopen this library
 * after you've moved the env via a call to setenv!  Just don't do it.  */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <link.h>
#include <pthread.h>
#include <asm/elf.h>
#include <auxv/auxv.h>

#include <errno.h>
#define __set_errno(the_errno)	*__errno_location() = the_errno

static char **saved_environ = NULL;

/* The user space application may perform a setenv which would effectively move
 * the env and therefore the assumed position of the auxv following the env
 * wouldn't be valid.  The constructor for this library saves the original
 * position of the env so that it can find the auxv if it needs to use the
 * fallback method, i.e., no /proc/self/auxv.  */
void __attribute__ ((__constructor__)) __attribute__ ((__visibility__ ("hidden")))
libauxv_init (void)
{
  saved_environ = __environ;
}

/* Scan to the end of the saved environ to find the aux vector.  */
static ElfW(auxv_t) * __attribute__ ((__noinline__))
__auxv_fallback (void)
{
  char **result = saved_environ;
  /* Scan over the env vector looking for the ending NULL */
  for (; *result != NULL; ++result)
    {
    }
  /* Bump the pointer one more step, which should be the auxv. */
  return (ElfW (auxv_t) *) ++result;
}

volatile static ElfW(auxv_t) *auxv_buf = NULL;

/* pthread_once won't return a ret val from the init routine so we have to
 * do this ourselves.  This needs to be process global so that regardless of
 * which thread ends up calling into fetch_auxv(), if the initialization has
 * failed, the init_errno will be visible to all other threads and they can set
 * their thread local errno from it.  This gets cleared everytime a thread makes
 * it into fetch_auxv() and successfully allocates auxv_buf.  */
static int init_errno = 0;

static pthread_once_t auxv_once_control = PTHREAD_ONCE_INIT;

/* Always return 0 in an error case because this is always called via
 * pthread_once and the return value isn't a condition of successful
 * fetch_auxv().  The init_errno indicates a successful fetch_auxv().  */
static ElfW(auxv_t) *
fetch_auxv()
{
  extern int getpagesize (void);
  ElfW(auxv_t) *auxv_temp = (ElfW(auxv_t) *)auxv_buf;
  int auxv_f;
  size_t page_size = getpagesize();
  ssize_t bytes;

  /* If the /proc/self/auxv file has not been copied into the heap
     yet, then do it */

  if(auxv_temp == NULL)
    {
      auxv_f = open("/proc/self/auxv", O_RDONLY);

      if(auxv_f == -1)
	{
	  /* Older kernels did not support /proc/<PID>/auxv. But the auvx
	  table does exist in the process address space following the
	  env table. So try scanning over the environment table to find
	  the auxv. */
	  if (errno == ENOENT)
	    {
	      /* Hopefully we successfully captured the __environ with the
	       * constructor before the user was able to move the env with a
	       * call to setenv.  This is most likely only possible if they call
	       * libauxv via dlopen().  If that were to happen the behavior is
	       * undefined.  */
	      auxv_temp = __auxv_fallback();
	    }
	  else
	    {
	      init_errno = errno;
	      perror("Error opening file /proc/self/auxv for reading.");
	      return 0;
	    }
	}
      else
	{
	  auxv_temp = (ElfW(auxv_t) *)malloc(page_size);
	  if (!auxv_temp)
	    {
	      init_errno = errno;
	      perror("Allocation of space for auxv failed.");
	      return 0;
	    }
	  bytes = read (auxv_f, (void*)auxv_temp, page_size);

	  if (bytes <=0)
	    {
	      free (auxv_temp);
	      auxv_temp = NULL;
	      close (auxv_f);
	      init_errno = errno;
	      perror("Error /proc/self/auxv read failed");
	      return 0;
	    }

	  /* We have the auxv buffered and the file handle is no longer
	     needed.  Close the file. */
	  if ( close (auxv_f) )
	    {
	      init_errno = errno;
	      perror("Error close failed");
	    }
	}
      init_errno=0; /* Clear it out each time through so failures can be retried.  */
      auxv_buf = auxv_temp;
    }
  return (ElfW(auxv_t) *)auxv_temp;
}


int prefetch_auxv(void)
{
  ElfW(auxv_t) *auxv_temp = (ElfW(auxv_t) *)auxv_buf;

  if(auxv_temp == NULL)
    {
      if (pthread_once (&auxv_once_control, (void (*)(void))fetch_auxv))
	{
	  perror("Error pthread_once(fetch_auxv()) failed");
	  /* pthread_once's errno should be valid.  */
	  return -1;
	}
      /* Assuming that pthread_once is blocking, this is valid.  */
      auxv_temp = (ElfW(auxv_t) *)auxv_buf;
    }

  /* Since pthread_once doesn't give a return value from fetch_auxv() we have
   * to see if the fetch_auxv() set our process global errno to indicate a
   * problem.  This may have happened in another thread as well, and if so,
   * we should propogate it to this thread's local errno and fail.  */

  if(auxv_temp == NULL)
    {
      __set_errno(init_errno);
      return -1;
    }

  return 0;
}

ElfW(auxv_t) *
get_auxv(void)
{
  return (ElfW(auxv_t) *)auxv_buf;
}

ElfW(Addr)
query_auxv(ElfW(Addr) type)
{
  ElfW(auxv_t) *auxv_temp;
  long i = 0;

  /* If the /proc/self/auxv file has not been manually copied into the heap
     yet, then do it */

  auxv_temp = (ElfW(auxv_t) *)auxv_buf;

  if(auxv_temp == NULL)
    {
      if (pthread_once (&auxv_once_control, (void (*)(void))fetch_auxv))
	{
	  perror("Error pthread_once(fetch_auxv()) failed");
	  /* pthread_once's errno should be valid.  */
	  return -1;
	}
      /* Assuming that pthread_once is blocking, this is valid.  */
      auxv_temp = (ElfW(auxv_t) *)auxv_buf;
    }

  /* Since pthread_once doesn't give a return value from fetch_auxv() we have
   * to see if the fetch_auxv() set our process global errno to indicate a
   * problem.  This may have happened in another thread as well, and if so,
   * we should propogate it to this thread's local errno and fail.  */

  if(auxv_temp == NULL)
    {
      __set_errno(init_errno);
      return -1;
    }

  i = 0;
  do
    {
      if(auxv_temp[i].a_type == type)
	{
	  return auxv_temp[i].a_un.a_val;
	}
      i++;
    } while (auxv_temp[i].a_type != AT_NULL);

  return 0;
}
