#! /bin/sh
cd libtifiles/trunk/po; make libtifiles2.pot-update; make update-po; cd ../../..
cd libticables/trunk/po; make libticables2.pot-update; make update-po; cd ../../..
cd libticalcs/trunk/po; make libticalcs2.pot-update; make update-po; cd ../../..
cd gfm/trunk/po; make gfm.pot-update; make update-po; cd ../../..
cd tilp/trunk/po; intltool-update --pot; intltool-update fr; cd ../../..
