#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "tasks_common.h"
#include "connections.h"
#include "MQTT/MqttClient.hpp"
#include "cJSON.h"
#include "esp_mac.h"
#include "rw_data.h"

namespace PROTOCOL
{

    class MqttPublish
    {
    private:
        struct subtopic
        {
            char *topic;
            char *value;
            int qos = 2;
            int retain = 1;
        };
        subtopic temperature;
        subtopic humidity;
        subtopic pressure;
        subtopic dewpoint;

        subtopic level;
        subtopic critical;
        subtopic voltage;
        subtopic charging;
        subtopic charged;
        subtopic manufactory;
        subtopic fwVer;
        subtopic model;
        subtopic MAC_address;
        subtopic clientID_pub;
        subtopic jsonToSite;

        char *clientID;

        void concat_string(char *resultado, char *str1, char *str2, char *str3);
        char *convert_value_to_string(int value);
        MqttPublish();                                // Construtor agora é privado.
        MqttPublish(const MqttPublish &) = delete;    // Construtor de cópia deletado.
        void operator=(const MqttPublish &) = delete; // Operador de atribuição deletado.
        char *create_Json_to_send();

    public:
        static MqttPublish &getInstance()
        {
            static MqttPublish instance; // Instância única criada internamente.
            return instance;
        }
        ~MqttPublish();

        void publish_all();
        void publish_temperature();
        void publish_humidity();
        void publish_pressure();
        void publish_dewpoint();

        void publish_level();
        void publish_critical();
        void publish_voltage();
        void publish_charging();
        void publish_charged();
        void publish_manufactory();
        void publish_fwVer();
        void publish_model();
        void publish_MAC();
        void publish_ClientID();
        void publish_to_site();
    };
} // namespace PROTOCOL
