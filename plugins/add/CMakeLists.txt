add_library(add_obj OBJECT)
file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(add_obj PRIVATE ${SRC_LIST})

add_library(add SHARED)
target_link_libraries(add PRIVATE add_obj)