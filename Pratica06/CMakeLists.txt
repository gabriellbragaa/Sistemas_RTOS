cmake_minimum_required(VERSION 3.12)

# Nome do projeto
set(ProjectName Pratica6)

# Caminho do FreeRTOS
set(FREERTOS_KERNEL_PATH /home/gabrielmachine/FreeRTOS-Kernel)

# Importa o Pico SDK e FreeRTOS
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define o projeto
project(${ProjectName})

# Inicializa o SDK
pico_sdk_init()

# Executável principal
add_executable(${ProjectName}
    main.c
)

# Inclui diretórios locais (se necessário)
target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Linka as bibliotecas necessárias, incluindo hardware_adc
target_link_libraries(${ProjectName} 
    pico_stdlib
    hardware_adc
    FreeRTOS-Kernel-Heap4
)

# Configura stdio para USB
pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)

# Gera os arquivos UF2 e outros
pico_add_extra_outputs(${ProjectName})

