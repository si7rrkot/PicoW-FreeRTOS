add_executable(blink
    main.c
)

target_link_libraries(blink pico_stdlib freertos letter_shell)
pico_add_extra_outputs(blink)