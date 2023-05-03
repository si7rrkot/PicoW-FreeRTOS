#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>
#include "shell_port.h"

void led_task()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    printf("the default led pin is %d\n", LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {

        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        gpio_put(LED_PIN, 0);
        vTaskDelay(100);
        printf("%s!\n", __FUNCTION__);
    }
}

void uart_task()
{
    while (true) {
        printf("Hello, world!\n");
        vTaskDelay(100);
    }
}

int main()
{
    stdio_init_all();
    printf("pico init stdio all finished\n");
    // xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    // xTaskCreate(uart_task, "UART_Task", 256, NULL, 1, NULL);
    xTaskCreate((TaskFunction_t)User_Shell_Init, "Shell", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1) {
    };
}