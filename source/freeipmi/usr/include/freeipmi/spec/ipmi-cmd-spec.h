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

#ifndef IPMI_CMD_SPEC_H
#define IPMI_CMD_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Notes:
   Refer to IPMIv1_5_rev1_1.pdf Table G-1, Command Number Assignments
   and Privilege Levels for complete description
 */

/* IPMI Device Global Commands */
#define IPMI_CMD_RESERVED                                         0x00
#define IPMI_CMD_GET_DEVICE_ID                                    0x01
#define IPMI_CMD_GET_DEVICE_ID_BCST                               IPMI_CMD_GET_DEVICE_ID
#define IPMI_CMD_COLD_RESET                                       0x02
#define IPMI_CMD_WARM_RESET                                       0x03
#define IPMI_CMD_GET_SELF_TEST_RESULTS                            0x04
#define IPMI_CMD_MANUFACTURING_TEST_ON                            0x05
#define IPMI_CMD_SET_ACPI_POWER_STATE                             0x06
#define IPMI_CMD_GET_ACPI_POWER_STATE                             0x07
#define IPMI_CMD_GET_DEVICE_GUID                                  0x08
#define IPMI_CMD_GET_NETFN_SUPPORT                                0x09
#define IPMI_CMD_GET_COMMAND_SUPPORT                              0x0A
#define IPMI_CMD_GET_COMMAND_SUB_FUNCTION_SUPPORT                 0x0B
#define IPMI_CMD_GET_CONFIGURABLE_COMMANDS                        0x0C
#define IPMI_CMD_GET_CONFIGURABLE_COMMAND_SUB_FUNCTIONS           0x0D
/* RESERVED                                                       0x0E to 0x0F */
#define IPMI_CMD_SET_COMMAND_ENABLES                              0x60
#define IPMI_CMD_GET_COMMAND_ENABLES                              0x61
#define IPMI_CMD_SET_COMMAND_SUB_FUNCTION_ENABLES                 0x62
#define IPMI_CMD_GET_COMMAND_SUB_FUNCTION_ENABLES                 0x63
#define IPMI_CMD_GET_OEM_NETFN_IANA_SUPPORT                       0x64

/* BMC Watchdog Timer Commands */
#define IPMI_CMD_RESET_WATCHDOG_TIMER                             0x22
#define IPMI_CMD_SET_WATCHDOG_TIMER                               0x24
#define IPMI_CMD_GET_WATCHDOG_TIMER                               0x25

/* BMC Device And Messaging Commands */
#define IPMI_CMD_SET_BMC_GLOBAL_ENABLES                           0x2E
#define IPMI_CMD_GET_BMC_GLOBAL_ENABLES                           0x2F
#define IPMI_CMD_CLEAR_MESSAGE_FLAGS                              0x30
#define IPMI_CMD_GET_MESSAGE_FLAGS                                0x31
#define IPMI_CMD_ENABLE_MESSAGE_CHANNEL_RECEIVE                   0x32
#define IPMI_CMD_GET_MESSAGE                                      0x33
#define IPMI_CMD_SEND_MESSAGE                                     0x34
#define IPMI_CMD_READ_EVENT_MESSAGE_BUFFER                        0x35
#define IPMI_CMD_GET_BT_INTERFACE_CAPABILITIES                    0x36
#define IPMI_CMD_GET_SYSTEM_GUID                                  0x37
#define IPMI_CMD_SET_SYSTEM_INFO_PARAMETERS                       0x58
#define IPMI_CMD_GET_SYSTEM_INFO_PARAMETERS                       0x59
#define IPMI_CMD_GET_CHANNEL_AUTHENTICATION_CAPABILITIES          0x38
#define IPMI_CMD_GET_SESSION_CHALLENGE                            0x39
#define IPMI_CMD_ACTIVATE_SESSION                                 0x3A
#define IPMI_CMD_SET_SESSION_PRIVILEGE_LEVEL                      0x3B
#define IPMI_CMD_CLOSE_SESSION                                    0x3C
#define IPMI_CMD_GET_SESSION_INFO                                 0x3D
/* UNASSIGNED                                                     0x3E */
#define IPMI_CMD_GET_AUTHCODE                                     0x3F
#define IPMI_CMD_SET_CHANNEL_ACCESS                               0x40
#define IPMI_CMD_GET_CHANNEL_ACCESS                               0x41
#define IPMI_CMD_GET_CHANNEL_INFO_COMMAND                         0x42
#define IPMI_CMD_SET_USER_ACCESS_COMMAND                          0x43
#define IPMI_CMD_GET_USER_ACCESS_COMMAND                          0x44
#define IPMI_CMD_SET_USER_NAME                                    0x45
#define IPMI_CMD_GET_USER_NAME_COMMAND                            0x46
#define IPMI_CMD_SET_USER_PASSWORD_COMMAND                        0x47
#define IPMI_CMD_ACTIVATE_PAYLOAD                                 0x48
#define IPMI_CMD_DEACTIVATE_PAYLOAD                               0x49
#define IPMI_CMD_GET_PAYLOAD_ACTIVATION_STATUS                    0x4A
#define IPMI_CMD_GET_PAYLOAD_INSTANCE_INFO                        0x4B
#define IPMI_CMD_SET_USER_PAYLOAD_ACCESS                          0x4C
#define IPMI_CMD_GET_USER_PAYLOAD_ACCESS                          0x4D
#define IPMI_CMD_GET_CHANNEL_PAYLOAD_SUPPORT                      0x4E
#define IPMI_CMD_GET_CHANNEL_PAYLOAD_VERSION                      0x4F
#define IPMI_CMD_GET_CHANNEL_OEM_PAYLOAD_INFO                     0x50
/* unassigned                                                     0x51 */
#define IPMI_CMD_MASTER_WRITE_READ                                0x52
/* unassigned                                                     0x53 */
#define IPMI_CMD_GET_CHANNEL_CIPHER_SUITES                        0x54
#define IPMI_CMD_SUSPEND_RESUME_PAYLOAD_ENCRYPTION                0x53
#define IPMI_CMD_SET_CHANNEL_SECURITY_KEYS                        0x56
#define IPMI_CMD_GET_SYSTEM_INTERFACE_CAPABILITIES                0x57
/* unassigned                                                     0x58 to 0x5F */
/* Firmware Firewall Configuration                                0x60 to 0x64 */

/* Chassis Device Commands */
/* achu: Cmd is named "set front panel enables", but cmd in appendix G is
 * named "set front panel button enables".  Go fig ...
 */
#define IPMI_CMD_GET_CHASSIS_CAPABILITIES                         0x00
#define IPMI_CMD_GET_CHASSIS_STATUS                               0x01
#define IPMI_CMD_CHASSIS_CONTROL                                  0x02
#define IPMI_CMD_CHASSIS_RESET                                    0x03
#define IPMI_CMD_CHASSIS_IDENTIFY                                 0x04
#define IPMI_CMD_SET_CHASSIS_CAPABILITIES                         0x05
#define IPMI_CMD_SET_POWER_RESTORE_POLICY                         0x06
#define IPMI_CMD_GET_SYSTEM_RESTART_CAUSE                         0x07
#define IPMI_CMD_SET_SYSTEM_BOOT_OPTIONS                          0x08
#define IPMI_CMD_GET_SYSTEM_BOOT_OPTIONS                          0x09
#define IPMI_CMD_SET_FRONT_PANEL_BUTTON_ENABLES                   0x0A
#define IPMI_CMD_SET_FRONT_PANEL_ENABLES                          IPMI_CMD_SET_FRONT_PANEL_BUTTON_ENABLES
#define IPMI_CMD_SET_POWER_CYCLE_INTERVAL                         0x0B
/* unassigned                                                     0x0C to 0x0E */
#define IPMI_CMD_GET_POWER_ON_HOURS_COUNTER                       0x0F


/* Event Commands */
#define IPMI_CMD_SET_EVENT_RECEIVER                               0x00
#define IPMI_CMD_GET_EVENT_RECEIVER                               0x01
#define IPMI_CMD_PLATFORM_EVENT                                   0x02 /* (a.k.a. Event Message) */
/* unassigned                                                     0x03h to 0x0F */

/* PEF and Alerting Commands */
#define IPMI_CMD_GET_PEF_CAPABILITIES                             0x10
#define IPMI_CMD_ARM_PEF_POSTPONE_TIMER                           0x11
#define IPMI_CMD_SET_PEF_CONFIGURATION_PARAMETERS                 0x12
#define IPMI_CMD_GET_PEF_CONFIGURATION_PARAMETERS                 0x13
#define IPMI_CMD_SET_LAST_PROCESSED_EVENT_ID                      0x14
#define IPMI_CMD_GET_LAST_PROCESSED_EVENT_ID                      0x15
#define IPMI_CMD_ALERT_IMMEDIATE                                  0x16
#define IPMI_CMD_PET_ACKNOWLEDGE                                  0x17

/* Sensor Device Commands */
#define IPMI_CMD_GET_DEVICE_SDR_INFO                              0x20
#define IPMI_CMD_GET_DEVICE_SDR                                   0x21
#define IPMI_CMD_RESERVE_DEVICE_SDR_REPOSITORY                    0x22
#define IPMI_CMD_GET_SENSOR_READING_FACTORS                       0x23
#define IPMI_CMD_SET_SENSOR_HYSTERESIS                            0x24
#define IPMI_CMD_GET_SENSOR_HYSTERESIS                            0x25
#define IPMI_CMD_SET_SENSOR_THRESHOLDS                            0x26
#define IPMI_CMD_GET_SENSOR_THRESHOLDS                            0x27
#define IPMI_CMD_SET_SENSOR_EVENT_ENABLE                          0x28
#define IPMI_CMD_GET_SENSOR_EVENT_ENABLE                          0x29
#define IPMI_CMD_RE_ARM_SENSOR_EVENTS                             0x2A
#define IPMI_CMD_GET_SENSOR_EVENT_STATUS                          0x2B
#define IPMI_CMD_GET_SENSOR_READING                               0x2D
#define IPMI_CMD_SET_SENSOR_TYPE                                  0x2E
#define IPMI_CMD_GET_SENSOR_TYPE                                  0x2F
#define IPMI_CMD_SET_SENSOR_READING_AND_EVENT_STATUS              0x30

/* FRU Device Commands */
#define IPMI_CMD_GET_FRU_INVENTORY_AREA_INFO                      0x10
#define IPMI_CMD_READ_FRU_DATA                                    0x11
#define IPMI_CMD_WRITE_FRU_DATA                                   0x12

/* SDR Device Commands */
#define IPMI_CMD_GET_SDR_REPOSITORY_INFO                          0x20
#define IPMI_CMD_GET_SDR_REPOSITORY_ALLOCATION_INFO               0x21
#define IPMI_CMD_RESERVE_SDR_REPOSITORY                           0x22
#define IPMI_CMD_GET_SDR                                          0x23
#define IPMI_CMD_ADD_SDR                                          0x24
#define IPMI_CMD_PARTIAL_ADD_SDR                                  0x25
#define IPMI_CMD_DELETE_SDR                                       0x26
#define IPMI_CMD_CLEAR_SDR_REPOSITORY                             0x27
#define IPMI_CMD_GET_SDR_REPOSITORY_TIME                          0x28
#define IPMI_CMD_SET_SDR_REPOSITORY_TIME                          0x29
#define IPMI_CMD_ENTER_SDR_REPOSITORY_UPDATE_MODE                 0x2A
#define IPMI_CMD_EXIT_SDR_REPOSITORY_UPDATE_MODE                  0x2B
#define IPMI_CMD_RUN_INITIALIZATION_AGENT                         0x2C

/* SEL Device Commands */
#define IPMI_CMD_GET_SEL_INFO                                     0x40
#define IPMI_CMD_GET_SEL_ALLOCATION_INFO                          0x41
#define IPMI_CMD_RESERVE_SEL                                      0x42
#define IPMI_CMD_GET_SEL_ENTRY                                    0x43
#define IPMI_CMD_ADD_SEL_ENTRY                                    0x44
#define IPMI_CMD_PARTIAL_ADD_SEL_ENTRY                            0x45
#define IPMI_CMD_DELETE_SEL_ENTRY                                 0x46
#define IPMI_CMD_CLEAR_SEL                                        0x47
#define IPMI_CMD_GET_SEL_TIME                                     0x48
#define IPMI_CMD_SET_SEL_TIME                                     0x49
#define IPMI_CMD_GET_AUXILIARY_LOG_STATUS                         0x5A
#define IPMI_CMD_SET_AUXILIARY_LOG_STATUS                         0x5B
#define IPMI_CMD_GET_SEL_TIME_UTC_OFFSET                          0x5C
#define IPMI_CMD_SET_SEL_TIME_UTC_OFFSET                          0x5D

/* LAN Device Commands */
#define IPMI_CMD_SET_LAN_CONFIGURATION_PARAMETERS                 0x01
#define IPMI_CMD_GET_LAN_CONFIGURATION_PARAMETERS                 0x02
#define IPMI_CMD_SUSPEND_BMC_ARPS                                 0x03
#define IPMI_CMD_GET_IP_UDP_RMCP_STATISTICS                       0x04

/* Serial/Modem Device Commands */
#define IPMI_CMD_SET_SERIAL_MODEM_CONFIGURATION                   0x10
#define IPMI_CMD_GET_SERIAL_MODEM_CONFIGURATION                   0x11
#define IPMI_CMD_SET_SERIAL_MODEM_MUX                             0x12
#define IPMI_CMD_GET_TAP_RESPONSE_CODES                           0x13
#define IPMI_CMD_SET_PPP_UDP_PROXY_TRANSMIT_DATA                  0x14
#define IPMI_CMD_GET_PPP_UDP_PROXY_TRANSMIT_DATA                  0x15
#define IPMI_CMD_SEND_PPP_UDP_PROXY_PACKET                        0x16
#define IPMI_CMD_GET_PPP_UDP_PROXY_RECEIVE_DATA                   0x17
#define IPMI_CMD_SERIAL_MODEM_CONNECTION_ACTIVE                   0x18
#define IPMI_CMD_CALLBACK                                         0x19
#define IPMI_CMD_SET_USER_CALLBACK_OPTIONS                        0x1A
#define IPMI_CMD_GET_USER_CALLBACK_OPTIONS                        0x1B
#define IPMI_CMD_SET_SERIAL_ROUTING_MUX                           0x1C
#define IPMI_CMD_SOL_ACTIVATING                                   0x20
#define IPMI_CMD_SET_SOL_CONFIGURATION_PARAMETERS                 0x21
#define IPMI_CMD_GET_SOL_CONFIGURATION_PARAMETERS                 0x22

/* Command Forwarding Commands */
#define IPMI_CMD_FORWARDED_COMMAND                                0x30
#define IPMI_CMD_SET_FORWARDED_COMMANDS                           0x31
#define IPMI_CMD_GET_FORWARDED_COMMANDS                           0x32
#define IPMI_CMD_ENABLE_FORWARDED_COMMANDS                        0x33

/* Bridge Management Commands (ICMB) */
#define IPMI_CMD_GET_BRIDGE_STATE                                 0x00
#define IPMI_CMD_SET_BRIDGE_STATE                                 0x01
#define IPMI_CMD_GET_ICMB_ADDRESS                                 0x02
#define IPMI_CMD_SET_ICMB_ADDRESS                                 0x03
#define IPMI_CMD_SET_BRIDGE_PROXY_ADDRESS                         0x04
#define IPMI_CMD_GET_BRIDGE_STATISTICS                            0x05
#define IPMI_CMD_GET_ICMB_CAPABILITIES                            0x06
#define IPMI_CMD_CLEAR_BRIDGE_STATISTICS                          0x08
#define IPMI_CMD_GET_BRIDGE_PROXY_ADDRESS                         0x09
#define IPMI_CMD_GET_ICMB_CONNECTOR_INFO                          0x0A
#define IPMI_CMD_GET_ICMB_CONNECTION_ID                           0x0B
#define IPMI_CMD_SEND_ICMB_CONNECTION_ID                          0x0C

/* Discovery Commands (ICMB) */
#define IPMI_CMD_PREPARE_FOR_DISCOVERY                            0x10
#define IPMI_CMD_GET_ADDRESSES                                    0x11
#define IPMI_CMD_SET_DISCOVERED                                   0x12
#define IPMI_CMD_GET_CHASSIS_DEVICE_ID                            0x13
#define IPMI_CMD_SET_CHASSIS_DEVICE_ID                            0x14

/* Bridging Commands (ICMB) */
#define IPMI_CMD_BRIDGE_REQUEST                                   0x20
#define IPMI_CMD_BRIDGE_MESSAGE                                   0x21

/* Event Commands (ICMB) */
#define IPMI_CMD_GET_EVENT_COUNT                                  0x30
#define IPMI_CMD_SET_EVENT_DESTINATION                            0x31
#define IPMI_CMD_SET_EVENT_RECEPTION_STATE                        0x32
#define IPMI_CMD_SEND_ICMB_EVENT_MESSAGE                          0x33
#define IPMI_CMD_GET_EVENT_DESTINATION                            0x34
#define IPMI_CMD_GET_EVENT_RECEPTION_STATE                        0x35

/* OEM Commands for Bridge NetFn */
/* OEM Commands                                                   0xC0 to 0xFE */

/* Other Bridge Commands */
#define IPMI_CMD_ERROR_REPORT                                     0xFF

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_SPEC_H */
