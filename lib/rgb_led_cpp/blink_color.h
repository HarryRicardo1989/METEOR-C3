/**
 * @file blink_color.h
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief lib to make rgbled blink
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "tasks_common.h"
#include "rgb_led.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void vTask_blink_color(void *pvParameters);
    void blink_color(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms);
    void blink_color_stop(void);

#ifdef __cplusplus
}
#endif
