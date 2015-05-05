# Man pages
dist_man1_MANS = lsauxv.1
dist_man3_MANS = auxv.3

.PHONY: install-data-hook
install-data-hook:
	ln -f -s auxv.3 $(DESTDIR)/$(mandir)/man3/libauxv.3

.PHONY: uninstall-local
uninstall-local:
	rm -f $(DESTDIR)/$(mandir)/man3/libauxv.3
