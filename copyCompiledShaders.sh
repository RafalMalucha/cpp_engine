#!/bin/bash

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
