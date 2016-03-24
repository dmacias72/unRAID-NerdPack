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

#ifndef IPMI_LAN_CMDS_TEMPLATES_H
#define IPMI_LAN_CMDS_TEMPLATES_H

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

Set LAN Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Set LAN Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set LAN Configuration Parameters (Set In Progress) Request
----------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Authentication Type Enables) Request
----------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_authentication_type_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }

    { 1, "callback_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "callback_level.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "user_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "user_level.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "operator_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "operator_level.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "admin_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "admin_level.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "oem_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "oem_level.reserved2", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (IP Address) Request
-----------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_ip_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (IP Address Source) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_ip_address_source_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "ip_address_source", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (MAC Address) Request
------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_mac_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Subnet Mask) Request
------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_subnet_mask_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 32, "subnet_mask", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (BMC Generated ARP Control) Request
--------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_bmc_generated_arp_control_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "bmc_generated_gratuitous_arps", REQUIRED, LENGTH-FIXED }
    { 1, "bmc_generated_arp_responses", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Gratuitous ARP Interval) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_gratuitous_arp_interval_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "gratuitous_arp_interval", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Default Gateway Address) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_default_gateway_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Default Gateway MAC Address) Request
----------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_default_gateway_mac_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Backup Gateway Address) Request
-----------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_backup_gateway_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Backup Gateway MAC Address) Request
---------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_backup_gateway_mac_address_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Community String) Request
-----------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_community_string_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 144, "community_string", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Destination Type) Request
-----------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_destination_type_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 3, "destination_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "alert_acknowledge", REQUIRED, LENGTH-FIXED }
    { 8, "alert_acknowledge_timeout", REQUIRED, LENGTH-FIXED }
    { 3, "retries", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }
    { 4, "reserved5", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (Destination Addresses) Request
----------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_destination_addresses_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "reserved3", REQUIRED, LENGTH-FIXED }
    { 4, "address_format", REQUIRED, LENGTH-FIXED }
    { 1, "gateway_selector", REQUIRED, LENGTH-FIXED }
    { 7, "reserved4", REQUIRED, LENGTH-FIXED }
    { 32, "alerting_ip_address", REQUIRED, LENGTH-FIXED }
    { 48, "alerting_mac_address", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (VLAN ID) Request
--------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_vlan_id_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 12, "vlan_id", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "vlan_id_enable", REQUIRED, LENGTH-FIXED }

  Notes: Vlan ID LS byte first.

Set LAN Configuration Parameters (VLAN Priority) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_vlan_priority_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 3, "vlan_priority", REQUIRED, LENGTH-FIXED }
    { 2, "unspecified", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }

Set LAN Configuration Parameters (RMCP+ Messaging Cipher Suite Privilege Levels) Request
----------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_rmcpplus_messaging_cipher_suite_privilege_levels_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_1", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_2", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_3", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_4", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_5", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_6", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_7", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_8", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_9", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_10", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_11", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_12", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_13", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_14", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_15", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_16", OPTIONAL, LENGTH-FIXED }

Set LAN Configuration Parameters (Bad Password Threshold) Request
-----------------------------------------------------------------

FIID Template: tmpl_cmd_set_lan_configuration_parameters_bad_password_threshold_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "user_disabled_event_message", REQUIRED, LENGTH-FIXED }
    { 7, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "bad_password_threshold_number", REQUIRED, LENGTH-FIXED }
    { 16, "attempt_count_reset_interval", REQUIRED, LENGTH-FIXED }
    { 16, "user_lockout_interval", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 3, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "get_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Get LAN Configuration Parameters (Set In Progress) Response
-----------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_set_in_progress_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Authentication Type Support) Response
-----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_authentication_type_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "none", REQUIRED, LENGTH-FIXED }
    { 1, "md2", REQUIRED, LENGTH-FIXED }
    { 1, "md5", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get LAN Configuration Parameters (Authentication Type Enables) Response
-----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_authentication_type_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "callback_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "callback_level.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "user_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "user_level.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "operator_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "operator_level.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "admin_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "admin_level.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.none", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.md2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.md5", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.straight_password", REQUIRED, LENGTH-FIXED }
    { 1, "oem_level.oem_proprietary", REQUIRED, LENGTH-FIXED }
    { 2, "oem_level.reserved2", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (IP Address) Response
------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_ip_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (IP Address Source) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_ip_address_source_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "ip_address_source", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (MAC Address) Response
-------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_mac_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Subnet Mask) Response
-------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_subnet_mask_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 32, "subnet_mask", REQUIRED, LENGTH-FIXED }


Get LAN Configuration Parameters (BMC Generated ARP Control) Response
---------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_bmc_generated_arp_control_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "bmc_generated_gratuitous_arps", REQUIRED, LENGTH-FIXED }
    { 1, "bmc_generated_arp_responses", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Gratuitous ARP Interval) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_gratuitous_arp_interval_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "gratuitous_arp_interval", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Default Gateway Address) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_default_gateway_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Default Gateway MAC Address) Response
-----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_default_gateway_mac_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Backup Gateway Address) Response
------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_backup_gateway_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 32, "ip_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Backup Gateway MAC Address) Response
----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_backup_gateway_mac_address_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 48, "mac_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Community String) Response
------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_community_string_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 144, "community_string", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Number of Destinations) Response
------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_number_of_destinations_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "number_of_lan_destinations", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Destination Type) Response
------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_destination_type_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 3, "destination_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "alert_acknowledge", REQUIRED, LENGTH-FIXED }
    { 8, "alert_acknowledge_timeout", REQUIRED, LENGTH-FIXED }
    { 3, "retries", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 4, "reserved4", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (Destination Addresses) Response
-----------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_destination_addresses_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "address_format", REQUIRED, LENGTH-FIXED }
    { 7, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "gateway_selector", REQUIRED, LENGTH-FIXED }
    { 32, "alerting_ip_address", REQUIRED, LENGTH-FIXED }
    { 48, "alerting_mac_address", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (VLAN ID) Response
---------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_vlan_id_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 12, "vlan_id", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "vlan_id_enable", REQUIRED, LENGTH-FIXED }

  Notes: Vlan ID LS byte first.

Get LAN Configuration Parameters (VLAN Priority) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_vlan_priority_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 3, "vlan_priority", REQUIRED, LENGTH-FIXED }
    { 2, "unspecified", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }

Get LAN Configuration Parameters (RMCP+ Messaging Cipher Suite Entry Support) Response
--------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_rmcpplus_messaging_cipher_suite_entry_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 5, "cipher_suite_entry_count", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get LAN Configuration Parameters (RMCP+ Messaging Cipher Suite Entries) Response
--------------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_rmcpplus_messaging_cipher_suite_entries_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_A", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_B", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_C", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_D", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_E", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_F", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_G", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_H", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_I", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_J", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_K", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_L", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_M", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_N", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_O", OPTIONAL, LENGTH-FIXED }
    { 8, "cipher_suite_id_entry_P", OPTIONAL, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get LAN Configuration Parameters (RMCP+ Messaging Cipher Suite Privilege Levels) Response
-----------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_rmcpplus_messaging_cipher_suite_privilege_levels_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_1", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_2", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_3", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_4", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_5", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_6", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_7", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_8", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_9", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_10", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_11", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_12", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_13", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_14", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_15", OPTIONAL, LENGTH-FIXED }
    { 4, "maximum_privilege_for_cipher_suite_16", OPTIONAL, LENGTH-FIXED }

Get LAN Configuration Parameters (Bad Password Threshold) Response
------------------------------------------------------------------

FIID Template: tmpl_cmd_get_lan_configuration_parameters_bad_password_threshold_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "user_disabled_event_message", REQUIRED, LENGTH-FIXED }
    { 7, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "bad_password_threshold_number", REQUIRED, LENGTH-FIXED }
    { 16, "attempt_count_reset_interval", REQUIRED, LENGTH-FIXED }
    { 16, "user_lockout_interval", REQUIRED, LENGTH-FIXED }

Suspend BMC ARPs Request
------------------------

FIID Template: tmpl_cmd_suspend_bmc_arps_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "gratuitous_arp_suspend", REQUIRED, LENGTH-FIXED }
    { 1, "arp_response_suspend", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Suspend BMC ARPs Response
-------------------------

FIID Template: tmpl_cmd_suspend_bmc_arps_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "gratuitous_arp_response_status", REQUIRED, LENGTH-FIXED }
    { 1, "arp_response_status", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Get IP UDP RMCP Statistics Request
----------------------------------

FIID Template: tmpl_cmd_get_ip_udp_rmcp_statistics_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "clear_all_statistics", REQUIRED, LENGTH-FIXED }
    { 7, "reserved2", REQUIRED, LENGTH-FIXED }

Get IP UDP RMCP Statistics Response
-----------------------------------

FIID Template: tmpl_cmd_get_ip_udp_rmcp_statistics_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "ip_packets_received", REQUIRED, LENGTH-FIXED }
    { 16, "received_ip_header_errors", REQUIRED, LENGTH-FIXED }
    { 16, "received_ip_address_errors", REQUIRED, LENGTH-FIXED }
    { 16, "fragmented_ip_packets_received", REQUIRED, LENGTH-FIXED }
    { 16, "ip_packets_transmitted", REQUIRED, LENGTH-FIXED }
    { 16, "udp_packets_received", REQUIRED, LENGTH-FIXED }
    { 16, "valid_rmcp_packets_received", REQUIRED, LENGTH-FIXED }
    { 16, "udp_proxy_packets_received", REQUIRED, LENGTH-FIXED }
    { 16, "udp_proxy_packets_dropped", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_LAN_CMDS_TEMPLATES_H */
