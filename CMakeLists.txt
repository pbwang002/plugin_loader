CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_STANDARD 11)
set(ENV_TYPE "APPLE")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

project(LibLoad)
message("++++++++++++++++${CMAKE_SOURCE_DIR}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/test.lds")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(environment)

add_library(load_lib_obj OBJECT)
add_subdirectory(plugin_loader)
add_subdirectory(plugin_manager)
add_subdirectory(plugins)

add_library(load_lib SHARED)
target_link_libraries(load_lib PRIVATE load_lib_obj dl)

if (FALSE) 
    add_subdirectory(third_party)
endif()
#set(EXTRA_LINK "-Wl,-T${CMAKE_LDS_DIR}/test.lds")
add_executable(run_test main.cpp)
target_link_libraries(run_test PRIVATE ${EXTRA_LINK} load_lib add)

