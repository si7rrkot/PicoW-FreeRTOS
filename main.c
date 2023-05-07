#include "pico/stdlib.h"
#include "shell_port.h"
#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>
int main()
{
    stdio_init_all();


    printf("pico init stdio all finished\n");
    xTaskCreate((TaskFunction_t)User_Shell_Init, "Shell", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1) {
    };
}