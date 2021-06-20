file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(load_lib_obj PRIVATE ${SRC_LIST})