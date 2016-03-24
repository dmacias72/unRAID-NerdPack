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

#ifndef IPMI_FRU_INFORMATION_RECORD_FORMAT_TEMPLATES_H
#define IPMI_FRU_INFORMATION_RECORD_FORMAT_TEMPLATES_H

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

FRU Common Header
-----------------

FIID Template: tmpl_fru_common_header

    { 4, "format_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "internal_use_area_starting_offset", REQUIRED, LENGTH-FIXED }
    { 8, "chassis_info_area_starting_offset", REQUIRED, LENGTH-FIXED }
    { 8, "board_info_area_starting_offset", REQUIRED, LENGTH-FIXED }
    { 8, "product_info_area_starting_offset", REQUIRED, LENGTH-FIXED }
    { 8, "multirecord_area_starting_offset", REQUIRED, LENGTH-FIXED }
    { 8, "pad", REQUIRED, LENGTH-FIXED }
    { 8, "checksum", REQUIRED, LENGTH-FIXED }

FRU Info Area Header
--------------------

FIID Template: tmpl_fru_info_area_header

    { 4, "format_version", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "info_area_length", REQUIRED, LENGTH-FIXED }

FRU Multirecord Area Header
---------------------------

FIID Template: tmpl_fru_multirecord_area_header

    { 8, "record_type_id", REQUIRED, LENGTH-FIXED }
    { 4, "record_format_version", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "end_of_list", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }
    { 8, "record_checksum", REQUIRED, LENGTH-FIXED }
    { 8, "header_checksum", REQUIRED, LENGTH-FIXED }

FRU Power Supply Information
----------------------------

FIID Template: tmpl_fru_power_supply_information

    { 12, "overall_capacity", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 16, "peak_va", REQUIRED, LENGTH-FIXED }
    { 8, "inrush_current", REQUIRED, LENGTH-FIXED }
    { 8, "inrush_interval", REQUIRED, LENGTH-FIXED }
    { 16, "low_end_input_voltage_range_1", REQUIRED, LENGTH-FIXED }
    { 16, "high_end_input_voltage_range_1", REQUIRED, LENGTH-FIXED }
    { 16, "low_end_input_voltage_range_2", REQUIRED, LENGTH-FIXED }
    { 16, "high_end_input_voltage_range_2", REQUIRED, LENGTH-FIXED }
    { 8, "low_end_input_frequency_range", REQUIRED, LENGTH-FIXED }
    { 8, "high_end_input_frequency_range", REQUIRED, LENGTH-FIXED }
    { 8, "ac_dropout_tolerance", REQUIRED, LENGTH-FIXED }
    { 1, "predictive_fail_support", REQUIRED, LENGTH-FIXED }
    { 1, "power_factor_correction", REQUIRED, LENGTH-FIXED }
    { 1, "autoswitch", REQUIRED, LENGTH-FIXED }
    { 1, "hot_swap_support", REQUIRED, LENGTH-FIXED }
    { 1, "tachometer_pulses_per_rotation_predictive_fail_polarity", REQUIRED, LENGTH-FIXED }
    { 3, "reserved2", REQUIRED, LENGTH-FIXED }
    { 12, "peak_capacity", REQUIRED, LENGTH-FIXED }
    { 4, "hold_up_time", REQUIRED, LENGTH-FIXED }
    { 4, "voltage_2", REQUIRED, LENGTH-FIXED }
    { 4, "voltage_1", REQUIRED, LENGTH-FIXED }
    { 16, "total_combined_wattage", REQUIRED, LENGTH-FIXED }
    { 8, "predictive_fail_tachometer_lower_threshold", REQUIRED, LENGTH-FIXED }

FRU DC Output
-------------

FIID Template: tmpl_fru_dc_output

    { 4, "output_number", REQUIRED, LENGTH-FIXED }
    { 3, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "standby", REQUIRED, LENGTH-FIXED }
    { 16, "nominal_voltage", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_negative_voltage_deviation", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_positive_voltage_deviation", REQUIRED, LENGTH-FIXED }
    { 16, "ripple_and_noise_pk_pk", REQUIRED, LENGTH-FIXED }
    { 16, "minimum_current_draw", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_current_draw", REQUIRED, LENGTH-FIXED }

FRU DC Load
-----------

FIID Template: tmpl_fru_dc_load

    { 4, "output_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 16, "nominal_voltage", REQUIRED, LENGTH-FIXED }
    { 16, "specd_minimum_voltage", REQUIRED, LENGTH-FIXED }
    { 16, "specd_maximum_voltage", REQUIRED, LENGTH-FIXED }
    { 16, "specd_ripple_and_noise_pk_pk", REQUIRED, LENGTH-FIXED }
    { 16, "minimum_current_load", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_current_load", REQUIRED, LENGTH-FIXED }

FRU Management Access Record
----------------------------

FIID Template: tmpl_fru_management_access_record

    { 8, "sub_record_type", REQUIRED, LENGTH-FIXED }
    { 2048, "record", REQUIRED, LENGTH-VARIABLE }

FRU Base Compatability Record
-----------------------------

FIID Template: tmpl_fru_base_compatibility_record

    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_code", REQUIRED, LENGTH-FIXED }
    { 8, "compatibility_base", REQUIRED, LENGTH-FIXED }
    { 7, "compatibility_code_start_value", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 4096, "code_range_mask", REQUIRED, LENGTH-VARIABLE }

FRU Extended Compatability Record
---------------------------------

FIID Template: tmpl_fru_extended_compatibility_record

    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_code", REQUIRED, LENGTH-FIXED }
    { 8, "compatibility_base", REQUIRED, LENGTH-FIXED }
    { 7, "compatibility_code_start_value", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }
    { 4096, "code_range_mask", REQUIRED, LENGTH-VARIABLE }

FRU OEM Record
--------------

FIID Template: tmpl_fru_oem_record

    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4096, "oem_data", REQUIRED, LENGTH-VARIABLE }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_INFORMATION_RECORD_FORMAT_TEMPLATES_H */
