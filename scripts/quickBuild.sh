#!/bin/bash

cmake -B build -S .   -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake   -DVCPKG_TARGET_TRIPLET=x64-linux   -DBUILD_TESTS=OFF

cmake --build build

ASSET_SRC_DIR="./assets"
ASSET_DST_DIR="./build/bin/assets"

if [[ -d "$ASSET_DST_DIR" ]]; then
    rm -rf "$ASSET_DST_DIR"
fi

cp -r "$ASSET_SRC_DIR" "$ASSET_DST_DIR"

cd ../..

cd build
ctest -C Debug --output-on-failure -V
cd ..
