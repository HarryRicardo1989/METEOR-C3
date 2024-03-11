// MqttClient.hpp
#pragma once

#include "mqtt_client.h"
#include "mqtt5_client.h"
#include "esp_log.h"
#include "sleep_timer.h"
#include "connections.h"
#include "rw_data.h"

namespace PROTOCOL
{
#define TAG "MQTT_EVENT"

    class MqttClient
    {
    public:
        static MqttClient &getInstance()
        {
            static MqttClient instance; // Instância única
            return instance;
        }

        MqttClient(MqttClient const &) = delete;
        void operator=(MqttClient const &) = delete;
        ~MqttClient(); // Destruidor

        void connect();
        void disconnect();
        void subscribe(const char *topic);
        void unsubscribe(const char *topic);
        void publish(const char *topic, char *data, int qos, int retain);

    private:
        MqttClient(); // Construtor privado
        esp_mqtt_client_config_t mqtt_cfg = {};
        esp_mqtt_client_handle_t client;
        static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
    };

}