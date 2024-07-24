
#include <FilePrinter.h>
#include <CMakeProperties.h>

#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>

namespace fs = std::filesystem;

namespace Fileprinter {

void FilePrinter::printProject(const std::string &project_name, const std::string &module_name) {
  // first we have to check, if there is an already existing project
  if (checkFileExistence("CMakeLists.txt") || checkFolderExistence("cmake")) {
	std::cout << "The project is already existing! (At least a CMakeLists.txt and a cmake-folder)\n";
	return;
  }

  // now we create the main-CMakeLists.txt
  printMainCMakeLists(project_name);

  // the next thing is creating the cmake-folder
  createFolder("cmake");
  createFolder("bin");

  // fill the cmake-folder with scripts
  printCMakeScriptFiles();

  // create a first module
  if (module_name.empty()) {
	printModule("Module1");
  } else {
	printModule(module_name);
  }
}

void FilePrinter::printModule(const std::string &raw_module_name) {

  // check if the project structure is there
  if (!(checkFileExistence("CMakeLists.txt") && checkFolderExistence("cmake") &&
	  checkFileExistence("cmake/CMakeLists.txt") && checkFileExistence("cmake/gtest.cmake") &&
	  checkFileExistence("cmake/gtest.in") && checkFileExistence("cmake/macros.cmake") &&
	  checkFileExistence("cmake/lib_create.cmake") && checkFileExistence("cmake/bin_create.cmake"))) {

	std::cout << "Project does not exist! (or only parts of it, not the full one)\n";
	return;
  }

  // check if the folder already exists
  if (checkFolderExistence(raw_module_name)) {
	std::cout << "This module is already existing (at least the folder....)\n";
	return;
  }

  std::string module_name = raw_module_name;

  // check if the first letter is capitalized
  if (islower(module_name.front())) {
	module_name[0] -= 32;
  }

  // create folder structure
  createFolder(module_name);
  createFolder(module_name + "/include");
  createFolder(module_name + "/src");
  createFolder(module_name + "/test");
  createFolder(module_name + "/test/test_files");

  // create CMakeLists file
  printModuleCMakeLists(module_name);

  // create init files for .h .cpp and .cc
  printModuleInitHeader(module_name);
  printModuleInitCPP(module_name);
  printModuleInitTest(module_name);

}

void printVectorToJsonFunction(std::ofstream& out) {
	const std::string output = 	R"(
function( vectorToJson vector vecname filename )
  
  list( LENGTH ${vector} len )
  if ( NOT len EQUAL 0 )
    file( APPEND ${filename} "  \"${vecname}\": [")
    math( EXPR last "${len} - 1")
    if( NOT (last EQUAL 0) )
    math(EXPR lastloop "${last} - 1")
      foreach( i RANGE 0 ${lastloop} )
        list( GET ${vector} i elem)
        file( APPEND ${filename} "\"${elem}\"," )
      endforeach( i )
    endif()
    list( GET ${vector} ${last} elem)
    file( APPEND ${filename} "\"${elem}\"" )
    file( APPEND ${filename} "]")
  endif()
  
endfunction()
  )";

	out << output;
}

void printTupleVectorToJsonFunction(std::ofstream& out) {
	const std::string output = 	R"(
function( tupleVectorToJson vector vecname filename type_name_1 type_name_2 )
  
  list( LENGTH ${vector} len )
  if ( NOT len EQUAL 0 )
    file( APPEND ${filename} "  \"${vecname}\": [")
    math( EXPR last "${len} - 2")
    if( NOT (last EQUAL 0) )
    math(EXPR lastloop "${last} - 2")
      foreach( i RANGE 0 ${lastloop} 2 )
        math(EXPR second "${i} + 1")
        list( GET ${vector} i elem_type)
        list( GET ${vector} second elem_name)
        file( APPEND ${filename} "{ \"${type_name_1}\": \"${elem_type}\"," )
        file( APPEND ${filename} "  \"${type_name_2}\": \"${elem_name}\" }," )
      endforeach( i )
    endif()
    math(EXPR second "${last} + 1")
    list( GET ${vector} ${last} elem_type)
    list( GET ${vector} ${second} elem_name)
    file( APPEND ${filename} "{ \"${type_name_1}\": \"${elem_type}\"," )
    file( APPEND ${filename} "  \"${type_name_2}\": \"${elem_name}\" }" )    
    file( APPEND ${filename} "]")
  endif()
  
endfunction()
  )";

	out << output;
}

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

void addPropertyRequestResult(std::stringstream& out, const std::string& target_property)
{

  const std::string var_name = str_tolower(target_property);

  const std::string output = R"(
get_property( )" + var_name + R"( TARGET ${target} PROPERTY )" + target_property + R"( )
if( )" + var_name + R"( )
  file( APPEND ${filename} ",\n" )
  vectorToJson( )" + var_name + R"( ")" + target_property + R"(" ${filename} )

endif()
)";

  out << output;
}

void printExtractProtertiesFunction(std::ofstream& out)
{
  std::stringstream output;
  output << R"(
function( extractProperties target )

  # create a filename to store valuable information in it
  set( filename "${CMAKE_BINARY_DIR}/results/${elem}.dat" )

  file( APPEND ${filename} "{\n" )
  file( APPEND ${filename} "  \"TARGET\": [\"${target}\"]" )

)";

  for(const auto& target : BuildStructureAnalyzer::CMakeProperties::p)
  {
    addPropertyRequestResult(output, target);
  }

  output << R"(
  file( APPEND ${filename} "\n}\n" )

endFunction()
)";

	out << output.str();
}

void overrideFunction(std::ofstream& out, const std::string& function_name, const std::string& dir, const std::string& out_var_name) {
	
  const std::string output = 	R"(
function( )" + function_name + R"( )

  # call the original function
  _)" + function_name + R"((${ARGN})

  # save the 
  set()" + out_var_name + R"( ${)" + out_var_name + R"(} ${ARGV0} CACHE INTERNAL )" + out_var_name + R"( )

endfunction()
  )";

	out << output;
}

void createVariables(std::ofstream& out, const std::string& name)
{
  const std::string output = 	R"(set( )" + name + R"( "" CACHE INTERNAL ""  ))";
	out << output;
}

void extractProperties(std::ofstream& out, const std::string& name)
{
  const std::string output = 	R"(
foreach( elem ${)" + name + R"(})
  extractProperties(${elem})
endforeach( elem ))";
	out << output;
}

void FilePrinter::printCMakeInterceptionScript(const std::string& dir, const std::string& code_sub_dir) {

	// create file
	std::ofstream out_file(dir + "/CMakeLists.txt");	
	out_file << "\n";

	// find a unique name fo a folder containing data
	const std::string dir_name = "code";

  // create new global variable storing value
  const std::string exe_out_file_name = "exe_targets";
  const std::string lib_out_file_name = "lib_targets";
 
  createVariables(out_file, exe_out_file_name);
	out_file << "\n";
  createVariables(out_file, lib_out_file_name);
	out_file << "\n";

  // print a function, which helps to output vectors in json-format
  printVectorToJsonFunction(out_file);
  printTupleVectorToJsonFunction(out_file);

  // print extractProperties function
  printExtractProtertiesFunction(out_file);

	// print add_executable override function
	overrideFunction(out_file, "add_executable", dir_name, exe_out_file_name);
	out_file << "\n";

	// print add_library override function
	overrideFunction(out_file, "add_library", dir_name, lib_out_file_name);
	out_file << "\n";

	// add the subdirectory containing the code base
	out_file << "add_subdirectory( " + code_sub_dir + " )\n";

  // print functionality to get properties
  extractProperties(out_file, exe_out_file_name);
  extractProperties(out_file, lib_out_file_name);

	out_file.close();

}


void FilePrinter::printModuleCMakeLists(const std::string &module_name) {

  const std::string file_name = module_name + "/CMakeLists.txt";
  std::ofstream out(file_name);

  const std::string output = R"(
# set the name of the module
set( module_name )" + module_name + R"( )

# set the name of the library
set( lib_name ${module_name} )

set( test_file_folder "test/test_files" )

# set link libraries for the whole module
set( module_link_libs "${GLOBAL_LINKING_FLAGS}" )

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
)";

  out << output;
  out.close();
}

void FilePrinter::printModuleInitHeader(const std::string &module_name) {

  const std::string file_name = module_name + "/include/" + module_name + ".h";
  std::ofstream out(file_name);

  const std::string output = ""
							 "// this file is generated by the IGS - template creator\n\n"
							 "namespace " + module_name + " {\n\n"
														  "struct " + module_name + " {\n"
																					"};\n\n"
																					"} // end namespace " + module_name
	  + "\n";

  out << output;

  out.close();
}

void FilePrinter::printModuleInitCPP(const std::string &module_name) {
  const std::string file_name = module_name + "/src/" + module_name + ".cpp";
  std::ofstream out(file_name);

  const std::string output = ""
							 "// this file is generated by the IGS - template creator\n\n"
							 "#include <" + module_name + ".h>\n\n"
														  "namespace " + module_name + " {\n\n"
																					   "} // end namespace "
	  + module_name + "\n";

  out << output;

  out.close();
}

void FilePrinter::printModuleInitTest(const std::string &module_name) {
  const std::string file_name = module_name + "/test/" + module_name + ".cc";
  std::ofstream out(file_name);

  const std::string output = ""
							 "// this file is generated by the IGS - template creator\n\n"
							 "#include <gtest/gtest.h>\n"
							 "#include <" + module_name + ".h>\n"
														  "using namespace " + module_name + ";\n\n"
																							 "TEST(" + module_name
	  + ", Basic) {\n\n"
		"}\n";

  out << output;

  out.close();
}

void FilePrinter::printMainCMakeLists(const std::string &project_name) {

  std::ofstream out("CMakeLists.txt");

  const std::string output = R"(
####################
# General properties
####################

cmake_minimum_required( VERSION 3.5 )
project( )" + project_name + R"( )

set( main_lib ${PROJECT_NAME} )

set( CMAKE_CXX_STANDARD 17 )

#################################################
# the folder 'cmake' has to be included first, as
# in there are important marcos
#################################################

add_subdirectory( cmake )

######################################
# add global compiler and linker flags
######################################

set( GLOBAL_COMPILE_FLAGS "" )
set( GLOBAL_LINKING_FLAGS "" )

if( UNIX )
	list( APPEND GLOBAL_LINKING_FLAGS "-pthread" )
endif()

set( GCC_COMPILE_FLAGS "${GLOBAL_COMPILE_FLAGS}" )
list( APPEND GCC_COMPILE_FLAGS "-fmax-errors=5" )

set( GCC_LINKING_FLAGS "${GLOBAL_LINKING_FLAGS}" )

set( CLANG_COMPILE_FLAGS "${GLOBAL_COMPILE_FLAGS}" )
list( APPEND CLANG_COMPILE_FLAGS "-ferror-limit=5" )

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

# find_package( Boost REQUIRED )
#
# if ( NOT Boost_FOUND )
#
#     message( FATAL_ERROR "This project requires the Boost library, and will not be compiled." )
#     return()
#
# endif()
# include_directories( ${Boost_INCLUDE_DIRS} )

#######################
# GTest - Google C Test
#######################

find_package( GTest )

if ( NOT GTEST_FOUND )

  # first check if it is already created in the build directory, cause then we don't need any other stuff
  if ( NOT EXISTS ${PROJECT_BINARY_DIR}/googletest-build/googlemock/gtest/libgtest.a AND NOT EXISTS ${PROJECT_BINARY_DIR}/googletest-build/googlemock/gtest/libgtest_main.a )
   message(  STATUS "GTest not found! Do workaround and download them")
    # if GTest is not already installed, we download it here,
    # compile it and make it availabe for all other tests
    include( cmake/gtest.cmake )
    message( STATUS "--- GTest installed in build folder ---")
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

glob_directories( dirs ${CMAKE_SOURCE_DIR} )

#####################################
# set include files of modules global
#####################################

foreach( module ${dirs} )
  include_directories( ${module}/include )
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

bin_create( ${main_lib} )
)";

  out << output;
  out.close();
}

void FilePrinter::createFolder(const std::string &dir_name) {
  struct stat st{0};

  if (stat(dir_name.c_str(), &st) == -1) {
	mkdir(dir_name.c_str(), 0755);
  }
}

bool FilePrinter::checkFolderExistence(const std::string &dir_name) {
  struct stat st{0};
  return stat(dir_name.c_str(), &st) == 0;
}

bool FilePrinter::checkFileExistence(const std::string &file_name) {
  return access(file_name.c_str(), F_OK) != -1;
}

void FilePrinter::printBinCreateScript() {

  std::ofstream out("cmake/bin_create.cmake");

  const std::string output = R"(macro( bin_create main_lib )

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
)";

  out << output;

  out.close();
}

void FilePrinter::printLibCreate() {

  std::ofstream out("cmake/lib_create.cmake");

  const std::string output = R"(macro( lib_create main_lib )

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
)";

  out << output;

  out.close();
}

void FilePrinter::printScriptCMakeLists() {

  std::ofstream out("cmake/CMakeLists.txt");

  const std::string output = ""
							 "\n"
							 "##################################\n"
							 "# include all cmake file from here\n"
							 "##################################\n"
							 "\n"
							 "include( macros.cmake )\n"
							 "include( bin_create.cmake )\n"
							 "include( lib_create.cmake )\n"
							 "include( shared_lib_utils.cmake )\n";

  out << output;

  out.close();
}

void FilePrinter::printGtestFiles() {

  std::ofstream out1("cmake/gtest.in");
  std::ofstream out2("cmake/gtest.cmake");

  const std::string output1 = ""
							  "project(googletest-download NONE)\n\n"
							  "cmake_minimum_required( VERSION 3.5 )\n\n"
							  "include(ExternalProject)\n\n"
							  "ExternalProject_Add(googletest\n"
							  "  GIT_REPOSITORY    https://github.com/google/googletest.git\n"
							  "  GIT_TAG           master\n"
							  "  SOURCE_DIR        \"${CMAKE_BINARY_DIR}/googletest-src\"\n"
							  "  BINARY_DIR        \"${CMAKE_BINARY_DIR}/googletest-build\"\n"
							  "  CONFIGURE_COMMAND \"\"\n"
							  "  BUILD_COMMAND     \"\"\n"
							  "  INSTALL_COMMAND   \"\"\n"
							  "  TEST_COMMAND      \"\"\n"
							  ")\n";

  const std::string output2 = R"(# Download and unpack googletest at configure time
configure_file(cmake/gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message (FATAL_ERROR "CMake step for googletest failed: ${result}" )
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if( result )
  message( FATAL_ERROR "Build step for googletest failed: ${result}" )
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
)";

  out1 << output1;
  out2 << output2;

  out1.close();
  out2.close();
}

void FilePrinter::printMacroScript() {

  std::ofstream out("cmake/macros.cmake");

  const std::string output = "\n"
							 "# big thanks to the insieme team (https://github.com/insieme) for these macros\n"
							 "macro( glob_headers output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.h ${input_path}/*.hpp ${input_path}/*.def ${input_path}/*.inc )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_sources output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.c ${input_path}/*.cpp )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_tests output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.cc )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_directories output_var input_path )\n"
							 "  file( GLOB children RELATIVE ${input_path} ${input_path}/* )\n"
							 "  set( dirlist \"\" )\n"
							 "  foreach( child ${children} )\n"
							 "    if( IS_DIRECTORY ${input_path}/${child}\n"
							 "        AND ${child} MATCHES \"^[A-Z]\" )\n"
							 "      list( APPEND dirlist ${child} )\n"
							 "    endif()\n"
							 "  endforeach( child )\n"
							 "  set( ${output_var} ${dirlist} )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_executables output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.cxx ${input_path}/*.cpp )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_test_files output_var input_path)\n"
							 "  file( GLOB_RECURSE ${output_var} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${input_path} ${input_path}/* )\n"
							 "endmacro()";

  out << output;

  out.close();
}

void FilePrinter::printSharedLibUtils() {
  std::ofstream out("cmake/shared_lib_utils.cmake");

  const std::string output = ""
							 "\n"
							 "# big thanks to the insieme team (https://github.com/insieme) for these macros\n"
							 "macro( glob_headers output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.h ${input_path}/*.hpp ${input_path}/*.def ${input_path}/*.inc )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_sources output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.c ${input_path}/*.cpp )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_tests output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.cc )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_directories output_var input_path )\n"
							 "  file( GLOB children RELATIVE ${input_path} ${input_path}/* )\n"
							 "  set( dirlist \"\" )\n"
							 "  foreach( child ${children} )\n"
							 "    if( IS_DIRECTORY ${input_path}/${child}\n"
							 "        AND ${child} MATCHES \"^[A-Z]\" )\n"
							 "      list( APPEND dirlist ${child} )\n"
							 "    endif()\n"
							 "  endforeach( child )\n"
							 "  set( ${output_var} ${dirlist} )\n"
							 "endmacro()\n"
							 "\n"
							 "macro( glob_executables output_var input_path )\n"
							 "    file( GLOB_RECURSE ${output_var} ${input_path}/*.cxx ${input_path}/*.cpp )\n"
							 "endmacro()";

  out << output;

  out.close();
}

void FilePrinter::printCMakeScriptFiles() {
  printScriptCMakeLists();
  printBinCreateScript();
  printLibCreate();
  printGtestFiles();
  printMacroScript();
  printSharedLibUtils();
}

} // end namespace FilePrinter
