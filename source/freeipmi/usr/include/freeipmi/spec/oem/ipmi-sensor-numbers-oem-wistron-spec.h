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

#ifndef IPMI_SENSOR_NUMBERS_OEM_WISTRON_SPEC_H
#define IPMI_SENSOR_NUMBERS_OEM_WISTRON_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Wistron / Dell Poweredge C6220
 */

#define IPMI_SENSOR_NUMBER_OEM_WISTRON_PROCESSOR          0x04
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_MEMORY             0x60
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_QPI_SENSOR_ID      0x71
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_INT_SENSOR_ID      0x72
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_PCI_SENSOR_ID      0x73
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_SB_SENSOR_ID       0x77
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_POST_START         0x81
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_POST_END           0x85 
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_POST_ERROR         0x86 
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_BIOS_RECOVERY_FAIL 0x89
#define IPMI_SENSOR_NUMBER_OEM_WISTRON_ME_FAIL            0x8A

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_NUMBERS_OEM_WISTRON_SPEC_H */
