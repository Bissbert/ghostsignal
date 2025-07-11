AC_PREREQ([2.69])
AC_INIT([ghostsignal], [1.0], [your-email@example.com])
AC_CONFIG_SRCDIR([src/ghostsignal.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC

# Add this line to tell autoheader what to include
AH_TOP([#ifndef CONFIG_H
#define CONFIG_H])
AH_BOTTOM([#endif // CONFIG_H])


# Checks for libraries.
PKG_CHECK_MODULES([X11], [x11])
PKG_CHECK_MODULES([XSS], [xscrnsaver])
PKG_CHECK_MODULES([GL], [gl])
PKG_CHECK_MODULES([GLU], [glu])

# AC_CHECK_LIB([png], [png_create_read_struct], [], [AC_MSG_ERROR([libpng is required.])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
