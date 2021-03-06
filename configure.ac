#                                               -*- Autoconf -*-
# SPDX-License-Identifier: LGPL-2.1-or-later
# configure.ac
# Copyright (C) 2016, 2019 Eric Herman
# https://github.com/ericherman/libeh-printf

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libeh-printf], [1.0.1], [eric@freesa.org])
AC_CONFIG_SRCDIR([src/eh-printf.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([\
errno.h \
float.h \
limits.h \
stdarg.h \
stddef.h \
stdint.h \
stdio.h \
string.h \
])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T

# Checks for library functions.
AC_CHECK_FUNCS([sqrt fileno memcpy fprintf])

AM_INIT_AUTOMAKE([subdir-objects -Werror -Wall])
AM_PROG_AR
LT_INIT

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
