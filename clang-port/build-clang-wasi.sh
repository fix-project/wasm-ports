#!/usr/bin/env bash
set -e

# https://github.com/WebAssembly/wasi-sdk
WASI_SDK=${HOME}/wasm-toolchain/sysroot
# https://github.com/singlestore-labs/wasix
WASIX_DIR=${HOME}/wasm-toolchain/sysroot/wasix

INST=${HOME}/wasm-ports/sysroot

export PATH=${WASI_SDK}/bin:$PATH
export CC="${WASI_SDK}/bin/clang"
export LDSHARED="${WASI_SDK}/bin/wasm-ld"
export AR="${WASI_SDK}/bin/llvm-ar"

export CFLAGS="-I${WASIX_DIR}/include -I${WASI_SDK}/include -D_WASI_EMULATED_SIGNAL -D_WASI_EMULATED_MMAN"
export CXXFLAGS="-I${WASIX_DIR}/include -I${WASI_SDK}/include -D_WASI_EMULATED_SIGNAL -D_WASI_EMULATED_MMAN"
export LDFLAGS="-L${WASIX_DIR}/lib -lwasix -L${WASI_SDK}/lib -L${WASI_SDK}/lib/wasm32-wasi -lwasi-emulated-signal -lwasi-emulated-mman"

cd llvm-project 
cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=MinSizeRel -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=${INST} -DLLVM_TARGET_ARCH=x86_64 -DLLVM_DEFAULT_TARGET_TRIPLE=x86_64-pc-linux-gnu -DLLVM_TARGETS_TO_BUILD="X86" -DCMAKE_CROSSCOMPILING:BOOL=ON -DLLVM_ENABLE_THREADS:BOOL=OFF -DLLVM_TABLEGEN=${WASI_SDK}/bin/llvm-tblgen -DCLANG_TABLEGEN=${WASI_SDK}/bin/clang-tblgen -DLLVM_INCLUDE_TESTS:BOOL=OFF -DLLVM_INCLUDE_EXAMPLES:BOOL=OFF -DLLVM_INCLUDE_UTILS:BOOL=OFF -DLLVM_INCLUDE_BENCHMARKS:BOOL=OFF -DLIBCLANG_BUILD_STATIC:BOOL=ON
ninja -C build clangFrontend clangDriver clangSerialization clangParse clangCodeGen clangSema clangAnalysis clangEdit clangAST clangLex clangBasic
ninja -C build LLVMX86AsmParser LLVMX86CodeGen LLVMX86Desc LLVMX86Disassembler LLVMX86Info LLVMX86TargetMCA
ninja -C build lldELF LLVMWindowsManifest
