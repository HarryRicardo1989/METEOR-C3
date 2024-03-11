#pragma once

#include "stdint.h"
#include "led_colors.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void blink_led_dual_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t blink_time_on_ms0, uint16_t blink_time_off_ms0, uint8_t blink_count0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms1, uint16_t blink_time_off_ms1, uint8_t blink_count1);
    void blink_led_two_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count);
    void blink_led_custom(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count);
    void set_rgb_led_interface(int red, int green, int blue);

#ifdef __cplusplus
}
#endif