#! /bin/bash
# Use explicit /bin/bash, as some implementations of /bin/sh (not dash, though) don't like this script.
(cd "tfdocgen/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilibs/libticonv/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilibs/libtifiles/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilibs/libticables/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilibs/libticalcs/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilibs/libtiopers/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilp_and_gfm/gfm/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
(cd "tilp_and_gfm/tilp/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd -) &
#(sleep 1; exit 1) &
RETCODE=0
wait %1 || RETCODE=1
wait %2 || RETCODE=2
wait %3 || RETCODE=3
wait %4 || RETCODE=4
wait %5 || RETCODE=5
wait %6 || RETCODE=6
wait %7 || RETCODE=7
wait %8 || RETCODE=8
#echo $RETCODE
exit $RETCODE
