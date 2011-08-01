#! /bin/sh
for module in tfdocgen libticonv libtifiles libticables libticalcs gfm tilp; do
echo Updating "$module"
cd "$module/trunk"; rm m4/*.m4; autoreconf -f -i || exit 1; cd ../..
done
