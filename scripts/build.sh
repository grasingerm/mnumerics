#!/bin/bash

mkdir build
cd build
cmake ../test/ -D CMAKE_BUILD_TYPE=release
make