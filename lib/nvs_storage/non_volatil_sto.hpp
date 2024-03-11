/**
 * @file non_volatil_sto.hpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief
 * @date 2022-10-27
 *
 *
 */
#pragma once

#include "string.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
namespace NVS
{
    class NvsMemory
    {
    private:
        nvs_handle_t nvs_handle;
        char const *nvs_storage_name;
        char const *nvs_partition_name;

    public:
        NvsMemory(char const *i_nvs_partition_name, char const *i_nvs_storage_name);

        void nvs_storage_open();
        void nvs_storage_close();
        void nvs_storage_erase_all();
        void nvs_saving_i8(char const *key, int8_t value);
        void nvs_saving_u8(char const *key, uint8_t value);
        void nvs_saving_u32(char const *key, uint32_t value);
        void nvs_saving_string(char const *key, char const *value);
        int nvs_read_i8(char const *key);
        uint8_t nvs_read_u8(char const *key);
        int nvs_read_u32(char const *key);
        char *nvs_read_string(char const *key);
        void nvs_status(void);
    };

} // namespace NVS
