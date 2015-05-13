/* The Auxiliary Vector Library Test Suite

   Author(s): Ryan S. Arnold <rsa@us.ibm.com>

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

#include <auxv/auxv.h>
#include <auxv/hwcap.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h> /* For __environ.  */
#include <stdlib.h> /* For setenv().  */

/* We want to test whether this successfully captures the __environ in the
 * libauxv constructor prior to 'main' calling setenv() and moving the env.  */
extern ElfW(auxv_t) * __auxv_fallback (void);

int main(int argc, char *argv[], char *envp[])
{

  /* Short circuit the normal method and invoke this internal symbol directly.
   * in order to test the fallback method.  */
  ElfW(auxv_t) *auxv_temp = NULL;
  ElfW(Addr) type = AT_PLATFORM;
  char **tenviron;

  int i;

  printf("envp@%p from envp[]\n", envp);
  printf("environ@%p before setenv().\n", __environ);

  auxv_temp = __auxv_fallback();
  printf("%p = __auxv_fallback() before setenv().\n", auxv_temp);

  /* If you want to force a failure to demonstrate the case that should fail
   * comment out the setenv().  */
  setenv("LIBAUXV_TEST", "BOGUS", 1);

  printf("environ@%p after setenv().\n", __environ);

  printf("Attempting to read the auxv following __environ after setenv().  This should fail.\n");
  tenviron = __environ;
  /* Scan over the env vector looking for the ending NULL */
  for (; *tenviron != NULL; ++tenviron)
    {
    }
  /* One more slot is where the auxv would be.  */
  auxv_temp = (ElfW (auxv_t) *) ++tenviron;

  i = 0;
  do
    {
      if(auxv_temp[i].a_type == type)
	{
	  fprintf (stderr,"Attempting to read the auxv from __environ after setenv() unexpectedly passed.  BUG\n");
	  fprintf (stderr,"AT_PLATFORM = %s.\n", (char *)auxv_temp[i].a_un.a_val);
	  return -1;
	}
      i++;
    } while (auxv_temp[i].a_type != AT_NULL);
  printf("... and it did.\n");

  auxv_temp = __auxv_fallback();
  printf("%p = __auxv_fallback() following setenv().\n", auxv_temp);

  printf("Attempting to read the auxv following the saved __environ pointer.\n");
  i = 0;
  do
    {
      if(auxv_temp[i].a_type == type)
	{
	  printf ("AT_PLATFORM = %s.\n", (char *)auxv_temp[i].a_un.a_val);
	  return 0;
	}
      i++;
    } while (auxv_temp[i].a_type != AT_NULL);
  fprintf (stderr,"Unable to read the auxv following the saved __environ pointer.  BUG!\\n");

  return -1;
}
