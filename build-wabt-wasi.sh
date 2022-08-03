#!/usr/bin/env bash
set -e

# https://github.com/WebAssembly/wasi-sdk
WASI_SDK=${HOME}/wasm-toolchain/sysroot
# https://github.com/singlestore-labs/wasix
WASIX_DIR=${HOME}/wasm-toolchain/sysroot/wasix

export PATH=${WASI_SDK}/bin:$PATH
export CC="${WASI_SDK}/bin/clang"
export CXX="${WASI_SDK}/bin/clang++"
export LDSHARED="${WASI_SDK}/bin/wasm-ld"
export AR="${WASI_SDK}/bin/llvm-ar"
export RANLIB="${WASI_SDK}/bin/llvm-ranlib"

mkdir -p wasi/build

pushd wabt 
cmake -S . -B build/ \
   -DBUILD_TESTS=OFF \
   -DBUILD_LIBWASM=OFF

cmake --build build/ --parallel $(nproc)
popd

