cmake_minimum_required (VERSION 2.8.11)
project (vu) #c-cpp)

# specify compiler
set(CMAKE_CXX_COMPILER g++)


# output executable in current directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the source files
#set(SOURCES
#    b.cpp
#)


#compile STATIC lib
# the implementation of the the function f in a.cpp is going to be
# compiled and put into the library libobergurgl.so.
# the naming is based on "lib" + name + ".so" from add_library( name ...)
add_library(obergurgl STATIC a.cpp)
# comment: the lib and .so or .a is added at compile time ...

add_executable(run b.cpp) 


target_link_libraries(run PRIVATE obergurgl)


# Add executable called "run" that is built from the source files
# and "b.cpp".

# As not all information is available, we need to link the
# executable to the created library
