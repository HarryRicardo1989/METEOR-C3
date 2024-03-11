/**
 * @file save_data.cpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief
 * @date 2022-10-27
 *
 *
 */

#include "rw_data.h"
#include "non_volatil_sto.hpp"
#include "tasks_common.h"

/* Creating an instance of the class `NvsMemory` from the namespace `NVS`. */
NVS::NvsMemory nvs_storage_instance = NVS::NvsMemory("RCP", "METEOR");

char *read_nvs_string_var(char *string_key)
{
    nvs_storage_instance.nvs_storage_open();
    char *readed_string = (char *)nvs_storage_instance.nvs_read_string(string_key);
    nvs_storage_instance.nvs_storage_close();
    return readed_string;
}

uint32_t read_nvs_uint32_var(char *u32_var_key)
{
    nvs_storage_instance.nvs_storage_open();
    uint32_t uint_var_value = nvs_storage_instance.nvs_read_u32(u32_var_key);
    nvs_storage_instance.nvs_storage_close();
    return uint_var_value;
}
void save_nvs_u32_var(char *u32_var_key, uint32_t uint_var_value)
{
    nvs_storage_instance.nvs_storage_open();
    nvs_storage_instance.nvs_saving_u32(u32_var_key, uint_var_value);
    nvs_storage_instance.nvs_storage_close();
}

int read_nvs_int8_var(char *int8_var_key)
{
    nvs_storage_instance.nvs_storage_open();
    int int8_var_value = nvs_storage_instance.nvs_read_i8(int8_var_key);
    nvs_storage_instance.nvs_storage_close();
    return int8_var_value;
}
void save_nvs_int8_var(char *int8_var_key, int8_t uint8_var_value)
{
    nvs_storage_instance.nvs_storage_open();
    nvs_storage_instance.nvs_saving_i8(int8_var_key, uint8_var_value);
    nvs_storage_instance.nvs_storage_close();
}

uint8_t read_nvs_u8_var(char *u8_var_key)
{
    nvs_storage_instance.nvs_storage_open();
    uint8_t u8_var_value = nvs_storage_instance.nvs_read_u8(u8_var_key);
    nvs_storage_instance.nvs_storage_close();
    return u8_var_value;
}

void save_nvs_u8_var(char *u8_var_key, uint8_t uint_var_value)
{
    nvs_storage_instance.nvs_storage_open();
    nvs_storage_instance.nvs_saving_u8(u8_var_key, uint_var_value);
    nvs_storage_instance.nvs_storage_close();
}
void save_nvs_string_var(char *string_var_key, char *string_var_value)
{
    nvs_storage_instance.nvs_storage_open();
    nvs_storage_instance.nvs_saving_string(string_var_key, string_var_value);
    nvs_storage_instance.nvs_storage_close();
}