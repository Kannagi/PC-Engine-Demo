#!/bin/sh

echo '[objects]' > temp
echo $1.obj >> temp

wla-huc6280 -o $1.pcs $1.obj
wlalink -vr temp $1.pce

rm $1.obj
rm temp