# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/taryn/src/other/pico/pico-sdk")

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(FreeRTOS_Pico C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(FreeRTOS_Pico FreeRTOS_Pico.c )

pico_set_program_name(FreeRTOS_Pico "FreeRTOS_Pico")
pico_set_program_version(FreeRTOS_Pico "0.1")

pico_enable_stdio_uart(FreeRTOS_Pico 1)
pico_enable_stdio_usb(FreeRTOS_Pico 0)

# Add the standard library to the build
target_link_libraries(FreeRTOS_Pico
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(FreeRTOS_Pico PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)
add_subdirectory(freertos)
add_subdirectory(ProjectFile)
add_subdirectory(service)
# Add any user requested libraries
target_link_libraries(FreeRTOS_Pico
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_cyw43_arch_lwip_threadsafe_background
        )

pico_add_extra_outputs(FreeRTOS_Pico)

