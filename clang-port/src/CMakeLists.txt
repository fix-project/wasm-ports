add_link_options(-nostdlib -Wl,--no-entry -Wl,--allow-undefined)

add_library(clang-fix-obj OBJECT "clang-fix.cc")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target wasm32")

add_custom_command(
  OUTPUT "clang-fix-no-asm.wasm"
  DEPENDS clang-fix-obj
          clang-fix.cc
  COMMAND $ENV{HOME}/wasm-toolchain/sysroot/bin/wasm-ld
          ${CMAKE_BINARY_DIR}/src/CMakeFiles/clang-fix-obj.dir/clang-fix.cc.o
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangFrontend.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangDriver.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangSerialization.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangParse.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangCodeGen.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangSema.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangAnalysis.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangEdit.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangAST.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangLex.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangBasic.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++abi.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc.a
          -o clang-fix-no-asm.wasm
          --no-entry
          --allow-undefined
)

add_custom_target(
  clang-fix ALL
  DEPENDS clang-fix-no-asm.wasm
)
