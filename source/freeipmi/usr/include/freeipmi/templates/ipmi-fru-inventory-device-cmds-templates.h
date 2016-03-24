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

#ifndef IPMI_FRU_INVENTORY_DEVICE_CMDS_TEMPLATES_H
#define IPMI_FRU_INVENTORY_DEVICE_CMDS_TEMPLATES_H

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

Get FRU Inventory Area Info Request
-----------------------------------

FIID Template: tmpl_cmd_get_fru_inventory_area_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "fru_device_id", REQUIRED, LENGTH-FIXED }

Get FRU Inventory Area Info Response
------------------------------------

FIID Template: tmpl_cmd_get_fru_inventory_area_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "fru_inventory_area_size", REQUIRED, LENGTH-FIXED }
    { 1, "device_is_accessed", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }

Read FRU Data Request
---------------------

FIID Template: tmpl_cmd_read_fru_data_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "fru_device_id", REQUIRED, LENGTH-FIXED }
    { 16, "fru_inventory_offset_to_read", REQUIRED, LENGTH-FIXED }
    { 8, "count_to_read", REQUIRED, LENGTH-FIXED }

Read FRU Data Response
----------------------

FIID Template: tmpl_cmd_read_fru_data_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "count_returned", REQUIRED, LENGTH-FIXED }
    { 2040, "requested_data", OPTIONAL, LENGTH-VARIABLE }

Write FRU Data Request
----------------------

FIID Template: tmpl_cmd_write_fru_data_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "fru_device_id", REQUIRED, LENGTH-FIXED }
    { 16, "fru_inventory_offset_to_write", REQUIRED, LENGTH-FIXED }
    { 2040, "data_to_write", REQUIRED, LENGTH-VARIABLE }

Write FRU Data Response
-----------------------

FIID Template: tmpl_cmd_write_fru_data_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "count_written", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_INVENTORY_DEVICE_CMDS_TEMPLATES_H */
