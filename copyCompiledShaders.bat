@echo off

cd ./build/bin/Debug

for %%f in (*.glsl) do (
    del %%f
    echo deleted previous shader: %%f
)

cd ../../..

cd ./src/shaders

for %%f in (*.glsl) do (
    copy %%f ..\..\build\bin\Debug
    echo copied new shader: %%f
)