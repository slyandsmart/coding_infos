macro( lib_create main_lib )

  ##################################################
  # get all names of the static libs of each modules
  ##################################################

  glob_directories( dirs ${CMAKE_SOURCE_DIR} )

  set( lib_names_static "" )

  foreach( dir ${dirs} )
    list( APPEND lib_names_static ${dir} )
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

  add_library( ${main_lib} SHARED ${CMAKE_BINARY_DIR}/empty.cpp )
  add_library( ${main_lib}_static STATIC ${CMAKE_BINARY_DIR}/empty.cpp )

  target_link_libraries( ${main_lib} ${lib_names_static} )
  target_link_libraries( ${main_lib}_static ${lib_names_static} )

  # rename booth libraries
  set_target_properties( ${main_lib} PROPERTIES OUTPUT_NAME ${main_lib} )
  set_target_properties( ${main_lib}_static PROPERTIES OUTPUT_NAME ${main_lib} )


  set_target_properties( ${main_lib} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
  set_target_properties( ${main_lib}_static PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )

  ############################################################
  # install libs
  ############################################################

  if( WIN32 )
    install( TARGETS ${main_lib} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
  else()
    install( TARGETS ${main_lib} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )
  endif()

  install( TARGETS ${main_lib}_static DESTINATION ${CMAKE_INSTALL_PREFIX}/lib )

endmacro()
