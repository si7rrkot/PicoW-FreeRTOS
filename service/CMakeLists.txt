set(LETTER_SHELL letter-shell)
set(WIFI wifi)

add_library(letter_shell
${LETTER_SHELL}/src/shell.c
${LETTER_SHELL}/src/shell_cmd_list.c
${LETTER_SHELL}/src/shell_companion.c
${LETTER_SHELL}/src/shell_ext.c
${LETTER_SHELL}/src/shell_port.c
)

target_include_directories(letter_shell PUBLIC
    .
    ${LETTER_SHELL}/includes/
    ${SOURCE_DIR}/FreeRTOS/FreeRTOS-Kernel/include/
    ${SOURCE_DIR}/FreeRTOS/
    ${SOURCE_DIR}/FreeRTOS/FreeRTOS-Kernel/portable/GCC/ARM_CM0
)

add_library(wifi
    ${WIFI}/src/wifi_scan.c
)

target_include_directories(wifi PUBLIC
    ${WIFI}/includes/
)

target_link_libraries(wifi
    pico_stdlib
    freertos
    pico_cyw43_arch_lwip_poll
)