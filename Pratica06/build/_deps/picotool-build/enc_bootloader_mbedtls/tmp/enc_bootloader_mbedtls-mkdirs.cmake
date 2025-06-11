# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-src/enc_bootloader"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/tmp"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/src/enc_bootloader_mbedtls-stamp"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/src"
  "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/src/enc_bootloader_mbedtls-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/src/enc_bootloader_mbedtls-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gabrielmachine/Documentos/RTOS/Pratica06/build/_deps/picotool-build/enc_bootloader_mbedtls/src/enc_bootloader_mbedtls-stamp${cfgdir}") # cfgdir has leading slash
endif()
