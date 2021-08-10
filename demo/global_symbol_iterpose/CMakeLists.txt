CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(global_symbol_iterpose)

add_library(a1 SHARED a1.cpp)
target_compile_options(a1 PRIVATE -fPIC)

add_library(a2 SHARED a2.cpp)
target_compile_options(a2 PRIVATE -fPIC)

add_library(b1 SHARED b1.cpp)
target_compile_options(b1 PRIVATE -fPIC)
target_link_libraries(b1 PRIVATE a1)

add_library(b2 SHARED b2.cpp)
target_compile_options(b2 PRIVATE -fPIC)
target_link_libraries(b2 PRIVATE a2)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE b1 b2)