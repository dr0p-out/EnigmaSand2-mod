#!/bin/bash

PKG_CONFIG='i686-pc-linux-gnu-pkg-config' CXX=clang++ cmake \
  -DCMAKE_CXX_FLAGS:STRING='-m32' \
  -DCMAKE_EXE_LINKER_FLAGS='-fuse-ld=lld' \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  "$@"
