#!/bin/bash

cd ./build/bin/Debug || exit

for f in *.glsl; do
    if [[ -f "$f" ]]; then
        rm "$f"
        echo "deleted previous shader: $f"
    fi
done

cd ../../..

cd ./src/shaders || exit

for f in *.glsl; do
    if [[ -f "$f" ]]; then
        cp "$f" ../../build/bin/Debug/
        echo "copied new shader: $f"
    fi
done
