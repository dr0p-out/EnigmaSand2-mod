#!/bin/bash

pacman -Q binutils gcc gcc-libs gdb \
  base-devel make pkgconf cmake \
  llvm clang compiler-rt lld \
  sdl12-compat sdl_ttf

CXX=clang++ cmake \
  -DCMAKE_EXE_LINKER_FLAGS='-fuse-ld=lld' \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  "$@"
