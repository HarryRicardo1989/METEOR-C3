#include "OtaUpdate.hpp"
#include <string.h>
#include "esp_log.h"

static const char *TAG = "OTA";

OtaUpdater::OtaUpdater() : httpClient(nullptr), otaHandle(0), updatePartition(nullptr), inProgress(false) {}
OtaUpdater::~OtaUpdater()
{
    if (httpClient)
    {
        esp_http_client_cleanup(httpClient);
    }
}

void OtaUpdater::begin(const char *updateUrl)
{
    if (inProgress)
        return; // Já em progresso

    esp_http_client_config_t config = {};
    config.url = updateUrl; // Certifique-se que começa com "http://"
    config.port = 80;       // Porta correta para HTTP
    config.event_handler = httpEventHandler;
    config.user_data = this;                         // Passa a instância atual como dado do usuário para o manipulador de eventos
    config.transport_type = HTTP_TRANSPORT_OVER_TCP; // Configuração correta para HTTP

    httpClient = esp_http_client_init(&config);

    if (startUpdate(updateUrl) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start OTA");
    }
}

void OtaUpdater::handle()
{
    if (!inProgress)
        return;

    // Processo de leitura de dados e atualização é gerenciado pelo evento HTTP
}

esp_err_t OtaUpdater::startUpdate(const char *url)
{
    ESP_LOGI(TAG, "Starting update from URL: %s", url);

    // Inicia a conexão HTTP
    esp_err_t err = esp_http_client_open(httpClient, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        return err;
    }

    // Obtém o tamanho do conteúdo do arquivo a ser baixado
    esp_http_client_fetch_headers(httpClient);

    // Lê os dados e escreve na partição OTA
    int data_read = esp_http_client_read(httpClient, (char *)update_buffer, UPDATE_BUFFER_SIZE); // Correção aqui
    while (data_read > 0)
    {
        if (esp_ota_write(otaHandle, (const void *)update_buffer, data_read) != ESP_OK) // Usando update_buffer diretamente
        {
            ESP_LOGE(TAG, "Error with OTA write operation");
            return ESP_FAIL; // Saída antecipada em caso de falha
        }

        // Tenta ler mais dados
        data_read = esp_http_client_read(httpClient, (char *)update_buffer, UPDATE_BUFFER_SIZE); // Correção aqui
    }
    if (data_read < 0)
    {
        ESP_LOGE(TAG, "Error or end of data reached");
    }

    // Fecha a conexão HTTP
    esp_http_client_close(httpClient);

    // Finaliza a atualização, se tudo correu bem
    if (data_read >= 0)
    {
        return finishUpdate();
    }

    inProgress = false;
    return ESP_FAIL;
}

esp_err_t OtaUpdater::performUpdate(uint8_t *data, int dataLen)
{
    if (data == nullptr || dataLen == 0)
    {
        return ESP_FAIL;
    }

    if (esp_ota_write(otaHandle, (const void *)data, dataLen) != ESP_OK)
    {
        ESP_LOGE(TAG, "Error with OTA write operation");
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t OtaUpdater::finishUpdate()
{
    if (esp_ota_end(otaHandle) != ESP_OK)
    {
        ESP_LOGE(TAG, "OTA end failed");
        return ESP_FAIL;
    }

    if (esp_ota_set_boot_partition(updatePartition) != ESP_OK)
    {
        ESP_LOGE(TAG, "OTA set boot partition failed");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "OTA Success, Rebooting...");
    esp_restart();
    return ESP_OK;
}

esp_err_t OtaUpdater::httpEventHandler(esp_http_client_event_t *evt)
{
    OtaUpdater *otaUpdater = static_cast<OtaUpdater *>(evt->user_data);

    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        if (!esp_http_client_is_chunked_response(evt->client))
        {
            otaUpdater->totalDataReceived += evt->data_len;

            ESP_LOGI(TAG, "Received %d bytes", otaUpdater->totalDataReceived);

            if (otaUpdater->inProgress)
            {
                otaUpdater->performUpdate((uint8_t *)evt->data, evt->data_len);
            }
        }
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        if (otaUpdater->inProgress)
        {
            otaUpdater->finishUpdate();
        }
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    default:
        break;
    }
    return ESP_OK;
}