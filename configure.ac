#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.5)
AC_INIT(Timetabler, 0.4, r0ssar00 at gmail.com)
AC_CONFIG_SRCDIR([frontends/include/Frontend.h])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile])
AM_SANITY_CHECK
AC_PROG_INSTALL
AC_ARG_PROGRAM
VERSION=0.4
PACKAGE=Timetabler
AC_PROG_RANLIB
AM_INIT_AUTOMAKE($PACKAGE,$VERSION)
# Checks for programs.
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADER([pme.h],[],[AC_ERROR([pme.h not found.  Install libpmd])])
#AX_CXX_CHECK_LIB([pme], [PME::options])
# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.

AC_OUTPUT([
frontends/src/Makefile
libdatastore/src/Makefile
libtimetable/src/Makefile
./src/Makefile
])
