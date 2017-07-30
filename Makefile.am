lib_LTLIBRARIES=libeh-printf.la
libeh_printf_la_SOURCES=\
 config.h \
 src/eh-printf.h \
 src/eh-printf.c \
 src/eh-printf-private.h \
 src/eh-printf-parse-float.h \
 src/eh-printf-parse-float.c \
 src/eh-printf-sys-context.h \
 src/eh-printf-sys-context-linux.c

include_HEADERS=src/eh-printf.h

C_STD=-std=gnu89

AM_CFLAGS=$(C_STD) -pipe -O2 -fomit-frame-pointer -ggdb \
 -Wall -Wextra -Wpedantic -Werror -Wno-long-long -I./src

TESTS=$(check_PROGRAMS)
check_PROGRAMS=\
 test-hex-int \
 test-negative \
 test-pct5d \
 test-unsigned \
 test-str \
 test-floats \
 test-misc \
 test-linux-write \
 test-linux-print \
 test-linux-fprintf \
 test-parse-float \
 test-simple

T_COMMON_LDADD=libeh-printf.la
T_COMMON_SRC=$(include_HEADERS) tests/eh-printf-tests.h

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

test_floats_SOURCES=tests/test-floats.c $(T_COMMON_SRC)
test_floats_LDADD=$(T_COMMON_LDADD) -lm

test_misc_SOURCES=tests/test-misc.c $(T_COMMON_SRC)
test_misc_LDADD=$(T_COMMON_LDADD)

test_str_SOURCES=tests/test-str.c $(T_COMMON_SRC)
test_str_LDADD=$(T_COMMON_LDADD)

test_parse_float_SOURCES=src/eh-parse-float.h tests/test-parse-float.c \
 $(T_COMMON_SRC)
test_parse_float_LDADD=$(T_COMMON_LDADD)

test_linux_fprintf_SOURCES=tests/test-linux-fprintf.c $(T_COMMON_SRC)
test_linux_fprintf_LDADD=$(T_COMMON_LDADD)
test_linux_fprintf_CFLAGS=$(AM_CFLAGS) -std=gnu89

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
		-T uint8_t \
		-T uint16_t \
		-T uint64_t \
		-T int8_t \
		-T int16_t \
		-T eh_printf_context_s \
		`find src tests -name '*.h' -o -name '*.c' -o -name '*.cpp'`
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
	libtool --mode=execute valgrind -q ./test-floats
	libtool --mode=execute valgrind -q ./test-misc
	libtool --mode=execute valgrind -q ./test-parse-float
	libtool --mode=execute valgrind -q ./test-linux-write
	libtool --mode=execute valgrind -q ./test-linux-print
	libtool --mode=execute valgrind -q ./test-linux-fprintf
