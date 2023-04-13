set(LETTER_SHELL letter-shell)

add_library(letter_shell
    ${LETTER_SHELL}/shell.c
    ${LETTER_SHELL}/shell_cmd_list.c
    ${LETTER_SHELL}/shell_companion.c
    ${LETTER_SHELL}/shell_ext.c

)

target_include_directories(letter_shell PUBLIC
    .
    ${LETTER_SHELL}/
)

