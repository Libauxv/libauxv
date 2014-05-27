/* lsauxv - The Auxiliary Vector Query Application

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

#include <stdio.h>
#include <strings.h>
#include <auxv.h>
#include <hwcap.h>

static void print_help(){
	printf("Usage: lsauxv [options]\n");
	printf("Options:\n");
	printf("--help\t\tDisplay this information\n");
	printf("--info\t\tDisplay some information about this application, as well as an example use.\n");
	printf("--list\t\tLists all supported a_type arguments.\n");
	printf("--hwcap\t\tPrint the system hardware capability (hwcap) information.\n");
	printf("[a_type]\tReplace [a_type] with one or more of the supported a_type's that are listed using --list.\n");
	printf("\t\tUse --info to find out more about this application, including what an a_type is.\n");
}

static void print_info(){
	printf("This application takes one or more arguments, where each argument is a supported a_type, and prints out\n");
	printf("the corresponding a_val. If there are N a_type arguments passed to lsauxv, then the standard output will\n");
	printf("consist of N lines, where each line is the a_val of the corresponding a_type argument. Use --list to get\n");
	printf("a list of the supported a_type arguments.\n\n");
	printf("In this context, an \"a_type\" argument refers to the a_type member of the auxv_t struct, which is defined\n");
	printf("in /usr/include/elf.h. For each a_type argument, the lsauxv application scans the auxv_t structures in\n");
	printf("/proc/self/auxv until a auxv_t structure with a matching a_type is found. The a_val of the matching auxv_t\n");
	printf("structure is then printed to standard out (one a_val per line per a_type parameter).\n\n");
	printf("Sample usage of lsauxv (with output): \n");
	printf("> lsauxv AT_PAGESZ AT_UID at_uid\n");
	printf("4096\n1016\n1016\n");
}

static void print_list(){
	printf("Below is a list of all supported arguments for the 'lsauxv' application. Use --help for more information about this application.\n\n");
	printf("Argument\tDescription\n");
	printf("--------\t-----------\n");
	printf("AT_NULL\t\tEnd of vector\n");
	printf("AT_IGNORE\tEntry should be ignored\n");
	printf("AT_EXECFD\tFile descriptor of program\n");
	printf("AT_PHDR\t\tProgram headers for program\n");
	printf("AT_PHENT\tSize of program header entry\n");
	printf("AT_PHNUM\tNumber of program headers\n");
	printf("AT_PAGESZ\tSystem page size\n");
	printf("AT_BASE\t\tBase address of interpreter\n");
	printf("AT_FLAGS\tFlags\n");
	printf("AT_ENTRY\tEntry point of program\n");
	printf("AT_NOTELF\tProgram is not ELF\n");
	printf("AT_UID\t\tReal uid\n");
	printf("AT_EUID\t\tEffective uid\n");
	printf("AT_GID\t\tReal gid\n");
	printf("AT_EGID\t\tEffective gid\n");
	printf("AT_CLKTCK\tFrequency of times()\n");
	printf("AT_PLATFORM\tString identifying platform\n");
	printf("AT_BASE_PLATFORM\tString identifying base platform\n");
	printf("AT_HWCAP\tMachine dependent hints about processor capabilities\n");
	printf("AT_FPUCW\tUsed FPU control word\n");
	printf("AT_DCACHEBSIZE\tData cache block size\n");
	printf("AT_ICACHEBSIZE\tInstruction cache block size\n");
	printf("AT_UCACHEBSIZE\tUnified cache block size\n");
	printf("AT_IGNOREPPC\tEntry should be ignored.\n");
	printf("AT_SECURE\tBoolean, was exec setuid-like?\n");
	printf("AT_SYSINFO\t\n");
	printf("AT_SYSINFO_EHDR\t\n");
	printf("AT_L1I_CACHESHAPE\t\n");
	printf("AT_L1D_CACHESHAPE\t\n");
	printf("AT_L2_CACHESHAPE\t\n");
	printf("AT_L3_CACHESHAPE\t\n");
}

static void print_hwcap(void)
{
	long hwcap_mask;
	long hwcap_mask2;
	hwcap_mask = query_auxv(AT_HWCAP);

	printf("HWCAP1 = 0x%08lX\n", hwcap_mask);
#ifdef __powerpc__
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
#endif

	hwcap_mask2 = query_auxv(AT_HWCAP2);
	printf("HWCAP2 = 0x%08lX\n", hwcap_mask2);
#ifdef __powerpc__
	if (hwcap_mask2 & PPC_FEATURE2_ARCH_2_07)
	    printf("  ISA 2.07\n");

	if (hwcap_mask2 & PPC_FEATURE2_HAS_HTM)
	    printf("  HTM\n");

	if (hwcap_mask2 & PPC_FEATURE2_HAS_DSCR)
	    printf("  HAS DSCR\n");

	if (hwcap_mask2 & PPC_FEATURE2_HAS_EBB)
	    printf("  HAS EBB\n");

	if (hwcap_mask2 & PPC_FEATURE2_HAS_ISEL)
	    printf("  HAS ISEL\n");

	if (hwcap_mask2 & PPC_FEATURE2_HAS_TAR)
	    printf("  HAS TAR\n");
#endif
}

static ElfW(Addr) translate_a_type(char *str){
	if(!strcasecmp("AT_NULL", str)) return AT_NULL;
	if(!strcasecmp("AT_IGNORE", str)) return AT_IGNORE;
	if(!strcasecmp("AT_EXECFD", str)) return AT_EXECFD;
	if(!strcasecmp("AT_PHDR", str)) return AT_PHDR;
	if(!strcasecmp("AT_PHENT", str)) return AT_PHENT;
	if(!strcasecmp("AT_PHNUM", str)) return AT_PHNUM;
	if(!strcasecmp("AT_PAGESZ", str)) return AT_PAGESZ;
	if(!strcasecmp("AT_BASE", str)) return AT_BASE;
	if(!strcasecmp("AT_FLAGS", str)) return AT_FLAGS;
	if(!strcasecmp("AT_ENTRY", str)) return AT_ENTRY;
	if(!strcasecmp("AT_NOTELF", str)) return AT_NOTELF;
	if(!strcasecmp("AT_UID", str)) return AT_UID;
	if(!strcasecmp("AT_EUID", str)) return AT_EUID;
	if(!strcasecmp("AT_GID", str)) return AT_GID;
	if(!strcasecmp("AT_EGID", str)) return AT_EGID;
	if(!strcasecmp("AT_CLKTCK", str)) return AT_CLKTCK;
	if(!strcasecmp("AT_PLATFORM", str)) return AT_PLATFORM;
	if(!strcasecmp("AT_BASE_PLATFORM", str)) return AT_BASE_PLATFORM;
	if(!strcasecmp("AT_HWCAP", str)) return AT_HWCAP;
	if(!strcasecmp("AT_FPUCW", str)) return AT_FPUCW;
	if(!strcasecmp("AT_DCACHEBSIZE", str)) return AT_DCACHEBSIZE;
	if(!strcasecmp("AT_ICACHEBSIZE", str)) return AT_ICACHEBSIZE;
	if(!strcasecmp("AT_UCACHEBSIZE", str)) return AT_UCACHEBSIZE;
	if(!strcasecmp("AT_IGNOREPPC", str)) return AT_IGNOREPPC;
	if(!strcasecmp("AT_SECURE", str)) return AT_SECURE;
	if(!strcasecmp("AT_SYSINFO", str)) return AT_SYSINFO;
	if(!strcasecmp("AT_SYSINFO_EHDR", str)) return AT_SYSINFO_EHDR;
	if(!strcasecmp("AT_L1I_CACHESHAPE", str)) return AT_L1I_CACHESHAPE;
	if(!strcasecmp("AT_L1D_CACHESHAPE", str)) return AT_L1D_CACHESHAPE;
	if(!strcasecmp("AT_L2_CACHESHAPE", str)) return AT_L2_CACHESHAPE;
	if(!strcasecmp("AT_L3_CACHESHAPE", str)) return AT_L3_CACHESHAPE;

	return -1;
}

int main(int argc, char *argv[]){
	long i;
	ElfW(Addr) a_type;
	ElfW(Addr) a_val;
	
	if(argc == 1){
		printf("No arguments specified.\n\n");
		print_help();
		return 0;
	}
	
	for(i = 1; i < argc; i++){
		if(!strcasecmp("--help", argv[i]) || !strcasecmp("-help", argv[i])){
			print_help();
			return 0;
		}
		if(!strcasecmp("--info", argv[i]) || !strcasecmp("-info", argv[i])){
			print_info();
			return 0;
		}
		if(!strcasecmp("--list", argv[i]) || !strcasecmp("-list", argv[i])){
			print_list();
			return 0;
		}
		if(!strcasecmp("--hwcap", argv[i]) || !strcasecmp("-hwcap", argv[i])){
			print_hwcap();
			return 0;
		}

	}

	for(i = 1; i < argc; i++){
		a_type = translate_a_type(argv[i]);
		a_val = query_auxv(a_type);
#ifdef __powerpc64__
 		 printf("%lu\n", a_val);
#else
		printf("%u\n", a_val);
#endif
	}

	return 0;
}

