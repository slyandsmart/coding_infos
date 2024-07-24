macro( bin_create main_lib )

  ################################################################
  # lookup all files with .cpp or .cxx ending in the bin-directory
  ################################################################

  glob_executables( exec-files bin )

  glob_directories( dirs ${CMAKE_SOURCE_DIR} )

  # for all files in the folder do
  foreach( file ${exec-files} )
    # create name
    get_filename_component( file_name "${file}" NAME_WE )

    # create a executable
    add_executable( ${file_name} ${file} )

    # set some properties
    set_target_properties( ${file_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

    # add all líbraries for linking
    target_link_libraries( ${file_name} ${main_lib} )

    # add global libraries for linking
    foreach( lib ${GLOBAL_LINKING_FLAGS} )
      target_link_libraries( ${file_name} ${lib} )
    endforeach( lib )

    # add libraries specially defined for binaries to linking
    foreach( lib ${BIN_LINKING_FLAGS} )
      target_link_libraries( ${file_name} ${lib} )
    endforeach( lib )

	  # install binary
  	install (TARGETS ${file_name} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )

  endforeach( file )

endmacro()
