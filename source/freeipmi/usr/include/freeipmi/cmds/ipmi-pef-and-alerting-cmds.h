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

#ifndef IPMI_PEF_AND_ALERTING_CMDS_H
#define IPMI_PEF_AND_ALERTING_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>
#include <freeipmi/spec/ipmi-sensor-types-spec.h>

#define IPMI_PEF_CONFIGURATION_PARAMETERS_NO_SET_SELECTOR                            0x0
#define IPMI_PEF_CONFIGURATION_PARAMETERS_NO_BLOCK_SELECTOR                          0x0

#define IPMI_PEF_CONFIGURATION_PARAMETERS_SET_COMPLETE                              0x00
#define IPMI_PEF_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS                           0x01
#define IPMI_PEF_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE                          0x02

#define IPMI_PEF_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS_VALID(__value) \
  (((__value) == IPMI_PEF_CONFIGURATION_PARAMETERS_SET_COMPLETE          \
    || (__value) == IPMI_PEF_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS    \
    || (__value) == IPMI_PEF_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE) ? 1 : 0)

#define IPMI_PEF_POSTPONE_TIMER_DISABLE                     0x00
#define IPMI_PEF_POSTPONE_TIMER_TEMPORARY_DISABLE           0xFE
#define IPMI_PEF_POSTPONE_TIMER_GET_PRESENT_COUNTDOWN_VALUE 0xFF

#define IPMI_PEF_ENABLE  0x1
#define IPMI_PEF_DISABLE 0x0

#define IPMI_PEF_VALID(__val)  \
  (((__val) == IPMI_PEF_ENABLE \
    || (__val) == IPMI_PEF_DISABLE) ? 1 : 0)

#define IPMI_PEF_ENABLE  0x1
#define IPMI_PEF_DISABLE 0x0

#define IPMI_PEF_VALID(__val)  \
  (((__val) == IPMI_PEF_ENABLE \
    || (__val) == IPMI_PEF_DISABLE) ? 1 : 0)

#define IPMI_PEF_EVENT_MESSAGES_ENABLE  0x1
#define IPMI_PEF_EVENT_MESSAGES_DISABLE 0x0

#define IPMI_PEF_EVENT_MESSAGES_VALID(__val)  \
  (((__val) == IPMI_PEF_EVENT_MESSAGES_ENABLE \
    || (__val) == IPMI_PEF_EVENT_MESSAGES_DISABLE) ? 1 : 0)

#define IPMI_PEF_STARTUP_DELAY_ENABLE  0x1
#define IPMI_PEF_STARTUP_DELAY_DISABLE 0x0

#define IPMI_PEF_STARTUP_DELAY_VALID(__val)  \
  (((__val) == IPMI_PEF_STARTUP_DELAY_ENABLE \
    || (__val) == IPMI_PEF_STARTUP_DELAY_DISABLE) ? 1 : 0)

#define IPMI_PEF_ALERT_STARTUP_DELAY_ENABLE  0x1
#define IPMI_PEF_ALERT_STARTUP_DELAY_DISABLE 0x0

#define IPMI_PEF_ALERT_STARTUP_DELAY_VALID(__val)  \
  (((__val) == IPMI_PEF_ALERT_STARTUP_DELAY_ENABLE \
    || (__val) == IPMI_PEF_ALERT_STARTUP_DELAY_DISABLE) ? 1 : 0)

#define IPMI_PEF_ALERT_ACTION_ENABLE  0x1
#define IPMI_PEF_ALERT_ACTION_DISABLE 0x0

#define IPMI_PEF_ALERT_ACTION_VALID(__val)  \
  (((__val) == IPMI_PEF_ALERT_ACTION_ENABLE \
    || (__val) == IPMI_PEF_ALERT_ACTION_DISABLE) ? 1 : 0)

#define IPMI_PEF_POWER_DOWN_ACTION_ENABLE  0x1
#define IPMI_PEF_POWER_DOWN_ACTION_DISABLE 0x0

#define IPMI_PEF_POWER_DOWN_ACTION_VALID(__val)  \
  (((__val) == IPMI_PEF_POWER_DOWN_ACTION_ENABLE \
    || (__val) == IPMI_PEF_POWER_DOWN_ACTION_DISABLE) ? 1 : 0)

#define IPMI_PEF_RESET_ACTION_ENABLE  0x1
#define IPMI_PEF_RESET_ACTION_DISABLE 0x0

#define IPMI_PEF_RESET_ACTION_VALID(__val)  \
  (((__val) == IPMI_PEF_RESET_ACTION_ENABLE \
    || (__val) == IPMI_PEF_RESET_ACTION_DISABLE) ? 1 : 0)

#define IPMI_PEF_POWER_CYCLE_ACTION_ENABLE  0x1
#define IPMI_PEF_POWER_CYCLE_ACTION_DISABLE 0x0

#define IPMI_PEF_POWER_CYCLE_ACTION_VALID(__val)  \
  (((__val) == IPMI_PEF_POWER_CYCLE_ACTION_ENABLE \
    || (__val) == IPMI_PEF_POWER_CYCLE_ACTION_DISABLE) ? 1 : 0)

#define IPMI_PEF_OEM_ACTION_ENABLE  0x1
#define IPMI_PEF_OEM_ACTION_DISABLE 0x0

#define IPMI_PEF_OEM_ACTION_VALID(__val)  \
  (((__val) == IPMI_PEF_OEM_ACTION_ENABLE \
    || (__val) == IPMI_PEF_OEM_ACTION_DISABLE) ? 1 : 0)

#define IPMI_PEF_DIAGNOSTIC_INTERRUPT_ENABLE  0x1
#define IPMI_PEF_DIAGNOSTIC_INTERRUPT_DISABLE 0x0

#define IPMI_PEF_DIAGNOSTIC_INTERRUPT_VALID(__val)  \
  (((__val) == IPMI_PEF_DIAGNOSTIC_INTERRUPT_ENABLE \
    || (__val) == IPMI_PEF_DIAGNOSTIC_INTERRUPT_DISABLE) ? 1 : 0)

#define IPMI_FILTER_CONFIGURATION_MANUFACTURER_PRE_CONFIGURED_FILTER  0x2
#define IPMI_FILTER_CONFIGURATION_SOFTWARE_CONFIGURABLE_FILTER        0x0

#define IPMI_FILTER_CONFIGURATION_FILTER_TYPE_VALID(__val)                  \
  (((__val) == IPMI_FILTER_CONFIGURATION_MANUFACTURER_PRE_CONFIGURED_FILTER \
    || (__val) == IPMI_FILTER_CONFIGURATION_SOFTWARE_CONFIGURABLE_FILTER) ? 1 : 0)

#define IPMI_FILTER_CONFIGURATION_FILTER_ENABLE  0x1
#define IPMI_FILTER_CONFIGURATION_FILTER_DISABLE 0x0

#define IPMI_FILTER_CONFIGURATION_FILTER_VALID(__val)  \
  (((__val) == IPMI_FILTER_CONFIGURATION_FILTER_ENABLE \
    || (__val) == IPMI_FILTER_CONFIGURATION_FILTER_DISABLE) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_ALERT    0x1
#define IPMI_EVENT_FILTER_ACTION_NO_ALERT 0x0

#define IPMI_EVENT_FILTER_ACTION_ALERT_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_ALERT       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_ALERT) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_POWER_OFF         0x1
#define IPMI_EVENT_FILTER_ACTION_NO_POWER_OFF      0x0

#define IPMI_EVENT_FILTER_ACTION_POWER_OFF_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_POWER_OFF       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_POWER_OFF) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_RESET    0x1
#define IPMI_EVENT_FILTER_ACTION_NO_RESET 0x0

#define IPMI_EVENT_FILTER_ACTION_RESET_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_RESET       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_RESET) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_POWER_CYCLE    0x1
#define IPMI_EVENT_FILTER_ACTION_NO_POWER_CYCLE 0x0

#define IPMI_EVENT_FILTER_ACTION_POWER_CYCLE_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_POWER_CYCLE       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_POWER_CYCLE) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_OEM_ACTION  0x1
#define IPMI_EVENT_FILTER_ACTION_NO_OEM      0x0

#define IPMI_EVENT_FILTER_ACTION_OEM_VALID(__val)  \
  (((__val) == IPMI_EVENT_FILTER_ACTION_OEM_ACTION \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_OEM) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_DIAGNOSTIC_INTERRUPT    0x1
#define IPMI_EVENT_FILTER_ACTION_NO_DIAGNOSTIC_INTERRUPT 0x0

#define IPMI_EVENT_FILTER_ACTION_DIAGNOSTIC_INTERRUPT_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_DIAGNOSTIC_INTERRUPT       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_DIAGNOSTIC_INTERRUPT) ? 1 : 0)

#define IPMI_EVENT_FILTER_ACTION_GROUP_CONTROL_OPERATION    0x1
#define IPMI_EVENT_FILTER_ACTION_NO_GROUP_CONTROL_OPERATION 0x0

#define IPMI_EVENT_FILTER_ACTION_GROUP_CONTROL_OPERATION_VALID(__val) \
  (((__val) == IPMI_EVENT_FILTER_ACTION_GROUP_CONTROL_OPERATION       \
    || (__val) == IPMI_EVENT_FILTER_ACTION_NO_GROUP_CONTROL_OPERATION) ? 1 : 0)

#define IPMI_EVENT_SEVERITY_UNSPECIFIED                0x00
#define IPMI_EVENT_SEVERITY_MONITOR                    0x01
#define IPMI_EVENT_SEVERITY_INFORMATION                0x02
#define IPMI_EVENT_SEVERITY_OK                         0x04
#define IPMI_EVENT_SEVERITY_NON_CRITICAL_CONDITION     0x08
#define IPMI_EVENT_SEVERITY_CRITICAL_CONDITION         0x10
#define IPMI_EVENT_SEVERITY_NON_RECOVERABLE_CONDITION  0x20

#define IPMI_EVENT_SEVERITY_VALID(__val)                     \
  (((__val) == IPMI_EVENT_SEVERITY_UNSPECIFIED               \
    || (__val) == IPMI_EVENT_SEVERITY_MONITOR                \
    || (__val) == IPMI_EVENT_SEVERITY_INFORMATION            \
    || (__val) == IPMI_EVENT_SEVERITY_OK                     \
    || (__val) == IPMI_EVENT_SEVERITY_NON_CRITICAL_CONDITION \
    || (__val) == IPMI_EVENT_SEVERITY_CRITICAL_CONDITION     \
    || (__val) == IPMI_EVENT_SEVERITY_NON_RECOVERABLE_CONDITION) ? 1 : 0)

#define IPMI_EVENT_SENSOR_TYPE_RESERVED                                 IPMI_SENSOR_TYPE_RESERVED
#define IPMI_EVENT_SENSOR_TYPE_TEMPERATURE                              IPMI_SENSOR_TYPE_TEMPERATURE
#define IPMI_EVENT_SENSOR_TYPE_VOLTAGE                                  IPMI_SENSOR_TYPE_VOLTAGE
#define IPMI_EVENT_SENSOR_TYPE_CURRENT                                  IPMI_SENSOR_TYPE_CURRENT
#define IPMI_EVENT_SENSOR_TYPE_FAN                                      IPMI_SENSOR_TYPE_FAN
#define IPMI_EVENT_SENSOR_TYPE_PHYSICAL_SECURITY                        IPMI_SENSOR_TYPE_PHYSICAL_SECURITY
#define IPMI_EVENT_SENSOR_TYPE_PLATFORM_SECURITY_VIOLATION_ATTEMPT      IPMI_SENSOR_TYPE_PLATFORM_SECURITY_VIOLATION_ATTEMPT
#define IPMI_EVENT_SENSOR_TYPE_PROCESSOR                                IPMI_SENSOR_TYPE_PROCESSOR
#define IPMI_EVENT_SENSOR_TYPE_POWER_SUPPLY                             IPMI_SENSOR_TYPE_POWER_SUPPLY
#define IPMI_EVENT_SENSOR_TYPE_POWER_UNIT                               IPMI_SENSOR_TYPE_POWER_UNIT
#define IPMI_EVENT_SENSOR_TYPE_COOLING_DEVICE                           IPMI_SENSOR_TYPE_COOLING_DEVICE
#define IPMI_EVENT_SENSOR_TYPE_OTHER_UNITS_BASED_SENSOR                 IPMI_SENSOR_TYPE_OTHER_UNITS_BASED_SENSOR
#define IPMI_EVENT_SENSOR_TYPE_MEMORY                                   IPMI_SENSOR_TYPE_MEMORY
#define IPMI_EVENT_SENSOR_TYPE_DRIVE_SLOT                               IPMI_SENSOR_TYPE_DRIVE_SLOT
#define IPMI_EVENT_SENSOR_TYPE_POST_MEMORY_RESIZE                       IPMI_SENSOR_TYPE_POST_MEMORY_RESIZE
#define IPMI_EVENT_SENSOR_TYPE_SYSTEM_FIRMWARE_PROGRESS                 IPMI_SENSOR_TYPE_SYSTEM_FIRMWARE_PROGRESS
#define IPMI_EVENT_SENSOR_TYPE_EVENT_LOGGING_DISABLED                   IPMI_SENSOR_TYPE_EVENT_LOGGING_DISABLED
#define IPMI_EVENT_SENSOR_TYPE_WATCHDOG1                                IPMI_SENSOR_TYPE_WATCHDOG1
#define IPMI_EVENT_SENSOR_TYPE_SYSTEM_EVENT                             IPMI_SENSOR_TYPE_SYSTEM_EVENT
#define IPMI_EVENT_SENSOR_TYPE_CRITICAL_INTERRUPT                       IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT
#define IPMI_EVENT_SENSOR_TYPE_BUTTON_SWITCH                            IPMI_SENSOR_TYPE_BUTTON_SWITCH
#define IPMI_EVENT_SENSOR_TYPE_MODULE_BOARD                             IPMI_SENSOR_TYPE_MODULE_BOARD
#define IPMI_EVENT_SENSOR_TYPE_MICROCONTROLLER_COPROCESSOR              IPMI_SENSOR_TYPE_MICROCONTROLLER_COPROCESSOR
#define IPMI_EVENT_SENSOR_TYPE_ADD_IN_CARD                              IPMI_SENSOR_TYPE_ADD_IN_CARD
#define IPMI_EVENT_SENSOR_TYPE_CHASSIS                                  IPMI_SENSOR_TYPE_CHASSIS
#define IPMI_EVENT_SENSOR_TYPE_CHIP_SET                                 IPMI_SENSOR_TYPE_CHIP_SET
#define IPMI_EVENT_SENSOR_TYPE_OTHER_FRU                                IPMI_SENSOR_TYPE_OTHER_FRU
#define IPMI_EVENT_SENSOR_TYPE_CABLE_INTERCONNECT                       IPMI_SENSOR_TYPE_CABLE_INTERCONNECT
#define IPMI_EVENT_SENSOR_TYPE_TERMINATOR                               IPMI_SENSOR_TYPE_TERMINATOR
#define IPMI_EVENT_SENSOR_TYPE_SYSTEM_BOOT_INITIATED                    IPMI_SENSOR_TYPE_SYSTEM_BOOT_INITIATED
#define IPMI_EVENT_SENSOR_TYPE_BOOT_ERROR                               IPMI_SENSOR_TYPE_BOOT_ERROR
#define IPMI_EVENT_SENSOR_TYPE_OS_BOOT                                  IPMI_SENSOR_TYPE_OS_BOOT
#define IPMI_EVENT_SENSOR_TYPE_OS_CRITICAL_STOP                         IPMI_SENSOR_TYPE_OS_CRITICAL_STOP
#define IPMI_EVENT_SENSOR_TYPE_SLOT_CONNECTOR                           IPMI_SENSOR_TYPE_SLOT_CONNECTOR
#define IPMI_EVENT_SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE                  IPMI_SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE
#define IPMI_EVENT_SENSOR_TYPE_WATCHDOG2                                IPMI_SENSOR_TYPE_WATCHDOG2
#define IPMI_EVENT_SENSOR_TYPE_PLATFORM_ALERT                           IPMI_SENSOR_TYPE_PLATFORM_ALERT
#define IPMI_EVENT_SENSOR_TYPE_ENTITY_PRESENCE                          IPMI_SENSOR_TYPE_ENTITY_PRESENCE
#define IPMI_EVENT_SENSOR_TYPE_MONITOR_ASIC_IC                          IPMI_SENSOR_TYPE_MONITOR_ASIC_IC
#define IPMI_EVENT_SENSOR_TYPE_LAN                                      IPMI_SENSOR_TYPE_LAN
#define IPMI_EVENT_SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH              IPMI_SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH
#define IPMI_EVENT_SENSOR_TYPE_BATTERY                                  IPMI_SENSOR_TYPE_BATTERY
#define IPMI_EVENT_SENSOR_TYPE_SESSION_AUDIT                            IPMI_SENSOR_TYPE_SESSION_AUDIT
#define IPMI_EVENT_SENSOR_TYPE_VERSION_CHANGE                           IPMI_SENSOR_TYPE_VERSION_CHANGE
#define IPMI_EVENT_SENSOR_TYPE_FRU_STATE                                IPMI_SENSOR_TYPE_FRU_STATE
#define IPMI_EVENT_SENSOR_TYPE_ANY                                      0xff

#define IPMI_STRING_SELECTOR_MIN 0x00
#define IPMI_STRING_SELECTOR_MAX 0x7F
#define IPMI_STRING_SELECTOR_VOLATILE    0x0

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_STRING_SELECTOR_VALID(__val)       \
  (((__val+1) >= (IPMI_STRING_SELECTOR_MIN + 1) \
    && (__val) <= IPMI_STRING_SELECTOR_MAX) ? 1 : 0)

#define IPMI_SET_RECORD_ID_FOR_LAST_RECORD_PROCESSED_BY_SOFTWARE 0x0
#define IPMI_SET_RECORD_ID_FOR_LAST_RECORD_PROCESSED_BY_BMC      0x1

#define IPMI_SET_RECORD_ID_FOR_LAST_RECORD_PROCESSED_VALID(__val)       \
  (((__val) == IPMI_SET_RECORD_ID_FOR_LAST_RECORD_PROCESSED_BY_SOFTWARE \
    || (__val) == IPMI_SET_RECORD_ID_FOR_LAST_RECORD_PROCESSED_BY_BMC) ? 1 : 0)

#define IPMI_ALERT_IMMEDIATE_OPERATION_INITIATE_ALERT               0x0
#define IPMI_ALERT_IMMEDIATE_OPERATION_GET_ALERT_IMMEDIATE_STATUS   0x1
#define IPMI_ALERT_IMMEDIATE_OPERATION_CLEAR_ALERT_IMMEDIATE_STATUS 0x2
#define IPMI_ALERT_IMMEDIATE_OPERATION_RESERVED                     0x3

#define IPMI_ALERT_IMMEDIATE_OPERATION_VALID(__val)                         \
  (((__val) == IPMI_ALERT_IMMEDIATE_OPERATION_INITIATE_ALERT                \
    || (__val) == IPMI_ALERT_IMMEDIATE_OPERATION_GET_ALERT_IMMEDIATE_STATUS \
    || (__val) == IPMI_ALERT_IMMEDIATE_OPERATION_CLEAR_ALERT_IMMEDIATE_STATUS) ? 1 : 0)

#define IPMI_SEND_ALERT_STRING_IDENTIFIED_BY_STRING_SELECTOR 0x1
#define IPMI_DO_NOT_SEND_AN_ALERT_STRING                     0x0

#define IPMI_SEND_ALERT_STRING_VALID(__val)                         \
  (((__val) == IPMI_SEND_ALERT_STRING_IDENTIFIED_BY_STRING_SELECTOR \
    || (__val) == IPMI_DO_NOT_SEND_AN_ALERT_STRING) ? 1 : 0)

#define IPMI_GET_PEF_PARAMETER                          0x0
#define IPMI_GET_PEF_PARAMETER_REVISION_ONLY            0x1

#define IPMI_GET_PEF_PARAMETER_VALID(__val) \
  (((__val) == IPMI_GET_PEF_PARAMETER       \
    || (__val) == IPMI_GET_PEF_PARAMETER_REVISION_ONLY) ? 1 : 0)

#define IPMI_PEF_ALERT_STRINGS_BLOCK_SIZE    16
#define IPMI_PEF_ALERT_STRINGS_BLOCK_SIZE_VALID(__val) \
  (((__val) <= IPMI_PEF_ALERT_STRINGS_BLOCK_SIZE) ? 1 : 0)

#define IPMI_ALERT_POLICY_ALWAYS_SEND_TO_THIS_DESTINATION                     0x0
#define IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY                               0x1
#define IPMI_ALERT_POLICY_DO_NOT_PROCEED_ANY_MORE_ENTRIES                     0x2
#define IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY_DIFFERENT_CHANNEL             0x3
#define IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY_DIFFERENT_DESTINATION_TYPE    0x4

#define IPMI_ALERT_POLICY_TABLE_POLICY_TYPE_VALID(__val)                    \
  (((__val) == IPMI_ALERT_POLICY_ALWAYS_SEND_TO_THIS_DESTINATION            \
    || (__val) == IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY                   \
    || (__val) == IPMI_ALERT_POLICY_DO_NOT_PROCEED_ANY_MORE_ENTRIES         \
    || (__val) == IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY_DIFFERENT_CHANNEL \
    || (__val) == IPMI_ALERT_POLICY_PROCEED_TO_NEXT_ENTRY_DIFFERENT_DESTINATION_TYPE) ? 1 : 0)

#define IPMI_ALERT_POLICY_DISABLED    0x0
#define IPMI_ALERT_POLICY_ENABLED     0x1
#define IPMI_ALERT_POLICY_ENABLED_DISABLED_VALID(__val) \
  (((__val) == IPMI_ALERT_POLICY_DISABLED               \
    || (__val) == IPMI_ALERT_POLICY_ENABLED) ? 1 : 0)

#define IPMI_EVENT_SPECIFIC_ALERT_STRING_NO     0x0
#define IPMI_EVENT_SPECIFIC_ALERT_STRING_YES    0x1
#define IPMI_EVENT_SPECIFIC_ALERT_STRING_VALID(__val) \
  (((__val) == IPMI_EVENT_SPECIFIC_ALERT_STRING_NO    \
    || (__val) == IPMI_EVENT_SPECIFIC_ALERT_STRING_YES) ? 1 : 0)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_get_pef_capabilities_rq;
extern fiid_template_t tmpl_cmd_get_pef_capabilities_rs;

extern fiid_template_t tmpl_cmd_arm_pef_postpone_timer_rq;
extern fiid_template_t tmpl_cmd_arm_pef_postpone_timer_rs;

extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_rs;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_set_in_progress_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_pef_control_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_pef_action_global_control_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_pef_startup_delay_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_pef_alert_startup_delay_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_event_filter_table_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_event_filter_table_data1_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_alert_string_keys_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_alert_strings_rq;
extern fiid_template_t tmpl_cmd_set_pef_configuration_parameters_alert_policy_table_rq;

extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_rq;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_set_in_progress_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_pef_control_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_pef_action_global_control_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_pef_startup_delay_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_pef_alert_startup_delay_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_number_of_event_filters_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_event_filter_table_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_event_filter_table_data1_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_number_of_alert_policy_entries_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_number_of_alert_strings_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_alert_string_keys_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_alert_strings_rs;
extern fiid_template_t tmpl_cmd_get_pef_configuration_parameters_alert_policy_table_rs;

extern fiid_template_t tmpl_cmd_set_last_processed_event_id_rq;
extern fiid_template_t tmpl_cmd_set_last_processed_event_id_rs;
extern fiid_template_t tmpl_cmd_get_last_processed_event_id_rq;
extern fiid_template_t tmpl_cmd_get_last_processed_event_id_rs;

extern fiid_template_t tmpl_cmd_alert_immediate_rq;
extern fiid_template_t tmpl_cmd_alert_immediate_rs;

extern fiid_template_t tmpl_cmd_pet_acknowledge_rq;
extern fiid_template_t tmpl_cmd_pet_acknowledge_rs;

int fill_cmd_get_pef_capabilities (fiid_obj_t obj_cmd_rq);

int fill_cmd_arm_pef_postpone_timer (uint8_t pef_postpone_timeout,
                                     fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters (uint8_t parameter_selector,
                                               const void *configuration_parameter_data,
                                               unsigned int configuration_parameter_data_len,
                                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_set_in_progress (uint8_t state,
                                                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_pef_control (uint8_t pef,
                                                           uint8_t pef_event_messages,
                                                           uint8_t pef_startup_delay,
                                                           uint8_t pef_alert_startup_delay,
                                                           fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_pef_action_global_control (uint8_t alert_action,
                                                                         uint8_t power_down_action,
                                                                         uint8_t reset_action,
                                                                         uint8_t power_cycle_action,
                                                                         uint8_t oem_action,
                                                                         uint8_t diagnostic_interrupt,
                                                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_pef_startup_delay (uint8_t pef_startup_delay,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_pef_alert_startup_delay (uint8_t pef_alert_startup_delay,
                                                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_event_filter_table (uint8_t filter_number,
                                                                  uint8_t filter_configuration_type,
                                                                  uint8_t filter_configuration_enable,
                                                                  uint8_t event_filter_action_alert,
                                                                  uint8_t event_filter_action_power_off,
                                                                  uint8_t event_filter_action_reset,
                                                                  uint8_t event_filter_action_power_cycle,
                                                                  uint8_t event_filter_action_oem,
                                                                  uint8_t event_filter_action_diagnostic_interrupt,
                                                                  uint8_t event_filter_action_group_control_operation,
                                                                  uint8_t alert_policy_number_policy_number,
                                                                  uint8_t alert_policy_number_group_control_selector,
                                                                  uint8_t event_severity,
                                                                  uint8_t generator_id_byte1,
                                                                  uint8_t generator_id_byte2,
                                                                  uint8_t sensor_type,
                                                                  uint8_t sensor_number,
                                                                  uint8_t event_trigger,
                                                                  uint16_t event_data1_offset_mask,
                                                                  uint8_t event_data1_AND_mask,
                                                                  uint8_t event_data1_compare1,
                                                                  uint8_t event_data1_compare2,
                                                                  uint8_t event_data2_AND_mask,
                                                                  uint8_t event_data2_compare1,
                                                                  uint8_t event_data2_compare2,
                                                                  uint8_t event_data3_AND_mask,
                                                                  uint8_t event_data3_compare1,
                                                                  uint8_t event_data3_compare2,
                                                                  fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_event_filter_table_data1 (uint8_t filter_number,
                                                                        uint8_t filter_configuration_type,
                                                                        uint8_t filter_configuration_enable,
                                                                        fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_alert_string_keys (uint8_t string_selector,
                                                                 uint8_t filter_number,
                                                                 uint8_t set_number_for_string,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_alert_strings (uint8_t string_selector,
                                                             uint8_t block_selector,
                                                             const uint8_t *string_data,
                                                             unsigned int string_data_len,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_set_pef_configuration_parameters_alert_policy_table (uint8_t alert_policy_entry_number,
                                                                  uint8_t policy_type,
                                                                  uint8_t policy_enabled,
                                                                  uint8_t policy_number,
                                                                  uint8_t destination_selector,
                                                                  uint8_t channel_number,
                                                                  uint8_t alert_string_set_selector,
                                                                  uint8_t event_specific_alert_string,
                                                                  fiid_obj_t obj_cmd_rq);

int fill_cmd_get_pef_configuration_parameters (uint8_t parameter_selector,
                                               uint8_t get_parameter,
                                               uint8_t set_selector,
                                               uint8_t block_selector,
                                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_last_processed_event_id (uint8_t set_record_id_for_last_record,
                                          uint16_t record_id,
                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_get_last_processed_event_id (fiid_obj_t obj_cmd_rq);

int fill_cmd_alert_immediate (uint8_t channel_number,
                              uint8_t destination_selector,
                              uint8_t operation,
                              uint8_t string_selector,
                              uint8_t send_alert_string,
                              fiid_obj_t obj_cmd_rq);

int fill_cmd_pet_acknowledge (uint16_t sequence_number,
                              uint32_t local_timestamp,
                              uint8_t event_source_type,
                              uint8_t sensor_device,
                              uint8_t sensor_number,
                              uint32_t event_data,
                              fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_PEF_AND_ALERTING_CMDS_H */
