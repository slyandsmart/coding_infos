cmake_minimum_required (VERSION 2.8.11)
# project (vu c-cpp) # when adding c-cpp to the project name the compiler does not work
project(vu)

# specify compiler
set(CMAKE_CXX_COMPILER g++)


# output executable in current directory; here a sub-directory as e.g. /build could be used too
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the source files
set(SOURCES
    a.cpp
    b.cpp
)

# Create the executable called "run" that is built from the source files
# "a.cpp" and "b.cpp".
add_executable(run ${SOURCES})
