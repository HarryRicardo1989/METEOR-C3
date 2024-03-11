/**
 * @file sleep_timer.c
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief  lib to controll the timer to go to deep sleep mode
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "tasks_common.h"
#include "gpio_map.h"
#include "rgb_led.h"
#include "blink_color.h"

#include "sleep_timer.h"
#include "driver/rtc_io.h"
#include "stdio.h"
#include "rw_data.h"
#include "esp_sleep.h"
#include "esp_cleanup.h"

TaskHandle_t task_sleep_timer_handle = NULL;

int tSleep_timer_time_s = 30;

void create_sleep_timer(int sleep_timer_time_s)
{
    tSleep_timer_time_s = sleep_timer_time_s;

    esp_sleep_pd_config(ESP_PD_DOMAIN_CPU, ESP_PD_OPTION_AUTO);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RC_FAST, ESP_PD_OPTION_AUTO);
    // esp_sleep_pd_config(ESP_PD_DOMAIN_VDDSDIO, ESP_PD_OPTION_AUTO);
    esp_sleep_enable_timer_wakeup(read_nvs_uint32_var(TIME_TO_WAKE_UP) * SECONDS);
    esp_sleep_is_valid_wakeup_gpio(WAKE_UP_PIN);
    printf("criou novo timer %d segundos \n", tSleep_timer_time_s);
    if (tSleep_timer_time_s == 0)
    {
        init_sleep();
    }

    xTaskCreate(vTask_sleep_timer, "TASK SLEEP TIMER", VTASK_STACK_SIZE_SLEEP_TIMER, NULL, VTASK_PRIORITY_SLEEP_TIMER, &task_sleep_timer_handle);
}

void vTask_sleep_timer(void *pvParameters)
{
    while (true)
    {
        vTaskDelay(tSleep_timer_time_s * 1000 / portTICK_PERIOD_MS);
        init_sleep();
    }
}

void delete_sleep_timer(void)
{
    vTaskDelete(task_sleep_timer_handle);
    printf("apagou timer de %d segundos \n", tSleep_timer_time_s);
}

void init_sleep(void)
{
    blink_color_stop();
    blink_led_dual_collor(GO_SLEEP_COLOR0, GO_SLEEP_TIMING0, GO_SLEEP_COLOR1, GO_SLEEP_TIMING1);
    cleanup();
    isolate_gpio();

    printf("\n\nsleeping\n\n");
    esp_deep_sleep_start();
}

void isolate_gpio(void)
{
    //esp_sleep_config_gpio_isolate();
}

void deisolate_gpio(void)
{
    // gpio_force_unhold_all();
}

wakeup_cause_name wakeup_cause()
{
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    switch (cause)
    {
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        return WAKEUP_TOUCHPAD;
    case ESP_SLEEP_WAKEUP_TIMER:
        return WAKEUP_TIMER;
    case ESP_SLEEP_WAKEUP_ULP:
        return WAKEUP_ULP;
    case ESP_SLEEP_WAKEUP_GPIO:
        return WAKEUP_GPIO;
    case ESP_SLEEP_WAKEUP_UART:
        return WAKEUP_UART;
    case ESP_SLEEP_WAKEUP_WIFI:
        return WAKEUP_WIFI;
    case ESP_SLEEP_WAKEUP_BT:
        return WAKEUP_BT;
    case ESP_SLEEP_WAKEUP_COCPU:
        return WAKEUP_COCPU;
    case ESP_SLEEP_WAKEUP_ALL:
        return WAKEUP_ALL;
    default:
        return WAKEUP_UNDEFINED;
    }
}
