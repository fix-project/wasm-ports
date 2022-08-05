#!/usr/bin/env bash
set -e

mkdir -p cpython/builddir/build
pushd cpython/builddir/build
../../configure -C
make -j$(nproc)
popd

# https://github.com/WebAssembly/wasi-sdk
WASI_SDK=${HOME}/wasm-toolchain/sysroot
# https://github.com/singlestore-labs/wasix
WASIX_DIR=${HOME}/wasm-toolchain/sysroot/wasix

export PATH=${WASI_SDK}/bin:$PATH
export CC="${WASI_SDK}/bin/clang"
export LDSHARED="${WASI_SDK}/bin/wasm-ld"
export AR="${WASI_SDK}/bin/llvm-ar"

# copy in third-party libraries
cp -r lib/* ${WASI_SDK}/lib/
cp -r include/* ${WASI_SDK}/include/

export CFLAGS="-isystem ${WASIX_DIR}/include -I${WASI_SDK}/include -Wno-error=int-conversion"
export LDFLAGS="-L${WASIX_DIR}/lib -lwasix -L${WASI_SDK}/lib"

mkdir -p cpython/builddir/wasi

pushd cpython/builddir/wasi
CONFIG_SITE=../../Tools/wasm/config.site-wasm32-wasi \
  ../../configure -C \
    --host=wasm32-unknown-wasi \
    --build=$(../../config.guess) \
    --with-build-python=$(pwd)/../build/python \
    --disable-ipv6

make -j$(nproc)
popd

# sentinel for getpath.py
touch cpython/Modules/Setup.local
