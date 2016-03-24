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

#ifndef IPMI_MESSAGING_SUPPORT_CMDS_TEMPLATES_H
#define IPMI_MESSAGING_SUPPORT_CMDS_TEMPLATES_H

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

Set BMC Global Enables Request
------------------------------

FIID Template: tmpl_cmd_set_bmc_global_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "receive_message_queue_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_message_buffer_full_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_message_buffer", REQUIRED, LENGTH-FIXED }
    { 1, "system_event_logging", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "oem_0", REQUIRED, LENGTH-FIXED }
    { 1, "oem_1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_2", REQUIRED, LENGTH-FIXED }

Set BMC Global Enables Response
-------------------------------

FIID Template: tmpl_cmd_set_bmc_global_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get BMC Global Enables Request
------------------------------

FIID Template: tmpl_cmd_get_bmc_global_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get BMC Global Enables Response
-------------------------------

FIID Template: tmpl_cmd_get_bmc_global_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "receive_message_queue_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_message_buffer_full_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "event_message_buffer", REQUIRED, LENGTH-FIXED }
    { 1, "system_event_logging", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "oem_0", REQUIRED, LENGTH-FIXED }
    { 1, "oem_1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_2", REQUIRED, LENGTH-FIXED }

Clear Message Flags Request
---------------------------

FIID Template: tmpl_cmd_clear_message_flags_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "clear_receive_message_queue", REQUIRED, LENGTH-FIXED }
    { 1, "clear_event_message_buffer", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "clear_watchdog_pre_timeout_interrupt_flag", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "clear_oem_0", REQUIRED, LENGTH-FIXED }
    { 1, "clear_oem_1", REQUIRED, LENGTH-FIXED }
    { 1, "clear_oem_2", REQUIRED, LENGTH-FIXED }

Clear Message Flags Response
----------------------------

FIID Template: tmpl_cmd_clear_message_flags_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Message Flags Request
-------------------------

FIID Template: tmpl_cmd_get_message_flags_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Message Flags Response
--------------------------

FIID Template: tmpl_cmd_get_message_flags_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "receive_message_available", REQUIRED, LENGTH-FIXED }
    { 1, "event_message_buffer_full", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "watchdog_pre_timeout_interrupt_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_0_data_available", REQUIRED, LENGTH-FIXED }
    { 1, "oem_1_data_available", REQUIRED, LENGTH-FIXED }
    { 1, "oem_2_data_available", REQUIRED, LENGTH-FIXED }

Enable Message Channel Receive Request
--------------------------------------

FIID Template: tmpl_cmd_enable_message_channel_receive_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 2, "channel_operation", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Enable Message Channel Receive Response
---------------------------------------

FIID Template: tmpl_cmd_enable_message_channel_receive_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "channel_state", REQUIRED, LENGTH-FIXED }
    { 7, "reserved2", REQUIRED, LENGTH-FIXED }

Get Message Request
-------------------

FIID Template: tmpl_cmd_get_message_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Message Response
--------------------

FIID Template: tmpl_cmd_get_message_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "inferred_privilege_level", REQUIRED, LENGTH-FIXED }
    { 1024, "message_data", OPTIONAL, LENGTH-VARIABLE }

Send Message Request
--------------------

FIID Template: tmpl_cmd_send_message_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 1, "send_message_with_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "send_message_with_encryption", REQUIRED, LENGTH-FIXED }
    { 2, "tracking_operation", REQUIRED, LENGTH-FIXED }
    { 1024, "message_data", REQUIRED, LENGTH-VARIABLE }

Send Message Response
---------------------

FIID Template: tmpl_cmd_send_message_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1024, "response_data", OPTIONAL, LENGTH-VARIABLE }

Read Event Message Buffer Request
---------------------------------

FIID Template: tmpl_cmd_read_event_message_buffer_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Read Event Message Buffer Response
----------------------------------

FIID Template: tmpl_cmd_read_event_message_buffer_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "message_data", REQUIRED, LENGTH-FIXED }

Get System Interface Capabilities Request
-----------------------------------------

FIID Template: tmpl_cmd_get_system_interface_capabilities_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "system_interface", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }


Get System Interface Capabilities Response
------------------------------------------

FIID Template: tmpl_cmd_get_system_interface_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "data", OPTIONAL, LENGTH-VARIABLE }

Get System Interface Capabilities (SSIF) Response
--------------------------------------------------

FIID Template: tmpl_cmd_get_system_interface_capabilities_ssif_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "reserved1", REQUIRED, LENGTH-FIXED }
    { 3, "ssif_version", REQUIRED, LENGTH-FIXED }
    { 1, "pec_support", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "transaction_support", REQUIRED, LENGTH-FIXED }
    { 8, "input_message_size", REQUIRED, LENGTH-FIXED }
    { 8, "output_message_size", REQUIRED, LENGTH-FIXED }

Get System Interface Capabilities (KCS) Response
------------------------------------------------

FIID Template: tmpl_cmd_get_system_interface_capabilities_kcs_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "reserved1", REQUIRED, LENGTH-FIXED }
    { 3, "system_interface_version", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "input_maximum_message_size", REQUIRED, LENGTH-FIXED }

Get BT Interface Capabilities Request
-------------------------------------

FIID Template: tmpl_cmd_get_bt_interface_capabilities_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get BT Interface Capabilities Response
--------------------------------------

FIID Template: tmpl_cmd_get_bt_interface_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "number_of_outstanding_requests_supported", REQUIRED, LENGTH-FIXED }
    { 8, "input_buffer_size", REQUIRED, LENGTH-FIXED }
    { 8, "output_buffer_size", REQUIRED, LENGTH-FIXED }
    { 8, "bmc_request_to_response_time", REQUIRED, LENGTH-FIXED }
    { 8, "recommended_retries", REQUIRED, LENGTH-FIXED }

Master Write-Read Request
-------------------------

FIID Template: tmpl_cmd_master_write_read_rq 

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "bus_type", REQUIRED, LENGTH-FIXED }
    { 3, "bus_id", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 7, "slave_address", REQUIRED, LENGTH-FIXED }
    { 8, "read_count", REQUIRED, LENGTH-FIXED }
    { 2040, "data", OPTIONAL, LENGTH-VARIABLE }

Master Write-Read Response
--------------------------

FIID Template: tmpl_cmd_master_write_read_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 2040, "data", OPTIONAL, LENGTH-VARIABLE }

Get Channel Authentication Capabilities Request
-----------------------------------------------

FIID Template: tmpl_cmd_get_channel_authentication_capabilities_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 3, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "get_ipmi_v2.0_extended_data", REQUIRED, LENGTH-FIXED }
    { 4, "maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Get Channel Authentication Capabilities Response
------------------------------------------------

FIID Template: tmpl_cmd_get_channel_authentication_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "channel_number", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.none", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.md2", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.md5", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.straight_password_key", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.oem_prop", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_type.ipmi_v2.0_extended_capabilities_available", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.anonymous_login", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.null_username", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.non_null_username", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.user_level_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.per_message_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_status.k_g", REQUIRED, LENGTH-FIXED }
    { 2, "authentication_status.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "channel_supports_ipmi_v1.5_connections", REQUIRED, LENGTH-FIXED }
    { 1, "channel_supports_ipmi_v2.0_connections", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }
    { 24, "oem_id", REQUIRED, LENGTH-FIXED }
    { 8, "oem_auxiliary_data", REQUIRED, LENGTH-FIXED }

Get System GUID Request
-----------------------

FIID Template: tmpl_cmd_get_system_guid_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get System GUID Response
------------------------

FIID Template: tmpl_cmd_get_system_guid_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "guid", REQUIRED, LENGTH-FIXED }

Get System GUID (with Format) Response
--------------------------------------

FIID Template: tmpl_cmd_get_system_guid_format_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 48, "node", REQUIRED, LENGTH-FIXED }
    { 8, "clock_seq_low", REQUIRED, LENGTH-FIXED }
    { 8, "clock_seq_hi_and_reserved", REQUIRED, LENGTH-FIXED }
    { 16, "time_high_and_version", REQUIRED, LENGTH-FIXED }
    { 16, "time_mid", REQUIRED, LENGTH-FIXED }
    { 32, "time_low", REQUIRED, LENGTH-FIXED }

  Notes: node and time values LS byte first. 

Set System Info Parameters Request
----------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Set System Info Parameters Response
-----------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set System Info Parameters (Set In Progress) Request
----------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (System Firmware Version First Set) Request
----------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_system_firmware_version_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (System Firmware Version) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_system_firmware_version_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (System Name First Set) Request
----------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_system_name_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (System Name) Request
------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_system_name_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (Primary Operating System Name First Set) Request
----------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_primary_operating_system_name_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (Primary Operating System Name) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_primary_operating_system_name_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (Operating System Name First Set) Request
--------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_operating_system_name_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (Operating System Name) Request
----------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_operating_system_name_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (Present OS Version Number First Set) Request
------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_present_os_version_number_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (Present OS Version Number) Request
--------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_present_os_version_number_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (BMC URL First Set) Request
------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_bmc_url_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (BMC URL) Request
--------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_bmc_url_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Set System Info Parameters (Base OS/Hypervisor URL First Set) Request
---------------------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_base_os_hypervisor_url_first_set_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Set System Info Parameters (Base OS/Hypervisor URL) Request
-----------------------------------------------------------

FIID Template: tmpl_cmd_set_system_info_parameters_base_os_hypervisor_url_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Get System Info Parameters Request
----------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "get_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get System Info Parameters Response
-----------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Get System Info Parameters (Set In Progress) Response
-----------------------------------------------------

Get System Info Parameters (System Firmware Version First Set) Response
-----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_system_firmware_version_first_set_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Get System Info Parameters (System Firmware Version) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_system_firmware_version_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Get System Info Parameters (System Name First Set) Response
-----------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_system_name_first_set_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Get System Info Parameters (System Name) Response
-------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_system_name_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Get System Info Parameters (Primary Operating System Name First Set) Response
-----------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_primary_operating_system_name_first_set_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Get System Info Parameters (Primary Operating System Name) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_primary_operating_system_name_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Get System Info Parameters (Operating System Name First Set) Response
---------------------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_operating_system_name_first_set_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 4, "encoding", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "string_length", REQUIRED, LENGTH-FIXED }
    { 112, "string", OPTIONAL, LENGTH-VARIABLE }

Get System Info Parameters (Operating System Name) Response
-----------------------------------------------------------

FIID Template: tmpl_cmd_get_system_info_parameters_operating_system_name_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 128, "string", REQUIRED, LENGTH-FIXED }

Get Channel Cipher Suites Request
---------------------------------

FIID Template: tmpl_cmd_get_channel_cipher_suites_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 6, "list_index", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "list_algorithm_type", REQUIRED, LENGTH-FIXED }

Get Channel Cipher Suites Response
----------------------------------

FIID Template: tmpl_cmd_get_channel_cipher_suites_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "channel_number", REQUIRED, LENGTH-FIXED }
    { 128, "cipher_suite_record_data", OPTIONAL, LENGTH-VARIABLE }

Get Session Challenge Request
-----------------------------

FIID Template: tmpl_cmd_get_session_challenge_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "authentication_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 128, "user_name", REQUIRED, LENGTH-FIXED }

Get Session Challenge Response
------------------------------

FIID Template: tmpl_cmd_get_session_challenge_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "temp_session_id", REQUIRED, LENGTH-FIXED }
    { 128, "challenge_string", REQUIRED, LENGTH-FIXED }

  Notes: Session id LS byte first.

Activiate Session Request
-------------------------

FIID Template: tmpl_cmd_activate_session_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "authentication_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 128, "challenge_string", REQUIRED, LENGTH-FIXED }
    { 32, "initial_outbound_sequence_number", REQUIRED, LENGTH-FIXED }

Activiate Session Response
--------------------------

FIID Template: tmpl_cmd_activate_session_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "authentication_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 32, "initial_inbound_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Set Session Privilege Level Request
-----------------------------------

FIID Template: tmpl_cmd_set_session_privilege_level_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }

Set Session Privilege Level Response
------------------------------------

FIID Template: tmpl_cmd_set_session_privilege_level_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }

Close Session Request
---------------------

FIID Template: tmpl_cmd_close_session_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 8, "session_handle", OPTIONAL, LENGTH-FIXED }

Close Session Response
----------------------

FIID Template: tmpl_cmd_close_session_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }


Set Channel Access Request
--------------------------

FIID Template: tmpl_cmd_set_channel_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 3, "ipmi_messaging_access_mode", REQUIRED, LENGTH-FIXED }
    { 1, "user_level_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "per_message_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "pef_alerting", REQUIRED, LENGTH-FIXED }
    { 2, "channel_access_set", REQUIRED, LENGTH-FIXED }
    { 4, "channel_privilege_level_limit", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "channel_privilege_level_limit_set", REQUIRED, LENGTH-FIXED }

Set Channel Access Response
---------------------------

FIID Template: tmpl_cmd_set_channel_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Channel Access Request
--------------------------

FIID Template: tmpl_cmd_get_channel_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "channel_access_get", REQUIRED, LENGTH-FIXED }

Get Channel Access Response
---------------------------

FIID Template: tmpl_cmd_get_channel_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 3, "ipmi_messaging_access_mode", REQUIRED, LENGTH-FIXED }
    { 1, "user_level_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "per_message_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "pef_alerting", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "channel_privilege_level_limit", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Get Channel Info Command Request
--------------------------------

FIID Template: tmpl_cmd_get_channel_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get Channel Info Command Response
---------------------------------

FIID Template: tmpl_cmd_get_channel_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "actual_channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "actual_channel_number.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "channel_medium_type", REQUIRED, LENGTH-FIXED }
    { 1, "channel_medium_type.reserved", REQUIRED, LENGTH-FIXED }
    { 5, "channel_protocol_type", REQUIRED, LENGTH-FIXED }
    { 3, "channel_protocol_type.reserved", REQUIRED, LENGTH-FIXED }
    { 6, "active_session_count", REQUIRED, LENGTH-FIXED }
    { 2, "session_support", REQUIRED, LENGTH-FIXED }
    { 24, "vendor_id", REQUIRED, LENGTH-FIXED }
    { 16, "auxiliary_channel_info", REQUIRED, LENGTH-FIXED }

Set Channel Security Keys Request
---------------------------------

FIID Template: tmpl_cmd_set_channel_security_keys_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "key_id", REQUIRED, LENGTH-FIXED }
    { 160, "key_value", OPTIONAL, LENGTH-VARIABLE }

Set Channel Security Keys Response
----------------------------------

FIID Template: tmpl_cmd_set_channel_security_keys_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 2, "lock_status", OPTIONAL, LENGTH-FIXED }
    { 6, "reserved", OPTIONAL, LENGTH-FIXED }
    { 160, "key_value", OPTIONAL, LENGTH-VARIABLE }

Set User Access Command Request
-------------------------------

FIID Template: tmpl_cmd_set_user_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 1, "user_ipmi_messaging", REQUIRED, LENGTH-FIXED }
    { 1, "user_link_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "user_restricted_to_callback", REQUIRED, LENGTH-FIXED }
    { 1, "change_bits_in_byte", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "user_privilege_level_limit", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "user_session_limit", REQUIRED, LENGTH-FIXED }
    { 4, "reserved3", REQUIRED, LENGTH-FIXED }

Set User Access Command Response
--------------------------------

FIID Template: tmpl_cmd_set_user_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get User Access Command Request
-------------------------------

FIID Template: tmpl_cmd_get_user_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }

Get User Access Command Response
--------------------------------

FIID Template: tmpl_cmd_get_user_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 6, "max_channel_user_ids", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "current_channel_user_ids", REQUIRED, LENGTH-FIXED }
    { 2, "user_id_enable_status", REQUIRED, LENGTH-FIXED }
    { 6, "current_channel_fixed_names", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "user_privilege_level_limit", REQUIRED, LENGTH-FIXED }
    { 1, "user_ipmi_messaging", REQUIRED, LENGTH-FIXED }
    { 1, "user_link_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "user_restricted_to_callback", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }

Set User Name Command Request
-----------------------------

FIID Template: tmpl_cmd_set_user_name_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "user_id.reserved", REQUIRED, LENGTH-FIXED }
    { 128, "user_name", REQUIRED, LENGTH-FIXED }

Set User Name Command Response
------------------------------

FIID Template: tmpl_cmd_set_user_name_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get User Name Command Request
-----------------------------

FIID Template: tmpl_cmd_get_user_name_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "user_id.reserved", REQUIRED, LENGTH-FIXED }

Get User Name Command Response
------------------------------

FIID Template: tmpl_cmd_get_user_name_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "user_name", REQUIRED, LENGTH-FIXED }

Set User Password Command Request
---------------------------------

FIID Template: tmpl_cmd_set_user_password_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 1, "user_id.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "password_size", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 6, "operation.reserved", REQUIRED, LENGTH-FIXED }
    { 160, "password", OPTIONAL, LENGTH-VARIABLE }

  Notes: password is variable length, but limited to length of 0, 16,
  or 20.

Set User Password Command Response
----------------------------------

FIID Template: tmpl_cmd_set_user_password_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_MESSAGING_SUPPORT_CMDS_TEMPLATES_H */
