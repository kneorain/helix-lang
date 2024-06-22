cmake_minimum_required(VERSION 3.14)
project(helix-lang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check if LLVM_DIR is provided; if not, prompt an error
if(NOT DEFINED ENV{LLVM_DIR})
    message(FATAL_ERROR "LLVM_DIR is not set. Please provide the path to the LLVM build directory.")
endif()

# Set LLVM paths
set(LLVM_DIR $ENV{LLVM_DIR})
set(LLVM_INCLUDE_DIR ${LLVM_DIR}/include)
set(LLVM_LIB_DIR ${LLVM_DIR}/lib)
set(LLVM_BIN_DIR ${LLVM_DIR}/bin)

include_directories(${LLVM_INCLUDE_DIR})
link_directories(${LLVM_LIB_DIR})

# Automatically include all .cc files in the source directory and its subdirectories
file(GLOB_RECURSE SOURCE_FILES "source/*.cc")

add_executable(helix ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(helix PRIVATE DEBUG)
    target_compile_options(helix PRIVATE -g -O0 -MDd)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
else()
    target_compile_definitions(helix PRIVATE NDEBUG)
    target_compile_options(helix PRIVATE -O3 -MD)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
endif()

if(APPLE)
    target_link_libraries(helix PRIVATE clang clang-cpp c++ c++abi)
else()
    target_link_libraries(helix PRIVATE clang clang-cpp libc++ libc++abi)
endif()

if(WIN32)
    target_compile_options(helix PRIVATE -stdlib=libc++ -I${LLVM_INCLUDE_DIR} -Xclang -nostdinc++)
    target_link_options(helix PRIVATE -stdlib=libc++ -L${LLVM_LIB_DIR} -lc++ -lc++abi)
    target_compile_definitions(helix PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(helix PRIVATE -stdlib=libc++ -fno-rtti -I${LLVM_INCLUDE_DIR})
    target_link_options(helix PRIVATE -stdlib=libc++ -L${LLVM_LIB_DIR} -lc++abi -Wl,-rpath,${LLVM_LIB_DIR})
endif()

find_program(LLVM_CONFIG llvm-config HINTS ${LLVM_BIN_DIR})

if(LLVM_CONFIG)
    execute_process(COMMAND ${LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDEDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${LLVM_CONFIG} --libdir OUTPUT_VARIABLE LLVM_LIBDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
    include_directories(BEFORE ${LLVM_INCLUDEDIR})
    link_directories(${LLVM_LIBDIR})
else()
    message(FATAL_ERROR "llvm-config not found!")
endif()
