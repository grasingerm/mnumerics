#!/bin/bash

scripts/build.sh

for f in build/bin/test_*
do
  echo "Running test: $f"
  $f
done

rm -R build/
