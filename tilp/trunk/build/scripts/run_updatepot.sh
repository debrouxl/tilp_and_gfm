#! /bin/bash
# Use explicit /bin/bash, as some implementations of /bin/sh (not dash, though) don't like this script.
(cd tilibs/libtifiles/trunk/po; make libtifiles2.pot-update; make update-po; cd ../../../..) &
(cd tilibs/libticables/trunk/po; make libticables2.pot-update; make update-po; cd ../../../..) &
(cd tilibs/libticalcs/trunk/po; make libticalcs2.pot-update; make update-po; cd ../../../..) &
(cd tilp_and_gfm/gfm/trunk/po; make gfm.pot-update; make update-po; cd ../../../..) &
(cd tilp_and_gfm/tilp/trunk/po; intltool-update --pot; intltool-update fr; intltool-update de; cd ../../../..) &
#(exit 1) &
RETCODE=0
wait %1 || RETCODE=1
wait %2 || RETCODE=2
wait %3 || RETCODE=3
wait %4 || RETCODE=4
wait %5 || RETCODE=5
#wait %6 || RETCODE=6
#echo $RETCODE
exit $RETCODE
