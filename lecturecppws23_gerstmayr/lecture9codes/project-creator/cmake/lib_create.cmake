macro( lib_create main_lib )

  ##################################################
  # get all names of the static libs of each modules
  ##################################################

  glob_directories_relative( dirs ${CMAKE_SOURCE_DIR} )

  set( lib_files_names "" )

  foreach( dir ${dirs} )
    glob_sources( tmp_dir_files ${dir} )
    foreach( file ${tmp_dir_files} )
      list( APPEND lib_files_names ${file} )
    endforeach( file )
  endforeach( dir )

  ############################################################
  # merge all the static libs together to a big shared library
  ############################################################
  # AND # :)
  ####################################################################
  # create one big shared library out of the small ones in the modules
  ####################################################################

  # create a empty cpp file in the build test_file_folder
  # (workaround, because add_library want at least one file to link to)

  file(WRITE ${CMAKE_BINARY_DIR}/empty.cpp "")

  add_library( ${main_lib} STATIC ${CMAKE_BINARY_DIR}/empty.cpp ${lib_files_names} )

  # rename booth libraries
  set_target_properties( ${main_lib} PROPERTIES OUTPUT_NAME ${main_lib} )
  set_target_properties( ${main_lib} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

  ############################################################
  # install libs
  ############################################################

  if( WIN32 )
    install( TARGETS ${main_lib} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
  else()
    install( TARGETS ${main_lib} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )
  endif()

endmacro()
