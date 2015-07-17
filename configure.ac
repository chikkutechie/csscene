dnl Process this file with autoconf to produce a configure script.

AC_INIT(chikkooos, 1.0, chikkusoftwares@gmail.com)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/core/rshape.cpp)

AC_CANONICAL_TARGET

#
#AC_CACHE_CHECK([target architecture],[csscene_target_arch],
#[case $target in
#  i*86-*)      csscene_target_arch="x86" ;;
#  sparc*-*)    csscene_target_arch="Sparc" ;;
#  powerpc*-*)  csscene_target_arch="PowerPC" ;;
#  *)           csscene_target_arch="Unknown" ;;
#esac])
#
#if test "$csscene_target_arch" = "Unknown" ; then
#  AC_MSG_WARN([Configuring for an unknown target archicture])
#fi

#AC_SUBST(ARCH, $csscene_target_arch)
# Only 32bit as of now
AC_SUBST(ARCH, "x86")

AM_INIT_AUTOMAKE


AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

AC_ARG_ENABLE([log], [  --enable-log        enable the use log])
AS_IF([test "x$enable_log" = "xyes"], [
AC_DEFINE(RDEBUG)
])

AC_ARG_ENABLE([gltrace], [  --enable-gltrace        enable opengl error tracing])
AS_IF([test "x$enable_gltrace" = "xyes"], [
AC_DEFINE(RGLERRORTRACE)
])

AC_DEFINE(HAVE_BULLET)
AC_DEFINE(HAVE_BOX2D)
AC_DEFINE(HAVE_CHIPMUNK)

AC_C_CONST
AC_TYPE_SIZE_T

AC_HEADER_STDC
AC_CHECK_HEADERS(GL/glut.h GL/gl.h)

AC_OUTPUT(
          Makefile
          linux/Makefile
          linux/gles1/Makefile
          linux/gles2/Makefile
          viewer/linux/Makefile
          viewer/linux/gles1/Makefile
          viewer/linux/gles2/Makefile
          utest/linux/Makefile
          )

