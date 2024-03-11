#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace RTOS
{
    class Mutex
    {
    private:
        SemaphoreHandle_t handle;

    public:
        Mutex() { this->handle = xSemaphoreCreateMutex(); }
        /**
         * @brief Tenta Obter o Mutex
         *
         * @param ticksToWait Tempo Máximo para tentar obter o Mutex
         * @return true
         * @return false
         */
        bool Take(TickType_t ticksToWait) { return xSemaphoreTake(handle, ticksToWait) == pdTRUE; }

        /**
         * @brief Devolve o Mutex
         *
         */
        void Give() { xSemaphoreGive(handle); }

        /**
         * @brief Deleta o Mutex
         *
         */
        void Delete() { vSemaphoreDelete(handle); }
    };

} // namespace RTOS
