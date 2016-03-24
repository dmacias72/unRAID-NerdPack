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

#ifndef IPMI_PEF_AND_ALERTING_CMDS_TEMPLATES_H
#define IPMI_PEF_AND_ALERTING_CMDS_TEMPLATES_H

#ifdef __cplusplus
extern "C" {
#endif

/* This header file is for documentation only */

#if 0

Please see fiid.h for details concerning the fiid interface.

The following list the configurable fields of individual packet/record
templates in FreeIPMI.  Each field is listed as a list of the
following.

{ bits, "field name", field flag, field flag, ... }

bits - indicates the number of bits in the field

field name - indicates the name of the field, used for getting/setting
             fields in the fiid API.

field flags - flags indicating qualities of the field.  The following
              qualities may exist for each field.

    REQUIRED - field is required for the packet/record
    OPTIONAL - field is optional for the packet/record

    LENGTH-FIXED - field length is fixed at the number of bits listed

    LENGTH-VARIABLE - field length is variable for the number of bits
                      listed

    MAKES-PACKET-SUFFICIENT - indicates field or fields are
                              "sufficient" to make a packet/record valid
                              and not malformed, but not necessarily a
                              complete packet/record.

Get PEF Capabilities Request
----------------------------

FIID Template: tmpl_cmd_get_pef_capabilities_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get PEF Capabilities Response
-----------------------------

FIID Template: tmpl_cmd_get_pef_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "pef_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "pef_version_minor", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.alert", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.power_down", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.reset", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.power_cycle", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.oem_action", REQUIRED, LENGTH-FIXED }
    { 1, "action_support.diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "oem_event_record_filtering_supported", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_event_filter_table_entries", REQUIRED, LENGTH-FIXED }

ARM PEF Postpone Timer Request
------------------------------

FIID Template: tmpl_cmd_arm_pef_postpone_timer_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "pef_postpone_timeout", REQUIRED, LENGTH-FIXED }

ARM PEF Postpone Timer Response
-------------------------------

FIID Template: tmpl_cmd_arm_pef_postpone_timer_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "present_timer_countdown_value", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Set PEF Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set PEF Configuration Parameters (Set In Progress) Request
----------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (PEF Control) Request
------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_pef_control_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "pef", REQUIRED, LENGTH-FIXED }
    { 1, "pef_event_messages", REQUIRED, LENGTH-FIXED }
    { 1, "pef_startup_delay", REQUIRED, LENGTH-FIXED }
    { 1, "pef_alert_startup_delay", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (PEF Action Global Control) Request
--------------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_pef_action_global_control_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "alert_action", REQUIRED, LENGTH-FIXED }
    { 1, "power_down_action", REQUIRED, LENGTH-FIXED }
    { 1, "reset_action", REQUIRED, LENGTH-FIXED }
    { 1, "power_cycle_action", REQUIRED, LENGTH-FIXED }
    { 1, "oem_action", REQUIRED, LENGTH-FIXED }
    { 1, "diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (PEF Startup Delay) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_pef_startup_delay_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "pef_startup_delay", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (PEF Alert Startup Delay) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_pef_alert_startup_delay_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "pef_alert_startup_delay", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (Event Filter Table) Request
-------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_event_filter_table_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 5, "filter_configuration.reserved", REQUIRED, LENGTH-FIXED }
    { 2, "filter_configuration.type", REQUIRED, LENGTH-FIXED }
    { 1, "filter_configuration.filter", REQUIRED, LENGTH-FIXED }

    { 1, "event_filter_action.alert", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.power_off", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.reset", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.power_cycle", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.oem", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.group_control_operation", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.reserved", REQUIRED, LENGTH-FIXED }

    { 4, "alert_policy_number.policy_number", REQUIRED, LENGTH-FIXED }
    { 3, "alert_policy_number.group_control_selector", REQUIRED, LENGTH-FIXED }
    { 1, "alert_policy_number.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "event_severity", REQUIRED, LENGTH-FIXED }
    { 8, "generator_id_byte1", REQUIRED, LENGTH-FIXED }
    { 8, "generator_id_byte2", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "event_trigger", REQUIRED, LENGTH-FIXED }
    { 16, "event_data1_offset_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_compare2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_compare2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_compare2", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (Event Filter Table Data1) Request
-------------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_event_filter_table_data1_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 5, "filter_configuration.reserved", REQUIRED, LENGTH-FIXED }
    { 2, "filter_configuration.type", REQUIRED, LENGTH-FIXED }
    { 1, "filter_configuration.filter", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (Alert String Keys) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_alert_string_keys_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "string_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    /* Not indicated as 8 bits in E451, but all other filter number fields adjusted to 8 bits */
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 7, "set_number_for_string", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }

Set PEF Configuration Parameters (Alert Strings) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_alert_strings_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "string_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string_data", OPTIONAL, LENGTH-VARIABLE }

Set PEF Configuration Parameters (Alert Policy Table) Request
-------------------------------------------------------------

FIID Template: tmpl_cmd_set_pef_configuration_parameters_alert_policy_table_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "alert_policy_entry_number", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 3, "policy_number.policy_type", REQUIRED, LENGTH-FIXED }
    { 1, "policy_number.enabled", REQUIRED, LENGTH-FIXED }
    { 4, "policy_number.policy_number", REQUIRED, LENGTH-FIXED }
    { 4, "channel_destination.destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "channel_destination.channel_number", REQUIRED, LENGTH-FIXED }
    { 7, "alert_string_key.alert_string_set_selector", REQUIRED, LENGTH-FIXED }
    { 1, "alert_string_key.event_specific_alert_string", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "get_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Get PEF Configuration Parameters (Set In Progress) Response
-----------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_set_in_progress_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (PEF Control) Response
-------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_pef_control_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "pef", REQUIRED, LENGTH-FIXED }
    { 1, "pef_event_messages", REQUIRED, LENGTH-FIXED }
    { 1, "pef_startup_delay", REQUIRED, LENGTH-FIXED }
    { 1, "pef_alert_startup_delay", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (PEF Action Global Control) Response
---------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_pef_action_global_control_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "alert_action", REQUIRED, LENGTH-FIXED }
    { 1, "power_down_action", REQUIRED, LENGTH-FIXED }
    { 1, "reset_action", REQUIRED, LENGTH-FIXED }
    { 1, "power_cycle_action", REQUIRED, LENGTH-FIXED }
    { 1, "oem_action", REQUIRED, LENGTH-FIXED }
    { 1, "diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (PEF Startup Delay) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_pef_startup_delay_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "pef_startup_delay", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (PEF Alert Startup Delay) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_pef_alert_startup_delay_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "pef_alert_startup_delay", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (Number of Event Filters) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_number_of_event_filters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_event_filters", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get PEF Configuration Parameters (Event Filter Table) Response
--------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_event_filter_table_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 5, "filter_configuration.reserved", REQUIRED, LENGTH-FIXED }
    { 2, "filter_configuration.type", REQUIRED, LENGTH-FIXED }
    { 1, "filter_configuration.filter", REQUIRED, LENGTH-FIXED }

    { 1, "event_filter_action.alert", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.power_off", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.reset", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.power_cycle", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.oem", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.group_control_operation", REQUIRED, LENGTH-FIXED }
    { 1, "event_filter_action.reserved", REQUIRED, LENGTH-FIXED }

    { 4, "alert_policy_number.policy_number", REQUIRED, LENGTH-FIXED }
    { 3, "alert_policy_number.group_control_selector", REQUIRED, LENGTH-FIXED }
    { 1, "alert_policy_number.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "event_severity", REQUIRED, LENGTH-FIXED }
    { 8, "generator_id_byte1", REQUIRED, LENGTH-FIXED }
    { 8, "generator_id_byte2", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "event_trigger", REQUIRED, LENGTH-FIXED }
    { 16, "event_data1_offset_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1_compare2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2_compare2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_AND_mask", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_compare1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3_compare2", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (Event Filter Table Data1) Response
--------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_event_filter_table_data1_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 5, "filter_configuration.reserved", REQUIRED, LENGTH-FIXED }
    { 2, "filter_configuration.type", REQUIRED, LENGTH-FIXED }
    { 1, "filter_configuration.filter", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (Number of Alert Policy Entries) Response
--------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_number_of_alert_policy_entries_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 7, "number_of_alert_policy_entries", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get PEF Configuration Parameters (Number of Alert Strings) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_number_of_alert_strings_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 7, "number_of_alert_strings", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get PEF Configuration Parameters (Alert String Keys) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_alert_string_keys_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 7, "string_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    /* Not indicated as 8 bits in E451, but all other filter number fields adjusted to 8 bits */
    { 8, "filter_number", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 7, "set_number_for_string", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }

Get PEF Configuration Parameters (Alert Strings) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_alert_strings_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 7, "string_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string_data", OPTIONAL, LENGTH-VARIABLE }

Get PEF Configuration Parameters (Alert Policy Table) Response
--------------------------------------------------------------

FIID Template: tmpl_cmd_get_pef_configuration_parameters_alert_policy_table_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 7, "alert_policy_entry_number", REQUIRED, LENGTH-FIXED }
    { 1, "alert_policy_entry_number.reserved", REQUIRED, LENGTH-FIXED }
    { 3, "policy_number.policy_type", REQUIRED, LENGTH-FIXED }
    { 1, "policy_number.enabled", REQUIRED, LENGTH-FIXED }
    { 4, "policy_number.policy_number", REQUIRED, LENGTH-FIXED }
    { 4, "channel_destination.destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "channel_destination.channel_number", REQUIRED, LENGTH-FIXED }
    { 7, "alert_string_key.alert_string_set_selector", REQUIRED, LENGTH-FIXED }
    { 1, "alert_string_key.event_specific_alert_string", REQUIRED, LENGTH-FIXED }

Set Last Processed Event ID Request
-----------------------------------

FIID Template: tmpl_cmd_set_last_processed_event_id_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "set_record_id_for_last_record", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }
    { 16, "record_id", REQUIRED, LENGTH-FIXED }

Set Last Processed Event ID Response
------------------------------------

FIID Template: tmpl_cmd_set_last_processed_event_id_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Last Processed Event ID Request
-----------------------------------

FIID Template: tmpl_cmd_get_last_processed_event_id_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Last Processed Event ID Response
------------------------------------

FIID Template: tmpl_cmd_get_last_processed_event_id_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "most_recent_addition_timestamp", REQUIRED, LENGTH-FIXED }
    { 16, "record_id_for_last_record_in_sel", REQUIRED, LENGTH-FIXED }
    { 16, "last_sw_processed_event_record_id", REQUIRED, LENGTH-FIXED }
    { 16, "last_bmc_processed_event_record_id", REQUIRED, LENGTH-FIXED }

Alert Immediate Request
-----------------------

FIID Template: tmpl_cmd_alert_immediate_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "destination_selector", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 7, "string_selector", REQUIRED, LENGTH-FIXED }
    { 1, "send_alert_string", REQUIRED, LENGTH-FIXED }

Alert Immediate Response
------------------------

FIID Template: tmpl_cmd_alert_immediate_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

PET Acknowledge Request
-----------------------

FIID Template: tmpl_cmd_pet_acknowledge_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 16, "sequence_number", REQUIRED, LENGTH-FIXED }
    { 32, "local_timestamp", REQUIRED, LENGTH-FIXED }
    { 8, "event_source_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_device", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 24, "event_data", REQUIRED, LENGTH-FIXED }

PET Acknowledge Response
------------------------

FIID Template: tmpl_cmd_pet_acknowledge_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_PEF_AND_ALERTING_CMDS_TEMPLATES_H */
