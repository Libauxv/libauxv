
 - Miscellaneous changes
    - config.log: Delete file.
    - config.status: Delete file.
    - .gitignore: New file.

 - Miscellaneous changes
    - lsauxv.c (print\_hwcap): Add support to HWCAP2.
    - Makefile.in [test\_auxv\_shared]: Fix link order to include library
      at the end.
      [test\_auxv\_fallback\_shared]: Likewise.

 - Miscellaneous changes
    - configure: Regenerated for libauxv 0.1.0.
    - config.h.in: Likewise.

 - Miscellaneous changes
    - configure: Regenerated for version 0.1.0.
    - Makefile.in: Added static library build and testcase.
    - README: Added --enable-static.
    - configure.ac: Updated to version 0.1.0 and added RANLIB export.

 - Miscellaneous changes
    - man/auxv.3 (RATIONALE): Added new section with information from
      the README.

 - Miscellaneous changes
    - README: Updated sections on Dependencies, GNU/Linux OS, GLIBC
      Minimum Version, Configuration, Make Rules, and Use.
    - test\_auxv.c (main): 'long' variables changed to 'unsigned long int'.
      Updated printf of hwcap to print leading zeros based on sizeof
      unsigned long int.
    - man/auxv.3 (EXAMPLES): Add example code which shows how to use all of
      the interfaces.  Add additional information on auxv/hwcap.h.
      (RETURN VALUES): Added return value description from prefetch\_auxv().
      (SYNOPSIS): Added hwcap.h to synopsis.
      (DEPENDENCIES): Added information on libpthread dependency.
      (FILES): Added auxv/hwcap.h to the files list.

 - Miscellaneous changes
    - Makefile.in (install): Install lsauxv.1 into $(inst\_mandir)/man1/
      and auxv.3 into man3/ rather than $(inst\_mandir).  Create libauxv.3
      symlink to auxv.3.
      (uninstall): Remove $(inst\_mandir)/man1/lsauxv.1 and
      $(inst\_mandir)/man3/auxv.3.  Remove libauxv.3 symlink.
