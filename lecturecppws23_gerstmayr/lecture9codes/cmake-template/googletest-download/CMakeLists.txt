project(googletest-download NONE)

cmake_minimum_required( VERSION 3.5 )

include(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           main
  SOURCE_DIR        "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-src"
  BINARY_DIR        "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
