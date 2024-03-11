#pragma once
// default libs
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
// payload
#include "battery.hpp"
#include "rgb_led.hpp"
#include "blink_color.h"
#include "MQTT/MqttClient.hpp"
#include "MQTT/MqttPublish.hpp"

void vTask_MQTT_auto_publish(void *pvParameters);
void mqtt_task_pub_init();

void mqtt_task_pub_stop();