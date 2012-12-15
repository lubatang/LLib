################################################
# Copyright (C) 2012-
# Luba Tang <lubatang@gmail.com>
####################
#  Autoconf/Automake Initialization

dnl AC_INIT(PKG_NAME, BUILD_VERSION, BUG_REPORTER)
AC_INIT([LViewer],[9562814],[lubatang@gmail.com])
AC_PREREQ(2.59)

AC_CONFIG_AUX_DIR([scripts])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9 dist-bzip2 foreign])

####################
#  Languages
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
LT_INIT

####################
# Check for header files
AC_CHECK_HEADERS([dlfcn.h fcntl.h])
AC_CHECK_HEADERS([malloc.h setjmp.h signal.h stdint.h termios.h unistd.h])
AC_CHECK_HEADERS([utime.h windows.h])
AC_CHECK_HEADERS([sys/mman.h sys/param.h sys/resource.h sys/time.h sys/uio.h])
AC_CHECK_HEADERS([sys/types.h sys/ioctl.h malloc/malloc.h mach/mach.h])

####################
# OUTPUT
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([debug/Makefile])
AC_CONFIG_FILES([utils/Makefile])
AC_CONFIG_FILES([utils/gtest/Makefile])
AC_CONFIG_FILES([utils/gtest/obj/Makefile])

AC_OUTPUT
