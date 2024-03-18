#include "MqttPublish.hpp"
namespace PROTOCOL
{

    char *MqttPublish::create_Json_to_send()
    {
        cJSON *rootJson;
        cJSON *eventJson;
        cJSON *batteryJson;
        cJSON *infoJson;
        cJSON *deviceJson;

        struct client
        {
            char *clientIDjson = NULL;
            struct event
            {
                char *temperature = 0;
                char *pressure = 0;
                char *humidity = 0;
                char *timestamp = 0;
                char *dewpoint = 0;
                char *altitude = 0;
            } event;
            struct battery_info
            {
                int battery_voltage = 0;
                int battery_level = 0;
                bool battery_charging = 0;
                bool battery_charged = 0;
            } battery_info;
            struct device_info
            {
                char *manufactory = MANUFACTORY;
                char *fw_version = FIRMWARE_VERSION;
                char *model = DEFAULT_MODEL;
            } device_info;

        } client;
        client.event.temperature = read_nvs_string_var(TEMPERATURE);
        client.event.pressure = read_nvs_string_var(PRESSURE);
        client.event.humidity = read_nvs_string_var(HUMIDITY);
        client.event.dewpoint = read_nvs_string_var(DEWPOINT);
        client.event.altitude = read_nvs_string_var(ALTITUDE);
        client.battery_info.battery_voltage = read_nvs_uint32_var(BATTERY_VALUE);
        client.battery_info.battery_level = read_nvs_int8_var(BATTERY_PERCENT_VALUE);
        client.battery_info.battery_charging = read_nvs_int8_var(BATTERY_CHARGING_STATUS);
        client.battery_info.battery_charged = read_nvs_int8_var(BATTERY_CHARGED_STATUS);
        client.clientIDjson = this->clientID;
        rootJson = cJSON_CreateObject();
        batteryJson = cJSON_CreateObject();
        eventJson = cJSON_CreateObject();
        infoJson = cJSON_CreateObject();
        deviceJson = cJSON_CreateObject();

        cJSON_AddItemToObject(batteryJson, "level", cJSON_CreateNumber(client.battery_info.battery_level));
        cJSON_AddItemToObject(batteryJson, "voltage", cJSON_CreateNumber(client.battery_info.battery_voltage));
        cJSON_AddItemToObject(batteryJson, "charging", cJSON_CreateNumber(client.battery_info.battery_charging));
        cJSON_AddItemToObject(batteryJson, "charged", cJSON_CreateNumber(client.battery_info.battery_charged));

        cJSON_AddItemToObject(eventJson, "temperature", cJSON_CreateString(client.event.temperature));
        cJSON_AddItemToObject(eventJson, "pressure", cJSON_CreateString(client.event.pressure));
        cJSON_AddItemToObject(eventJson, "humidity", cJSON_CreateString(client.event.humidity));
        cJSON_AddItemToObject(eventJson, "dewpoint", cJSON_CreateString(client.event.dewpoint));
        cJSON_AddItemToObject(eventJson, "altitude", cJSON_CreateString(client.event.altitude));
        cJSON_AddItemToObject(eventJson, "timestamp", cJSON_CreateString(client.event.timestamp));

        cJSON_AddItemToObject(infoJson, "manufactory", cJSON_CreateString(client.device_info.manufactory));
        cJSON_AddItemToObject(infoJson, "fwVer", cJSON_CreateString(client.device_info.fw_version));
        cJSON_AddItemToObject(infoJson, "model", cJSON_CreateString(client.device_info.model));

        cJSON_AddItemToObject(deviceJson, "event", eventJson);
        cJSON_AddItemToObject(deviceJson, "battery", batteryJson);
        cJSON_AddItemToObject(deviceJson, "info", infoJson);

        cJSON_AddItemToObject(rootJson, client.clientIDjson, deviceJson);
        char *json_string = cJSON_Print(rootJson);

        cJSON_Minify(json_string);
        cJSON_Delete(rootJson);
        return json_string;
    }
}