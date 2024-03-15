#include "esp_init.hpp"
#include "esp_cleanup.h"
#include "OledDisplay.hpp"

WiFiManager *wifi = nullptr;
PROTOCOL::MqttInit *mqtt_initialize = nullptr;
PROTOCOL::I2c *i2c = nullptr;
OLED *oledDisplay = nullptr;

void init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    if (esp_reset_reason() == ESP_RST_DEEPSLEEP)
    {
        printf("\n\nACORDEI\n\n");

        deisolate_gpio();
    }
    int updateStatus = read_nvs_int8_var(UPDATE_STATUS);
    if (updateStatus != 0 && updateStatus != 1)
    {
        save_nvs_int8_var(UPDATE_STATUS, 0);
    }
}
void init_routines(void)
{
    battery_things();
    generate_client_ID();

    init_i2c();
    capture_data();
    tryConnectToWiFi();

    if (wifi->isConnected())
    {
        esp_ip4_addr_t ip = wifi->getIP();
        ESP_LOGW("WIFI-STATUS", "Connected at IP: %d.%d.%d.%d", IP2STR(&ip));
        mqtt_initialize->connect();
        blink_led_custom(0, 100, 0, 20, 50, 1);
        mqtt_initialize->subscribe();
        blink_led_custom(100, 100, 100, 20, 50, 3);
        mqtt_task_pub_init();
    }
}
void capture_data(void)
{
    CPPBME280::BME280 bme280i2c;
    bme280i2c.InitI2c(i2c, 0x76);
    bme280i2c.Init();
    bme280i2c.SetMode(3);
    bme280i2c.SetConfigFilter(1);
    float i2cTemperature;
    float i2cPressure;
    int i2cHumidity;
    float i2cDewPoint;
    bme280i2c.GetAllResults(&i2cTemperature, &i2cHumidity, &i2cPressure, &i2cDewPoint);
    int bat_level = read_nvs_int8_var(BATTERY_PERCENT_VALUE);
    uint32_t bat_mv = read_nvs_uint32_var(BATTERY_VALUE);
    save_nvs_string_var(TEMPERATURE, convert_float_to_string(i2cTemperature));
    save_nvs_string_var(HUMIDITY, convert_value_to_string(i2cHumidity));
    save_nvs_string_var(PRESSURE, convert_float_to_string(i2cPressure));
    save_nvs_string_var(DEWPOINT, convert_float_to_string(i2cDewPoint));
    display_meteor(i2cTemperature, i2cPressure, i2cHumidity, i2cDewPoint, bat_level, bat_mv);
}

void scanI2CDevices(int sdaPin, int sclPin)
{
    printf("Scan init...\n");
    printf("Scan prepare...\n");

    printf("Scanning I2C bus...\n");
    for (uint8_t address = 1; address < 0x7F; address++)
    {

        if (i2c->testConnection(address))
        {
            printf("I2C device found at address 0x%2X \n", address);
        }
    }
}

void tryConnectToWiFi(void)
{
    const char *ssids[] = {SSID3, SSID1};
    const char *passwords[] = {PASSWORD3, PASSWORD1};
    wifi = new WiFiManager();
    mqtt_initialize = new PROTOCOL::MqttInit();

    for (int i = 0; i < 5; i++)
    {
        wifi->connect(ssids[i], passwords[i]);
        int attempt = 0;
        while (!wifi->isConnected() && attempt < 30)
        { // Tenta até 10 vezes para cada rede
            ESP_LOGW("WIFI-STATUS", "Attempting to connect to %s", ssids[i]);
            vTaskDelay(100 * portTICK_PERIOD_MS);
            attempt++;
            blink_led_custom(50, 0, 50, 30, 50, 1);
        }
        if (wifi->isConnected())
        {
            blink_led_custom(0, 100, 0, 20, 50, 4);
            ESP_LOGI("WIFI-STATUS", "Connected to %s", ssids[i]);
            return; // Conexão bem-sucedida, sai da função
        }

        wifi->disconnect();
    }
    blink_led_custom(100, 0, 0, 15, 50, 5);
    ESP_LOGW("WIFI-STATUS", "Failed to connect to any network");
}
void generate_client_ID(void)
{
    char clientID_raw[30];
    char mac_str[18];
    char *clientID;
    char *mac_address;
    uint8_t raw_mac[6];

    esp_read_mac(raw_mac, ESP_MAC_WIFI_STA);

    sprintf(mac_str, "%02X:%02X:%02X:%02X:%02X:%02X", raw_mac[0], raw_mac[1], raw_mac[2], raw_mac[3], raw_mac[4], raw_mac[5]);
    sprintf(clientID_raw, "METEOR-%02X:%02X:%02X:%02X:%02X:%02X", raw_mac[0], raw_mac[1], raw_mac[2], raw_mac[3], raw_mac[4], raw_mac[5]);
    mac_address = mac_str;
    clientID = clientID_raw;
    save_nvs_string_var(CLIENT_ID, clientID);
    save_nvs_string_var(MAC_ADDRESS, mac_address);
}
extern "C"
{
    void cleanup()
    {
        if (wifi != nullptr)
        {
            delete wifi;
            wifi = nullptr;
        }

        if (mqtt_initialize != nullptr)
        {
            delete mqtt_initialize;
            mqtt_initialize = nullptr;
        }
        if (i2c != nullptr)
        {

            delete i2c;
            i2c = nullptr;
        }
        if (oledDisplay != nullptr)
        {
            delete oledDisplay;
            oledDisplay = nullptr;
        }
    }
}

char *convert_value_to_string(int value)
{
    std::string stringValue = std::to_string(value);
    char *string = new char[stringValue.length() + 1];
    strcpy(string, stringValue.c_str());

    return string;
}

char *convert_float_to_string(float value)
{
    // Utiliza stringstream para controle de formato
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value; // Limita a 2 casas decimais
    std::string stringValue = stream.str();

    // Aloca memória para o resultado
    char *string = new char[stringValue.length() + 1];
    strcpy(string, stringValue.c_str());

    return string;
}

void battery_things(void)
{
    BATTERY::BatteryStatus bat_status = BATTERY::BatteryStatus();
    uint32_t bat_mv;
    uint8_t bat_level;
    bat_mv = bat_status.battery_read(100);
    bat_level = bat_status.battery_percent(bat_mv);
    bool charged = bat_status.battery_charged();
    bool charging = bat_status.battery_charging();
    save_nvs_u32_var(BATTERY_VALUE, bat_mv);
    save_nvs_int8_var(BATTERY_PERCENT_VALUE, bat_level);
    save_nvs_int8_var(BATTERY_CHARGED_STATUS, charged);
    save_nvs_int8_var(BATTERY_CHARGING_STATUS, charging);
    ESP_LOGI("BATTERY", "%ld", bat_mv);
}

void init_i2c(void)
{
    i2c = new PROTOCOL::I2c(I2C_NUM_0);
    i2c->InitMaster(SDA_PIN, SCL_PIN, I2C_CLK_SPEED_HZ, true, true);
    oledDisplay = new OLED(i2c, 0x3c);
    oledDisplay->init();
    oledDisplay->setContrast(1);
    oledDisplay->initScreenBuffer();
}

void display_meteor(float temperature, float pressure, int humidity, float i2cDewPoint, int battery_level, u_int32_t battery_voltage)
{
    char buffer[30]; // Buffer para armazenar o texto formatado

    oledDisplay->displayTextBuffered("*METEOR*", 10, 0);
    sprintf(buffer, "%d%%", battery_level); // Formata o nível da bateria
    oledDisplay->displayTextBuffered(buffer, 95, 0);

    sprintf(buffer, "Temp: %2.2fC", temperature); // Formata a temperatura
    oledDisplay->displayTextBuffered(buffer, 0, 16);

    sprintf(buffer, "Humid: %d%%", humidity); // Formata a umidade
    oledDisplay->displayTextBuffered(buffer, 0, 24);

    sprintf(buffer, "Press: %4.2fhPa", pressure); // Formata a pressão
    oledDisplay->displayTextBuffered(buffer, 0, 32);

    sprintf(buffer, "DewP: %2.2fC", i2cDewPoint); // Formata o ponto de orvalho
    oledDisplay->displayTextBuffered(buffer, 0, 40);

    sprintf(buffer, "Bat: %ldmV", battery_voltage); // Formata a tensao da bateria
    oledDisplay->displayTextBuffered(buffer, 0, 56);

    oledDisplay->updateDisplay();
}

void otaInit(void)
{
    char buffer[30];
    ESP_LOGW("WIFI-STATUS", "passou 1");
    tryConnectToWiFi();
    ESP_LOGW("WIFI-STATUS", "passou 2");

    if (wifi->isConnected())
    {
        ESP_LOGW("WIFI-STATUS", "passou 3");
        esp_ip4_addr_t ip = wifi->getIP();
        ESP_LOGW("WIFI-STATUS", "Connected at IP: %d.%d.%d.%d", IP2STR(&ip));
        init_i2c();
        oledDisplay->init();
        oledDisplay->displayWakeUp();
        oledDisplay->initScreenBuffer();

        sprintf(buffer, "Updating!");
        oledDisplay->displayTextBuffered(buffer, 20, 24);
        OtaUpdate otaUpdater;
        oledDisplay->updateDisplay();

        otaUpdater.start(read_nvs_string_var(OTA_URL));
        sprintf(buffer, "Update success!");
        oledDisplay->displayTextBuffered(buffer, 10, 24);
        oledDisplay->updateDisplay();
        vTaskDelay(1 * PORT_TICK_PERIOD_SECONDS);

        oledDisplay->displayClear();
        oledDisplay->displaySleep();
        esp_restart();
    }
}