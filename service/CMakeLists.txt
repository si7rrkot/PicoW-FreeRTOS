set(LETTER_SHELL letter-shell)


add_library(letter_shell
${LETTER_SHELL}/shell.c
${LETTER_SHELL}/shell_cmd_list.c
${LETTER_SHELL}/shell_companion.c
${LETTER_SHELL}/shell_ext.c
${LETTER_SHELL}/shell_port.c
)

target_include_directories(letter_shell PUBLIC
    .
    ${LETTER_SHELL}/
    ${LETTER_SHELL}/../../freertos/FreeRTOS-Kernel/include/
    ${LETTER_SHELL}/../../freertos/
    ${LETTER_SHELL}/../../freertos/FreeRTOS-Kernel/portable/GCC/ARM_CM0
)