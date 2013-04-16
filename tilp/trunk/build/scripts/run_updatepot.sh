#! /bin/sh
cd tilibs/libtifiles/trunk/po; make libtifiles2.pot-update; make update-po; cd ../../../..
cd tilibs/libticables/trunk/po; make libticables2.pot-update; make update-po; cd ../../../..
cd tilibs/libticalcs/trunk/po; make libticalcs2.pot-update; make update-po; cd ../../../..
cd tilp_and_gfm/gfm/trunk/po; make gfm.pot-update; make update-po; cd ../../../..
cd tilp_and_gfm/tilp/trunk/po; intltool-update --pot; intltool-update fr; cd ../../../..
