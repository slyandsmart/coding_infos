# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-src"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-build"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/tmp"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/src/googletest-stamp"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/src"
  "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/src/googletest-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Git_local/lecturecppws23/lecture9codes/cmake-template/googletest-download/googletest-prefix/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
