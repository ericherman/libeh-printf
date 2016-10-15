lib_LTLIBRARIES=libeh-printf.la
libeh_printf_la_SOURCES=src/eh-printf.c

include_HEADERS=src/eh-printf.h

TESTS=$(check_PROGRAMS)
check_PROGRAMS=\
 test-simple

test_simple_SOURCES=tests/test-simple.c src/eh-printf.h

test_simple_LDADD=libeh-printf.la -lecheck

ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=misc

AM_CFLAGS=-std=c89 -O3 -ggdb -Wall -Wextra -Wpedantic -Werror

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
	libtool --mode=execute valgrind ./test-simple
