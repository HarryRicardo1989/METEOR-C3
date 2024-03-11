#pragma once
#include "tasks_common.h"
#include "gpio_map.h"
#include <vector>
#include <utility>
#include "rw_data.h"
#include "GPIO/gpio.hpp"
#include "math.h"
#include "ADC_control/adc.hpp"
#include "kalman_filter.hpp"

namespace BATTERY
{
    class BatteryStatus
    {
    private:
        FILTER::KalmanFilter kf_battery = FILTER::KalmanFilter(0.01, 8.0, 1.0);
        Perifericos::Gpio is_charging = Perifericos::Gpio(CHARGING, GPIO_MODE_INPUT, GPIO_PULLUP_ONLY);

        Perifericos::Gpio is_charged = Perifericos::Gpio(CHARGED, GPIO_MODE_INPUT, GPIO_PULLUP_ONLY);
        uint8_t map_in_min = 0;
        uint16_t map_in_max = 4096;
        uint8_t map_out_min = 0;
        uint16_t map_out_max = 4250;

        int nvs_battery_saved = 0;
        uint16_t battery_level = 0;
        float battery_map = 0;
        bool battery_is_critical = false;

        float bat_percent = 0;

    public:
        BatteryStatus(void);
        int battery_read(uint16_t count);
        int battery_percent(uint16_t voltage_mV);
        bool battery_charging();
        bool battery_charged();
        bool battery_critical(int battery_percent_level);
    };

} // namespace BATTERY
