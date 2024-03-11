/**
 * @file gpio.cpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief Class to controll the Gpio modes
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "gpio.hpp"

namespace Perifericos
{

    bool Gpio::isr_is_installed = false;
    Gpio::Gpio() {}

    Gpio::Gpio(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode)
    {
        gpio_num = num;
        esp_rom_gpio_pad_select_gpio(num);
        // gpio_pad_select_gpio(num); //deprecated
        gpio_set_direction(num, mode);
        gpio_set_pull_mode(num, pull_mode);
    }

    Gpio::Gpio(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode, gpio_int_type_t int_mode, gpio_isr_t handle, void *pArgs)
    {
        gpio_num = num;

        esp_rom_gpio_pad_select_gpio(num);
        // gpio_pad_select_gpio(num); //deprecated
        gpio_set_direction(num, mode);
        gpio_set_pull_mode(num, pull_mode);
        gpio_set_intr_type(num, int_mode);
        if (!isr_is_installed)
        {
            gpio_install_isr_service(0);
            isr_is_installed = true;
        }
        gpio_isr_handler_add(num, handle, pArgs);
    }
} // namespace Libraries