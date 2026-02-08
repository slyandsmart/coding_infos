cmake_minimum_required(VERSION 3.10)
project(my_project)

set(CMAKE_CXX_STANDARD 11)

# include header directory
include_directories(
    "include"
)


# Add the library target and specify the source file
add_library(my_code_lib STATIC src/my_code.cpp)
target_include_directories(my_code_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# Add the executable target and specify the source file
add_executable(main 
        src/main.cpp 
)


target_link_libraries(main PRIVATE my_code_lib)


# Info to the keywords
# add_library: This command creates a library target. In this case, 
#           we create a static library named my_code_lib from the source file my_code.cpp.
# target_include_directories: This command specifies the include directories for the library target. 
#           We set it to PUBLIC, which means that any target that links against my_code_lib will 
#           also have access to the include directories specified here.
# add_executable: This command creates an executable target. We create an executable named main from the source file main.cpp.
# target_link_libraries: This command specifies the libraries that the executable target should link against.
#           In this case, we link the main executable against the my_code_lib library we created earlier. 
#           The PRIVATE keyword indicates that the library is only used for linking and does 
#           not affect the include directories of the main target.
# PRIVATE: Only the target itself uses it. Nothing else that links to the target inherits it.
# PUBLIC: The target uses it, and anything that links to the target also inherits it.
# (Also exists: INTERFACE: Only consumers inherit it; the target itself does not use it.)



