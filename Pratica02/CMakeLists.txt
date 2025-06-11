cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName projeto01)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH /home/gabrielmachine/FreeRTOS-Kernel)

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Define project
project(${ProjectName})

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(src)

# add_subdirectory(lib) ← se necessário no futuro

