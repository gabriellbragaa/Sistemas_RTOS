# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-src"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-build"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/tmp"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/src"
  "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gabrielmachine/Downloads/RTS-main/labs/lab_01/src/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
