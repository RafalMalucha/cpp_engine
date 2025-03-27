#!/bin/bash

cmake -B build -S .   -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake   -DVCPKG_TARGET_TRIPLET=x64-linux 

cmake --build build

cd ./build/bin || exit

for f in *.glsl; do
    if [[ -f "$f" ]]; then
        rm "$f"
        echo "deleted previous shader: $f"
    fi
done

cd ../..

cd ./src/shaders || exit

for f in *.glsl; do
    if [[ -f "$f" ]]; then
        cp "$f" ../../build/bin/
        echo "copied new shader: $f"
    fi
done
