#!/bin/bash

scripts/build.sh

for f in build/bin/test_*
do
  echo "Running test: $f"
  $f
done

cp build/libmnumerics.so /usr/lib/
echo "libmnumerics.so installed in /usr/lib/"

for f in include/*.h
do
  cp $f /usr/include/
  echo "$f installed in /usr/include/"
done

rm -R build/
