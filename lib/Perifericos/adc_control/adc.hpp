#pragma once

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

#include "esp_log.h"

namespace ADC
{
    class AdcController
    {

    private:
        esp_err_t err = ESP_OK;

        adc_unit_t adc_oneshot_unit;
        adc_bitwidth_t adc_oneshot_bitwidth;
        adc_atten_t adc_oneshot_attenuation;
        adc_channel_t adc_oneshot_channel;

        adc_oneshot_unit_handle_t adc_oneshot_handle;

        adc_oneshot_unit_init_cfg_t init_config;
        adc_oneshot_chan_cfg_t adc_oneshot_channel_config;

        adc_cali_curve_fitting_config_t cali_config;

        adc_cali_scheme_ver_t cali_scheme_mask;

        adc_cali_handle_t cali_handle = nullptr;

        bool _calEnabled;

        bool _checkCalFuse();

    public:
        AdcController(adc_unit_t unit, adc_bitwidth_t width, adc_atten_t attenuation, adc_channel_t channel);
        ~AdcController();
        int GetRaw();
        int GetVoltage();
    };
} // namespace ADC
