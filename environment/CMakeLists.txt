add_library(environment_obj OBJECT)

# if(${ENV_TYPE} STREQUAL "APPLE")
#     add_subdirectory(apple)
# endif()
add_subdirectory(apple)

add_library(environment SHARED)
target_link_libraries(environment PRIVATE environment_obj)
target_compile_options(environment PRIVATE -fPIC)
