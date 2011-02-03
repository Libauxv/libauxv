/* Hardware capability constants for the Auxiliary Vector Library  */

#ifndef _AUXV_HWCAP_H
#define _AUXV_HWCAP_H

#ifdef __powerpc__

/* Auxlliary Vector Hardware Capability (AT_HWCAP) features for PowerPC.   */

  #define PPC_FEATURE_32                  0x80000000 /* 32-bit mode.  */
  #define PPC_FEATURE_64                  0x40000000 /* 64-bit mode.  */
  #define PPC_FEATURE_601_INSTR           0x20000000 /* 601 chip, Old POWER ISA.  */
  #define PPC_FEATURE_HAS_ALTIVEC         0x10000000 /* SIMD/Vector Unit.  */
  #define PPC_FEATURE_HAS_FPU             0x08000000 /* Floating Point Unit.  */
  #define PPC_FEATURE_HAS_MMU             0x04000000 /* Memory Management Unit.  */
  #define PPC_FEATURE_HAS_4xxMAC          0x02000000 /* 4xx Multiply Accumulator.  */
  #define PPC_FEATURE_UNIFIED_CACHE       0x01000000 /* Unified I/D cache.  */
  #define PPC_FEATURE_HAS_SPE             0x00800000 /* Signal Processing ext.  */
  #define PPC_FEATURE_HAS_EFP_SINGLE      0x00400000 /* SPE Float.  */
  #define PPC_FEATURE_HAS_EFP_DOUBLE      0x00200000 /* SPE Double.  */
  #define PPC_FEATURE_NO_TB               0x00100000 /* 601/403gx have no timebase.  */
  #define PPC_FEATURE_POWER4              0x00080000 /* POWER4 ISA 2.01.  */
  #define PPC_FEATURE_POWER5              0x00040000 /* POWER5 ISA 2.02.  */
  #define PPC_FEATURE_POWER5_PLUS         0x00020000 /* POWER5+ ISA 2.03.  */
  #define PPC_FEATURE_CELL_BE             0x00010000 /* CELL Broadband Engine */
  #define PPC_FEATURE_BOOKE               0x00008000 /* ISA Embedded Category.  */
  #define PPC_FEATURE_SMT                 0x00004000 /* Simultaneous Multi-Threading.  */
  #define PPC_FEATURE_ICACHE_SNOOP        0x00002000
  #define PPC_FEATURE_ARCH_2_05           0x00001000 /* ISA 2.05.  */
  #define PPC_FEATURE_PA6T                0x00000800 /* PA Semi 6T Core.  */
  #define PPC_FEATURE_HAS_DFP             0x00000400 /* Decimal FP Unit.  */
  #define PPC_FEATURE_POWER6_EXT          0x00000200 /* P6 + mffgpr/mftgpr.  */
  #define PPC_FEATURE_ARCH_2_06           0x00000100 /* ISA 2.06.  */
  #define PPC_FEATURE_HAS_VSX             0x00000080 /* P7 Vector Scalar Extension.  */
  #define PPC_FEATURE_PSERIES_PERFMON_COMPAT \
					  0x00000040 /* Has ISA >= 2.05 PMU basic subset support.  */
  #define PPC_FEATURE_TRUE_LE             0x00000002 /* Processor in true Little Endian mode.  */
  #define PPC_FEATURE_PPC_LE              0x00000001 /* Processor emulates Little Endian Mode.  */

  #define PPC_FEATURE_970 (PPC_FEATURE_POWER4 | PPC_FEATURE_HAS_ALTIVEC)
  #define PPC_FEATURE_POWER7 (PPC_FEATURE_ARCH_2_06 | PPC_FEATURE_HAS_VSX)

#endif /* __powerpc__  */

#endif /* _AUXV_HWCAP_H  */
