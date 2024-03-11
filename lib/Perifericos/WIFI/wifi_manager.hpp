#pragma once

// wifi_manager.hpp
#include "esp_wifi.h"
#include "esp_event.h"
#include <cstring>
#include "esp_log.h"

class WiFiManager
{
public:
    WiFiManager();
    ~WiFiManager();
    void connect(const char *ssid, const char *password);
    void disconnect();
    esp_ip4_addr_t getIP();
    bool isConnected();

private:
    static void eventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
    static esp_ip4_addr_t ip;
    static bool connected;
};
