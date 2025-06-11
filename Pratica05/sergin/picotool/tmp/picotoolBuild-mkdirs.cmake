# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/_deps/picotool-src"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/_deps/picotool-build"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/_deps"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/tmp"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/src/picotoolBuild-stamp"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/src"
  "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gabrielmachine/Documentos/RTOS/Pratica05/sergin/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
