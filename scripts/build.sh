#!/bin/bash

mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=release ../test/
make