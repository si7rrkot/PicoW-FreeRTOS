#include "hardware/clocks.h"
#include "hardware/vreg.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "shell_port.h"
#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

static int quit_flag = 0;

static int scan_result(void *env, const cyw43_ev_scan_result_t *result)
{
    if (result) {
        printf("ssid: %-32s rssi: %4d chan: %3d mac: %02x:%02x:%02x:%02x:%02x:%02x sec: %u\n",
               result->ssid, result->rssi, result->channel,
               result->bssid[0], result->bssid[1], result->bssid[2], result->bssid[3], result->bssid[4], result->bssid[5],
               result->auth_mode);
        quit_flag = 1;
    }
    return 0;
}

int wifi_scan()
{
    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    absolute_time_t scan_time        = nil_time;
    bool            scan_in_progress = false;
    while (true) {
        if (absolute_time_diff_us(get_absolute_time(), scan_time) < 0) {
            if (!scan_in_progress) {
                if (quit_flag) {
                    quit_flag = 0;
                    break;
                }
                cyw43_wifi_scan_options_t scan_options = {0};

                int err = cyw43_wifi_scan(&cyw43_state, &scan_options, NULL, scan_result);
                if (err == 0) {
                    printf("\nPerforming wifi scan\n");
                    scan_in_progress = true;
                } else {
                    printf("Failed to start scan: %d\n", err);
                    scan_time = make_timeout_time_ms(10000);   // wait 10s and scan again
                }
            } else if (!cyw43_wifi_scan_active(&cyw43_state)) {
                scan_time        = make_timeout_time_ms(10000);   // wait 10s and scan again
                scan_in_progress = false;
            }
        }
        // the following #ifdef is only here so this same example can be used in multiple modes;
        // you do not need it in your code
#if PICO_CYW43_ARCH_POLL
        // if you are using pico_cyw43_arch_poll, then you must poll periodically from your
        // main loop (not from a timer) to check for Wi-Fi driver or lwIP work that needs to be done.
        cyw43_arch_poll();
        // you can poll as often as you like, however if you have nothing else to do you can
        // choose to sleep until either a specified time, or cyw43_arch_poll() has work to do:
        cyw43_arch_wait_for_work_until(scan_time);
#else
        // if you are not using pico_cyw43_arch_poll, then WiFI driver and lwIP work
        // is done via interrupt in the background. This sleep is just an example of some (blocking)
        // work you might be doing.
        sleep_ms(1000);
#endif
    }

    cyw43_arch_deinit();
    return 0;
}

int main()
{
    stdio_init_all();


    printf("pico init stdio all finished\n");
    xTaskCreate((TaskFunction_t)User_Shell_Init, "Shell", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1) {
    };
}