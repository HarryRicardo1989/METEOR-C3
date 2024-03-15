// wifi_manager.cpp
#include "wifi_manager.hpp"

esp_ip4_addr_t WiFiManager::ip;
bool WiFiManager::connected;

WiFiManager::WiFiManager()
{
    this->connected = false;
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &eventHandler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &eventHandler, NULL));
    ESP_LOGI("WiFiManager", "Constructor");
}

WiFiManager::~WiFiManager()
{
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &eventHandler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &eventHandler));
    esp_wifi_stop();
    esp_wifi_deinit();
    ESP_LOGI("WiFiManager", "Destructor");
}

void WiFiManager::connect(const char *ssid, const char *password)
{
    wifi_config_t wifi_config = {};
    strncpy((char *)wifi_config.sta.ssid, ssid, 32);
    strncpy((char *)wifi_config.sta.password, password, 64);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI("WiFiManager", "Connecting");
}

void WiFiManager::disconnect()
{
    ESP_LOGI("WiFiManager", "Disconnect");
    esp_wifi_disconnect();
    ESP_LOGI("WiFiManager", "Disconnected");
}

esp_ip4_addr_t WiFiManager::getIP()
{
    return ip;
}

void WiFiManager::eventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ESP_LOGI("WiFiManager", "eventHandler called with event_base=%s, event_id=%ld", event_base, event_id);
    if (event_base == WIFI_EVENT)
    {

        switch (event_id)
        {
        case WIFI_EVENT_WIFI_READY:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_WIFI_READY");

            break;
        case WIFI_EVENT_SCAN_DONE:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_SCAN_DONE");

            break;
        case WIFI_EVENT_STA_START:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_STA_START");
            connected = false;
            esp_wifi_connect();
            ESP_LOGI("WiFiManager-WIFI_EVENT", "retry to connect to the AP");
            break;
        case WIFI_EVENT_STA_STOP:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_STA_STOP");

            break;
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_STA_CONNECTED");

            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_STA_DISCONNECTED");
            connected = false;
            esp_wifi_connect();
            ESP_LOGI("WiFiManager-WIFI_EVENT", "retry to connect to the AP");
            break;
        case WIFI_EVENT_AP_START:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_AP_START");

            break;
        case WIFI_EVENT_AP_STOP:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_AP_STOP");

            break;
        case WIFI_EVENT_STA_WPS_ER_FAILED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_STA_WPS_ER_FAILED");

            break;
        case WIFI_EVENT_AP_STACONNECTED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_AP_STACONNECTED");

            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_AP_STACONNECTED");

            break;
        case WIFI_EVENT_AP_PROBEREQRECVED:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_AP_PROBEREQRECVED");

            break;
        case WIFI_EVENT_FTM_REPORT:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "WIFI_EVENT_FTM_REPORT");
            break;
        default:
            ESP_LOGI("WiFiManager-WIFI_EVENT", "%d", (int)event_base);

            break;
        }
    }
    else if (event_base == IP_EVENT)
    {

        switch (event_id)
        {
        case IP_EVENT_STA_GOT_IP:
        {
            ESP_LOGI("WiFiManager", "IP_EVENT_STA_GOT_IP");
            connected = true;
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
            ip = event->ip_info.ip;
            ESP_LOGI("WiFiManager-IP_EVENT", "got ip:" IPSTR, IP2STR(&ip));
        }
        break;
        case IP_EVENT_STA_LOST_IP:
        {
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_STA_LOST_IP");
        }
        break;
        case IP_EVENT_AP_STAIPASSIGNED:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_AP_STAIPASSIGNED");
            break;
        case IP_EVENT_GOT_IP6:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_GOT_IP6");
            break;
        case IP_EVENT_ETH_GOT_IP:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_ETH_GOT_IP");

            break;
        case IP_EVENT_ETH_LOST_IP:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_ETH_LOST_IP");

            break;
        case IP_EVENT_PPP_GOT_IP:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_PPP_GOT_IP");

            break;
        case IP_EVENT_PPP_LOST_IP:
            ESP_LOGI("WiFiManager-IP_EVENT", "IP_EVENT_PPP_LOST_IP");

            break;
        default:
            ESP_LOGI("WiFiManager-IP_EVENT", "%d", (int)event_base);

            break;
        }
    }
}

bool WiFiManager::isConnected()
{
    return connected;
}