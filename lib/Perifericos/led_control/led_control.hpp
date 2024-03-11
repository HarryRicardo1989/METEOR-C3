/**
 * @file led_control.hpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief Class to controll the PWM things of esp32 ledcontroll API
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "driver/ledc.h"
#include "esp_err.h"
#include "led_control_timer.hpp"

namespace Perifericos
{

    class LED_CONTROL
    {
    private:
        ledc_channel_config_t _channel_config;
        void _set_defaults();

    public:
        LED_CONTROL(void);
        LED_CONTROL(int gpioNum);
        LED_CONTROL(int gpioNum, ledc_timer_t timerNum);

        esp_err_t SetChannelGpio(int gpio_num);
        esp_err_t SetChannelSpeedMode(ledc_mode_t speed_mode);
        esp_err_t SetChannel(ledc_channel_t channel);
        esp_err_t SetChannelInterruptEn(ledc_intr_type_t intr_type);
        esp_err_t SetChannelTimerSource(ledc_timer_t timer_num);
        esp_err_t SetChannelDutyCycle(uint32_t duty);
        esp_err_t SetChannelHpoint(int hpoint);
        esp_err_t SetChannelAll(int gpio_num,
                                ledc_mode_t speed_mode,
                                ledc_channel_t channel,
                                ledc_intr_type_t intr_type,
                                ledc_timer_t timer_num,
                                uint32_t duty,
                                int hpoint);

    }; // LED_CONTROL class

}
