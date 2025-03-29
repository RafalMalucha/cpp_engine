@echo off

echo Deleting previous build...
if exist build (
    rmdir /s /q build
    echo Build folder deleted.
) else (
    echo Build folder does not exist.
)

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -DBUILD_TESTS=ON

cmake --build build 

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

cd ../..

cd /d build
ctest -C Debug --output-on-failure -V
cd ..