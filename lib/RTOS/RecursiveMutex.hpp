#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class RecursiveMutex
{
private:
    SemaphoreHandle_t handle;

public:
    /**
     * @brief Construct a new Recursive Mutex object
     *
     */
    RecursiveMutex() { handle = xSemaphoreCreateRecursiveMutex(); };

    /**
     * @brief Tenta Obter o Mutex
     *
     * @param ticksToWait Tempo Máximo para tentar obter o Mutex
     * @return true
     * @return false
     */
    bool Take(TickType_t ticksToWait) { return xSemaphoreTakeRecursive(handle, ticksToWait) == pdTRUE; }

    /**
     * @brief Devolve o Mutex
     *
     */
    void Give() { xSemaphoreGiveRecursive(handle); }

    /**
     * @brief Deleta o Mutex
     *
     */
    void Delete() { vSemaphoreDelete(handle); }
};
