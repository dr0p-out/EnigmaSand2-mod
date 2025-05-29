#!/bin/bash

CXX=clang++ cmake \
  -DCMAKE_EXE_LINKER_FLAGS='-fuse-ld=lld' \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  "$@"
