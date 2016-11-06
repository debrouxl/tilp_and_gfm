#! /bin/sh
for module in tfdocgen tilibs/libticonv tilibs/libtifiles tilibs/libticables tilibs/libticalcs tilibs/libtiopers tilp_and_gfm/gfm tilp_and_gfm/tilp; do
echo Updating "$module"
cd "$module/trunk"; make install || exit 1; cd -
done
