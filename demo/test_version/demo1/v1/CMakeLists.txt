set(CMAKE_LDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--version-script=${CMAKE_LDS_DIR}b.lds")
add_library(b SHARED b.c)
target_compile_options(b PRIVATE -fPIC)