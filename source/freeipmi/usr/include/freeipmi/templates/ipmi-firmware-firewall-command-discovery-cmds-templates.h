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

#ifndef IPMI_FIRMWARE_FIRMWARE_COMMAND_DISCOVERY_CMDS_TEMPLATES_H
#define IPMI_FIRMWARE_FIRMWARE_COMMAND_DISCOVERY_CMDS_TEMPLATES_H

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

Get NetFN Support Request
-------------------------

FIID Template: tmpl_cmd_get_netfn_support_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get NetFN Support Response
--------------------------

FIID Template: tmpl_cmd_get_netfn_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 2, "lun0", REQUIRED, LENGTH-FIXED }
    { 2, "lun1", REQUIRED, LENGTH-FIXED }
    { 2, "lun2", REQUIRED, LENGTH-FIXED }
    { 2, "lun3", REQUIRED, LENGTH-FIXED }
    { 32, "lun0_netfn_support_bitmask", REQUIRED, LENGTH-FIXED }
    { 32, "lun1_netfn_support_bitmask", REQUIRED, LENGTH-FIXED }
    { 32, "lun2_netfn_support_bitmask", REQUIRED, LENGTH-FIXED }
    { 32, "lun3_netfn_support_bitmask", REQUIRED, LENGTH-FIXED }

Get Command Support Request
---------------------------

FIID Template: tmpl_cmd_get_command_support_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Command Support Response
----------------------------

FIID Template: tmpl_cmd_get_command_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "command_support_mask", REQUIRED, LENGTH-FIXED }

Get Command Sub-Function Support Request
----------------------------------------

FIID Template: tmpl_cmd_get_command_sub_function_support_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Command Sub-Function Support (Specification Errata) Response
----------------------------------------------------------------

FIID Template: tmpl_cmd_get_command_sub_function_support_specification_errata_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "errata_version", REQUIRED, LENGTH-FIXED }
    { 4, "specification_type", REQUIRED, LENGTH-FIXED }
    { 8, "specification_version", REQUIRED, LENGTH-FIXED }
    { 8, "specification_revision", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_support_mask", REQUIRED, LENGTH-FIXED }

Get Command Sub-Function Support (Extension Errata) Response
------------------------------------------------------------

FIID Template: tmpl_cmd_get_command_sub_function_support_extension_errata_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "oem_group_defining_body_errata", REQUIRED, LENGTH-FIXED }
    { 8, "specification_version", REQUIRED, LENGTH-FIXED }
    { 8, "specification_revision", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_support_mask", REQUIRED, LENGTH-FIXED }

Get Configurable Commands Request
---------------------------------

FIID Template: tmpl_cmd_get_configurable_commands_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Configurable Commands Response
----------------------------------

FIID Template: tmpl_cmd_get_configurable_commands_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "command_support_mask", REQUIRED, LENGTH-FIXED }

Get Configurable Command Sub-Functions Request
----------------------------------------------

FIID Template: tmpl_cmd_get_configurable_command_sub_functions_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Configurable Command Sub-Functions Response
-----------------------------------------------

FIID Template: tmpl_cmd_get_configurable_command_sub_functions_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "sub_function_enables1", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables2", OPTIONAL, LENGTH-FIXED }

Set Command Enables Request
---------------------------

FIID Template: tmpl_cmd_set_command_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 128, "enable_disable_mask", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Set Command Enables Response
----------------------------

FIID Template: tmpl_cmd_set_command_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Command Enables Request
---------------------------

FIID Template: tmpl_cmd_get_command_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Command Enables Response
----------------------------

FIID Template: tmpl_cmd_get_command_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "enable_disable_mask", REQUIRED, LENGTH-FIXED }

Set Command Sub-Function Enables Request
----------------------------------------

FIID Template: tmpl_cmd_set_command_sub_function_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables1", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables2", OPTIONAL, LENGTH-FIXED }

Set Command Sub-Function Enables (Defining Body Code) Request
-------------------------------------------------------------

FIID Template: tmpl_cmd_set_command_sub_function_enables_defining_body_code_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 8, "defining_body_code", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables1", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables2", OPTIONAL, LENGTH-FIXED }


Set Command Sub-Function Enables (OEM IANA) Request
---------------------------------------------------

FIID Template: tmpl_cmd_set_command_sub_function_enables_oem_iana_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 24, "oem_iana", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables1", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables2", OPTIONAL, LENGTH-FIXED }


Set Command Sub-Function Enables Response
-----------------------------------------

FIID Template: tmpl_cmd_set_command_sub_function_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Command Sub-Function Enables Request
----------------------------------------

FIID Template: tmpl_cmd_get_command_sub_function_enables_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 2, "lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "command", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }

Get Command Sub-Function Enables Response
-----------------------------------------

FIID Template: tmpl_cmd_get_command_sub_function_enables_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "sub_function_enables1", REQUIRED, LENGTH-FIXED }
    { 32, "sub_function_enables2", OPTIONAL, LENGTH-FIXED }

Get OEM NetFN IANA Support Request
----------------------------------

FIID Template: tmpl_cmd_get_oem_netfn_iana_support_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "net_fn", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 6, "list_index", REQUIRED, LENGTH-FIXED }
    { 2, "reserved3", REQUIRED, LENGTH-FIXED }

Get OEM NetFN IANA Support Response
-----------------------------------

FIID Template: tmpl_cmd_get_oem_netfn_iana_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 7, "last_iana", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 2, "lun0", REQUIRED, LENGTH-FIXED }
    { 2, "lun1", REQUIRED, LENGTH-FIXED }
    { 2, "lun2", REQUIRED, LENGTH-FIXED }
    { 2, "lun3", REQUIRED, LENGTH-FIXED }
    { 24, "net_fn_data", OPTIONAL, LENGTH-VARIABLE }


#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_CMDS_TEMPLATES_H */
