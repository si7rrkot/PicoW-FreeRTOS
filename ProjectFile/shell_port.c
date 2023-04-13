
#include "shell_port.h"
#include "shell.h"
// #include "pico/stdlib.h"
#include "stdio.h"
#include <FreeRTOS.h>

Shell shell;
char  shell_buffer[512];

// shell写函数原型：typedef void (*shellWrite)(const char);
signed short User_Shell_Write(char *data, unsigned short len)
{
    unsigned short length = len;
    while (length--) {
        putchar(*data++);
    }
    return len;
}

/* 3. 编写初始化函数 */
void *User_Shell_Init(void *argv)
{
    char c;
    // 注册自己实现的写函数
    shell.write         = User_Shell_Write;

    // 调用shell初始化函数
    shellInit(&shell, shell_buffer, 512);
    while (1) {
        c = getchar();
        shellHandler(&shell, c);
        }
        vTaskDelay(100);
    return NULL;
}
