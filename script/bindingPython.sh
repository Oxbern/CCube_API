#!/bin/bash

cd ../build
cmake .. && make
cd ../src/
rm -rf build
python3.5 setup.py build
cp ../build/src/libcube.so build/lib.linux-x86_64-3.5/libcube.so
cd build/lib.linux-x86_64-3.5/
python3.5

