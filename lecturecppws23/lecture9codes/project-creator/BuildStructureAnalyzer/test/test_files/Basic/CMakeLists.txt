
cmake_minimum_required( VERSION 3.5 )
project( test-Basic )

set( CMAKE_CXX_STANDARD 17 )

include_directories( "/path/to/custom/libs" )

add_library( lib_a OBJECT a.cpp )
target_compile_options( lib_a PRIVATE "-fmax_error=5" )

add_library( lib_b OBJECT b.cpp )
target_compile_options( lib_b PUBLIC  "-O2" )

add_library( lib_ab ab.cpp )
target_link_libraries( lib_ab STATIC lib_a )
target_link_libraries( lib_ab SHARED lib_b )
target_compile_options( lib_ab PUBLIC  "-O3" )

add_executable( exec_foo SubFolder/foo.cpp)
target_compile_options( lib_ab PUBLIC  "-O1" )
target_link_libraries( exec_foo STATIC lib_a )
target_link_libraries( exec_foo STATIC lib_b )
