#pragma once
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "nvs_flash.h"
#include "tasks_common.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "battery.hpp"
#include "rw_data.h"
#include "rgb_led.hpp"
#include "blink_color.h"

void charging_status_read_init();
void battery_read_stop();

void vTask_charging_status_read(void *pvParameters);
void battery_single_read_save(int count);
