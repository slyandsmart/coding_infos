macro( add_shared_lib_properties lib_name )

  # By default, symbols provided by the sublibs that are not used by mainlib (which is all of them in this case)
  # are not used. This changes that.
  if (WIN32)
      set_target_properties(${lib_name} PROPERTIES
          LINK_FLAGS "/WHOLEARCHIVE"
      )
  elseif (APPLE)
      set_target_properties(${lib_name} PROPERTIES
          LINK_FLAGS "-Wl,-all_load"
      )
  else ()
      set_target_properties(${lib_name} PROPERTIES
          LINK_FLAGS "-Wl,--whole-archive"
      )
  endif ()

endmacro()
