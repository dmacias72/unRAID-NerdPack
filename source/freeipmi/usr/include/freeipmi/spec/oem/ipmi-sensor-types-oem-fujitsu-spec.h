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

#ifndef IPMI_SENSOR_TYPES_OEM_FUJITSU_SPEC_H
#define IPMI_SENSOR_TYPES_OEM_FUJITSU_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Fujitsu Siemens Computers
 * Fujitsu Technology Solutions
 * iRMC S1 / iRMC S2
 */

#define IPMI_SENSOR_TYPE_OEM_FUJITSU_I2C_BUS                    0xC0
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_SYSTEM_POWER_CONSUMPTION   0xDD // Events only
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_STATUS              0xDE
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_CONFIG              0xDF
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY                     0xE1 // Events only
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_HW_ERROR                   0xE3 // Events only
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_SYS_ERROR                  0xE4 // Events only
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_FAN_STATUS                 0xE6
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_STATUS                 0xE8
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_REDUNDANCY             0xE9
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_COMMUNICATION              0xEA // Reserved
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_FLASH                      0xEC // Events only
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_EVENT                      0xEE // Reserved
#define IPMI_SENSOR_TYPE_OEM_FUJITSU_CONFIG_BACKUP              0xEF

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_TYPES_OEM_FUJITSU_SPEC_H */
