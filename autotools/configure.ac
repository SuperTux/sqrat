AC_INIT(sqrat, [0.8.93])
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE


AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_CC_C_O

AC_DEFINE(_GNU_SOURCE, 1)

AC_CHECK_SIZEOF([void *])

if test "$ac_cv_sizeof_void_p" -eq 8
then 
    AC_DEFINE(_SQ64, 1)
    CFLAGS="$CFLAGS -m64"
    CXXFLAGS="$CXXFLAGS -m64"
fi


AC_SYS_LARGEFILE

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN],
[test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])

AC_CONFIG_FILES(Makefile)

AC_OUTPUT
