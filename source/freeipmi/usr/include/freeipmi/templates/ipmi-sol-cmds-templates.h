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

#ifndef IPMI_SOL_CMDS_TEMPLATES_H
#define IPMI_SOL_CMDS_TEMPLATES_H

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

Set SOL Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Set SOL Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set SOL Configuration Parameters (Set In Progress) Request
----------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Enable) Request
-----------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_enable_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "sol_enable", REQUIRED, LENGTH-FIXED }
    { 7, "reserved2", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Authentication) Request
--------------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_authentication_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "sol_privilege_level", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "force_sol_payload_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "force_sol_payload_encryption", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (Character Accumulate Interval and Send Threshold) Request
-------------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_character_accumulate_interval_and_send_threshold_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "character_accumulate_interval", REQUIRED, LENGTH-FIXED }
    { 8, "character_send_threshold", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Retry) Request
----------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_retry_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 3, "retry_count", REQUIRED, LENGTH-FIXED }
    { 5, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "retry_interval", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Non-Volatile Bit Rate) Request
--------------------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_non_volatile_bit_rate_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Volatile Bit Rate) Request
----------------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_volatile_bit_rate_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Set SOL Configuration Parameters (SOL Payload Port Number) Request
------------------------------------------------------------------

FIID Template: tmpl_cmd_set_sol_configuration_parameters_sol_payload_port_number_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 16, "port_number", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters Request
----------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "get_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters Response
-----------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Get SOL Configuration Parameters (Set In Progress) Response
-----------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_set_in_progress_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Enable) Response
------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_enable_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "sol_enable", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Authentication) Response
--------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_authentication_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "sol_privilege_level", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "force_sol_payload_authentication", REQUIRED, LENGTH-FIXED }
    { 1, "force_sol_payload_encryption", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (Character Accumulate Interval and Send Threshold) Response
--------------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_character_accumulate_interval_and_send_threshold_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "character_accumulate_interval", REQUIRED, LENGTH-FIXED }
    { 8, "character_send_threshold", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Retry) Response
-----------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_retry_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 3, "retry_count", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "retry_interval", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Non-Volatile Bit Rate) Response
---------------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_non_volatile_bit_rate_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Volatile Bit Rate) Response
-----------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_volatile_bit_rate_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get SOL Configuration Parameters (SOL Payload Channel) Response
---------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_payload_channel_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "payload_channel", REQUIRED, LENGTH-FIXED }

  Notes: Read only field, no "set" equivalent.

Get SOL Configuration Parameters (SOL Payload Port Number) Response
-------------------------------------------------------------------

FIID Template: tmpl_cmd_get_sol_configuration_parameters_sol_payload_port_number_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 16, "port_number", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_CMDS_TEMPLATES_H */
