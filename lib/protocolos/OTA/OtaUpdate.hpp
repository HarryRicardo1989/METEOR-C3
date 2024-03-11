#pragma once

#include "esp_http_client.h"
#include "esp_ota_ops.h"

class OtaUpdater
{
public:
    OtaUpdater();
    ~OtaUpdater();
    void begin(const char *updateUrl);
    void handle();

private:
    static const int UPDATE_BUFFER_SIZE = 2048; // Tamanho do buffer para dados OTA
    uint8_t update_buffer[UPDATE_BUFFER_SIZE];  // Buffer para armazenar dados temporariamente

    esp_http_client_handle_t httpClient;
    esp_ota_handle_t otaHandle;
    const esp_partition_t *updatePartition;
    bool inProgress;
    esp_err_t startUpdate(const char *url);
    esp_err_t finishUpdate();
    esp_err_t performUpdate(uint8_t *data, int dataLen);
    static esp_err_t httpEventHandler(esp_http_client_event_t *evt);
    size_t totalDataReceived = 0; // Adiciona esta linha
    size_t totalDataSize = 0;
};
