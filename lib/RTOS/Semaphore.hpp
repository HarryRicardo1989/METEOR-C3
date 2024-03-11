#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace RTOS
{
    class Semaphore
    {
    private:
        SemaphoreHandle_t semaphore_handle;

    public:
        /**
         * @brief Construct a new Semaphore object
         *
         */
        Semaphore();
        /**
         * @brief
         *
         * @param ticks
         * @return BaseType_t
         */
        BaseType_t Take(TickType_t ticks);
    };
} // namespace RTOS
