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

#ifndef IPMI_CMD_OEM_QUANTA_SPEC_H
#define IPMI_CMD_OEM_QUANTA_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Quanta S99Q/Dell FS12-TY
 */

/* IPMI_NET_FN_FIRMWARE_RQ / IPMI_NET_FN_FIRMWARE_RS */
#define IPMI_CMD_OEM_QUANTA_UPDATE_FIRMARE      0x01
#define IPMI_CMD_OEM_QUANTA_GET_UPDATE_STATUS   0x02
#define IPMI_CMD_OEM_QUANTA_COPY_IMAGE_DATA     0x03
#define IPMI_CMD_OEM_QUANTA_USB_FIRMWARE_UPDATE 0x04

/* IPMI_NET_FN_OEM_QUANTA_GENERIC_RQ / IPMI_NET_FN_OEM_QUANTA_GENERIC_RS */
#define IPMI_CMD_OEM_QUANTA_RESERVED_EXTENDED_CONFIGURATION   0x01
#define IPMI_CMD_OEM_QUANTA_GET_EXTENDED_CONFIGURATION        0x02
#define IPMI_CMD_OEM_QUANTA_SET_EXTENDED_CONFIGURATION        0x03
#define IPMI_CMD_OEM_QUANTA_RESET_TO_DEFAULTS                 0x04
#define IPMI_CMD_OEM_QUANTA_GET_RESTORE_STATUS                0x05
#define IPMI_CMD_OEM_QUANTA_GET_SENSOR_TEMPERATURE_READING    0x10
#define IPMI_CMD_OEM_QUANTA_GET_PROCESSOR_INFORMATION         0x18
#define IPMI_CMD_OEM_QUANTA_SET_POWER_ON_BY_WAKE_ON_LAN_EVENT 0x1B

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_QUANTA_SPEC_H */
