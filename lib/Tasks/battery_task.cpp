#include "battery_task.hpp"
TaskHandle_t task_charging_read_handle = NULL;
BATTERY::BatteryStatus bat_status = BATTERY::BatteryStatus();

void charging_status_read_init()
{
    xTaskCreate(vTask_charging_status_read, "TASK BATTERY CHARGiNG STATUS", VTASK_STACK_SIZE_CHARGING_STATUS, NULL, VTASK_PRIORITY_CHARGING_STATUS, &task_charging_read_handle);
}
void battery_read_stop()
{
    vTaskDelete(task_charging_read_handle);
}

void vTask_charging_status_read(void *pvParameters)
{
    bool is_blink_charging = false;
    bool is_blink_charged = false;
    bool is_blink_Unpluged = false;
    while (true)
    {
        // battery_single_read_save(1000);
        bool charged = bat_status.battery_charged();
        bool charging = bat_status.battery_charging();
        save_nvs_int8_var(BATTERY_CHARGED_STATUS, charged);
        save_nvs_int8_var(BATTERY_CHARGING_STATUS, charging);
        if (charged == true)
        {
            if (is_blink_charged == false)
            {
                // blink_color_stop();
                is_blink_charged = true;
                is_blink_charging = false;
                is_blink_Unpluged = false;
                blink_color(CHARGED_COLOR, CHARGED_TIMING);
                ESP_LOGI("BATTERY", "Carregado");
            }
        }
        else if (charging == true)
        {
            if (is_blink_charging == false)
            {
                // blink_color_stop();
                is_blink_charged = false;
                is_blink_charging = true;
                is_blink_Unpluged = false;
                // blink_color_stop();
                blink_color(CHARGING_COLOR, CHARGING_TIMING);
                ESP_LOGI("BATTERY", "Carregando");
            }
        }
        else
        {
            if (is_blink_Unpluged == false)
            {
                // blink_color_stop();
                is_blink_charged = false;
                is_blink_charging = false;
                is_blink_Unpluged = true;

                // blink_color_stop();
                blink_color(ON_WF_STATUS_COLOR, ON_WF_STATUS_TIMING);
                ESP_LOGI("BATTERY", "Unpluged");
            }
        }

        vTaskDelay(1 * PORT_TICK_PERIOD_SECONDS);
    }
}
void battery_single_read_save(int count)
{
    uint32_t bat_mv;
    uint8_t bat_level;
    bat_mv = bat_status.battery_read(count);
    bat_level = bat_status.battery_percent(bat_mv);
    save_nvs_u32_var(BATTERY_VALUE, bat_mv);
    save_nvs_int8_var(BATTERY_PERCENT_VALUE, bat_level);
    save_nvs_int8_var(BATTERY_CRITICAL_STATUS, bat_status.battery_critical(bat_level));

    printf("bat percent: %d bat voltage: %ldmV \n", bat_level, bat_mv);
    printf("NVS bat percent: %d NVS bat voltage: %ldmV \n", read_nvs_int8_var(BATTERY_PERCENT_VALUE), read_nvs_uint32_var(BATTERY_VALUE));
}