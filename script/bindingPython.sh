#!/bin/bash

cd ../build
cmake .. && make -j8
cd ../src/
rm -rf build
python3.5 setup.py build
cp ../build/src/libcube.so build/lib.linux-x86_64-3.5/libcube.so
cp ../build/src/libcube.so libcube.so
cd build/lib.linux-x86_64-3.5/
python3.5

