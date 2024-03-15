#include "adc.hpp"

namespace ADC
{
    AdcController::AdcController(adc_unit_t adc_unit, adc_bitwidth_t bitwidth, adc_atten_t attenuation, adc_channel_t channel)
    {
        adc_oneshot_unit = adc_unit;
        adc_oneshot_bitwidth = bitwidth;
        adc_oneshot_attenuation = attenuation;
        adc_oneshot_channel = channel;
        ESP_LOGW("ADC", "adc_unit: %d", adc_unit);
        ESP_LOGW("ADC", "bitwidth: %d", bitwidth);
        ESP_LOGW("ADC", "attenuation: %d", attenuation);
        ESP_LOGW("ADC", "channel: %d", channel);

        _calEnabled = _checkCalFuse();

        if (_calEnabled)
        {
            cali_config.unit_id = adc_oneshot_unit;
            cali_config.atten = adc_oneshot_attenuation;
            cali_config.bitwidth = adc_oneshot_bitwidth;
            cali_scheme_mask = ADC_CALI_SCHEME_VER_CURVE_FITTING;
            err = adc_cali_create_scheme_curve_fitting(&cali_config, &cali_handle);
            if (err != ESP_OK)
            {
                ESP_LOGE("ADC", "Falha ao criar esquema de calibração");
                _calEnabled = false; // Desabilita calibração se falhar
            }
        }
    }
    AdcController::~AdcController()
    {
        if (_calEnabled && cali_handle)
        {
            // Deletar o esquema de calibração aqui
        }
    }

    int AdcController::GetRaw()
    {

        this->init_config.unit_id = this->adc_oneshot_unit;
        this->init_config.ulp_mode = ADC_ULP_MODE_DISABLE;
        this->init_config.clk_src = ADC_DIGI_CLK_SRC_DEFAULT;

        this->adc_oneshot_channel_config.bitwidth = this->adc_oneshot_bitwidth;
        this->adc_oneshot_channel_config.atten = this->adc_oneshot_attenuation;

        err = adc_oneshot_new_unit(&this->init_config, &this->adc_oneshot_handle);
        if (err != ESP_OK)
        {
            ESP_LOGE("ADC", "adc_oneshot_new_unit ERROR");
        }
        err = adc_oneshot_config_channel(this->adc_oneshot_handle, this->adc_oneshot_channel, &this->adc_oneshot_channel_config);
        if (err != ESP_OK)
        {
            ESP_LOGE("ADC", "adc_oneshot_config_channel ERROR");
        }
        int out_raw;
        err = adc_oneshot_read(this->adc_oneshot_handle, this->adc_oneshot_channel, &out_raw);
        if (err != ESP_OK)
        {
            if (err == ESP_ERR_INVALID_ARG)
            {
                ESP_LOGE("ADC", "ESP_ERR_INVALID_ARG");
            }
            else if (err == ESP_ERR_TIMEOUT)
            {
                ESP_LOGE("ADC", "ESP_ERR_TIMEOUT");
            }
            ESP_LOGE("ADC", "GetRaw ERROR");
        }
        adc_oneshot_del_unit(this->adc_oneshot_handle);
        return out_raw;
    }

    int AdcController::GetVoltage()
    {
        if (!_calEnabled)
        {
            return -1; // Calibração não habilitada ou falhou
        }

        int voltage = 0;
        int raw = GetRaw();
        err = adc_cali_raw_to_voltage(cali_handle, raw, &voltage);
        if (err != ESP_OK)
        {
            ESP_LOGE("ADC", "Erro ao converter raw para tensão");
            return -1;
        }
        return voltage;
    }

    bool AdcController::_checkCalFuse()
    {
        return true;
    }
} // namespace ADC