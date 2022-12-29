add_link_options(-nostdlib -Wl,--no-entry -Wl,--allow-undefined)

add_library(wasm2c-simple-obj OBJECT "wasm2c-simple.cc" "wasminspector.cc" "initcomposer.cc")
target_link_libraries(wasm2c-simple-obj wabt)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target wasm32")

add_custom_command(
  OUTPUT  "wasm2c-simple-no-asm.wasm"
  DEPENDS wasm2c-simple-obj 
          wasm2c-simple.cc
          wasminspector.cc
          wasm2c
  COMMAND $ENV{HOME}/wasm-toolchain/sysroot/bin/wasm-ld
          ${CMAKE_BINARY_DIR}/src/CMakeFiles/wasm2c-simple-obj.dir/wasm2c-simple.cc.o
          ${CMAKE_BINARY_DIR}/src/CMakeFiles/wasm2c-simple-obj.dir/wasminspector.cc.o
          ${CMAKE_BINARY_DIR}/src/CMakeFiles/wasm2c-simple-obj.dir/initcomposer.cc.o
          ${CMAKE_BINARY_DIR}/wabt/libwabt.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++abi.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc.a
          -o wasm2c-simple-no-asm.wasm
          --no-entry
          --allow-undefined
          -z stack-size=1048576
)

add_custom_command(
  OUTPUT "asm.wasm"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/asm.wat
  COMMAND $ENV{HOME}/wasm-toolchain/wabt/build/wat2wasm
          --enable-multi-memory
	        --enable-exceptions
          ${CMAKE_CURRENT_SOURCE_DIR}/asm.wat
          -o asm.wasm
)

add_custom_command(
  OUTPUT "wasisnapshot.wasm"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/wasisnapshot.wat
  COMMAND $ENV{HOME}/wasm-toolchain/wabt/build/wat2wasm
          ${CMAKE_CURRENT_SOURCE_DIR}/wasisnapshot.wat
          -o wasisnapshot.wasm
)

add_custom_command(
  OUTPUT "wasm2c-simple-no-wasi.wasm"
  DEPENDS asm.wasm
          wasm2c-simple-no-asm.wasm
  COMMAND $ENV{HOME}/wasm-toolchain/wasm-tools/build/src/module-combiner/wasmlink
          --enable-multi-memory
	        --enable-exceptions
          wasm2c-simple-no-asm.wasm
          asm.wasm
          -m wasm2c
          -o wasm2c-simple-no-wasi.wasm
)

add_custom_command(
  OUTPUT "wasm2c-simple.wasm"
  DEPENDS wasisnapshot.wasm
          wasm2c-simple-no-wasi.wasm
  COMMAND $ENV{HOME}/wasm-toolchain/wasm-tools/build/src/module-combiner/wasmlink
          --enable-multi-memory
	        --enable-exceptions
          wasm2c-simple-no-wasi.wasm
          wasisnapshot.wasm
          -m wasm2c
          -n wasi_snapshot_preview1
          -o wasm2c-simple.wasm
)

add_custom_target(
  wasm2c-simple ALL
  DEPENDS wasm2c-simple.wasm
)
