lib_LTLIBRARIES=libeh-printf.la
libeh_printf_la_SOURCES=src/eh-printf.c src/eh-sys-context-linux.c

include_HEADERS=src/eh-printf.h src/eh-sys-context.h

AM_CFLAGS=-std=c89 -O2 -ggdb -Wall -Wextra -Wpedantic -Werror

TESTS=$(check_PROGRAMS)
check_PROGRAMS=\
 test-hex-int \
 test-negative \
 test-pct5d \
 test-unsigned \
 test-str \
 test-linux-write \
 test-linux-print \
 test-simple

T_COMMON_LDADD=libeh-printf.la
T_COMMON_SRC=src/eh-printf.h tests/eh-printf-tests.h

test_simple_SOURCES=tests/test-simple.c $(T_COMMON_SRC)
test_simple_LDADD=$(T_COMMON_LDADD)

test_hex_int_SOURCES=tests/test-hex-int.c $(T_COMMON_SRC)
test_hex_int_LDADD=$(T_COMMON_LDADD)

test_negative_SOURCES=tests/test-negative.c $(T_COMMON_SRC)
test_negative_LDADD=$(T_COMMON_LDADD)

test_pct5d_SOURCES=tests/test-pct5d.c $(T_COMMON_SRC)
test_pct5d_LDADD=$(T_COMMON_LDADD)

test_unsigned_SOURCES=tests/test-unsigned.c $(T_COMMON_SRC)
test_unsigned_LDADD=$(T_COMMON_LDADD)

test_str_SOURCES=tests/test-str.c $(T_COMMON_SRC)
test_str_LDADD=$(T_COMMON_LDADD)

test_linux_write_SOURCES=tests/test-linux-write.c $(T_COMMON_SRC)
test_linux_write_LDADD=$(T_COMMON_LDADD)
test_linux_write_CFLAGS=$(AM_CFLAGS) -std=gnu89

test_linux_print_SOURCES=tests/test-linux-print.c $(T_COMMON_SRC)
test_linux_print_LDADD=$(T_COMMON_LDADD)
test_linux_print_CFLAGS=$(AM_CFLAGS) -std=gnu89

ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=misc


# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

tidy:
	patch -Np1 -i misc/pre-tidy.patch
	$(LINDENT) \
		-T FILE \
		-T size_t \
		`find src tests -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch

spotless: clean
	rm -rf `cat .gitignore | sed -e 's/#.*//'`
	pushd src && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd
	pushd tests && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd

valgrind: $(check_PROGRAMS)
	libtool --mode=execute valgrind -q ./test-simple
	libtool --mode=execute valgrind -q ./test-hex-int
	libtool --mode=execute valgrind -q ./test-negative
	libtool --mode=execute valgrind -q ./test-pct5d
	libtool --mode=execute valgrind -q ./test-unsigned
	libtool --mode=execute valgrind -q ./test-str
	libtool --mode=execute valgrind -q ./test-linux-write
	libtool --mode=execute valgrind -q ./test-linux-print
