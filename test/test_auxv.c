/* The Auxiliary Vector Library Test Suite

   Author(s): Steve Munroe <munroesj@us.ibm.com>
              Ryan S. Arnold <rsa@us.ibm.com>

     Copyright (c) 2010, 2011, IBM Corporation
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
#include <unistd.h> /* for __environ.  */

int main(int argc, char *argv[], char *envp[])
{
	unsigned long int clock_tick;
	unsigned long int page_size;
	unsigned long int dcache_size;
	unsigned long int icache_size;
	unsigned long int ucache_size;
	char * platform = NULL;
	char * base_platform = NULL;
	ElfW(auxv_t) *at_ptr = NULL;
	unsigned long int hwcap_mask,
			  hwcap2_mask;

	printf("envp@%p\n", envp);
	printf("environ@%p\n", __environ);

	if(prefetch_auxv())
	  {
		  printf("prefetch_auxv() failed with errno %d.\n", errno);
		  return -1;
	  }

        at_ptr = get_auxv();
	printf("get_auxv() = %p\n", at_ptr);

	clock_tick = (unsigned long int) query_auxv (AT_CLKTCK);

	if (clock_tick != 0)
	  printf("CLKTCK=%ld\n", clock_tick);

	dcache_size =  (unsigned long int) query_auxv (AT_DCACHEBSIZE);

	printf("DCACHE_SIZE=%ld\n", dcache_size);

	icache_size = (unsigned long int) query_auxv (AT_ICACHEBSIZE);;

	printf("ICACHE_SIZE=%ld\n", icache_size);

	ucache_size = (unsigned long int) query_auxv (AT_UCACHEBSIZE);

	printf("UCACHE_SIZE=%ld\n", ucache_size);

	page_size = (unsigned long int) query_auxv (AT_PAGESZ);

	printf("PAGE_SIZE=%ld\n", page_size);

	platform = (char*) query_auxv (AT_PLATFORM);

	if (platform)
	    printf("PLATFORM=%s\n", platform);
	else
	    printf("AT_PLATFORM not supported\n");

	if (base_platform)
	    printf("BASE_PLATFORM=%s\n", base_platform);
	else
	    printf("AT_BASE_PLATFORM not supported\n");

	hwcap_mask = (unsigned long int) query_auxv (AT_HWCAP);

	printf("HWCAP=0x%0*lx\n",2 * (int) sizeof(unsigned long int), hwcap_mask);

#ifdef __powerpc__
	hwcap2_mask = (unsigned long int) query_auxv (AT_HWCAP2);

	printf("HWCAP2=0x%0*lx\n",2 * (int) sizeof(unsigned long int), hwcap2_mask);

	if (hwcap_mask & PPC_FEATURE_32)
	    printf("  32-bit\n");

	if (hwcap_mask & PPC_FEATURE_64)
	    printf("  64-bit\n");

	if (hwcap_mask & PPC_FEATURE_601_INSTR)
	    printf("  HAS_601_INSTR\n");

	if (hwcap_mask & PPC_FEATURE_HAS_ALTIVEC)
	    printf("  HAS_ALTIVEC\n");

	if (hwcap_mask & PPC_FEATURE_HAS_FPU)
	    printf("  HAS_FPU\n");

	if (hwcap_mask & PPC_FEATURE_HAS_MMU)
	    printf("  HAS_MMU\n");

	if (hwcap_mask & PPC_FEATURE_HAS_4xxMAC)
	    printf("  HAS_4xxMAC\n");

	if (hwcap_mask & PPC_FEATURE_HAS_SPE)
	    printf("  HAS_SPE\n");

	if (hwcap_mask & PPC_FEATURE_HAS_EFP_SINGLE)
	    printf("  HAS_SPE_SINGLE\n");

	if (hwcap_mask & PPC_FEATURE_HAS_EFP_DOUBLE)
	    printf("  HAS_SPE_DOUBLE\n");

	if (hwcap_mask & PPC_FEATURE_NO_TB)
	    printf("  NO_TIMEBASE\n");

	if (hwcap_mask & PPC_FEATURE_POWER4)
	    printf("  POWER4 ISA\n");

	if (hwcap_mask & PPC_FEATURE_POWER5)
	    printf("  POWER5 ISA\n");

	if (hwcap_mask & PPC_FEATURE_POWER5_PLUS)
	    printf("  POWER5+ ISA\n");

	if (hwcap_mask & PPC_FEATURE_CELL_BE)
	    printf("  CELL BE\n");

	if (hwcap_mask & PPC_FEATURE_SMT)
	    printf("  HAS_SMT\n");

	if (hwcap_mask & PPC_FEATURE_ICACHE_SNOOP)
	    printf("  ICache Snoop\n");

	if (hwcap_mask & PPC_FEATURE_ARCH_2_05)
	    printf("  ARCH_2_05 ISA\n");

	if (hwcap_mask & PPC_FEATURE_ARCH_2_06)
	    printf("  ARCH_2_06 ISA\n");

	if (hwcap_mask & PPC_FEATURE_HAS_DFP)
	    printf("  HAS DFP\n");

	if (hwcap_mask & PPC_FEATURE_POWER6_EXT)
	    printf("  POWER6x instructions\n");

	if (hwcap_mask & PPC_FEATURE_HAS_VSX)
	    printf("  HAS VSX\n");

	if (hwcap2_mask & PPC_FEATURE2_ARCH_2_07)
	    printf("  ARCH_2_07 ISA\n");

	if (hwcap2_mask & PPC_FEATURE2_HAS_HTM)
	    printf("  HAS HTM\n");

	if (hwcap2_mask & PPC_FEATURE2_HAS_DSCR)
	    printf("  HAS DSCR\n");

	if (hwcap2_mask & PPC_FEATURE2_HAS_EBB)
	    printf("  HAS EBB\n");

	if (hwcap2_mask & PPC_FEATURE2_HAS_ISEL)
	    printf("  HAS ISEL\n");

	if (hwcap2_mask & PPC_FEATURE2_HAS_TAR)
	    printf("  HAS TAR\n");

#endif
	return (0);
}
