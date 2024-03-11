#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <map>

namespace RTOS
{

    class SoftwareTimer
    {
    private:
        TimerHandle_t timerHandle;
        static void internalCallback(TimerHandle_t timerHandle);
        static std::map<TimerHandle_t, SoftwareTimer *> timersMap;
        void (*callback)(SoftwareTimer *pTimer);

    public:
        SoftwareTimer(const char *name, TickType_t period, UBaseType_t autoReload,
                      void (*callback)(SoftwareTimer *pTimer), void *data);
        ~SoftwareTimer();

        /**
         * @brief Inicia o timer
         * NOTE: Este Metódo não deve ser usado em Interrupções
         *
         * @param blockTime Tempo para aguardar
         */
        void Start(TickType_t blockTime) { xTimerStart(timerHandle, blockTime); }

        /**
         * @brief Para o Timer
         * NOTE: Este Metódo não deve ser usado em Interrupções
         *
         * @param blockTime Tempo para aguardar
         */
        void Stop(TickType_t blockTime) { xTimerStop(timerHandle, blockTime); }

        /**
         * @brief Inicia o Timer
         * NOTE: Metódo seguro para usar em Interrupções
         *
         * @param woken
         */
        void StartFromISR(BaseType_t *woken) { xTimerStartFromISR(timerHandle, woken); }

        /**
         * @brief Para o Timer
         * NOTE: Metódo seguro para usar em Interrupções
         *
         * @param woken
         */
        void StopFromISR(BaseType_t *woken) { xTimerStopFromISR(timerHandle, woken); }

        /**
         * @brief Ajusta um Novo Período
         * NOTE: Este Metódo não deve ser usado em Interrupções
         *
         * @param period
         * @param blockTime
         */
        void SetPeriod(TickType_t period, TickType_t blockTime) { xTimerChangePeriod(timerHandle, period, blockTime); }

        /**
         * @brief Ajusta um Novo Período
         * NOTE: Metódo seguro para usar em Interrupções
         *
         * @param period
         * @param woken
         */
        void SetPeriodFromISR(TickType_t period, BaseType_t *woken) { xTimerChangePeriodFromISR(timerHandle, period, woken); }

        /**
         * @brief Obtém o Período Atual
         *
         * @return TickType_t
         */
        TickType_t GetPeriod() { return xTimerGetPeriod(timerHandle); }

        /**
         * @brief Obtem os dados
         *
         * @return void*
         */
        void *GetData() { return pvTimerGetTimerID(timerHandle); }

        /**
         * @brief Set the Data object
         *
         * @param data
         */
        void SetData(void *data) { vTimerSetTimerID(timerHandle, data); }

        /**
         * @brief Checa se o Timer está ativo
         *
         * @return true
         * @return false
         */
        bool IsActive() { return xTimerIsTimerActive(timerHandle) != pdFALSE; }
    };
} // namespace RTOS