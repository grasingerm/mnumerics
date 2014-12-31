#!/bin/bash

scripts/build.sh

cp build/libmnumerics.so /usr/lib/
echo "libmnumerics.so installed in /usr/lib/"

for f in include/*.h
do
  cp $f /usr/include/
  echo "$f installed in /usr/include/"
done

rm -R build/
