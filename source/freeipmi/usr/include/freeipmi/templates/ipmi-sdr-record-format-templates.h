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

#ifndef IPMI_SDR_RECORD_FORMAT_TEMPLATES_H
#define IPMI_SDR_RECORD_FORMAT_TEMPLATES_H

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

SDR Record Header
-----------------

FIID Template: tmpl_sdr_record_header

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

SDR Full Sensor Record
----------------------

FIID Template: tmpl_sdr_full_sensor_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.settable_sensor", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 16, "assertion_event_lower_threshold_reading_mask", REQUIRED, LENGTH-FIXED }
    { 16, "deassertion_event_upper_threshold_reading_mask", REQUIRED, LENGTH-FIXED }
    { 16, "discrete_reading_settable_threshold_readable_threshold_mask", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 7, "linearization", REQUIRED, LENGTH-FIXED }
    { 1, "linearization.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "m_ls", REQUIRED, LENGTH-FIXED }
    { 6, "tolerance", REQUIRED, LENGTH-FIXED }
    { 2, "m_ms", REQUIRED, LENGTH-FIXED }
    { 8, "b_ls", REQUIRED, LENGTH-FIXED }
    { 6, "accuracy_ls", REQUIRED, LENGTH-FIXED }
    { 2, "b_ms", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 2, "accuracy_exp", REQUIRED, LENGTH-FIXED }
    { 4, "accuracy_ms", REQUIRED, LENGTH-FIXED }
    { 4, "b_exponent", REQUIRED, LENGTH-FIXED }
    { 4, "r_exponent", REQUIRED, LENGTH-FIXED }

    { 1, "analog_characteristics_flag.nominal_reading", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_max", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_min", REQUIRED, LENGTH-FIXED }
    { 5, "analog_characteristics_flag.reserved", REQUIRED, LENGTH-FIXED }

    { 8, "nominal_reading", REQUIRED, LENGTH-FIXED }
    { 8, "normal_maximum", REQUIRED, LENGTH-FIXED }
    { 8, "normal_minimum", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_maximum_reading", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_minimum_reading", REQUIRED, LENGTH-FIXED }

    { 8, "upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }

    { 16, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Full Sensor Record (Non-Threshold Base Sensors)
---------------------------------------------------

FIID Template: tmpl_sdr_full_sensor_record_non_threshold_based_sensors

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.reserved", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_mask.event_offset_0", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_1", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_2", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_3", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_4", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_5", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_6", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_7", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_8", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_9", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_10", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_11", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_12", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_13", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_14", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "deassertion_event_mask.event_offset_0", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_1", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_2", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_3", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_4", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_5", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_6", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_7", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_8", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_9", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_10", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_11", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_12", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_13", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_14", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "discrete_reading_mask.state_bit_0", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_1", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_2", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_3", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_4", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_5", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_6", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_7", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_8", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_9", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_10", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_11", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_12", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_13", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_14", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 7, "linearization", REQUIRED, LENGTH-FIXED }
    { 1, "linearization.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "m_ls", REQUIRED, LENGTH-FIXED }
    { 6, "tolerance", REQUIRED, LENGTH-FIXED }
    { 2, "m_ms", REQUIRED, LENGTH-FIXED }
    { 8, "b_ls", REQUIRED, LENGTH-FIXED }
    { 6, "accuracy_ls", REQUIRED, LENGTH-FIXED }
    { 2, "b_ms", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 2, "accuracy_exp", REQUIRED, LENGTH-FIXED }
    { 4, "accuracy_ms", REQUIRED, LENGTH-FIXED }
    { 4, "b_exponent", REQUIRED, LENGTH-FIXED }
    { 4, "r_exponent", REQUIRED, LENGTH-FIXED }

    { 1, "analog_characteristics_flag.nominal_reading", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_max", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_min", REQUIRED, LENGTH-FIXED }
    { 5, "analog_characteristics_flag.reserved", REQUIRED, LENGTH-FIXED }

    { 8, "nominal_reading", REQUIRED, LENGTH-FIXED }
    { 8, "normal_maximum", REQUIRED, LENGTH-FIXED }
    { 8, "normal_minimum", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_maximum_reading", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_minimum_reading", REQUIRED, LENGTH-FIXED }

    { 8, "upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }

    { 16, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Full Sensor Record (Threshold Base Sensors)
-----------------------------------------------

FIID Template: tmpl_sdr_full_sensor_record_threshold_based_sensors

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.reserved", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 1, "threshold_assertion_event_mask.lower_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_non_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_non_recoverable_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "threshold_deassertion_event_mask.lower_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_non_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_non_recoverable_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "readable_threshold_mask.lower_non_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.lower_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.lower_non_recoverable_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_non_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_non_recoverable_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_non_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_non_recoverable_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_non_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_non_recoverable_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 7, "linearization", REQUIRED, LENGTH-FIXED }
    { 1, "linearization.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "m_ls", REQUIRED, LENGTH-FIXED }
    { 6, "tolerance", REQUIRED, LENGTH-FIXED }
    { 2, "m_ms", REQUIRED, LENGTH-FIXED }
    { 8, "b_ls", REQUIRED, LENGTH-FIXED }
    { 6, "accuracy_ls", REQUIRED, LENGTH-FIXED }
    { 2, "b_ms", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 2, "accuracy_exp", REQUIRED, LENGTH-FIXED }
    { 4, "accuracy_ms", REQUIRED, LENGTH-FIXED }
    { 4, "b_exponent", REQUIRED, LENGTH-FIXED }
    { 4, "r_exponent", REQUIRED, LENGTH-FIXED }

    { 1, "analog_characteristics_flag.nominal_reading", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_max", REQUIRED, LENGTH-FIXED }
    { 1, "analog_characteristics_flag.normal_min", REQUIRED, LENGTH-FIXED }
    { 5, "analog_characteristics_flag.reserved", REQUIRED, LENGTH-FIXED }

    { 8, "nominal_reading", REQUIRED, LENGTH-FIXED }
    { 8, "normal_maximum", REQUIRED, LENGTH-FIXED }
    { 8, "normal_minimum", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_maximum_reading", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_minimum_reading", REQUIRED, LENGTH-FIXED }

    { 8, "upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }

    { 16, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Compact Sensor Record
-------------------------

FIID Template: tmpl_sdr_compact_sensor_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.reserved", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 16, "assertion_event_lower_threshold_reading_mask", REQUIRED, LENGTH-FIXED }
    { 16, "deassertion_event_upper_threshold_reading_mask", REQUIRED, LENGTH-FIXED }
    { 16, "discrete_reading_settable_threshold_readable_threshold_mask", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 4, "share_count", REQUIRED, LENGTH-FIXED }
    { 2, "id_string_instance_modifier_type", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 7, "id_string_instance_modifier_offset", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance_sharing", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }

    { 24, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Compact Sensor Record (Non-Threshold Based Sensors)
-------------------------------------------------------

FIID Template: tmpl_sdr_compact_sensor_record_non_threshold_based_sensors

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.reserved", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_mask.event_offset_0", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_1", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_2", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_3", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_4", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_5", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_6", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_7", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_8", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_9", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_10", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_11", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_12", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_13", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.event_offset_14", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "deassertion_event_mask.event_offset_0", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_1", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_2", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_3", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_4", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_5", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_6", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_7", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_8", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_9", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_10", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_11", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_12", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_13", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.event_offset_14", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "discrete_reading_mask.state_bit_0", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_1", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_2", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_3", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_4", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_5", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_6", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_7", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_8", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_9", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_10", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_11", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_12", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_13", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.state_bit_14", REQUIRED, LENGTH-FIXED }
    { 1, "discrete_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 4, "share_count", REQUIRED, LENGTH-FIXED }
    { 2, "id_string_instance_modifier_type", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 7, "id_string_instance_modifier_offset", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance_sharing", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 24, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }
    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Compact Sensor Record (Threshold Based Sensors)
---------------------------------------------------

FIID Template: tmpl_sdr_compact_sensor_record_threshold_based_sensors

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_initialization.sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.event_generation", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_sensor_type", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_hysteresis", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_thresholds", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_events", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.init_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_initialization.reserved", REQUIRED, LENGTH-FIXED }

    { 2, "sensor_capabilities.event_message_control_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.threshold_access_support", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_capabilities.hysteresis_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.auto_re_arm_support", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_capabilities.entity_ignore_support", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 1, "threshold_assertion_event_mask.lower_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.lower_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_assertion_event_mask.upper_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_non_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.lower_non_recoverable_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "lower_threshold_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "threshold_deassertion_event_mask.lower_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.lower_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_critical_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_critical_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_recoverable_going_low_supported", REQUIRED, LENGTH-FIXED }
    { 1, "threshold_deassertion_event_mask.upper_non_recoverable_going_high_supported", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_non_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_critical_threshold_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.upper_non_recoverable_is_comparison", REQUIRED, LENGTH-FIXED }
    { 1, "upper_threshold_reading_mask.reserved", REQUIRED, LENGTH-FIXED }

    { 1, "readable_threshold_mask.lower_non_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.lower_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.lower_non_recoverable_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_non_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_critical_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.upper_non_recoverable_threshold_is_readable", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "readable_threshold_mask.reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_non_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.lower_non_recoverable_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_non_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_critical_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.upper_non_recoverable_threshold_is_settable", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "settable_threshold_mask.reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "sensor_unit1.percentage", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.modifier_unit", REQUIRED, LENGTH-FIXED }
    { 3, "sensor_unit1.rate_unit", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_unit1.analog_data_format", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit2.base_unit", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_unit3.modifier_unit", REQUIRED, LENGTH-FIXED }

    { 4, "share_count", REQUIRED, LENGTH-FIXED }
    { 2, "id_string_instance_modifier_type", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 7, "id_string_instance_modifier_offset", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance_sharing", REQUIRED, LENGTH-FIXED }

    { 8, "positive_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis", REQUIRED, LENGTH-FIXED }

    { 24, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Event Only Record
---------------------

FIID Template: tmpl_sdr_event_only_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "sensor_owner_id.type", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_owner_id", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2, "fru_inventory_device_owner_lun", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "event_reading_type_code", REQUIRED, LENGTH-FIXED }

    /*******************************************
     * Sensor Record Sharing, Sensor Direction *
     *******************************************/
    { 4, "share_count", REQUIRED, LENGTH-FIXED }
    { 2, "id_string_instance_modifier_type", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_direction", REQUIRED, LENGTH-FIXED }
    { 7, "id_string_instance_modifier_offset", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance_sharing", REQUIRED, LENGTH-FIXED }

    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "id_string_type_length_code", REQUIRED, LENGTH-FIXED }
    { 128, "id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Entity Association Record
-----------------------------

FIID Template: tmpl_sdr_entity_association_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 8, "container_entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "container_entity_instance", REQUIRED, LENGTH-FIXED }
    { 5, "flags.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "flags.sensor_presence", REQUIRED, LENGTH-FIXED }
    { 1, "flags.record_link", REQUIRED, LENGTH-FIXED }
    { 1, "flags.contained_entities", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_1", REQUIRED, LENGTH-FIXED }
    { 8, "instance_id_contained_entity_range_1", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "entity_id_contained_entity_range_2", REQUIRED, LENGTH-FIXED }
    { 8, "instance_id_contained_entity_range_2", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_3", REQUIRED, LENGTH-FIXED }
    { 8, "instance_id_contained_entity_range_3", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_4", REQUIRED, LENGTH-FIXED }
    { 8, "instance_id_contained_entity_range_4", REQUIRED, LENGTH-FIXED }

SDR Device Relative Entity Association Record
---------------------------------------------

FIID Template: tmpl_sdr_device_relative_entity_association_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 8, "container_entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "container_entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "container_entity_device_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "container_entity_device_address", REQUIRED, LENGTH-FIXED }
    { 4, "container_entity_device_channel.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "container_entity_device_channel", REQUIRED, LENGTH-FIXED }

    { 5, "flags.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "flags.sensor_presence", REQUIRED, LENGTH-FIXED }
    { 1, "flags.record_link", REQUIRED, LENGTH-FIXED }
    { 1, "flags.contained_entities", REQUIRED, LENGTH-FIXED }

    { 1, "contained_entity_1_device_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "contained_entity_1_device_address", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_1_device_channel.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_1_device_channel", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_1", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_contained_entity_range_1", REQUIRED, LENGTH-FIXED }

    { 1, "contained_entity_2_device_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "contained_entity_2_device_address", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_2_device_channel.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_2_device_channel", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_2", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_contained_entity_range_2", REQUIRED, LENGTH-FIXED }

    { 1, "contained_entity_3_device_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "contained_entity_3_device_address", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_3_device_channel.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_3_device_channel", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_3", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_contained_entity_range_3", REQUIRED, LENGTH-FIXED }

    { 1, "contained_entity_4_device_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "contained_entity_4_device_address", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_4_device_channel.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "contained_entity_4_device_channel", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id_contained_entity_range_4", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_contained_entity_range_4", REQUIRED, LENGTH-FIXED }

    { 48, "reserved", REQUIRED, LENGTH-FIXED }

SDR Generic Device Locator Record
---------------------------------

FIID Template: tmpl_sdr_generic_device_locator_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "direct_access_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "direct_access_address", REQUIRED, LENGTH-FIXED }

    { 1, "channel_number_ms", REQUIRED, LENGTH-FIXED }
    { 7, "device_slave_address", REQUIRED, LENGTH-FIXED }

    { 3, "private_bus_id", REQUIRED, LENGTH-FIXED }
    { 2, "lun_for_master_write_read_command", REQUIRED, LENGTH-FIXED }
    { 3, "channel_number_ls", REQUIRED, LENGTH-FIXED }

    { 3, "address_span", REQUIRED, LENGTH-FIXED }
    { 5, "address_span.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "device_type", REQUIRED, LENGTH-FIXED }
    { 8, "device_type_modifier", REQUIRED, LENGTH-FIXED }

    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "device_id_string_type_length", REQUIRED, LENGTH-FIXED }
    { 128, "device_id_string", OPTIONAL, LENGTH-VARIABLE }

SDR FRU Device Locator Record
-----------------------------

FIID Template: tmpl_sdr_fru_device_locator_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "direct_access_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "direct_access_address", REQUIRED, LENGTH-FIXED }

    { 8, "logical_fru_device_device_slave_address", REQUIRED, LENGTH-FIXED }

    { 3, "private_bus_id", REQUIRED, LENGTH-FIXED }
    { 2, "lun_for_master_write_read_fru_command", REQUIRED, LENGTH-FIXED }
    { 2, "logical_physical_access_lun_bus_id.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "logical_physical_fru_device", REQUIRED, LENGTH-FIXED }

    { 4, "channel_number.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/

    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "device_type", REQUIRED, LENGTH-FIXED }
    { 8, "device_type_modifier", REQUIRED, LENGTH-FIXED }
    { 8, "fru_entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "fru_entity_instance", REQUIRED, LENGTH-FIXED }

    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "device_id_string_type_length", REQUIRED, LENGTH-FIXED }
    { 128, "device_id_string", OPTIONAL, LENGTH-VARIABLE }

SDR FRU Device Locator Record (Non-Intelligent)
-----------------------------------------------

FIID Template: tmpl_sdr_fru_device_locator_record_non_intelligent

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "direct_access_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "direct_access_address", REQUIRED, LENGTH-FIXED }

    { 1, "non_intelligent_fru_device.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "non_intelligent_fru_device.slave_address", REQUIRED, LENGTH-FIXED }

    { 3, "private_bus_id", REQUIRED, LENGTH-FIXED }
    { 2, "lun_for_master_write_read_fru_command", REQUIRED, LENGTH-FIXED }
    { 2, "logical_physical_access_lun_bus_id.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "logical_physical_fru_device", REQUIRED, LENGTH-FIXED }

    { 4, "channel_number.reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 8, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "device_type", REQUIRED, LENGTH-FIXED }
    { 8, "device_type_modifier", REQUIRED, LENGTH-FIXED }
    { 8, "fru_entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "fru_entity_instance", REQUIRED, LENGTH-FIXED }
    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "device_id_string_type_length", REQUIRED, LENGTH-FIXED }
    { 128, "device_id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Management Controller Device Locator Record
-----------------------------------------------

FIID Template: tmpl_sdr_management_controller_device_locator_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "device_slave_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "device_slave_address", REQUIRED, LENGTH-FIXED }

    { 4, "channel_number", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number.reserved", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 2, "global_initialization.event_message_generation", REQUIRED, LENGTH-FIXED }
    { 1, "global_initialization.log_initialization_agent_errors", REQUIRED, LENGTH-FIXED }
    { 1, "global_initialization.controller_logs_initialization_agent_errors", REQUIRED, LENGTH-FIXED }
    { 1, "power_state_notification.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "power_state_notification.controller", REQUIRED, LENGTH-FIXED }
    { 1, "power_state_notification.acpi_device_power_state_notification", REQUIRED, LENGTH-FIXED }
    { 1, "power_state_notification.acpi_system_power_state_notification", REQUIRED, LENGTH-FIXED }

    { 1, "device_capabilities.sensor_device", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.sdr_repository_device", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.sel_device", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.fru_inventory_device", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.ipmb_event_receiver", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.ipmb_event_generator", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.bridge", REQUIRED, LENGTH-FIXED }
    { 1, "device_capabilities.chassis_device", REQUIRED, LENGTH-FIXED }

    { 24, "reserved", REQUIRED, LENGTH-FIXED }

    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 7, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 1, "entity_instance.type", REQUIRED, LENGTH-FIXED }

    { 8, "oem", REQUIRED, LENGTH-FIXED }

    { 8, "device_id_string_type_length", REQUIRED, LENGTH-FIXED }
    { 128, "device_id_string", OPTIONAL, LENGTH-VARIABLE }

SDR Management Controller Confirmation Record
---------------------------------------------

FIID Template: tmpl_sdr_management_controller_confirmation_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 1, "device_slave_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "device_slave_address", REQUIRED, LENGTH-FIXED }
    { 8, "device_id", REQUIRED, LENGTH-FIXED }
    { 4, "device_revision", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    /*********************
     * Record Body Bytes *
     *********************/
    { 7, "major_firmware_revision", REQUIRED, LENGTH-FIXED }
    { 1, "major_firmware_revision.reserved", REQUIRED, LENGTH-FIXED }
    { 8, "minor_firmware_revision", REQUIRED, LENGTH-FIXED }
    { 8, "ipmi_version", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 16, "product_id", REQUIRED, LENGTH-FIXED }
    { 128, "device_guid", REQUIRED, LENGTH-FIXED }

SDR BMC Message Channel Info
----------------------------

FIID Template: tmpl_sdr_bmc_message_channel_info_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 4, "channel_0_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_0_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_0_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_1_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_1_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_1_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_2_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_2_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_2_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_3_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_3_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_3_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_4_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_4_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_4_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_5_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_5_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_5_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_6_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_6_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_6_transmit_supported", REQUIRED, LENGTH-FIXED }
    { 4, "channel_7_protocol", REQUIRED, LENGTH-FIXED }
    { 3, "channel_7_message_receive_lun", REQUIRED, LENGTH-FIXED }
    { 1, "channel_7_transmit_supported", REQUIRED, LENGTH-FIXED }

SDR OEM Record
--------------

FIID Template: tmpl_sdr_oem_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4, "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 8, "record_length", REQUIRED, LENGTH-FIXED }

    /********************
     * Record Key Bytes *
     ********************/
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 448, "oem_data", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_RECORD_FORMAT_TEMPLATES_H */
