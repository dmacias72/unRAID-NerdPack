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

#ifndef IPMI_SDR_REPOSITORY_CMDS_TEMPLATES_H
#define IPMI_SDR_REPOSITORY_CMDS_TEMPLATES_H

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

Get SDR Repository Info Request
-------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get SDR Repository Info Response
--------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 16, "record_count", REQUIRED, LENGTH-FIXED }
    { 16, "free_space", REQUIRED, LENGTH-FIXED }
    { 32, "most_recent_addition_timestamp", REQUIRED, LENGTH-FIXED }
    { 32, "most_recent_erase_timestamp", REQUIRED, LENGTH-FIXED }
    { 1, "get_sdr_repository_allocation_info_command_supported", REQUIRED, LENGTH-FIXED }
    { 1, "reserve_sdr_repository_command_supported", REQUIRED, LENGTH-FIXED }
    { 1, "partial_add_sdr_command_supported", REQUIRED, LENGTH-FIXED }
    { 1, "delete_sdr_command_supported", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 2, "modal_non_modal_sdr_repository_update_operation_supported", REQUIRED, LENGTH-FIXED }
    { 1, "overflow_flag", REQUIRED, LENGTH-FIXED }

Get SDR Repository Allocation Info Request
------------------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_allocation_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get SDR Repository Allocation Info Response
-------------------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_allocation_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "number_of_possible_allocation_units", REQUIRED, LENGTH-FIXED }
    { 16, "allocation_unit_size", REQUIRED, LENGTH-FIXED }
    { 16, "number_of_free_allocation_units", REQUIRED, LENGTH-FIXED }
    { 16, "largest_free_block", REQUIRED, LENGTH-FIXED }
    { 8, "maximum_record_size", REQUIRED, LENGTH-FIXED }

Reserve SDR Repository Request
------------------------------

FIID Template: tmpl_cmd_reserve_sdr_repository_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Reserve SDR Repository Response
-------------------------------

FIID Template: tmpl_cmd_reserve_sdr_repository_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "reservation_id", REQUIRED, LENGTH-FIXED }

Get SDR Request
---------------

FIID Template: tmpl_cmd_get_sdr_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 16, "reservation_id", REQUIRED, LENGTH-FIXED }
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "offset_into_record", REQUIRED, LENGTH-FIXED }
    { 8, "bytes_to_read", REQUIRED, LENGTH-FIXED }

Get SDR Response
----------------

FIID Template: tmpl_cmd_get_sdr_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "next_record_id", REQUIRED, LENGTH-FIXED }
    /* 2040 = 255 * 8, 255 b/c bytes_to_read field in request is 1 byte long */
    { 2040, "record_data", REQUIRED, LENGTH-VARIABLE }

Get SDR Repository Time Request
-------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_time_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get SDR Repository Time Response
--------------------------------

FIID Template: tmpl_cmd_get_sdr_repository_time_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 32, "time", REQUIRED, LENGTH-FIXED }

Set SDR Repository Time Request
-------------------------------

FIID Template: tmpl_cmd_set_sdr_repository_time_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 32, "time", REQUIRED, LENGTH-FIXED }

Set SDR Repository Time Response
--------------------------------

FIID Template: tmpl_cmd_set_sdr_repository_time_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_REPOSITORY_CMDS_TEMPLATES_H */
