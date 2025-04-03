@echo off

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows -DBUILD_TESTS=OFF

cmake --build build 

set ASSET_SRC=assets
set ASSET_DST=build\bin\Debug\assets

if exist "%ASSET_DST%" (
    echo Deleting old assets folder...
    rmdir /s /q "%ASSET_DST%"
)

xcopy /E /I /Y "%ASSET_SRC%" "%ASSET_DST%"