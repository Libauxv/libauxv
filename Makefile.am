ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src man test
dist_doc_DATA = README COPYING.txt GFDLv1.3.txt ChangeLog.md

ChangeLog.md:
	$(am__cd) $(top_srcdir) && ./generate-changelog.sh \
	  > $(abs_top_builddir)/$@

.PHONY: clean-local
clean-local:
	rm -f ChangeLog.md
