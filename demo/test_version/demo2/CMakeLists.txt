add_library(test_obj OBJECT)
file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_sources(test_obj PRIVATE ${SRC_LIST})

add_library(test SHARED)
target_link_libraries(test PRIVATE test_obj)
target_compile_options(test PRIVATE -fPIC -Wl,--version-script libx-1.map)


add_library(test2_obj OBJECT)
file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_sources(test2_obj PRIVATE ${SRC_LIST})

add_library(test SHARED)
target_link_libraries(test PRIVATE test2_obj)
target_compile_options(test PRIVATE -fPIC -Wl,--version-script libx-1.map)