/**
 * @file sleep_timer.h
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief lib to controll the timer to go to deep sleep mode
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        WAKEUP_BT,
        WAKEUP_EXT0,
        WAKEUP_EXT1,
        WAKEUP_TIMER,
        WAKEUP_TOUCHPAD,
        WAKEUP_ULP,
        WAKEUP_GPIO,
        WAKEUP_UART,
        WAKEUP_WIFI,
        WAKEUP_COCPU,
        WAKEUP_ALL,
        WAKEUP_UNDEFINED,
    } wakeup_cause_name;

    void create_sleep_timer(int sleep_timer_time_s);
    void vTask_sleep_timer(void *pvParameters);
    void delete_sleep_timer(void);
    void init_sleep(void);
    void deisolate_gpio(void);
    void isolate_gpio(void);
    wakeup_cause_name wakeup_cause();

#ifdef __cplusplus
}
#endif