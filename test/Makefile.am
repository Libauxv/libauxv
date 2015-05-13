# Define which check programs should be built
check_PROGRAMS =
if TEST_SHARED
check_PROGRAMS += test_auxv_shared test_auxv_fallback_shared
endif
if TEST_STATIC
check_PROGRAMS += test_auxv_static
endif

if TEST_SHARED
test_auxv_shared_SOURCES = test_auxv.c auxv_test.map
test_auxv_shared_DEPENDENCIES = libauxv_test.so
test_auxv_shared_CFLAGS = -I$(top_srcdir)/src
test_auxv_shared_LDADD = libauxv_test.so -lpthread
test_auxv_fallback_shared_SOURCES = test_auxv_fallback.c auxv_test.map
test_auxv_fallback_shared_DEPENDENCIES = libauxv_test.so
test_auxv_fallback_shared_CFLAGS = -I$(top_srcdir)/src
test_auxv_fallback_shared_LDADD = libauxv_test.so -lpthread
endif

if TEST_STATIC
test_auxv_static_SOURCES = test_auxv.c
test_auxv_static_DEPENDENCIES = libauxv_test.a
test_auxv_static_CFLAGS = -I$(top_srcdir)/src
test_auxv_static_LDADD = libauxv_test.a -lpthread
endif

auxv_test_shared.o: $(top_builddir)/src/.libs/auxv.o
	objcopy --globalize-symbol=__auxv_fallback $< $@

libauxv_test-1.0.0.so: auxv_test_shared.o
	@CC@ @CFLAGS@ -shared \
	-Wl,--version-script=$(top_srcdir)/test/auxv_test.map \
	-Wl,-soname,libauxv_test.so.1 \
	$< -o $@

libauxv_test.so.1: libauxv_test-1.0.0.so
	ln -f -s $< $@

libauxv_test.so: libauxv_test.so.1
	ln -f -s $< $@

auxv_test_static.o: $(top_builddir)/src/auxv.o
	cp $< $@

libauxv_test.a: $(top_builddir)/src/.libs/libauxv.a
	cp $< $@

.PHONY: test_auxv_shared.test
test_auxv_shared.test: test_auxv_shared
	$(top_srcdir)/test/$@

.PHONY: test_auxv_fallback_shared.test
test_auxv_fallback_shared.test: test_auxv_fallback_shared
	$(top_srcdir)/test/$@

.PHONY: test_auxv_static.test
test_auxv_static.test: test_auxv_static
	$(top_srcdir)/test/$@

.PHONY: clean-local
clean-local:
	rm -f libauxv_test-1.0.0.so \
	      libauxv_test.so.1 \
	      libauxv_test.so \
	      libauxv_test.a \
	      test_auxv_shared.out \
	      test_auxv_fallback_shared.out \
	      test_auxv_static.out

# Define which check programs should be executed
TESTS =
if TEST_SHARED
TESTS += test_auxv_shared.test test_auxv_fallback_shared.test
endif
if TEST_STATIC
TESTS += test_auxv_static.test
endif

EXTRA_DIST = $(TESTS)

