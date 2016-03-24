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

#ifndef IPMI_CHASSIS_CMDS_TEMPLATES_H
#define IPMI_CHASSIS_CMDS_TEMPLATES_H

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

Get Chassis Capabilities Request
--------------------------------

FIID Template: tmpl_cmd_get_chassis_capabilities_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Chassis Capabilities Response
---------------------------------

FIID Template: tmpl_cmd_get_chassis_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "capabilities_flags.provides_intrusion_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "capabilities_flags.provides_front_panel_lockout", REQUIRED, LENGTH-FIXED }
    { 1, "capabilities_flags.provides_diagnostic_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "capabilities_flags.provides_power_interlock", REQUIRED, LENGTH-FIXED }
    { 4, "capabilities_flags.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "fru_info_device_address", REQUIRED, LENGTH-FIXED }
    { 8, "sdr_device_address", REQUIRED, LENGTH-FIXED }
    { 8, "sel_device_address", REQUIRED, LENGTH-FIXED }
    { 8, "system_management_device_address", REQUIRED, LENGTH-FIXED }
    { 8, "bridge_device_address", OPTIONAL, LENGTH-FIXED }

Get Chassis Status Request
--------------------------

FIID Template: tmpl_cmd_get_chassis_status_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Chassis Status Response
---------------------------

FIID Template: tmpl_cmd_get_chassis_status_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "current_power_state.power_is_on", REQUIRED, LENGTH-FIXED }
    { 1, "current_power_state.power_overload", REQUIRED, LENGTH-FIXED }
    { 1, "current_power_state.interlock", REQUIRED, LENGTH-FIXED }
    { 1, "current_power_state.power_fault", REQUIRED, LENGTH-FIXED }
    { 1, "current_power_state.power_control_fault", REQUIRED, LENGTH-FIXED }
    { 2, "current_power_state.power_restore_policy", REQUIRED, LENGTH-FIXED }
    { 1, "current_power_state.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "last_power_event.ac_failed", REQUIRED, LENGTH-FIXED }
    { 1, "last_power_event.power_down_caused_by_power_overload", REQUIRED, LENGTH-FIXED }
    { 1, "last_power_event.power_down_caused_by_power_interlock_being_activated", REQUIRED, LENGTH-FIXED }
    { 1, "last_power_event.power_down_caused_by_power_fault", REQUIRED, LENGTH-FIXED }
    { 1, "last_power_event.power_on_entered_via_ipmi", REQUIRED, LENGTH-FIXED }
    { 3, "last_power_event.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.chassis_intrusion_active", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.front_panel_lockout_active", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.drive_fault", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.cooling_fan_fault_detected", REQUIRED, LENGTH-FIXED }
    { 2, "misc_chassis_state.chassis_identify_state", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.chassis_identify_command_and_state_info_supported", REQUIRED, LENGTH-FIXED }
    { 1, "misc_chassis_state.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "front_panel.power_off_button_disabled", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.reset_button_disabled", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.diagnostic_interrupt_button_disabled", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.standby_button_disabled", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.power_off_button_disable_allowed", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.reset_button_disable_allowed", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.diagnostic_interrupt_button_disable_allowed", OPTIONAL, LENGTH-FIXED }
    { 1, "front_panel.standby_button_disable_allowed", OPTIONAL, LENGTH-FIXED }

Chassis Control Request
-----------------------

FIID Template: tmpl_cmd_chassis_control_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "chassis_control", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Chassis Control Response
------------------------

FIID Template: tmpl_cmd_chassis_control_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Chassis Identify Request
------------------------

FIID Template: tmpl_cmd_chassis_identify_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "identify_interval", OPTIONAL, LENGTH-FIXED }
    { 1, "force_identify", OPTIONAL, LENGTH-FIXED }
    { 7, "reserved", OPTIONAL, LENGTH-FIXED }

Chassis Identify Response
-------------------------

FIID Template: tmpl_cmd_chassis_identify_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set Front Panel Button Enables Request
--------------------------------------

FIID Template: tmpl_cmd_set_front_panel_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "disable_power_off_button_for_power_off_only", REQUIRED, LENGTH-FIXED }
    { 1, "disable_reset_button", REQUIRED, LENGTH-FIXED }
    { 1, "disable_diagnostic_interrupt_button", REQUIRED, LENGTH-FIXED }
    { 1, "disable_standby_button_for_entering_standby", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Set Front Panel Button Enables Response
---------------------------------------

FIID Template: tmpl_cmd_set_front_panel_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set Power Restore Policy Request
--------------------------------

FIID Template: tmpl_cmd_set_power_restore_policy_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 3, "power_restore_policy", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }

Set Power Restore Policy Response
---------------------------------

FIID Template: tmpl_cmd_set_power_restore_policy_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "powered_off_after_ac_mains_returns", REQUIRED, LENGTH-FIXED }
    { 1, "restoring_power_to_state_when_ac_mains_was_lost", REQUIRED, LENGTH-FIXED }
    { 1, "always_powering_up_after_ac_mains_returns", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }

Set Power Cycle Interval Request
--------------------------------

FIID Template: tmpl_cmd_set_power_cycle_interval_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "interval", REQUIRED, LENGTH-FIXED }

Set Power Cycle Interval Response
---------------------------------

FIID Template: tmpl_cmd_set_power_cycle_interval_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get System Restart Cause Request
--------------------------------

FIID Template: tmpl_cmd_get_system_restart_cause_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get System Restart Cause Response
---------------------------------

FIID Template: tmpl_cmd_get_system_restart_cause_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "restart_cause", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "channel", REQUIRED, LENGTH-FIXED }

Set System Boot Options Request
-------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 296, "configuration_parameter_data", OPTIONAL, LENGTH-VARIABLE }

Set System Boot Options Response
--------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set System Boot Options (Set In Progress) Request
-------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Service Partition Selector) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_service_partition_selector_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 8, "service_partition_selector", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Service Partition Scan) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_service_partition_scan_rq

    {8, "cmd", REQUIRED, LENGTH-FIXED }
    {7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    {1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    {1, "service_partition_discovered", REQUIRED, LENGTH-FIXED }
    {1, "service_partition_scan", REQUIRED, LENGTH-FIXED }
    {6, "reserved", REQUIRED, LENGTH-FIXED }

Set System Boot Options (BMC Boot Flag Valid Bit Clearing) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_BMC_boot_flag_valid_bit_clearing_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_power_up_via_power_pushbutton_or_wake_event", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_pushbutton_reset_soft_reset", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_reset_power_cycle_caused_by_watchdog_timeout", REQUIRED, LENGTH-FIXED }
    { 1, "dont_automatically_clear_boot_flag_valid_bit_if_chassis_control_command_not_received_within_60_second_timeout", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_reset_power_cycle_caused_by_PEF", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Boot Info Acknowledge) Request
-------------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_boot_info_acknowledge_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_0", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_1", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_2", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_3", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_4", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_5", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_6", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_7", REQUIRED, LENGTH-FIXED }
    { 1, "bios_or_post_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "os_loader_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "os_or_service_partition_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "sms_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "oem_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Boot Flags) Request
--------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_boot_flags_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "bios_boot_type", REQUIRED, LENGTH-FIXED }
    { 1, "boot_flags_persistent", REQUIRED, LENGTH-FIXED }
    { 1, "boot_flags_valid", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_reset_button", REQUIRED, LENGTH-FIXED }
    { 1, "screen_blank", REQUIRED, LENGTH-FIXED }
    { 4, "boot_device", REQUIRED, LENGTH-FIXED }
    { 1, "lock_keyboard", REQUIRED, LENGTH-FIXED }
    { 1, "cmos_clear", REQUIRED, LENGTH-FIXED }
    { 2, "console_redirection", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_sleep_button", REQUIRED, LENGTH-FIXED }
    { 1, "user_password_bypass", REQUIRED, LENGTH-FIXED }
    { 1, "force_progress_event_traps", REQUIRED, LENGTH-FIXED }
    { 2, "firmware_bios_verbosity", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_via_power_button", REQUIRED, LENGTH-FIXED }
    { 3, "bios_mux_control_override", REQUIRED, LENGTH-FIXED }
    { 1, "bios_shared_mode_override", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 5, "device_instance_selector", REQUIRED, LENGTH-FIXED }
    { 3, "reserved3", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Boot Initiator Info) Request
-----------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_boot_initiator_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 4, "boot_source.channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "boot_source.reserved", REQUIRED, LENGTH-FIXED }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 32, "boot_info_timestamp", REQUIRED, LENGTH-FIXED }

Set System Boot Options (Boot Initiator Mailbox) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_system_boot_options_boot_initiator_mailbox_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "block_data", OPTIONAL, LENGTH-VARIABLE }

Get System Boot Options Request
-------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get System Boot Options Response
--------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 296, "configuration_parameter_data", OPTIONAL, LENGTH-VARIABLE }

Get System Boot Options (Set In Progress) Response
--------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_set_in_progress_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Get System Boot Options (Service Partition Selector) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_service_partition_selector_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 8, "service_partition_selector", REQUIRED, LENGTH-FIXED }

Get System Boot Options (Service Partition Scan) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_service_partition_scan_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 1, "service_partition_discovered", REQUIRED, LENGTH-FIXED }
    { 1, "service_partition_scan", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Get System Boot Options (BMC Boot Flag Valid Bit Clearing) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_BMC_boot_flag_valid_bit_clearing_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_power_up_via_power_pushbutton_or_wake_event", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_pushbutton_reset_soft_reset", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_reset_power_cycle_caused_by_watchdog_timeout", REQUIRED, LENGTH-FIXED }
    { 1, "dont_automatically_clear_boot_flag_valid_bit_if_chassis_control_command_not_received_within_60_second_timeout", REQUIRED, LENGTH-FIXED }
    { 1, "dont_clear_valid_bit_on_reset_power_cycle_caused_by_PEF", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }

Get System Boot Options (Boot Info Acknowledge) Response
--------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_boot_info_acknowledge_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_0", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_1", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_2", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_3", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_4", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_5", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_6", REQUIRED, LENGTH-FIXED }
    { 1, "enable_write_bit_7", REQUIRED, LENGTH-FIXED }
    { 1, "bios_or_post_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "os_loader_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "os_or_service_partition_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "sms_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 1, "oem_handled_boot_info", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }

Get System Boot Options (Boot Flags) Response
---------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_boot_flags_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "bios_boot_type", REQUIRED, LENGTH-FIXED }
    { 1, "boot_flags_persistent", REQUIRED, LENGTH-FIXED }
    { 1, "boot_flags_valid", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_reset_button", REQUIRED, LENGTH-FIXED }
    { 1, "screen_blank", REQUIRED, LENGTH-FIXED }
    { 4, "boot_device", REQUIRED, LENGTH-FIXED }
    { 1, "lock_keyboard", REQUIRED, LENGTH-FIXED }
    { 1, "cmos_clear", REQUIRED, LENGTH-FIXED }
    { 2, "console_redirection", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_sleep_button", REQUIRED, LENGTH-FIXED }
    { 1, "user_password_bypass", REQUIRED, LENGTH-FIXED }
    { 1, "force_progress_event_traps", REQUIRED, LENGTH-FIXED }
    { 2, "firmware_bios_verbosity", REQUIRED, LENGTH-FIXED }
    { 1, "lock_out_via_power_button", REQUIRED, LENGTH-FIXED }
    { 3, "bios_mux_control_override", REQUIRED, LENGTH-FIXED }
    { 1, "bios_shared_mode_override", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 5, "device_instance_selector", REQUIRED, LENGTH-FIXED }
    { 3, "reserved3", REQUIRED, LENGTH-FIXED }

Get System Boot Options (Boot Initiator Info) Response
------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_boot_initiator_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 4, "boot_source.channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "boot_source.reserved", REQUIRED, LENGTH-FIXED }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 32, "boot_info_timestamp", REQUIRED, LENGTH-FIXED }
  
Get System Boot Options (Boot Initiator Mailbox) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_system_boot_options_boot_initiator_mailbox_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "parameter_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "parameter_valid", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "block_data", OPTIONAL, LENGTH-VARIABLE }

Get Power On Hours Counter Request
----------------------------------

FIID Template: tmpl_cmd_get_power_on_hours_counter_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Power On Hours Counter Response
-----------------------------------

FIID Template: tmpl_cmd_get_power_on_hours_counter_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "minutes_per_counter", REQUIRED, LENGTH-FIXED }
    { 32, "counter_reading", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CHASSIS_CMDS_TEMPLATES_H */
