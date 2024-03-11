/**
 * @file rgb_led.cpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief Class to make 3 intances of led_controll to make controll of RGB led
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "rgb_led.hpp"
#include "rgb_led.h"
#include "led_colors.h"
#include "gpio_map.h"

namespace LED_RGB
{

    RGB_CONTROL::RGB_CONTROL()
    {
        InitializeDefaults();
        SetTimerDutyResolution(led_Duty_Resolution);

        led_controller_r.SetChannel(LEDC_CHANNEL_0);
        led_controller_g.SetChannel(LEDC_CHANNEL_1);
        led_controller_b.SetChannel(LEDC_CHANNEL_2);

        led_controller_r.SetChannelGpio(gpio_r);
        led_controller_g.SetChannelGpio(gpio_g);
        led_controller_b.SetChannelGpio(gpio_b);
    }

    void RGB_CONTROL::set_color(uint32_t red, uint32_t green, uint32_t blue)
    {
        led_controller_r.SetChannelDutyCycle(red);
        led_controller_g.SetChannelDutyCycle(green);
        led_controller_b.SetChannelDutyCycle(blue);
    }

    void RGB_CONTROL::blink_led_custom(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count)
    {
        for (int i = 1; i <= blink_count; i++)
        {
            set_color(red, green, blue);
            vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
            set_color(BLACK);

            vTaskDelay(blink_time_off_ms / portTICK_PERIOD_MS);
        }
    }
    void RGB_CONTROL::blink_led_dual_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t blink_time_on_ms0, uint16_t blink_time_off_ms0, uint8_t blink_count0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms1, uint16_t blink_time_off_ms1, uint8_t blink_count1)
    {
        for (int i = 1; i <= blink_count0; i++)
        {
            set_color(red0, green0, blue0);
            vTaskDelay(blink_time_on_ms0 / portTICK_PERIOD_MS);
            set_color(BLACK);

            vTaskDelay(blink_time_off_ms0 / portTICK_PERIOD_MS);
        }
        for (int i = 1; i <= blink_count1; i++)
        {
            set_color(red1, green1, blue1);
            vTaskDelay(blink_time_on_ms1 / portTICK_PERIOD_MS);

            set_color(BLACK);

            vTaskDelay(blink_time_off_ms1 / portTICK_PERIOD_MS);
        }
    }

    void RGB_CONTROL::blink_led_two_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count)
    {
        for (int i = 1; i <= blink_count; i++)
        {
            set_color(red0, green0, blue0);
            vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
            set_color(red1, green1, blue1);
            vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
            set_color(BLACK);
            vTaskDelay(blink_time_off_ms / portTICK_PERIOD_MS);
        }
    }

} // namespace LED_RGB

LED_RGB::RGB_CONTROL rgbLedControl;

void set_rgb_led_interface(int red, int green, int blue)
{

    rgbLedControl.set_color(red, green, blue);
}

void blink_led_custom(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count)
{
    for (int i = 1; i <= blink_count; i++)
    {
        rgbLedControl.set_color(red, green, blue);
        vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
        rgbLedControl.set_color(BLACK);

        vTaskDelay(blink_time_off_ms / portTICK_PERIOD_MS);
    }
}
void blink_led_dual_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t blink_time_on_ms0, uint16_t blink_time_off_ms0, uint8_t blink_count0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms1, uint16_t blink_time_off_ms1, uint8_t blink_count1)
{
    for (int i = 1; i <= blink_count0; i++)
    {
        rgbLedControl.set_color(red0, green0, blue0);
        vTaskDelay(blink_time_on_ms0 / portTICK_PERIOD_MS);
        rgbLedControl.set_color(BLACK);

        vTaskDelay(blink_time_off_ms0 / portTICK_PERIOD_MS);
    }
    for (int i = 1; i <= blink_count1; i++)
    {
        rgbLedControl.set_color(red1, green1, blue1);
        vTaskDelay(blink_time_on_ms1 / portTICK_PERIOD_MS);

        rgbLedControl.set_color(BLACK);

        vTaskDelay(blink_time_off_ms1 / portTICK_PERIOD_MS);
    }
}

void blink_led_two_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count)
{
    for (int i = 1; i <= blink_count; i++)
    {
        rgbLedControl.set_color(red0, green0, blue0);
        vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
        rgbLedControl.set_color(red1, green1, blue1);
        vTaskDelay(blink_time_on_ms / portTICK_PERIOD_MS);
        rgbLedControl.set_color(BLACK);
        vTaskDelay(blink_time_off_ms / portTICK_PERIOD_MS);
    }
}