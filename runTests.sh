#!/bin/bash

if [ ! -f build/engine_tests ]; then
  echo "Test binary not found."
  exit 1
fi

cd build
ctest --output-on-failure

echo "done