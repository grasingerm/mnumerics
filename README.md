mnumerics
=========

Minimal numerics and containers for c

build
--------

to build manually,

    cd /path/to/mnumerics_root
    mkdir build
    cd build
    cmake ../test/ -D CMAKE_BUILD_TYPE=release
    make

or on linux systems, a bash script is provided for easy build, test, and install

    cd /path/to/mnumerics_root
    sudo scripts/build_test_install_clean.sh

example
--------

An example of the api can be found in the test directory
https://github.com/grasingerm/mnumerics/blob/master/test/mnm_ex.c