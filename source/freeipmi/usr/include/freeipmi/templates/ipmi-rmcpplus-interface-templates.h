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

#ifndef IPMI_RMCPPLUS_INTERFACE_TEMPLATES_H
#define IPMI_RMCPPLUS_INTERFACE_TEMPLATES_H

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

RMCP+ Session Header
--------------------

FIID Template: tmpl_rmcpplus_session_hdr

    { 4, "authentication_type", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 6, "payload_type", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type.authenticated", REQUIRED, LENGTH-FIXED }
    { 1, "payload_type.encrypted", REQUIRED, LENGTH-FIXED }
    { 24, "oem_iana", OPTIONAL, LENGTH-FIXED }
    { 8, "reserved2", OPTIONAL, LENGTH-FIXED }
    { 16, "oem_payload_id", OPTIONAL, LENGTH-FIXED }
    { 32, "session_id", REQUIRED, LENGTH-FIXED }
    { 32, "session_sequence_number", REQUIRED, LENGTH-FIXED }
    { 16, "ipmi_payload_len", REQUIRED, LENGTH-FIXED }

RMCP+ Session Trailer
---------------------

FIID Template: tmpl_rmcpplus_session_trlr

    { 32, "integrity_pad", OPTIONAL, LENGTH-VARIABLE }
    { 8, "pad_length", REQUIRED, LENGTH-FIXED }
    { 8, "next_header", REQUIRED, LENGTH-FIXED }
    { 256, "authentication_code", OPTIONAL, LENGTH-VARIABLE }

RMCP+ Payload
-------------

FIID Template: tmpl_rmcpplus_payload

    { 512, "confidentiality_header", OPTIONAL, LENGTH-VARIABLE }
    { 524288, "payload_data", REQUIRED, LENGTH-VARIABLE }
    { 512, "confidentiality_trailer", OPTIONAL, LENGTH-VARIABLE }

RMCP+ Open Session Request
--------------------------

FIID Template: tmpl_rmcpplus_open_session_request

    { 8, "message_tag", REQUIRED, LENGTH-FIXED }
    { 4, "requested_maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 16, "reserved2", REQUIRED, LENGTH-FIXED }
    { 32, "remote_console_session_id", REQUIRED, LENGTH-FIXED }
    { 8, "authentication_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "authentication_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "authentication_payload.authentication_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved4", REQUIRED, LENGTH-FIXED }
    { 24, "reserved5", REQUIRED, LENGTH-FIXED }
    { 8, "integrity_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved6", REQUIRED, LENGTH-FIXED }
    { 8, "integrity_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "integrity_payload.integrity_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved7", REQUIRED, LENGTH-FIXED }
    { 24, "reserved8", REQUIRED, LENGTH-FIXED }
    { 8, "confidentiality_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved9", REQUIRED, LENGTH-FIXED }
    { 8, "confidentiality_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "confidentiality_payload.confidentiality_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved10", REQUIRED, LENGTH-FIXED }
    { 24, "reserved11", REQUIRED, LENGTH-FIXED }

RMCP+ Open Session Response
---------------------------

FIID Template: tmpl_rmcpplus_open_session_response

    { 8, "message_tag", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "rmcpplus_status_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "reserved2", REQUIRED, LENGTH-FIXED }
    { 32, "remote_console_session_id", REQUIRED, LENGTH-FIXED }
    { 32, "managed_system_session_id", REQUIRED, LENGTH-FIXED }
    { 8, "authentication_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "authentication_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "authentication_payload.authentication_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved4", REQUIRED, LENGTH-FIXED }
    { 24, "reserved5", REQUIRED, LENGTH-FIXED }
    { 8, "integrity_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved6", REQUIRED, LENGTH-FIXED }
    { 8, "integrity_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "integrity_payload.integrity_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved7", REQUIRED, LENGTH-FIXED }
    { 24, "reserved8", REQUIRED, LENGTH-FIXED }
    { 8, "confidentiality_payload.payload_type", REQUIRED, LENGTH-FIXED }
    { 16, "reserved9", REQUIRED, LENGTH-FIXED }
    { 8, "confidentiality_payload.payload_length", REQUIRED, LENGTH-FIXED }
    { 6, "confidentiality_payload.confidentiality_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "reserved10", REQUIRED, LENGTH-FIXED }
    { 24, "reserved11", REQUIRED, LENGTH-FIXED }

RMCP+ RAKP Message 1
--------------------

FIID Template: tmpl_rmcpplus_rakp_message_1

    { 8, "message_tag", REQUIRED, LENGTH-FIXED }
    { 24, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "managed_system_session_id", REQUIRED, LENGTH-FIXED }
    { 128, "remote_console_random_number", REQUIRED, LENGTH-FIXED }
    { 4, "requested_maximum_privilege_level", REQUIRED, LENGTH-FIXED }
    { 1, "name_only_lookup", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }
    { 16, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "user_name_length", REQUIRED, LENGTH-FIXED }
    { 128, "user_name", OPTIONAL, LENGTH-VARIABLE }

RMCP+ RAKP Message 2
--------------------

FIID Template: tmpl_rmcpplus_rakp_message_2

    { 8, "message_tag", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "rmcpplus_status_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "remote_console_session_id", REQUIRED, LENGTH-FIXED }
    { 128, "managed_system_random_number", REQUIRED, LENGTH-FIXED }
    { 128, "managed_system_guid", REQUIRED, LENGTH-FIXED }
    { 512, "key_exchange_authentication_code", OPTIONAL, LENGTH-VARIABLE }

RMCP+ RAKP Message 3
--------------------

FIID Template: tmpl_rmcpplus_rakp_message_3

    { 8, "message_tag", REQUIRED, LENGTH-FIXED }
    { 8, "rmcpplus_status_code", REQUIRED, LENGTH-FIXED }
    { 16, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "managed_system_session_id", REQUIRED, LENGTH-FIXED }
    { 512, "key_exchange_authentication_code", OPTIONAL, LENGTH-VARIABLE }

RMCP+ RAKP Message 4
--------------------

FIID Template: tmpl_rmcpplus_rakp_message_4

    { 8, "message_tag", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "rmcpplus_status_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "reserved1", REQUIRED, LENGTH-FIXED }
    { 32, "remote_console_session_id", REQUIRED, LENGTH-FIXED }
    { 512, "integrity_check_value", OPTIONAL, LENGTH-VARIABLE }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_RMCPPLUS_INTERFACE_TEMPLATES_H */
