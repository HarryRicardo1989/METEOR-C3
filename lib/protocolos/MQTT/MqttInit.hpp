#pragma once
#include "connections.h"
#include <vector>
#include <string>
#include "tasks_common.h"
#include "MqttClient.hpp"
#include "MqttPublish.hpp"
namespace PROTOCOL
{
    class MqttInit
    {
    private:
        std::vector<char> mqttsub_scription;

    public:
        MqttInit(/* args */);
        ~MqttInit();
        void connect();
        void disconnect();
        void subscribe();
        void unsubscribe();
        void publish_full_data();
    };

}