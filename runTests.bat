@echo off

if not exist "build/bin/Debug/engine_tests.exe" (
    echo Test binary not found.
    exit /b 1
)

cd /d build
ctest -C Debug --output-on-failure
cd ..

echo done