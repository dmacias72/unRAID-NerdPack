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

#ifndef IPMI_DEVICE_GLOBAL_CMDS_TEMPLATES_H
#define IPMI_DEVICE_GLOBAL_CMDS_TEMPLATES_H

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

Get Device ID Request
---------------------

FIID Template: tmpl_cmd_get_device_id_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Device ID Response
----------------------

FIID Template: tmpl_cmd_get_device_id_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "device_id", REQUIRED, LENGTH-FIXED }
    { 4, "device_revision.revision", REQUIRED, LENGTH-FIXED }
    { 3, "device_revision.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "device_revision.sdr_support", REQUIRED, LENGTH-FIXED }
    { 7, "firmware_revision1.major_revision", REQUIRED, LENGTH-FIXED }
    { 1, "firmware_revision1.device_available", REQUIRED, LENGTH-FIXED }
    { 8, "firmware_revision2.minor_revision", REQUIRED, LENGTH-FIXED }
    { 4, "ipmi_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "ipmi_version_minor", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.sensor_device", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.sdr_repository_device", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.sel_device", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.fru_inventory_device", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.ipmb_event_receiver", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.ipmb_event_generator", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.bridge", REQUIRED, LENGTH-FIXED }
    { 1, "additional_device_support.chassis_device", REQUIRED, LENGTH-FIXED }
    { 20, "manufacturer_id.id", REQUIRED, LENGTH-FIXED }
    { 4, "manufacturer_id.reserved1", REQUIRED, LENGTH-FIXED }
    { 16, "product_id", REQUIRED, LENGTH-FIXED }
    { 32, "auxiliary_firmware_revision_information", OPTIONAL, LENGTH-FIXED }

Cold Reset Request
------------------

FIID Template: tmpl_cmd_cold_reset_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Cold Reset Response
-------------------

FIID Template: tmpl_cmd_cold_reset_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Warm Reset Request
------------------

FIID Template: tmpl_cmd_warm_reset_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Warm Reset Response
-------------------

FIID Template: tmpl_cmd_warm_reset_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Set ACPI Power State Request
----------------------------

FIID Template: tmpl_cmd_set_acpi_power_state_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 7, "system_power_state_enumeration", REQUIRED, LENGTH-FIXED }
    { 1, "set_system_power_state", REQUIRED, LENGTH-FIXED }
    { 7, "device_power_state_enumeration", REQUIRED, LENGTH-FIXED }
    { 1, "set_device_power_state", REQUIRED, LENGTH-FIXED }

Set ACPI Power State Response
-----------------------------

FIID Template: tmpl_cmd_set_acpi_power_state_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get ACPI Power State Request
----------------------------

FIID Template: tmpl_cmd_get_acpi_power_state_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get ACPI Power State Response
-----------------------------

FIID Template: tmpl_cmd_get_acpi_power_state_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 7, "system_power_state_enumeration", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 7, "device_power_state_enumeration", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }

Get Self Test Results Request
-----------------------------

FIID Template: tmpl_cmd_get_self_test_results_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Self Test Results Response
------------------------------

FIID Template: tmpl_cmd_get_self_test_results_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "self_test_result", REQUIRED, LENGTH-FIXED }
    { 1, "controller_operation_firmware_corrupted", REQUIRED, LENGTH-FIXED }
    { 1, "controller_update_boot_block_firmware_corrupted", REQUIRED, LENGTH-FIXED }
    { 1, "internal_use_area_of_bmc_fru_corrupted", REQUIRED, LENGTH-FIXED }
    { 1, "sdr_repository_empty", REQUIRED, LENGTH-FIXED }
    { 1, "ipmb_signal_lines_do_not_respond", REQUIRED, LENGTH-FIXED }
    { 1, "cannot_access_bmc_fru_device", REQUIRED, LENGTH-FIXED }
    { 1, "cannot_access_sdr_repository", REQUIRED, LENGTH-FIXED }
    { 1, "cannot_access_sel_device", REQUIRED, LENGTH-FIXED }

Get Device GUID Request
-----------------------

FIID Template: tmpl_cmd_get_device_guid_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }

Get Device GUID Response
------------------------

FIID Template: tmpl_cmd_get_device_guid_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 128, "guid", REQUIRED, LENGTH-FIXED }

Get Device GUID (with Format) Response
--------------------------------------

FIID Template: tmpl_cmd_get_device_guid_format_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 48, "node", REQUIRED, LENGTH-FIXED }
    { 8, "clock_seq_low", REQUIRED, LENGTH-FIXED }
    { 8, "clock_seq_hi_and_reserved", REQUIRED, LENGTH-FIXED }
    { 16, "time_high_and_version", REQUIRED, LENGTH-FIXED }
    { 16, "time_mid", REQUIRED, LENGTH-FIXED }
    { 32, "time_low", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DEVICE_GLOBAL_CMDS_TEMPLATES_H */
