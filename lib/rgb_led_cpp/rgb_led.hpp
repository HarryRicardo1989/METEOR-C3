/**
 * @file rgb_led.hpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief Class to make 3 intances of led_controll to make controll of RGB led
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "Led_Control/led_control.hpp"
#include "Led_Control/led_control_timer.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rgb_led.h"
#include "gpio_map.h"

namespace LED_RGB
{
    /**
     * @brief Construct a new rgb led object
     *
     * @param gpio_r GPIO pin led Red
     * @param gpio_g GPIO pin led Green
     * @param gpio_b GPIO pin led Blue
     * @param led_Duty_Resolution LEDC PWM duty resolution of bits
     * LEDC_TIMER_8_BIT = 255
     * LEDC_TIMER_9_BIT = 512
     * LEDC_TIMER_10_BIT = 1024
     * LEDC_TIMER_12_BIT = 4096
     * LEDC_TIMER_13_BIT = 8192
     * LEDC_TIMER_14_BIT = 16384
     * LEDC_TIMER_15_BIT = 32768
     * LEDC_TIMER_16_BIT = 65536
     */
    class RGB_CONTROL : Perifericos::LED_CONTROL_TIMER
    {
    private:
        Perifericos::LED_CONTROL led_controller_r = Perifericos::LED_CONTROL();
        Perifericos::LED_CONTROL led_controller_g = Perifericos::LED_CONTROL();
        Perifericos::LED_CONTROL led_controller_b = Perifericos::LED_CONTROL();
        // LED::LED_CONTROL_TIMER led_controller_timer = LED::LED_CONTROL_TIMER();
        TaskHandle_t task_blink_color_handle = NULL;
        void vTask_blink_color(void *pvParameters);
        int gpio_r = RGB_LED_RED_GPIO;
        int gpio_g = RGB_LED_GREEN_GPIO;
        int gpio_b = RGB_LED_BLUE_GPIO;
        ledc_timer_bit_t led_Duty_Resolution = LED_DUTY_RESOLUTION;

    public:
        /**
         * @brief Construct a new rgb led object
         *
         *
         * @param gpio_r GPIO pin led Red
         * @param gpio_g GPIO pin led Green
         * @param gpio_b GPIO pin led Blue
         * @param led_Duty_Resolution LEDC PWM duty resolution of bits
         * LEDC_TIMER_8_BIT = 255
         * LEDC_TIMER_9_BIT = 512
         * LEDC_TIMER_10_BIT = 1024
         * LEDC_TIMER_12_BIT = 4096
         * LEDC_TIMER_13_BIT = 8192
         * LEDC_TIMER_14_BIT = 16384
         * LEDC_TIMER_15_BIT = 32768
         * LEDC_TIMER_16_BIT = 65536
         */
        RGB_CONTROL();

        /**
         * @brief Method for change duty cycle of each led
         *
         *
         * @param red   PWM duty cycle uint32_t but depends of led_Duty_Resolution
         * @param green PWM duty cycle uint32_t but depends of led_Duty_Resolution
         * @param blue  PWM duty cycle uint32_t but depends of led_Duty_Resolution
         */
        void set_color(uint32_t red, uint32_t green, uint32_t blue);

        void blink_led_dual_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t blink_time_on_ms0, uint16_t blink_time_off_ms0, uint8_t blink_count0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms1, uint16_t blink_time_off_ms1, uint8_t blink_count1);
        void blink_led_two_collor(uint16_t red0, uint16_t green0, uint16_t blue0, uint16_t red1, uint16_t green1, uint16_t blue1, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count);
        void blink_led_custom(uint16_t red, uint16_t green, uint16_t blue, uint16_t blink_time_on_ms, uint16_t blink_time_off_ms, uint8_t blink_count);
    };

} // namespace RGB
