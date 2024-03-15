// MqttClient.cpp
#include "MqttClient.hpp"

namespace PROTOCOL
{
    MqttClient::MqttClient()
    {
        mqtt_cfg.broker.address.hostname = MQTT_URI;
        mqtt_cfg.broker.address.port = MQTT_PORT;
        // mqtt_cfg.broker.address.transport = MQTT_TRANSPORT_OVER_SSL;
        mqtt_cfg.broker.address.transport = MQTT_TRANSPORT_OVER_TCP;

        mqtt_cfg.credentials.client_id = read_nvs_string_var(CLIENT_ID);
        mqtt_cfg.credentials.username = MQTT_CLIENT_USER;
        mqtt_cfg.credentials.authentication.password = MQTT_CLIENT_PASS;
        mqtt_cfg.credentials.authentication.use_secure_element = true;
        // mqtt_cfg.session.protocol_ver = MQTT_PROTOCOL_V_3_1;
        mqtt_cfg.session.protocol_ver = MQTT_PROTOCOL_V_3_1_1;
        // mqtt_cfg.session.protocol_ver = MQTT_PROTOCOL_V_5;

        // Inicializa o cliente MQTT
        client = esp_mqtt_client_init(&mqtt_cfg);
        esp_mqtt_set_config(client, &mqtt_cfg);
    }

    MqttClient::~MqttClient()
    {
        if (this->client != nullptr)
        {
            esp_mqtt_client_stop(this->client);
            esp_mqtt_client_destroy(this->client);
            this->client = nullptr;
        }
    }

    void MqttClient::connect()
    {
        ESP_LOGI("MqttClient", "try to start");
        esp_mqtt_client_register_event(client, static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID), MqttClient::mqtt_event_handler, this);
        esp_mqtt_client_start(this->client);
        ESP_LOGI("MqttClient", "started");
    }

    void MqttClient::disconnect()

    {
        ESP_LOGI("MqttClient", "try to stop");
        esp_mqtt_client_stop(client);

        ESP_LOGI("MqttClient", "stop");
    }

    void MqttClient::subscribe(const char *topic)
    {
        ESP_LOGI("MqttClient", "try to subscribe");
        esp_mqtt_client_subscribe(client, topic, 2);
        ESP_LOGI("SUBSCRIBE", "%s", topic);
    }

    void MqttClient::unsubscribe(const char *topic)
    {
        esp_mqtt_client_unsubscribe(client, topic);
        ESP_LOGI("MqttClient", "unsubscribe");
    }

    void MqttClient::publish(const char *topic, char *data, int qos, int retain)
    {
        esp_mqtt_client_publish(client, topic, data, 0, qos, retain);
    }
    void MqttClient::concat_string(char *resultado, char *str1, char *str2)
    {
        strcpy(resultado, str1); // Copia a primeira string para o resultado
        strcat(resultado, str2); // Concatena a segunda string ao resultado
    }
    void MqttClient::mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
    {
        MqttClient *instance = static_cast<MqttClient *>(handler_args);
        ESP_LOGI("mqtt_event_handler", "in");

        switch (event_id)
        {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI("MQTT_EVENT", "Connected to MQTT broker");
            break;

        case MQTT_EVENT_SUBSCRIBED:
        {
            esp_mqtt_event_handle_t event_handle = static_cast<esp_mqtt_event_handle_t>(event_data);
            if (event_handle != nullptr && event_handle->topic != nullptr)
            {

                ESP_LOGI("MQTT_EVENT", "Subscribed to topic '%s'", event_handle->topic);
            }
            break;
        }
        case MQTT_EVENT_DATA:
        {
            esp_mqtt_event_handle_t event_handle = static_cast<esp_mqtt_event_handle_t>(event_data);
            if (event_handle != nullptr && event_handle->data != nullptr)
            {
                size_t data_len = event_handle->data_len;
                char *received_data = static_cast<char *>(malloc(data_len + 1)); // +1 para o caractere nulo
                if (received_data != nullptr)
                {
                    strncpy(received_data, event_handle->data, data_len);
                    received_data[data_len] = '\0'; // Adiciona o caractere nulo ao final da string

                    // Agora 'received_data' contém os dados recebidos do tópico
                    ESP_LOGI("MQTT_EVENT", "Received data on topic '%s'", received_data);
                    if (strcmp(received_data, "vairfactory") == 0)
                    {
                        ESP_LOGW("FACTORY", "Factory Default");
                    }
                    else
                    {

                        ESP_LOGW("COMMAND", "%s", received_data);
                        save_nvs_int8_var(UPDATE_STATUS, true);
                        save_nvs_string_var(OTA_URL, received_data);
                        ESP_LOGW("UPDATE_STATUS", "true");
                        char *client_ID = read_nvs_string_var(CLIENT_ID);
                        char *topic = new char[100];
                        instance->concat_string(topic, client_ID, MQTT_SUBTOPIC_OTA);
                        instance->publish(topic, (char *)"", 2, true);

                        vTaskDelay(3 * PORT_TICK_PERIOD_SECONDS);
                        esp_restart();
                    }
                    // Lembre-se de liberar a memória alocada quando não precisar mais
                    free(received_data);
                }
            }
        }

        break;

        default:
            break;
        }
    }

}