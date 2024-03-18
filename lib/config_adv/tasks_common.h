/**
 * @file tasks_common.h
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief ALL off tasks things and commom defines
 * @version 0.1
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * @brief
 * 1ºnumber  MAJOR version when you make incompatible
 * 2ºnumber  MINOR version when you add functionality in a backwards compatible manner
 * 3ºnumber  MAINTENANCE release number (bugfixes only)
 * 4ºnumber  BUILD NUMBER (Hardware release)
 */
#define FIRMWARE_VERSION (char *)"0.1.2"
#define MANUFACTORY (char *)"RICARDOPASCHOALI"
#define MAC_ADDRESS (char *)"mac"

#define PORT_TICK_PERIOD_SECONDS (1000 / portTICK_PERIOD_MS)
#define SECONDS 1000000
#define TIME_TO_WAKE_UP (char *)"timeToWakeUp"

#define VTASK_PRIORITY_SLEEP_TIMER 1
#define VTASK_STACK_SIZE_SLEEP_TIMER configMINIMAL_STACK_SIZE + 1024

#define VTASK_PRIORITY_BLINK_COLOR 1
#define VTASK_STACK_SIZE_BLINK_COLOR configMINIMAL_STACK_SIZE + 2048

#define VTASK_PRIORITY_CHARGING_STATUS 5
#define VTASK_STACK_SIZE_CHARGING_STATUS configMINIMAL_STACK_SIZE + 2048

#define VTASK_PRIORITY_MQTT_PUBLISH 5
#define VTASK_STACK_SIZE_MQTT_PUBLISH configMINIMAL_STACK_SIZE + 2048

// Timers Sleep
#define SLEEP_TIME_MAIN_INIT 10
#define SLEEP_TIME_IDLE 30
#define SLEEP_TIME_ACCESS_DENIED_CODE 1
#define SLEEP_TIME_OTA 90
#define SLEEP_TIME_WIFI_ENABLED 60
#define SLEEP_TIME_WIFI_CONNECTED 60

// Generic Configs
#define DELAY_MS_BEFORE_MOTOR_RUN 500
#define DENY_LED_COUNT 3
#define DENY_LED_TIME 100

// Battery read Config
#define BATTERY_DEFAULT_VALUE 4000.0
#define BATTERY_IS_CRITICAL 15
#define AVERAGE_BATTERY_COUNTER 100
#define R1 47e3
#define R2 47e3
#define V_CORRECTION 0.986
/**
 * @brief NVS/ACTIONS defines NAMES
 *
 */

#define TEMPERATURE (char *)"temperature"
#define MODEL (char *)"model"
#define HUMIDITY (char *)"humidity"
#define PRESSURE (char *)"pressure"
#define ALTITUDE (char *)"altitude"
#define DEWPOINT (char *)"dewPoint"
#define UPDATE_STATUS (char *)"updateStatus"
#define OTA_URL (char *)"otaUrl"

/**
 * @brief AES Crypto config
 *
 */
/**
 * @brief JSON Read Configs
 *
 */
#define BATTERY_VALUE (char *)"batmv"
#define BATTERY_CRITICAL_STATUS (char *)"batCritical"
#define BATTERY_PERCENT_VALUE (char *)"batPercent"
#define BATTERY_CHARGED_STATUS (char *)"chargedStatus"
#define BATTERY_CHARGING_STATUS (char *)"chargingStatus "

/**
 * @brief NVS Models config
 *
 */
#define DEFAULT_MODEL (char *)"METEOR_Monitor" // default model

#define WAKEUP_TOUCH_TRESHOLD (char *)"wakeupTreshold" // 900
                                                       // #wake up setpoint

/**
 * @brief precisa gravar todos os NVS antes de rodar
 *
 */