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

#ifndef IPMI_SERIAL_MODEM_CMDS_TEMPLATES_H
#define IPMI_SERIAL_MODEM_CMDS_TEMPLATES_H

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

Set Serial Modem Configuration Request
--------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Set Serial Modem Configuration Response
---------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set Serial Modem Configuration (Set In Progress) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_set_in_progress_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved2", REQUIRED, LENGTH-FIXED }

Set Serial Modem Configuration (Connection Mode) Request
--------------------------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_connection_mode_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 1, "basic_mode", REQUIRED, LENGTH-FIXED }
    { 1, "ppp_mode", REQUIRED, LENGTH-FIXED }
    { 1, "terminal_mode", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "connect_mode", REQUIRED, LENGTH-FIXED }

Set Serial Modem Configuration (IPMI Messaging Comm Settings) Request
---------------------------------------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_ipmi_messaging_comm_settings_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 5, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "dtr_hangup", REQUIRED, LENGTH-FIXED }
    { 2, "flow_control", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved3", REQUIRED, LENGTH-FIXED }

Set Serial Modem Configuration (Page Blackout Interval) Request
---------------------------------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_page_blackout_interval_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "page_blackout_interval", REQUIRED, LENGTH-FIXED }

Set Serial Modem Configuration (Call Retry Interval) Request
------------------------------------------------------------

FIID Template: tmpl_cmd_set_serial_modem_configuration_call_retry_interval_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "call_retry_interval", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration Request
--------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "get_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "block_selector", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration Response
---------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

Get Serial Modem Configuration (Set In Progress) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_set_in_progress_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 2, "state", REQUIRED, LENGTH-FIXED }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration (Connection Mode) Response
---------------------------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_connection_mode_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 1, "basic_mode", REQUIRED, LENGTH-FIXED }
    { 1, "ppp_mode", REQUIRED, LENGTH-FIXED }
    { 1, "terminal_mode", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "connect_mode", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration (IPMI Messaging Comm Settings) Response
----------------------------------------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_ipmi_messaging_comm_settings_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "dtr_hangup", REQUIRED, LENGTH-FIXED }
    { 2, "flow_control", REQUIRED, LENGTH-FIXED }
    { 4, "bit_rate", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration (Page Blackout Interval) Response
----------------------------------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_page_blackout_interval_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "page_blackout_interval", REQUIRED, LENGTH-FIXED }

Get Serial Modem Configuration (Call Retry Interval) Response
-------------------------------------------------------------

FIID Template: tmpl_cmd_get_serial_modem_configuration_call_retry_interval_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "present_revision", REQUIRED, LENGTH-FIXED }
    { 4, "oldest_revision_parameter", REQUIRED, LENGTH-FIXED }
    { 8, "call_retry_interval", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SERIAL_MODEM_CMDS_TEMPLATES_H */
