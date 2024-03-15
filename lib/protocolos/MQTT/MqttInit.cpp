#include "MqttInit.hpp"
#include <cstring>
#include <string>
namespace PROTOCOL
{

    MqttInit::MqttInit()
    {
    }
    MqttInit::~MqttInit()
    {
    }

    void MqttInit::connect()
    {

        auto &mqtt_client_instance = MqttClient::getInstance();
        mqtt_client_instance.connect();
    }
    void MqttInit::disconnect()
    {

        auto &mqtt_client_instance = MqttClient::getInstance();
        mqtt_client_instance.disconnect();
    }
    void MqttInit::subscribe()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();
        std::string client_id = read_nvs_string_var(CLIENT_ID);
        size_t client_id_size = client_id.size();
        size_t total_size = client_id_size + strlen(MQTT_SUBTOPIC_OTA) + 1;
        mqttsub_scription.resize(total_size);
        std::memcpy(mqttsub_scription.data(), client_id.c_str(), client_id_size);
        std::strcat(mqttsub_scription.data(), MQTT_SUBTOPIC_OTA);
        mqtt_client_instance.subscribe(mqttsub_scription.data());
    }
    void MqttInit::unsubscribe()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();
        mqtt_client_instance.unsubscribe(mqttsub_scription.data());
    }

    void MqttInit::publish_full_data()
    {
        auto &mqtt_publish_instance = PROTOCOL::MqttPublish::getInstance();

        mqtt_publish_instance.publish_all();
    }

}
