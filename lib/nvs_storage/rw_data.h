#pragma once

#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

    char *read_nvs_string_var(char *string_key);
    uint32_t read_nvs_uint32_var(char *u32_var_key);
    int read_nvs_int8_var(char *int8_var_key);
    void save_nvs_int8_var(char *int8_var_key, int8_t uint8_var_value);

    uint8_t read_nvs_u8_var(char *u8_var_key);
    void save_nvs_string_var(char *string_var_key, char *string_var_value);
    void save_nvs_u32_var(char *u32_var_key, uint32_t uint_var_value);
    void save_nvs_u8_var(char *u8_var_key, uint8_t uint_var_value);

#ifdef __cplusplus
}
#endif