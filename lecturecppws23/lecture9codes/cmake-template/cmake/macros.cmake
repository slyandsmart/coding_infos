
# big thanks to the insieme team (https://github.com/insieme) for these macros
macro( glob_headers output_var input_path )
    file( GLOB_RECURSE ${output_var} ${input_path}/*.h ${input_path}/*.hpp ${input_path}/*.def ${input_path}/*.inc )
endmacro()

macro( glob_sources output_var input_path )
    file( GLOB_RECURSE ${output_var} ${input_path}/*.c ${input_path}/*.cpp )
endmacro()

macro( glob_tests output_var input_path )
    file( GLOB_RECURSE ${output_var} ${input_path}/*.cc )
endmacro()

macro( glob_directories output_var input_path )
  file( GLOB children RELATIVE ${input_path} ${input_path}/* )
  set( dirlist "" )
  foreach( child ${children} )
    if( IS_DIRECTORY ${input_path}/${child}
        AND ${child} MATCHES "^[A-Z]" )
      list( APPEND dirlist ${child} )
    endif()
  endforeach( child )
  set( ${output_var} ${dirlist} )
endmacro()

macro( glob_executables output_var input_path )
    file( GLOB_RECURSE ${output_var} ${input_path}/*.cxx ${input_path}/*.cpp )
endmacro()

macro( glob_test_files output_var input_path)
  file( GLOB_RECURSE ${output_var} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${input_path} ${input_path}/* )
endmacro()

macro( glob_test_files_relative output_var input_path)
  file( GLOB_RECURSE ${output_var} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${input_path} ${input_path}/* )
endmacro()

macro( get_filename_from_path output_var input_var )
  get_filename_component( ${output_var} ${input_var} NAME )
endmacro()

macro( get_path_from_filename output_var input_var )
  get_filename_component( ${output_var} ${input_var} DIRECTORY )
endmacro()
