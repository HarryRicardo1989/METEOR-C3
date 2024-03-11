#include "SoftwareTimer.hpp"

namespace RTOS
{

    std::map<TimerHandle_t, SoftwareTimer *> SoftwareTimer::timersMap = std::map<TimerHandle_t, SoftwareTimer *>();

    SoftwareTimer::SoftwareTimer(const char *name, TickType_t period, UBaseType_t autoReload,
                                 void (*callback)(SoftwareTimer *pTimer), void *data)
    {
        assert(callback != nullptr);
        this->callback = callback;
        timerHandle = xTimerCreate(name, period, autoReload, data, internalCallback);
        timersMap.insert(std::make_pair(timerHandle, this));
    }

    SoftwareTimer::~SoftwareTimer()
    {
        xTimerDelete(timerHandle, portMAX_DELAY);
        timersMap.erase(timerHandle);
    }

    void SoftwareTimer::internalCallback(TimerHandle_t timerHandle)
    {
        SoftwareTimer *timer = timersMap.at(timerHandle);
        timer->callback(timer);
    }

} // namespace RTOS
