/**
 * @file blink_color.c
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief lib to make rgbled blink
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "blink_color.h"

TaskHandle_t task_blink_color_handle = NULL;

uint16_t tRed;
uint16_t tBlue;
uint16_t tGreen;
uint16_t tBlink_time_on_ms;
uint16_t tBlink_time_off_ms;
bool is_blinking = false;

void blink_color(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms)
{
    if (is_blinking == true)
    {
        blink_color_stop();
    }

    tRed = red;
    tBlue = blue;
    tGreen = green;
    tBlink_time_on_ms = blink_time_on_ms;
    tBlink_time_off_ms = blink_time_off_ms;

    xTaskCreate(vTask_blink_color, "TASK BLINKCOLOR", VTASK_STACK_SIZE_BLINK_COLOR, NULL, VTASK_PRIORITY_BLINK_COLOR, &task_blink_color_handle);
    ESP_LOGI("BLINK_COLOR", "Created successfully");
}

void vTask_blink_color(void *pvParameters)
{
    is_blinking = true;
    ESP_LOGI("BLINK_COLOR", "init successfully");
    while (true)
    {
        set_rgb_led_interface(tRed, tGreen, tBlue);
        vTaskDelay(tBlink_time_on_ms / portTICK_PERIOD_MS);
        set_rgb_led_interface(BLACK);
        vTaskDelay(tBlink_time_off_ms / portTICK_PERIOD_MS);
    }
}

void blink_color_stop(void)
{
    if (is_blinking == true)
    {
        is_blinking = false;
        vTaskDelete(task_blink_color_handle);
        task_blink_color_handle = NULL;
        ESP_LOGI("BLINK_COLOR", "was killed successfully");

        return;
    }
    else
    {
        ESP_LOGI("BLINK_COLOR", "is not blinking");
    }
}