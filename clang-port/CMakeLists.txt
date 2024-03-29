cmake_minimum_required(VERSION 2.8.12)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0115 NEW)

project(clang-port)

include(etc/clang_format.cmake)

include_directories(${PROJECT_SOURCE_DIR}/llvm-project/clang/include)
include_directories(${PROJECT_SOURCE_DIR}/llvm-project/lld/include)
include_directories(${PROJECT_SOURCE_DIR}/llvm-project/llvm/include)
include_directories(${PROJECT_SOURCE_DIR}/llvm-project/build/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -mreference-types -Wold-style-cast -fno-exceptions   -Wall -Wextra -Wno-unused-parameter -Wpointer-arith -Wuninitialized -std=c++17")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Weverything -Werror -Wno-gnu-include-next -Wno-reserved-macro-identifier -Wno-reserved-identifier -Wno-unused-parameter -Wno-unreachable-code -Wno-unused-command-line-argument -Wno-unused-but-set-variable -Wno-c++98-compat -std=c17 -Os -target wasm32 -mreference-types")
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
