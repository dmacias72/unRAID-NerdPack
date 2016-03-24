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

#ifndef IPMI_EVENT_CMDS_TEMPLATES_H
#define IPMI_EVENT_CMDS_TEMPLATES_H

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

Set Event Receiver Request
--------------------------

FIID Template: tmpl_cmd_set_event_receiver_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "event_receiver_slave_address", REQUIRED, LENGTH-FIXED }
    { 2, "event_receiver_lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Set Event Receiver Response
---------------------------

FIID Template: tmpl_cmd_set_event_receiver_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Event Receiver Request
--------------------------

FIID Template: tmpl_cmd_get_event_receiver_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Event Receiver Response
---------------------------

FIID Template: tmpl_cmd_get_event_receiver_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "event_receiver_slave_address", REQUIRED, LENGTH-FIXED }
    { 2, "event_receiver_lun", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Platform Event Request
----------------------

FIID Template: tmpl_cmd_platform_event_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "generator_id", OPTIONAL, LENGTH-FIXED }
    { 8, "event_message_format_version", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 7, "event_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "event_dir", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Platform Event Response
-----------------------

FIID Template: tmpl_cmd_platform_event_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_CMDS_TEMPLATES_H */
