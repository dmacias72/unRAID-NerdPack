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

#ifndef IPMI_BMC_WATCHDOG_TIMER_CMDS_TEMPLATES_H
#define IPMI_BMC_WATCHDOG_TIMER_CMDS_TEMPLATES_H

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

Reset Watchdog Timer Request
----------------------------

FIID Template: tmpl_cmd_reset_watchdog_timer_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Reset Watchdog Timer Response
-----------------------------

FIID Template: tmpl_cmd_reset_watchdog_timer_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set Watchdog Timer Request
--------------------------

FIID Template: tmpl_cmd_set_watchdog_timer_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 3, "timer_use", REQUIRED, LENGTH-FIXED }
    { 3, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "stop_timer", REQUIRED, LENGTH-FIXED }
    { 1, "log", REQUIRED, LENGTH-FIXED }
    { 3, "timeout_action", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 3, "pre_timeout_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "pre_timeout_interval", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.bios_frb2", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.bios_post", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.os_load", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.sms_os", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.oem", REQUIRED, LENGTH-FIXED }
    { 1, "reserved5", REQUIRED, LENGTH-FIXED }
    { 1, "reserved6", REQUIRED, LENGTH-FIXED }
    { 16, "initial_countdown_value", REQUIRED, LENGTH-FIXED }

Set Watchdog Timer Response
---------------------------

FIID Template: tmpl_cmd_set_watchdog_timer_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Watchdog Timer Request
--------------------------

FIID Template: tmpl_cmd_get_watchdog_timer_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Watchdog Timer Response
---------------------------

FIID Template: tmpl_cmd_get_watchdog_timer_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 3, "timer_use", REQUIRED, LENGTH-FIXED }
    { 3, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "timer_state", REQUIRED, LENGTH-FIXED }
    { 1, "log", REQUIRED, LENGTH-FIXED }
    { 3, "timeout_action", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 3, "pre_timeout_interrupt", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }
    { 8, "pre_timeout_interval", REQUIRED, LENGTH-FIXED }
    { 1, "reserved4", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.bios_frb2", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.bios_post", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.os_load", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.sms_os", REQUIRED, LENGTH-FIXED }
    { 1, "timer_use_expiration_flag.oem", REQUIRED, LENGTH-FIXED }
    { 1, "reserved5", REQUIRED, LENGTH-FIXED }
    { 1, "reserved6", REQUIRED, LENGTH-FIXED }
    { 16, "initial_countdown_value", REQUIRED, LENGTH-FIXED }
    { 16, "present_countdown_value", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_BMC_WATCHDOG_TIMER_CMDS_TEMPLATES_H */
