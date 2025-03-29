#!/bin/bash

cd build
ctest -C Debug --output-on-failure -V
cd ..