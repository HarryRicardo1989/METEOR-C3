/**
 * @file gpio.hpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief  Class to controll the GPIO modes
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <driver/gpio.h>
#include "esp_rom_gpio.h"

namespace Perifericos
{

    class Gpio
    {
    private:
        static bool isr_is_installed; // Checa e o Serviço de Interrupção já está instalado
        gpio_num_t gpio_num;

    public:
        Gpio();
        /**
         * @brief Construct a new Gpio object
         *
         * @param num Número do Gpio
         * @param mode Modo do Gpio
         * @param pull_mode Modo do Resistor
         */
        Gpio(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode);
        /**
         * @brief Construct a new GPIO object
         *
         * @param num Número do GPIO
         * @param mode Modo do GPIO
         * @param pull_mode Modo do Resistor
         * @param int_mode Tipo da Interrupção
         * @param handle Função a ser invocada
         * @param pArgs Argumento a ser passado para a função
         */
        Gpio(gpio_num_t num, gpio_mode_t mode, gpio_pull_mode_t pull_mode, gpio_int_type_t int_mode, gpio_isr_t handle, void *pArgs);
        /**
         * @brief Lê o Status do GPIO caso seja configurado como entrada
         *
         * @return true
         * @return false
         */
        inline bool get_level(void)
        {
            return gpio_get_level(gpio_num) == 1;
        }
        /**
         * @brief Escreve o valor no GPIO caso seja configurado como saída
         *
         * @param state Valor a ser enviado para o GPIO true/false
         */
        inline void set_level(bool state)
        {
            gpio_set_level(gpio_num, state ? 1 : 0);
        }

        /**
         * @brief Desabilita a Interrupção
         *
         */
        inline void disableInterrupt(void)
        {
            gpio_intr_disable(gpio_num);
        }

        /**
         * @brief Habilita a Interrupção
         *
         */
        inline void enableInterrupt(void)
        {
            gpio_intr_enable(gpio_num);
        }
    };
} // namespace
