add_library(wasm2c-simple-obj OBJECT "wasm2c-simple.cc" "wasminspector.cc")
target_link_libraries(wasm2c-simple-obj wabt)
