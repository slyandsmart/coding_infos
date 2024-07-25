
####################
# General properties
####################

cmake_minimum_required( VERSION 3.5 )
project( project-creator )

set( main_lib ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )

#################################################
# the folder 'cmake' has to be included first, as
# in there are important marcos
#################################################

add_subdirectory( cmake )
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

######################################
# add global compiler and linker flags
######################################

set( GLOBAL_COMPILE_FLAGS "" )
set( GLOBAL_LINKING_FLAGS "" )

if( UNIX )
	list( APPEND GLOBAL_LINKING_FLAGS "-pthread" )
endif()

set( GCC_COMPILE_FLAGS "${GLOBAL_COMPILE_FLAGS}" )
list( APPEND GCC_COMPILE_FLAGS " -fmax-errors=5" )

set( GCC_LINKING_FLAGS "${GLOBAL_LINKING_FLAGS}" )

set( CLANG_COMPILE_FLAGS "${GLOBAL_COMPILE_FLAGS}" )
list( APPEND CLANG_COMPILE_FLAGS " -ferror-limit=5" )

set( CLANG_LINKING_FLAGS "${GLOBAL_LINKING_FLAGS}" )

set( MSVC_COMPILE_FLAGS "${GLOBAL_COMPILE_FLAGS}" )
set( MSVC_LINKING_FLAGS "${GLOBAL_LINKING_FLAGS}" )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
  set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CLANG_COMPILE_FLAGS}" )
  set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CLANG_LINKING_FLAGS}" )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
  set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )
  set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINKING_FLAGS}" )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MSVC_COMPILE_FLAGS}" )
  set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LINKING_FLAGS}" )
endif()

#####################
# check prerequisites
#####################

##########################################
# Boost - The mighty, mighty BOOST library
##########################################

find_package( Boost COMPONENTS program_options REQUIRED )

if ( NOT Boost_FOUND )

  message( FATAL_ERROR "This project requires the Boost library, and will not be compiled." )
   return()

endif()
include_directories( ${Boost_INCLUDE_DIRS} )
list( APPEND BIN_LINKING_FLAGS ${Boost_LIBRARIES})

##################################
# nlohmann_json - for json parsing
##################################

find_package( nlohmann_json REQUIRED )

if( NOT nlohmann_json_FOUND )
  message( FATAL_ERROR "nlohmann_json library not found. Please download and install is from here \"https://github.com/nlohmann/json\"")
endif()

#######################
# GTest - Google C Test
#######################

find_package( GTest )

if ( NOT GTEST_FOUND )
  # first check if it is already created in the build directory, cause then we don't need any other stuff
  if ( NOT EXISTS ${PROJECT_BINARY_DIR}/lib/libgtest.a AND NOT EXISTS ${PROJECT_BINARY_DIR}/googletest-build/googlemock/gtest/libgtest_main.a )
	message(  STATUS "GTest not found! Do workaround and download them")
  # if GTest is not already installed, we download it here,
  # compile it and make it availabe for all other tests
  include( cmake/gtest.cmake )

  # disable adding gtest to install by default
  set( INSTALL_GTEST false CACHE BOOL "" FORCE )
  set( INSTALL_GMOCK false CACHE BOOL "" FORCE )
  endif()
    
  # set GTEST variables
  include_directories( SYSTEM ${PROJECT_BINARY_DIR}/googletest-src/googletest/include )

endif()

enable_testing()

##################################################################
# set up the cmake stuff for all our own modules and project parts
##################################################################

glob_directories_relative( dirs ${CMAKE_SOURCE_DIR} )

#####################################
# set include files of modules global
#####################################

foreach( module ${dirs} )
  include_directories( SYSTEM ${module}/include )
endforeach( module )

#########################
# include sub directories
#########################

foreach( module ${dirs} )
  add_subdirectory( ${module} )
endforeach( module )

##########################
# set up the final library
##########################

lib_create( ${main_lib} )

#######################################
# set up all binaries in the bin folder
#######################################

set( BIN_LINKING_FLAGS "" )
list( APPEND BIN_LINKING_FLAGS "-lboost_program_options" )

bin_create( ${main_lib} )
