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

#ifndef IPMI_SOL_PAYLOAD_TEMPLATES_H
#define IPMI_SOL_PAYLOAD_TEMPLATES_H

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

SOL Payload Data
----------------

FIID Template: tmpl_sol_payload_data

    { 4, "packet_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "packet_ack_nack_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "accepted_character_count", REQUIRED, LENGTH-FIXED }
    { 8, "operation_status", REQUIRED, LENGTH-FIXED }
    { 524288, "character_data", OPTIONAL, LENGTH-VARIABLE }

SOL Payload Data Remote Console to BMC
--------------------------------------

FIID Template: tmpl_sol_payload_data_remote_console_to_bmc

    { 4, "packet_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "packet_ack_nack_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "accepted_character_count", REQUIRED, LENGTH-FIXED }
    { 1, "flush_outbound", REQUIRED, LENGTH-FIXED }
    { 1, "flush_inbound", REQUIRED, LENGTH-FIXED }
    { 1, "drop_dcd_dsr", REQUIRED, LENGTH-FIXED }
    { 1, "cts_pause", REQUIRED, LENGTH-FIXED }
    { 1, "generate_break", REQUIRED, LENGTH-FIXED }
    { 1, "ring_wor", REQUIRED, LENGTH-FIXED }
    { 1, "nack", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 524288, "character_data", OPTIONAL, LENGTH-VARIABLE }

SOL Payload Data BMC to Remote Console
--------------------------------------

FIID Template: tmpl_sol_payload_data_bmc_to_remote_console

    { 4, "packet_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "packet_ack_nack_sequence_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "accepted_character_count", REQUIRED, LENGTH-FIXED }
    { 2, "reserved3", REQUIRED, LENGTH-FIXED }
    { 1, "break_condition", REQUIRED, LENGTH-FIXED }
    { 1, "transmit_overrun", REQUIRED, LENGTH-FIXED }
    { 1, "sol_deactivating", REQUIRED, LENGTH-FIXED }
    { 1, "character_transfer_unavailable", REQUIRED, LENGTH-FIXED }
    { 1, "nack", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }
    { 524288, "character_data", OPTIONAL, LENGTH-VARIABLE }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_CMDS_TEMPLATES_H */
