#!/bin/bash

build_dir=cmake-build-tests-gcc-mingw-w32

set -e

mkdir -p "$build_dir"
cd ./$build_dir || exit 1

cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc-posix -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++-posix -S .. -B . &&
    make all --jobs "$(nproc)"

shopt -s nullglob
for test_executable in *.exe; do
    wine "$test_executable"
done
