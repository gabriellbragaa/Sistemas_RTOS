# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-src"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-build"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/tmp"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/src/picotoolBuild-stamp"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/src"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/src/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
