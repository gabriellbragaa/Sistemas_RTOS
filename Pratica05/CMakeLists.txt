cmake_minimum_required(VERSION 3.12)

# Name project
set(ProjectName Pratica05_1)

# Set any variables required for importing libraries
set(FREERTOS_KERNEL_PATH /home/gabrielmachine/FreeRTOS-Kernel)

# Import Pico SDK and FreeRTOS
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName})

# Import the Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize the SDK
pico_sdk_init()

# Create executable
add_executable(${ProjectName}
    main.c
)

# Include current directory for headers
target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Link against SDK and FreeRTOS
target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4
)

# Enable USB stdio, disable UART stdio
pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)

# Generate UF2 file and other outputs
pico_add_extra_outputs(${ProjectName})

