/*
 * Copyright (C) 2003-2015 FreeIPMI Core Team
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_FUJITSU_SPEC_H
#define IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_FUJITSU_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 * Fujitsu Siemens Computers
 * Fujitsu Technology Solutions
 * iRMC S1 / iRMC S2
 */

/* 0xC0 / IPMI_SENSOR_TYPE_OEM_FUJITSU_I2C_BUS*/
extern const char * const ipmi_sensor_type_oem_fujitsu_i2c_bus[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_i2c_bus_max_index;

/* 0xDD / IPMI_SENSOR_TYPE_OEM_FUJITSU_SYSTEM_POWER_CONSUMPTION */
extern const char * const ipmi_sensor_type_oem_fujitsu_system_power_consumption[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_system_power_consumption_max_index;

/* 0xDE / IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_STATUS */
extern const char * const ipmi_sensor_type_oem_fujitsu_memory_status[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_memory_status_max_index;

/* 0xDF / IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_CONFIG */
extern const char * const ipmi_sensor_type_oem_fujitsu_memory_config[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_memory_config_max_index;

/* 0xE1 / IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY */
extern const char * const ipmi_sensor_type_oem_fujitsu_memory[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_memory_max_index;

/* 0xE3 / IPMI_SENSOR_TYPE_OEM_FUJITSU_HW_ERROR */
extern const char * const ipmi_sensor_type_oem_fujitsu_hw_error[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_hw_error_max_index;

/* 0xE4 / IPMI_SENSOR_TYPE_OEM_FUJITSU_SYS_ERROR */
extern const char * const ipmi_sensor_type_oem_fujitsu_sys_error[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_sys_error_max_index;

/* 0xE6 / IPMI_SENSOR_TYPE_OEM_FUJITSU_FAN_STATUS */
extern const char * const ipmi_sensor_type_oem_fujitsu_fan_status[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_fan_status_max_index;

/* 0xE8 / IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_STATUS */
extern const char * const ipmi_sensor_type_oem_fujitsu_psu_status[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_psu_status_max_index;

/* 0xE9 / IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_REDUNDANCY */
extern const char * const ipmi_sensor_type_oem_fujitsu_psu_redundancy[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_psu_redundancy_max_index;

/* 0xEC / IPMI_SENSOR_TYPE_OEM_FUJITSU_FLASH */
extern const char * const ipmi_sensor_type_oem_fujitsu_flash[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_flash_max_index;

/* 0xEF / IPMI_SENSOR_TYPE_OEM_FUJITSU_CONFIG_BACKUP */
extern const char * const ipmi_sensor_type_oem_fujitsu_config_backup[];
extern unsigned int ipmi_sensor_type_oem_fujitsu_config_backup_max_index;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_FUJITSU_SPEC_H */
