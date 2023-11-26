#!/bin/bash

cd tests

# Copy SRC to test
rm -rf src
mkdir src
cp ../src/DataCom.* src/

# Build and Run
rm -rf build/
cmake -B build
cd build
make
chmod +x main
./main
