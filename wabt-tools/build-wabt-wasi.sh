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

export CFLAGS="-I${WASIX_DIR}/include -I${WASI_SDK}/include -D_WASI_EMULATED_SIGNAL -D_WASI_EMULATED_MMAN"
export CXXFLAGS="-I${WASIX_DIR}/include -I${WASI_SDK}/include -D_WASI_EMULATED_SIGNAL -D_WASI_EMULATED_MMAN"
export LDFLAGS="-L${WASIX_DIR}/lib -lwasix -L${WASI_SDK}/lib -L${WASI_SDK}/lib/wasm32-wasi -lwasi-emulated-signal -lwasi-emulated-mman -z stack-size=1048576"

mkdir -p wabt/build 
cp wabt-cmake/CMakeLists.txt wabt/CMakeLists.txt

cmake -S . -B build/ \
   -DBUILD_TESTS=OFF \
   -DBUILD_LIBWASM=OFF \
   -DCMAKE_BUILD_TYPE=Release

cmake --build build/ --parallel $(nproc)
