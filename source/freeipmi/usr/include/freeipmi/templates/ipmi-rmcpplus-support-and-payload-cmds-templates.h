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

#ifndef IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_TEMPLATES_H
#define IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_TEMPLATES_H

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

Activate Payload Request
------------------------

FIID Template: tmpl_cmd_activate_payload_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "payload_instance", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 32, "auxiliary_request_data", REQUIRED, LENGTH-FIXED }

Activate Payload (SOL) Request
------------------------------

FIID Template: tmpl_cmd_activate_payload_sol_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "payload_instance", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "sol_startup_handshake", REQUIRED, LENGTH-FIXED }
    { 2, "shared_serial_alert_behavior", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }
    { 1, "test_mode", REQUIRED, LENGTH-FIXED }
    { 1, "authentication_activation", REQUIRED, LENGTH-FIXED }
    { 1, "encryption_activation", REQUIRED, LENGTH-FIXED }
    { 24, "reserved5", REQUIRED, LENGTH-FIXED }

Activate Payload Response
-------------------------

FIID Template: tmpl_cmd_activate_payload_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "auxiliary_response_data", REQUIRED, LENGTH-FIXED }
    { 16, "inbound_payload_size", REQUIRED, LENGTH-FIXED }
    { 16, "outbound_payload_size", REQUIRED, LENGTH-FIXED }
    { 16, "payload_udp_port_number", REQUIRED, LENGTH-FIXED }
    { 16, "payload_vlan_number", REQUIRED, LENGTH-FIXED }

Activate Payload (SOL) Response
-------------------------------

FIID Template: tmpl_cmd_activate_payload_sol_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "test_mode", REQUIRED, LENGTH-FIXED }
    { 31, "reserved1", REQUIRED, LENGTH-FIXED }
    { 16, "inbound_payload_size", REQUIRED, LENGTH-FIXED }
    { 16, "outbound_payload_size", REQUIRED, LENGTH-FIXED }
    { 16, "payload_udp_port_number", REQUIRED, LENGTH-FIXED }
    { 16, "payload_vlan_number", REQUIRED, LENGTH-FIXED }

Deactivate Payload Request
--------------------------

FIID Template: tmpl_cmd_deactivate_payload_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "payload_instance", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 32, "payload_auxiliary_data", REQUIRED, LENGTH-FIXED }

Deactivate Payload Response
---------------------------

FIID Template: tmpl_cmd_deactivate_payload_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Suspend Resume Payload Encryption Request
-----------------------------------------

FIID Template: tmpl_cmd_suspend_resume_payload_encryption_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 2, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "payload_instance", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    /* achu: The IPMI spec says [4:0] for Operation and [7:2] for
       reserved3.  Needless to say, one is wrong.  Since there are
       only three operations, we'll assume they meant for operation to
       be a 2 bit field
    */
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 6, "reserved3", REQUIRED, LENGTH-FIXED }

Suspend Resume Payload Encryption Response
------------------------------------------

FIID Template: tmpl_cmd_suspend_resume_payload_encryption_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Payload Activation Status Request
-------------------------------------

FIID Template: tmpl_cmd_get_payload_activation_status_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "payload_type", REQUIRED, LENGTH-FIXED }

Get Payload Activation Status Response
--------------------------------------

FIID Template: tmpl_cmd_get_payload_activation_status_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "instance_capacity", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "instance_1", REQUIRED, LENGTH-FIXED }
    { 1, "instance_2", REQUIRED, LENGTH-FIXED }
    { 1, "instance_3", REQUIRED, LENGTH-FIXED }
    { 1, "instance_4", REQUIRED, LENGTH-FIXED }
    { 1, "instance_5", REQUIRED, LENGTH-FIXED }
    { 1, "instance_6", REQUIRED, LENGTH-FIXED }
    { 1, "instance_7", REQUIRED, LENGTH-FIXED }
    { 1, "instance_8", REQUIRED, LENGTH-FIXED }
    { 1, "instance_9", REQUIRED, LENGTH-FIXED }
    { 1, "instance_10", REQUIRED, LENGTH-FIXED }
    { 1, "instance_11", REQUIRED, LENGTH-FIXED }
    { 1, "instance_12", REQUIRED, LENGTH-FIXED }
    { 1, "instance_13", REQUIRED, LENGTH-FIXED }
    { 1, "instance_14", REQUIRED, LENGTH-FIXED }
    { 1, "instance_15", REQUIRED, LENGTH-FIXED }
    { 1, "instance_16", REQUIRED, LENGTH-FIXED }

Get Payload Instance Info Request
---------------------------------

FIID Template: tmpl_cmd_get_payload_instance_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "payload_type", REQUIRED, LENGTH-FIXED }
    { 8, "payload_instance", REQUIRED, LENGTH-FIXED }

Get Payload Instance Info Response
----------------------------------

FIID Template: tmpl_cmd_get_payload_instance_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 8, "port_number", REQUIRED, LENGTH-FIXED }
    { 56, "reserved", REQUIRED, LENGTH-FIXED }

Set User Payload Access Request
-------------------------------

FIID Template: tmpl_cmd_set_user_payload_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "operation", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_1", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_2", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_3", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_4", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_5", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_6", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_7", REQUIRED, LENGTH-FIXED }
    { 8, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_0", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_3", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_4", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_5", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_6", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_7", REQUIRED, LENGTH-FIXED }
    { 8, "reserved4", REQUIRED, LENGTH-FIXED }

Set User Payload Access Response
--------------------------------

FIID Template: tmpl_cmd_set_user_payload_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get User Payload Access Request
-------------------------------

FIID Template: tmpl_cmd_get_user_payload_access_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "user_id", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }

Get User Payload Access Response
--------------------------------

FIID Template: tmpl_cmd_get_user_payload_access_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_1", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_2", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_3", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_4", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_5", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_6", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_7", REQUIRED, LENGTH-FIXED }
    { 8, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_0", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_1", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_2", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_3", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_4", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_5", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_6", REQUIRED, LENGTH-FIXED }
    { 1, "oem_payload_7", REQUIRED, LENGTH-FIXED }
    { 8, "reserved3", REQUIRED, LENGTH-FIXED }

Get Channel Payload Support Request
-----------------------------------

FIID Template: tmpl_cmd_get_channel_payload_support_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }

Get Channel Payload Support Response
------------------------------------

FIID Template: tmpl_cmd_get_channel_payload_support_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "standard_payload_type_0_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_1_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_2_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_3_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_4_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_5_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_6_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_7_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_8_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_9_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_10_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_11_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_12_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_13_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_14_supported", REQUIRED, LENGTH-FIXED }
    { 1, "standard_payload_type_15_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_0_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_1_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_2_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_3_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_4_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_5_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_6_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_7_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_8_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_9_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_10_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_11_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_12_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_13_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_14_supported", REQUIRED, LENGTH-FIXED }
    { 1, "session_setup_payload_15_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_20h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_21h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_22h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_23h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_24h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_25h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_26h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_27h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_28h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_29h_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Ah_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Bh_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Ch_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Dh_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Eh_supported", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type_2Fh_supported", REQUIRED, LENGTH-FIXED }
    { 16, "reserved", REQUIRED, LENGTH-FIXED }

Get Channel Payload Version Request
-----------------------------------

FIID Template: tmpl_cmd_get_channel_payload_version_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "payload_type", REQUIRED, LENGTH-FIXED }

Get Channel Payload Version Response
------------------------------------

FIID Template: tmpl_cmd_get_channel_payload_version_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "minor_format_version", REQUIRED, LENGTH-FIXED }
    { 4, "major_format_version", REQUIRED, LENGTH-FIXED }

Get Channel OEM Payload Info Request
------------------------------------

FIID Template: tmpl_cmd_get_channel_oem_payload_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "payload_type", REQUIRED, LENGTH-FIXED }
    { 24, "oem_iana", REQUIRED, LENGTH-FIXED }
    { 16, "oem_payload_id", REQUIRED, LENGTH-FIXED }

Get Channel OEM Payload Info Response
-------------------------------------

FIID Template: tmpl_cmd_get_channel_oem_payload_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "payload_type", REQUIRED, LENGTH-FIXED }
    { 24, "oem_iana", REQUIRED, LENGTH-FIXED }
    { 16, "oem_payload_id", REQUIRED, LENGTH-FIXED }
    { 4, "minor_format_version", REQUIRED, LENGTH-FIXED }
    { 4, "major_format_version", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_TEMPLATES_H */
