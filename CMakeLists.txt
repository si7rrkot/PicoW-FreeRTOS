# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/taryn/src/other/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)


set(PICO_BOARD pico_w CACHE STRING "Board type")


if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(FreeRTOS C CXX ASM)

pico_sdk_init()

add_executable(FreeRTOS
    main.c
)

pico_set_program_name(FreeRTOS "FreeRTOS")
pico_set_program_version(FreeRTOS "0.1")

pico_enable_stdio_uart(FreeRTOS 1)
pico_enable_stdio_usb(FreeRTOS 0)


target_include_directories(FreeRTOS PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)
target_link_libraries(FreeRTOS 
        pico_stdlib 
        freertos 
        letter_shell 
        pico_cyw43_arch_lwip_poll)

add_subdirectory(freertos)
add_subdirectory(service)

# Add any user requested libraries
target_link_libraries(FreeRTOS
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_cyw43_arch_lwip_poll
        )

pico_add_extra_outputs(FreeRTOS)