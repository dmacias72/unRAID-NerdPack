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

#ifndef IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_SPEC_H
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel Node Manager
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 * Intel S2600KP
 * Intel S2600WT2
 * Intel S2600WTT
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 * Quanta QSSC-S4R/Appro GB812X-CN
 */

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_EXCEPTION_EVENT                       0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_HEALTH_EVENT                          0x73
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_OPERATIONAL_CAPABILITIES_CHANGE_EVENT 0x74
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_ALERT_THRESHOLD_EXCEEDED              0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_ME_FIRMWARE_HEALTH_EVENT                           0x75
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_SERVER_PLATFORM_SERVICES_FIRMWARE_HEALTH           IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_ME_FIRMWARE_HEALTH_EVENT
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_THERMAL_SENSOR_ON_DIMM                             0x76

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_CUPS_EVENT                            0x72

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_NODE_MANAGER_SPEC_H */
