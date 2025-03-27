Simple cpp 3d game engine (someday, maybe)

clang cmake glwf glad

cd build

cmake ..

cmake --build .

## Important

### Windows

Remove-Item -Recurse -Force .\build\ 

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build  

### Linux

rm -rf build/

cmake -B build -S .   -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake   -DVCPKG_TARGET_TRIPLET=x64-linux 

cmake --build build