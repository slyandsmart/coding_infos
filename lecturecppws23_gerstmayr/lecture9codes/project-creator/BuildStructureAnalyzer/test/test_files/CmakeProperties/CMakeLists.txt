
cmake_minimum_required( VERSION 3.5 )
project( test-Basic )

set( CMAKE_CXX_STANDARD 14 )

add_library( lib_a STATIC a.cpp )
add_library( lib_b SHARED b.cpp )

add_executable( exe_c c.cpp)
target_link_libraries( exe_c lib_a lib_b )
