#pragma once

#include "esp_err.h"
#include "esp_http_client.h"

class OtaUpdate
{
public:
    OtaUpdate();
    esp_err_t start(const char *ota_url);

private:
    static esp_err_t http_event_handler(esp_http_client_event_t *evt); // Corrigido
};
