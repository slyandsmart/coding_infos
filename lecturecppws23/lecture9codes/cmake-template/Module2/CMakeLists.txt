
# set the name of the module
set( module_name Module2 )

# set the name of the library
set( lib_name ${module_name} )

set( test_file_folder "test/test_files" )

# set link libraries for the whole module
set( module_link_libs "${GLOBAL_LINKING_FLAGS} Module" )

#######################################################
# compile all source files and make a library out of it
#######################################################

# find all source files
glob_sources( ${module_name}_sources src )

# find all the includes
glob_headers( ${module_name}_headers include )

# shared and static libraries built from the same object files
add_library( ${lib_name} STATIC ${${module_name}_headers} ${${module_name}_sources} )

# rename booth libraries
set_target_properties( ${lib_name} PROPERTIES OUTPUT_NAME ${lib_name} )

# add include directories
target_include_directories( ${lib_name} PUBLIC include )

# add link libraries for the libraries
foreach( link_lib ${module_link_libs} )
  target_link_libraries( ${lib_name} ${link_lib} )
endforeach( link_lib )

# install libraries -- lib
install( TARGETS ${lib_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )

# install libraries -- includes
install( FILES ${${module_name}_headers} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${module_name} )

#########################################################
# copy all example files to corresponding build directory
#########################################################

glob_test_files_relative( test_files ${test_file_folder} ${CMAKE_CURRENT_SOURCE_DIR}/test )

if( test_files )
 
  set( test_files_folder "test/test_files" )
  set( test_files_folder_dest "test_files" )

  # copy all the files
  foreach( copyfile ${test_files} )
    get_filename_component( dir ${copyfile} DIRECTORY )
    file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/${test_files_folder}/${copyfile} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${test_files_folder_dest}/${dir} )
  endforeach()

endif()

###########################################
# compile all test files in the test-folder
###########################################

glob_tests( ${module_name}_tests test )

foreach( test ${${module_name}_tests} )

    # create name
    get_filename_component( file_name "${test}" NAME_WE )
    set( test_name ut_${file_name} )

    # create executable
    add_executable( ${test_name} ${test} )

    # add link libraries
    target_link_libraries( ${test_name} gtest gtest_main )
    target_link_libraries( ${test_name} ${lib_name} )

    foreach( link_lib ${module_link_libs} )
      target_link_libraries( ${test_name} ${link_lib} )
    endforeach( link_lib )

    # add test
    add_test(
            NAME ${test_name}
            COMMAND ${test_name}
    )

endforeach( test )
