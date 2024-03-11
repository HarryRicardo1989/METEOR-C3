#include "MqttPublish.hpp"
#include "MqttPublish.h"
namespace PROTOCOL
{

    MqttPublish::MqttPublish()
    {
        this->clientID = read_nvs_string_var(CLIENT_ID);
    }

    MqttPublish::~MqttPublish()
    {
    }

    void MqttPublish::publish_all()
    {
        publish_temperature();
        publish_humidity();
        publish_pressure();
        publish_dewpoint();
        // publish_voltage();
        // publish_charging();
        // publish_charged();
        publish_to_site();
        /*         publish_level();
                publish_critical();
                publish_manufactory();
                publish_fwVer();
                publish_model();
                publish_MAC();
                publish_ClientID(); */
    }
    void MqttPublish::publish_temperature()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_EVENT, MQTT_SUBTOPIC_TEMPERATURE);
        this->temperature.topic = topic;
        this->temperature.value = read_nvs_string_var(TEMPERATURE);
        // this->temperature.value = convert_value_to_string(read_nvs_uint32_var(TEMPERATURE));
        ESP_LOGI("PUBLISH", "%s / %s", this->temperature.topic, this->temperature.value);
        mqtt_client_instance.publish(this->temperature.topic, this->temperature.value, this->temperature.qos, this->temperature.retain);
    }
    void MqttPublish::publish_humidity()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_EVENT, MQTT_SUBTOPIC_HUMIDITY);
        this->humidity.topic = topic;
        // this->humidity.value = convert_value_to_string(read_nvs_uint32_var(HUMIDITY));
        this->humidity.value = read_nvs_string_var(HUMIDITY);
        ESP_LOGI("PUBLISH", "%s / %s", this->humidity.topic, this->humidity.value);

        mqtt_client_instance.publish(humidity.topic, humidity.value, humidity.qos, humidity.retain);
    }
    void MqttPublish::publish_pressure()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_EVENT, MQTT_SUBTOPIC_PRESSURE);
        this->pressure.topic = topic;
        this->pressure.value = read_nvs_string_var(PRESSURE);
        ESP_LOGI("PUBLISH", "%s / %s", this->pressure.topic, this->pressure.value);

        mqtt_client_instance.publish(pressure.topic, pressure.value, pressure.qos, pressure.retain);
    }
    void MqttPublish::publish_dewpoint()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_EVENT, MQTT_SUBTOPIC_DEWPOINT);
        this->dewpoint.topic = topic;
        this->dewpoint.value = read_nvs_string_var(DEWPOINT);
        ESP_LOGI("PUBLISH", "%s / %s", this->dewpoint.topic, this->dewpoint.value);

        mqtt_client_instance.publish(dewpoint.topic, dewpoint.value, dewpoint.qos, dewpoint.retain);
    }

    void MqttPublish::publish_level()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_BATTERY, MQTT_SUBTOPIC_BATTERY_LEVEL);
        this->level.topic = topic;
        this->level.value = convert_value_to_string(read_nvs_int8_var(BATTERY_PERCENT_VALUE));
        ESP_LOGI("PUBLISH", "%s / %s", this->level.topic, this->level.value);

        mqtt_client_instance.publish(level.topic, level.value, level.qos, level.retain);
    }
    void MqttPublish::publish_critical()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_BATTERY, MQTT_SUBTOPIC_BATTERY_CRITICAL);
        this->critical.topic = topic;
        this->critical.value = convert_value_to_string(read_nvs_int8_var(BATTERY_CRITICAL_STATUS));
        ESP_LOGI("PUBLISH", "%s / %s", this->critical.topic, this->critical.value);

        mqtt_client_instance.publish(critical.topic, critical.value, critical.qos, critical.retain);
    }
    void MqttPublish::publish_voltage()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_BATTERY, MQTT_SUBTOPIC_BATTERY_VOLTAGE);
        this->voltage.topic = topic;
        this->voltage.value = convert_value_to_string(read_nvs_uint32_var(BATTERY_VALUE));
        ESP_LOGI("PUBLISH", "%s / %s", this->voltage.topic, this->voltage.value);

        mqtt_client_instance.publish(voltage.topic, voltage.value, voltage.qos, voltage.retain);
    }
    void MqttPublish::publish_charging()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_BATTERY, MQTT_SUBTOPIC_BATTERY_CHARGING);
        this->charging.topic = topic;
        this->charging.value = convert_value_to_string(read_nvs_int8_var(BATTERY_CHARGING_STATUS));
        ESP_LOGI("PUBLISH", "%s / %s", this->charging.topic, this->charging.value);

        mqtt_client_instance.publish(charging.topic, charging.value, charging.qos, charging.retain);
    }
    void MqttPublish::publish_charged()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_BATTERY, MQTT_SUBTOPIC_BATTERY_CHARGED);
        this->charged.topic = topic;
        this->charged.value = convert_value_to_string(read_nvs_int8_var(BATTERY_CHARGED_STATUS));
        ESP_LOGI("PUBLISH", "%s / %s", this->charged.topic, this->charged.value);

        mqtt_client_instance.publish(charged.topic, charged.value, charged.qos, charged.retain);
    }
    void MqttPublish::publish_manufactory()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_INFO, MQTT_SUBTOPIC_INFO_MANUFACTORY);
        this->manufactory.topic = topic;
        this->manufactory.value = MANUFACTORY;
        ESP_LOGI("PUBLISH", "%s / %s", this->manufactory.topic, this->manufactory.value);

        mqtt_client_instance.publish(manufactory.topic, manufactory.value, manufactory.qos, manufactory.retain);
    }

    void MqttPublish::publish_fwVer()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_INFO, MQTT_SUBTOPIC_INFO_FIRMWARE_VERSION);
        this->fwVer.topic = topic;
        this->fwVer.value = FIRMWARE_VERSION;
        ESP_LOGI("PUBLISH", "%s / %s", this->fwVer.topic, this->fwVer.value);

        mqtt_client_instance.publish(fwVer.topic, fwVer.value, fwVer.qos, fwVer.retain);
    }

    void MqttPublish::publish_model()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_INFO, MQTT_SUBTOPIC_INFO_MODEL);
        this->model.topic = topic;
        this->model.value = read_nvs_string_var(MODEL);
        ESP_LOGI("PUBLISH", "%s / %s", this->model.topic, this->model.value);

        mqtt_client_instance.publish(model.topic, model.value, model.qos, model.retain);
    }
    void MqttPublish::publish_MAC()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_INFO, MQTT_SUBTOPIC_INFO_MAC_ADDRESS);
        this->MAC_address.topic = topic;
        this->MAC_address.value = read_nvs_string_var(MAC_ADDRESS);
        ESP_LOGI("PUBLISH", "%s / %s", this->MAC_address.topic, this->MAC_address.value);

        mqtt_client_instance.publish(MAC_address.topic, MAC_address.value, MAC_address.qos, MAC_address.retain);
    }
    void MqttPublish::publish_ClientID()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        char *topic = new char[100];
        concat_string(topic, MQTT_TOPIC, MQTT_SUBTOPIC_INFO, MQTT_SUBTOPIC_INFO_CLIENTID);
        this->clientID_pub.topic = topic;
        this->clientID_pub.value = this->clientID;
        ESP_LOGI("PUBLISH", "%s / %s", this->clientID_pub.topic, this->clientID_pub.value);

        mqtt_client_instance.publish(clientID_pub.topic, clientID_pub.value, clientID_pub.qos, clientID_pub.retain);
    }
    void MqttPublish::publish_to_site()
    {
        auto &mqtt_client_instance = MqttClient::getInstance();

        this->jsonToSite.topic = MQTT_TOPIC_TO_SITE;
        this->jsonToSite.value = create_Json_to_send();
        ESP_LOGI("PUBLISH", "%s / %s", this->jsonToSite.topic, this->jsonToSite.value);

        mqtt_client_instance.publish(jsonToSite.topic, jsonToSite.value, jsonToSite.qos, jsonToSite.retain);
    }

    void MqttPublish::concat_string(char *resultado, char *str1, char *str2, char *str3)
    {
        strcpy(resultado, str1); // Copia a primeira string para o resultado
        strcat(resultado, str2); // Concatena a segunda string ao resultado
        strcat(resultado, str3); // Concatena a segunda string ao resultado
    }

    char *MqttPublish::convert_value_to_string(int value)
    {
        std::string stringValue = std::to_string(value);
        char *string = new char[stringValue.length() + 1];
        strcpy(string, stringValue.c_str());

        return string;
    }

}
extern "C"
{
    void publish_from_c()
    {
        auto &mqttPublish = PROTOCOL::MqttPublish::getInstance();
        mqttPublish.publish_all();
    }
}