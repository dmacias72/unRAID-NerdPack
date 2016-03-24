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

#ifndef IPMI_CMD_OEM_INVENTEC_SPEC_H
#define IPMI_CMD_OEM_INVENTEC_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 */

/* IPMI_NET_FN_FIRMWARE_RQ / IPMI_NET_FN_FIRMWARE_RS */
#define IPMI_CMD_OEM_INVENTEC_UPDATE_FIRMARE    0x01
#define IPMI_CMD_OEM_INVENTEC_GET_UPDATE_STATUS 0x02
#define IPMI_CMD_OEM_INVENTEC_COPY_IMAGE_DATA   0x03

/* IPMI_NET_FN_OEM_GROUP_RQ / IPMI_NET_FN_OEM_GROUP_RS */
/* achu: not official names, named based on use context */
#define IPMI_CMD_OEM_INVENTEC_SET_DEDICATED_MAC_ADDRESS    0x21
#define IPMI_CMD_OEM_INVENTEC_SET_SHARED_MAC_ADDRESS       0x23

/* IPMI_NET_FN_OEM_INVENTEC_GENERIC_RQ / IPMI_NET_FN_OEM_INVENTEC_GENERIC_RS */
#define IPMI_CMD_OEM_INVENTEC_RESERVED_EXTENDED_CONFIGURATION 0x01
#define IPMI_CMD_OEM_INVENTEC_GET_EXTENDED_CONFIGURATION      0x02
#define IPMI_CMD_OEM_INVENTEC_SET_EXTENDED_CONFIGURATION      0x03
#define IPMI_CMD_OEM_INVENTEC_RESTORE_TO_DEFAULTS             0x04
#define IPMI_CMD_OEM_INVENTEC_GET_RESTORE_STATUS              0x05
#define IPMI_CMD_OEM_INVENTEC_SET_SYSTEM_GUID                 0xB3

/* IPMI_NET_FN_OEM_INVENTEC_SPECIFIC_RQ / IPMI_NET_FN_OEM_INVENTEC_SPECIFIC_RS */ 
#define IPMI_CMD_OEM_INVENTEC_SET_WEB_PORT_NUM                0x02
#define IPMI_CMD_OEM_INVENTEC_GET_WEB_PORT_NUM                0x03
#define IPMI_CMD_OEM_INVENTEC_SET_BOARD_ID                    0x10
#define IPMI_CMD_OEM_INVENTEC_GET_BOARD_ID                    0x11
#define IPMI_CMD_OEM_INVENTEC_SET_ASSET_TAG                   0x12
#define IPMI_CMD_OEM_INVENTEC_SET_LAN_SOURCE                  0x13
#define IPMI_CMD_OEM_INVENTEC_GET_LAN_SOURCE                  0x14
#define IPMI_CMD_OEM_INVENTEC_SET_FCB_FW_VERSION              0x15
#define IPMI_CMD_OEM_INVENTEC_GET_FCB_FW_VERSION              0x16
#define IPMI_CMD_OEM_INVENTEC_SET_FAN_CONTROL                 0x61
#define IPMI_CMD_OEM_INVENTEC_GET_FAN_CONTROL                 0x62
#define IPMI_CMD_OEM_INVENTEC_SET_FSC_TABLE                   0x63
#define IPMI_CMD_OEM_INVENTEC_GET_FSC_TABLE                   0x64
#define IPMI_CMD_OEM_INVENTEC_GET_FCB_SKU_INFO                0x6A
#define IPMI_CMD_OEM_INVENTEC_GET_FCB_POWER_THROTTLING_STATUS 0x6B
#define IPMI_CMD_OEM_INVENTEC_OEM_GET_PIC_MODEL               0x70
#define IPMI_CMD_OEM_INVENTEC_OEM_SET_FLASH_PIN               0x71
#define IPMI_CMD_OEM_INVENTEC_OEM_GET_FLASH_PIN               0x72
#define IPMI_CMD_OEM_INVENTEC_OEM_NEW_MASTER_WRITE_READ       0x73
#define IPMI_CMD_OEM_INVENTEC_SET_POWER_THROTTLING_BEHAVIOR   0xB1
#define IPMI_CMD_OEM_INVENTEC_GET_POWER_THROTTLING_BEHAVIOR   0xB2
#define IPMI_CMD_OEM_INVENTEC_GET_PSU_MISMATCH_AND_TYPE       0xB3

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_INVENTEC_SPEC_H */
