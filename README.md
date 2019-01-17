# Bloom Filter
[![Build Status](https://travis-ci.com/rdtscp/bloom_filter.svg?branch=master)](https://travis-ci.com/rdtscp/bloom_filter)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

Bloom Filter implementation in C++. Built using CMake and Google Test. 

# Download
```
git clone https://github.com/acwilson96/bloom_filter
cd bloom_filter
```
The following should be run from within the "bloom_filter" directory.
# Release Install
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make install
cd ..
```
# Debug Install & Run Unit Tests
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make install
ctest -V
cd ..
```
# Uninstall
```
cd build
xargs rm < install_manifest.txt
cd ..
rm -rf ./build/
```
