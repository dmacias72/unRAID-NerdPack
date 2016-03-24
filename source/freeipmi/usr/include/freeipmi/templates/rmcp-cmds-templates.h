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

#ifndef RMCP_CMDS_TEMPLATES_H
#define RMCP_CMDS_TEMPLATES_H

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

ASF Presence Ping
-----------------

FIID Template: tmpl_cmd_asf_presence_ping

    { 32, "iana_enterprise_number", REQUIRED, LENGTH-FIXED }
    { 8, "message_type", REQUIRED, LENGTH-FIXED }
    { 8, "message_tag", REQUIRED, LENGTH-FIXED }
    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "data_length", REQUIRED, LENGTH-FIXED }

ASF Presence Pong
-----------------

FIID Template: tmpl_cmd_asf_presence_pong

    { 32, "iana_enterprise_number", REQUIRED, LENGTH-FIXED }
    { 8, "message_type", REQUIRED, LENGTH-FIXED }
    { 8, "message_tag", REQUIRED, LENGTH-FIXED }
    { 8, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "data_length", REQUIRED, LENGTH-FIXED }
    { 32, "oem_iana_enterprise_number", REQUIRED, LENGTH-FIXED }
    { 32, "oem_defined", REQUIRED, LENGTH-FIXED }
    { 4, "supported_entities.version", REQUIRED, LENGTH-FIXED }
    { 3, "supported_entities.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "supported_entities.ipmi_supported", REQUIRED, LENGTH-FIXED }
    { 7, "supported_interactions.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "supported_interactions.security_extensions", REQUIRED, LENGTH-FIXED }
    { 48, "reserved2", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* RMCP_CMDS_TEMPLATES_H */
