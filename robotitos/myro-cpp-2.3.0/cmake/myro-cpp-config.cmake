#!/bin/sh 

MAJOR_VERSION=@MYRO_PKG_VER_MAJOR@
MINOR_VERSION=@MYRO_PKG_VER_MINOR@
PATCH_VERSION=@MYRO_PKG_VER_PATCH@
VERSION="$MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION"

selfdir=`dirname $0`

prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
exec_prefix_set=no
bindir=${exec_prefix}/bin
includedir=${prefix}/include/Myro-Cpp
libdir=${exec_prefix}/lib

LDLIBS="-lmyro-cpp"

usage ()
{
    echo "Usage: myro-cpp-config [OPTIONS]
Options:
	[--version]

Options telling what information we request:
	[--cflags]        return flags to compile
	[--libs]          return myro-cpp libraries full path for dependencies
"
    exit $1
}

if test $# -eq 0; then
    usage 1
fi

while test $# -gt 0 
do
    case "$1" in
	-*=*) 
	    optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'`
	    ;;
	*)
	    optarg=
	    ;;
    esac

    case $1 in
	--version)
	    echo $VERSION
	    ;;
	--cflags)
	    echo_cflags=yes
	    ;;
	--libs)
	    echo_libs=yes
	    ;;
	*)
	    echo_help=yes
	    ;;
    esac
    shift
done

if test "$echo_help" = "yes" ; then
    usage 1
fi

if test "$includedir" != /usr/include; then
    includes="-I$includedir"
else
    includes=
fi

if test "$libdir" != /usr/lib -a "$libdir" != /usr/lib32; then
    libs="-L$libdir"
else
    libs=
fi

to_echo=""

if test "$echo_cflags" = "yes" ; then 
    to_echo="$includes"
fi

if test "$echo_libs" = "yes" ; then 
    to_echo="$to_echo $libs $LDLIBS"
fi

echo $to_echo
