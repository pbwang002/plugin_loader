CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
project(test_version)
# 1分版本测试
#add_subdirectory(v1)
#add_subdirectory(v2)

# 2:合并测试
# set(CMAKE_LDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
# set (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--version-script=${CMAKE_LDS_DIR}b.lds")
# add_library(b SHARED b.c)
# target_compile_options(b PRIVATE -fPIC)
add_library(c1 SHARED c1.c)
target_link_libraries(c1 PRIVATE ${CMAKE_BINARY_DIR}/v1/libb.so)
target_compile_options(c1 PRIVATE -fPIC)

add_library(c2 SHARED c2.c)
target_link_libraries(c2 PRIVATE ${CMAKE_BINARY_DIR}/v1/libb.so)
target_compile_options(c2 PRIVATE -fPIC)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE c1 c2)