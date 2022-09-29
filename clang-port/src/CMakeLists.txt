add_link_options(-nostdlib -Wl,--no-entry -Wl,--allow-undefined)

add_library(clang-fix-obj OBJECT "clang-fix.cc")
add_library(stub-obj OBJECT "stubs.c")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target wasm32")

add_custom_command(
  OUTPUT "clang-fix-no-asm.wasm"
  DEPENDS clang-fix-obj
          clang-fix.cc
          stub-obj
          stubs.c
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
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libclangSupport.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMAggressiveInstCombine.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMAnalysis.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMAsmParser.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMAsmPrinter.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMBinaryFormat.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMBitReader.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMBitWriter.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMBitstreamReader.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMCFGuard.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMCodeGen.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMCore.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMCoroutines.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMCoverage.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMDebugInfoCodeView.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMDebugInfoDWARF.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMDebugInfoMSF.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMDebugInfoPDB.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMDemangle.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMExtensions.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMFrontendOpenMP.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMGlobalISel.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMIRReader.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMInstCombine.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMInstrumentation.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMLTO.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMLinker.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMMC.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMMCA.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMMCDisassembler.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMMCParser.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMObjCARCOpts.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMObject.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMOption.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMPasses.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMProfileData.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMRemarks.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMScalarOpts.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMSelectionDAG.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMSupport.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMSymbolize.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMTarget.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMTextAPI.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMTransformUtils.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMVectorize.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMWindowsDriver.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86AsmParser.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86CodeGen.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86Desc.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86Disassembler.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86Info.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMX86TargetMCA.a
          ${CMAKE_BINARY_DIR}/../llvm-project/build/lib/libLLVMipo.a
          ${CMAKE_BINARY_DIR}/src/CMakeFiles/stub-obj.dir/stubs.c.o
          $ENV{HOME}/wasm-toolchain/sysroot/wasix/lib/libwasix.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libwasi-emulated-signal.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libwasi-emulated-mman.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc++abi.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/wasm32-wasi/libc.a
          $ENV{HOME}/wasm-toolchain/sysroot/lib/clang/16.0.0/lib/wasi/libclang_rt.builtins-wasm32.a
          -o clang-fix-no-asm.wasm
          --no-entry
          --allow-undefined
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
  OUTPUT "clang-fix-no-wasi.wasm"
  DEPENDS asm.wasm
          clang-fix-no-asm.wasm
  COMMAND $ENV{HOME}/wasm-toolchain/wasm-tools/build/src/module-combiner/wasmlink
          --enable-multi-memory
	        --enable-exceptions
          clang-fix-no-asm.wasm
          asm.wasm
          -m clang 
          -o clang-fix-no-wasi.wasm
)

add_custom_target(
  clang-fix ALL
  DEPENDS clang-fix-no-wasi.wasm
)
