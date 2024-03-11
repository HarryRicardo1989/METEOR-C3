#include "battery.hpp"
#include <vector>
namespace BATTERY
{

    BatteryStatus::BatteryStatus(void)
    {
    }

    int BatteryStatus::battery_read(uint16_t count)
    {
        ADC::AdcController adc = ADC::AdcController(ADC_UNIT_1, ADC_BITWIDTH_12, ADC_ATTEN_DB_11, ADC_CHANNEL_0);
        for (uint16_t i = 0; i < count; i++)
        {
            battery_level = kf_battery.filter((adc.GetVoltage() * (((R1 + R1 + R2) / R2) /* V_CORRECTION*/)));
            vTaskDelay(50 / configTICK_RATE_HZ);
        }
        // battery_level /= count;
        //  ESP_LOGI("BAT", "ADC-RAW: %d", adc.GetRaw());
        //  ESP_LOGI("BAT", "ADC-GetVoltage: %d", adc.GetVoltage());
        battery_map = (battery_level - map_in_min) / (float)(map_in_max - map_in_min) * (map_out_max - map_out_min) + map_out_min;
        //  ESP_LOGI("BAT", "BAT_ V_div: %d", battery_level);
        //   ESP_LOGI("BAT", "BAT multip: %d", static_cast<int>(round(battery_level * 1.33)));
        //   ESP_LOGI("BAT", "BAT_ Voltage: %d", (int)floor(battery_map));

        // if (battery_level >= 4200)
        //{
        //     battery_level = 4200;
        // }

        return (int)floor(battery_level);
    }
    int BatteryStatus::battery_percent(uint16_t voltage_mV)
    {
        const std::vector<std::pair<uint16_t, int>> voltageToPercentage = {
            {4000, 100},
            {3700, 90},
            {3600, 80},
            {3530, 70},
            {3450, 60},
            {3350, 50},
            {3250, 40},
            {3150, 30},
            {3000, 20},
            {2800, 10},
        };

        if (voltage_mV >= voltageToPercentage[0].first)
        {
            return voltageToPercentage[0].second;
        }
        else if (voltage_mV <= voltageToPercentage.back().first)
        {
            return voltageToPercentage.back().second;
        }

        for (size_t i = 0; i < voltageToPercentage.size() - 1; ++i)
        {
            if (voltage_mV >= voltageToPercentage[i + 1].first)
            {
                const auto &upperPoint = voltageToPercentage[i];
                const auto &lowerPoint = voltageToPercentage[i + 1];
                double voltageRange = static_cast<double>(upperPoint.first - lowerPoint.first);
                double percentRange = static_cast<double>(upperPoint.second - lowerPoint.second);
                double voltageDifference = static_cast<double>(voltage_mV - lowerPoint.first);
                double interpolatedPercent = lowerPoint.second + (voltageDifference / voltageRange) * percentRange;
                // interpolatedPercent = kf_percent.filter(interpolatedPercent);
                if (interpolatedPercent >= 95)
                    return 100;
                else if (interpolatedPercent >= 90)
                    return 95;
                else if (interpolatedPercent >= 85)
                    return 90;
                else if (interpolatedPercent >= 80)
                    return 85;
                else if (interpolatedPercent >= 75)
                    return 80;
                else if (interpolatedPercent >= 70)
                    return 75;
                else if (interpolatedPercent >= 65)
                    return 70;
                else if (interpolatedPercent >= 60)
                    return 65;
                else if (interpolatedPercent >= 55)
                    return 60;
                else if (interpolatedPercent >= 50)
                    return 55;
                else if (interpolatedPercent >= 45)
                    return 50;
                else if (interpolatedPercent >= 40)
                    return 45;
                else if (interpolatedPercent >= 35)
                    return 40;
                else if (interpolatedPercent >= 30)
                    return 35;
                else if (interpolatedPercent >= 25)
                    return 30;
                else if (interpolatedPercent >= 20)
                    return 25;
                else if (interpolatedPercent >= 15)
                    return 20;
                else if (interpolatedPercent >= 10)
                    return 15;
                else if (interpolatedPercent >= 5)
                    return 10;
                else
                    return 5;

                // return static_cast<int>(interpolatedPercent);
            }
        }

        return 0;
    }

    bool BatteryStatus::battery_charging()
    {

        return !is_charging.get_level();
    }
    bool BatteryStatus::battery_charged()
    {

        return !is_charged.get_level();
    }
    bool BatteryStatus::battery_critical(int battery_percent_level)
    {
        return (battery_percent_level <= BATTERY_IS_CRITICAL) ? true : false;
    }

} // namespace BATTERY
