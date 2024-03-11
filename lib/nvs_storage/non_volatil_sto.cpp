/**
 * @file non_volatil_sto.cpp
 * @author Ricardo da Costa Paschoali (ricardo.paschoali@assaabloy.com)
 * @brief
 * @date 2022-10-27
 *
 *
 */
#include "non_volatil_sto.hpp"

/* A class that is used to save and read data from the NVS memory. */
namespace NVS
{
    /**
     * The function initializes the NVS flash memory and sets the partition name and storage name
     *
     * @param i_nvs_partition_name The name of the partition to use.
     * @param i_nvs_storage_name This is the name of the NVS storage area.
     */
    NvsMemory::NvsMemory(char const *i_nvs_partition_name, char const *i_nvs_storage_name)
    {
        nvs_flash_init();
        nvs_partition_name = i_nvs_partition_name;
        nvs_storage_name = i_nvs_storage_name;
        nvs_flash_init_partition(nvs_partition_name);
    }

    void NvsMemory::nvs_storage_open()
    {
        nvs_open(nvs_storage_name, NVS_READWRITE, &nvs_handle);
    }

    void NvsMemory::nvs_storage_close()
    {
        nvs_close(nvs_handle);
    }
    void NvsMemory::nvs_storage_erase_all()
    {
        nvs_erase_all(nvs_handle);
        nvs_flash_erase_partition(nvs_partition_name);
        nvs_flash_erase();
    }
    void NvsMemory::nvs_saving_u32(char const *key, uint32_t value)
    {
        nvs_erase_key(nvs_handle, key);
        nvs_set_u32(nvs_handle, key, value);
        nvs_commit(nvs_handle);
    }
    void NvsMemory::nvs_saving_i8(char const *key, int8_t value)
    {
        nvs_erase_key(nvs_handle, key);
        nvs_set_i8(nvs_handle, key, value);
        nvs_commit(nvs_handle);
    }
    void NvsMemory::nvs_saving_u8(char const *key, uint8_t value)
    {
        nvs_erase_key(nvs_handle, key);
        nvs_set_u8(nvs_handle, key, value);
        nvs_commit(nvs_handle);
    }
    void NvsMemory::nvs_saving_string(char const *key, char const *value)
    {
        nvs_erase_key(nvs_handle, key);
        nvs_set_str(nvs_handle, key, value);
        nvs_commit(nvs_handle);
    }
    int NvsMemory::nvs_read_u32(char const *key)
    {
        uint32_t read_data;
        nvs_get_u32(nvs_handle, key, &read_data);
        return read_data;
    }
    int NvsMemory::nvs_read_i8(char const *key)
    {
        int8_t read_data;
        nvs_get_i8(nvs_handle, key, &read_data);
        return read_data;
    }
    uint8_t NvsMemory::nvs_read_u8(char const *key)
    {
        uint8_t read_data;
        nvs_get_u8(nvs_handle, key, &read_data);
        return read_data;
    }

    char *NvsMemory::nvs_read_string(char const *key)
    {
        size_t required_size;
        nvs_get_str(nvs_handle, key, NULL, &required_size);
        char *message_nvs_string = (char *)malloc(required_size);
        nvs_get_str(nvs_handle, key, message_nvs_string, &required_size);
        return message_nvs_string;
    }
    void NvsMemory::nvs_status(void)
    {
        nvs_stats_t nvs_stats;
        nvs_get_stats(NULL, &nvs_stats);
        printf("Count: UsedEntries = (%d), FreeEntries = (%d), AllEntries = (%d)\n", nvs_stats.used_entries, nvs_stats.free_entries, nvs_stats.total_entries);
    }

} // namespace NVS
