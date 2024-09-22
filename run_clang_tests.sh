#!/bin/bash

build_dir=cmake-build-tests-clang

set -e

if [ -d "$build_dir" ]; then rm -r "$build_dir"; fi
mkdir -p "$build_dir"
cp ./u64-primes.txt ./$build_dir/u64-primes.txt
cp ./u128-primes.txt ./$build_dir/u128-primes.txt
cd ./$build_dir || return 1

cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -S .. -B . &&
        make all --jobs "$(nproc)" &&
        env CTEST_OUTPUT_ON_FAILURE=1 make test
