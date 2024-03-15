#include "mqtt_task.hpp"

TaskHandle_t task_mqtt_pub_handle = NULL;

void vTask_MQTT_auto_publish(void *pvParameters)
{

    while (true)
    {
        auto &mqtt_publish_instance = PROTOCOL::MqttPublish::getInstance();

        mqtt_publish_instance.publish_all();

        vTaskDelay(40 * PORT_TICK_PERIOD_SECONDS);
    }
}

void mqtt_task_pub_init()
{
    auto &mqtt_client_instance = PROTOCOL::MqttClient::getInstance();
    mqtt_client_instance.connect();
    xTaskCreate(vTask_MQTT_auto_publish, "TASK MQTT publish", VTASK_STACK_SIZE_MQTT_PUBLISH, NULL, VTASK_PRIORITY_MQTT_PUBLISH, &task_mqtt_pub_handle);
}

void mqtt_task_pub_stop()
{
    vTaskDelete(task_mqtt_pub_handle);
}
