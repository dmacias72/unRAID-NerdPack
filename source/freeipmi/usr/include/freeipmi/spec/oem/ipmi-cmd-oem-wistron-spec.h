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

#ifndef IPMI_CMD_OEM_WISTRON_SPEC_H
#define IPMI_CMD_OEM_WISTRON_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Wistron / Dell Poweredge C6220
 */

/* IPMI_NET_FN_FIRMWARE_RQ / IPMI_NET_FN_FIRMWARE_RS */
#define IPMI_CMD_OEM_WISTRON_UPDATE_FIRMARE           0x01
#define IPMI_CMD_OEM_WISTRON_GET_UPDATE_STATUS        0x02
#define IPMI_CMD_OEM_WISTRON_COPY_IMAGE_DATA          0x03
#define IPMI_CMD_OEM_WISTRON_USB_FIRMWARE_UPDATE      0x04
#define IPMI_CMD_OEM_WISTRON_WRITE_PROPRIETARY_STRING 0x0B
#define IPMI_CMD_OEM_WISTRON_READ_PROPRIETARY_STRING  0x0C
#define IPMI_CMD_OEM_WISTRON_CLEAR_PROPRIETARY_STRING 0x0D

/* IPMI_NET_FN_OEM_WISTRON_GENERIC_RQ / IPMI_NET_FN_OEM_WISTRON_GENERIC_RS */
#define IPMI_CMD_OEM_WISTRON_RESERVED_EXTENDED_CONFIGURATION     0x01
#define IPMI_CMD_OEM_WISTRON_GET_EXTENDED_CONFIGURATION          0x02
#define IPMI_CMD_OEM_WISTRON_SET_EXTENDED_CONFIGURATION          0x03
#define IPMI_CMD_OEM_WISTRON_RESET_TO_DEFAULTS                   0x04
#define IPMI_CMD_OEM_WISTRON_GET_RESTORE_STATUS                  0x05
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_CONFIGURATION           0x11
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_CONFIGURATION           0x12
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_NAME                    0x13
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_NAME                    0x14
#define IPMI_CMD_OEM_WISTRON_SET_SENSOR_INFO                     0x15
#define IPMI_CMD_OEM_WISTRON_GET_SENSOR_INFO                     0x16
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_ENCLOSURE_POWER_CAPPING 0x17
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_ENCLOSURE_POWER_CAPPING 0x18
#define IPMI_CMD_OEM_WISTRON_SET_FAN_SPEED_CONTROL               0x19
#define IPMI_CMD_OEM_WISTRON_GET_FAN_SPEED_CONTROL               0x1A
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_LED_STATUS              0x1B
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_LED_STATUS              0x1C
#define IPMI_CMD_OEM_WISTRON_SET_HDD_INFO                        0x1D
#define IPMI_CMD_OEM_WISTRON_SET_PSU_INFO                        0x1E
#define IPMI_CMD_OEM_WISTRON_GET_PSU_INFO                        0x1F
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_SERVICE_TAG             0x20
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_SERVICE_TAG             0x25
#define IPMI_CMD_OEM_WISTRON_SYNCHRONIZE CHASSIS_SERVICE_TAG     0x26
#define IPMI_CMD_OEM_WISTRON_SET_PSU_CONFIGURATION               0x27
#define IPMI_CMD_OEM_WISTRON_GET_PSU_CONFIGURATION               0x28
#define IPMI_CMD_OEM_WISTRON_SYNCHRONIZE_CHASSIS_ENCLOSURE_POWER 0x29
#define IPMI_CMD_OEM_WISTRON_SET_THERMAL_THROTTLING              0x2A
#define IPMI_CMD_OEM_WISTRON_GET_THERMAL_THROTTLING              0x2B
#define IPMI_CMD_OEM_WISTRON_GET_BMC_SC_BMC_PROTOCOL_VERSION     0x2C
#define IPMI_CMD_OEM_WISTRON_GET_SC_SC_BMC_PROTOCOL_VERSION      0x2D
#define IPMI_CMD_OEM_WISTRON_GET_CHASSIS_POWER_READINGS          0x2E
#define IPMI_CMD_OEM_WISTRON_SET_CHASSIS_POWER_READINGS          0x2F
#define IPMI_CMD_OEM_WISTRON_SET_PASSWORD_POLICY                 0x51

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_WISTRON_SPEC_H */
