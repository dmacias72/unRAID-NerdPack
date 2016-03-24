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

#ifndef IPMI_CMD_OEM_DELL_SPEC_H
#define IPMI_CMD_OEM_DELL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Dell Poweredge R610
 * Dell Poweredge R710
 * Dell Poweredge R720
 */

/* IPMI_NET_FN_OEM_GROUP_RQ / IPMI_NET_FN_OEM_GROUP_RS */
#define IPMI_CMD_OEM_DELL_RESERVED_EXTENDED_CONFIGURATION 0x01
#define IPMI_CMD_OEM_DELL_GET_EXTENDED_CONFIGURATION      0x02
#define IPMI_CMD_OEM_DELL_SET_EXTENDED_CONFIGURATION      0x03

/* IPMI_NET_FN_OEM_DELL_GENERIC_RQ / IPMI_NET_FN_OEM_DELL_GENERIC_RS */
#define IPMI_CMD_OEM_DELL_RESET_TO_DEFAULTS                                    0x21
#define IPMI_CMD_OEM_DELL_SET_NIC_SELECTION                                    0x24
#define IPMI_CMD_OEM_DELL_GET_NIC_SELECTION                                    0x25
#define IPMI_CMD_OEM_DELL_QUERY_CHASSIS_IDENTIFY_STATUS                        0x32
#define IPMI_CMD_OEM_DELL_GET_CPLD_VERSION                                     0x33
#define IPMI_CMD_OEM_DELL_GET_POWER_CONSUMPTION_DATA                           0x9C
#define IPMI_CMD_OEM_DELL_RESET_POWER_CONSUMPTION_DATA                         0x9D
#define IPMI_CMD_OEM_DELL_POWER_SUPPLY_INFO                                    0xB0
#define IPMI_CMD_OEM_DELL_POWER_MONITORING_OVER_A_SPECIFIED_AVERAGING_INTERVAL 0xB1
#define IPMI_CMD_OEM_DELL_POWER_MONITORING_AVERAGING_INTERVAL_RANGE            0xB2
#define IPMI_CMD_OEM_DELL_POWER_CONSUMPTION                                    0xB3
#define IPMI_CMD_OEM_DELL_FRONT_PANEL_INFO                                     0xB5
/* renamed "front panel info" in 12g */
#define IPMI_CMD_OEM_DELL_LCD_INFO                                             IPMI_CMD_OEM_DELL_FRONT_PANEL_INFO
/* achu: this one is taken from code, is correct name? */
#define IPMI_CMD_OEM_DELL_POWER_CAPACITY_STATUS                                0xBA
#define IPMI_CMD_OEM_DELL_GET_POWER_HEAD_ROOM                                  0xBB
#define IPMI_CMD_OEM_DELL_ROLLBACK_FIRMWARE_VERSION                            0xBE
#define IPMI_CMD_OEM_DELL_GET_IDRAC_FIRMWARE_VERSION_NUMBER                    0xBF
#define IPMI_CMD_OEM_DELL_GET_ACTIVE_LOM_STATUS                                0xC1
#define IPMI_CMD_OEM_DELL_IDRAC_VIRTUAL_MAC                                    0xC9

/*
 * Dell Poweredge R720
 */

#define IPMI_CMD_OEM_DELL_GET_BLADE_SLOT_ID                                     0x18
#define IPMI_CMD_OEM_DELL_SET_NIC_SELECTION_FAILOVER                            0x28
#define IPMI_CMD_OEM_DELL_GET_NIC_SELECTION_FAILOVER                            0x29
#define IPMI_CMD_OEM_DELL_FRESH_AIR                                             0x35
#define IPMI_CMD_OEM_DELL_GET_LAST_POST_CODE                                    0x99
#define IPMI_CMD_OEM_DELL_POWER_MONITORING_OVER_A_SPECIFIED_AVERAGING_INTERVAL2 0xCC
#define IPMI_CMD_OEM_DELL_POWER_MONITORING_AVERAGING_INTERVAL_RANGE2            0xCD

/*
 * Dell Poweredge C410x
 */

/* IPMI_NET_FN_OEM_DELL_GENERIC_RQ / IPMI_NET_FN_OEM_DELL_GENERIC_RS */
#define IPMI_CMD_OEM_DELL_SLOT_POWER_CONTROL 0xF0

/* IPMI_NET_FN_OEM_DELL_GENERIC_PORT_MAP_RQ / IPMI_NET_FN_OEM_DELL_GENERIC_PORT_MAP_RS */
#define IPMI_CMD_OEM_DELL_PORT_MAP           0xC8

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_DELL_SPEC_H */
