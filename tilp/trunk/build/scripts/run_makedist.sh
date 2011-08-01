#! /bin/sh
for module in tfdocgen libticonv libtifiles libticables libticalcs gfm tilp; do
echo Updating "$module"
cd "$module/trunk"; make dist || exit 1; cd ../..
done
