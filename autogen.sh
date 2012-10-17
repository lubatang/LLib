#!/bin/sh
#                     The MCLinker project
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.

my_uname=`uname`

if [ ${my_uname} = "Darwin" ]; then
  LIBTOOLIZE=glibtoolize
fi
root=`dirname $0`
cd $root

aclocal
automake --add-missing
autoconf
