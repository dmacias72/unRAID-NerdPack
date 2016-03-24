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

#ifndef IPMI_SENSOR_CMDS_TEMPLATES_H
#define IPMI_SENSOR_CMDS_TEMPLATES_H

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

Get Device SDR Info Request
---------------------------

FIID Template: tmpl_cmd_get_device_sdr_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 1, "operation", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }

Get Device SDR Info Response
----------------------------

FIID Template: tmpl_cmd_get_device_sdr_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "number", REQUIRED, LENGTH-FIXED }
    { 1, "flags.device_lun_0_has_sensors", REQUIRED, LENGTH-FIXED }
    { 1, "flags.device_lun_1_has_sensors", REQUIRED, LENGTH-FIXED }
    { 1, "flags.device_lun_2_has_sensors", REQUIRED, LENGTH-FIXED }
    { 1, "flags.device_lun_3_has_sensors", REQUIRED, LENGTH-FIXED }
    { 3, "flags.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "flags.sensor_population", REQUIRED, LENGTH-FIXED }
    { 32, "sensor_population_change_indicator", REQUIRED, LENGTH-FIXED }

Get Device SDR Request
----------------------

FIID Template: tmpl_cmd_get_device_sdr_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 16, "reservation_id", REQUIRED, LENGTH-FIXED }
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "offset_into_record", REQUIRED, LENGTH-FIXED }
    { 8, "bytes_to_read", REQUIRED, LENGTH-FIXED }

Get Device SDR Response
-----------------------

FIID Template: tmpl_cmd_get_device_sdr_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 16, "next_record_id", REQUIRED, LENGTH-FIXED }
    /* 2040 = 255 * 8, 255 b/c bytes_to_read field in request is 1 byte long */
    { 2040, "record_data", REQUIRED, LENGTH-VARIABLE }

Reserve Device SDR Repository Request
-------------------------------------

FIID Template: tmpl_cmd_reserve_device_sdr_repository_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED },

Reserve Device SDR Repository Response
--------------------------------------

FIID Template: tmpl_cmd_reserve_device_sdr_repository_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT },
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT },
    { 16, "reservation_id", REQUIRED, LENGTH-FIXED },  /* LS byte first */

Get Sensor Reading Factors Request
----------------------------------

FIID Template: tmpl_cmd_get_sensor_reading_factors_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "reading_byte", REQUIRED, LENGTH-FIXED }

Get Sensor Reading Factors Response
-----------------------------------

FIID Template: tmpl_cmd_get_sensor_reading_factors_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "next_reading", REQUIRED, LENGTH-FIXED }
    { 8, "m_ls", REQUIRED, LENGTH-FIXED }
    { 6, "tolerance", REQUIRED, LENGTH-FIXED }
    { 2, "m_ms", REQUIRED, LENGTH-FIXED }
    { 8, "b_ls", REQUIRED, LENGTH-FIXED }
    { 6, "accuracy_ls", REQUIRED, LENGTH-FIXED }
    { 2, "b_ms", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 2, "accuracy_exp", REQUIRED, LENGTH-FIXED }
    { 4, "accuracy_ms", REQUIRED, LENGTH-FIXED }
    { 4, "b_exponent", REQUIRED, LENGTH-FIXED }
    { 4, "r_exponent", REQUIRED, LENGTH-FIXED }

Set Sensor Hysteresis Request
-----------------------------

FIID Template: tmpl_cmd_set_sensor_hysteresis_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "hysteresis_mask", REQUIRED, LENGTH-FIXED }
    { 8, "positive_going_threshold_hysteresis_value", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis_value", REQUIRED, LENGTH-FIXED }

Set Sensor Hysteresis Response
------------------------------

FIID Template: tmpl_cmd_set_sensor_hysteresis_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Sensor Hysteresis Request
-----------------------------

FIID Template: tmpl_cmd_get_sensor_hysteresis_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "hysteresis_mask", REQUIRED, LENGTH-FIXED }

Get Sensor Hysteresis Response
------------------------------

FIID Template: tmpl_cmd_get_sensor_hysteresis_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "positive_going_threshold_hysteresis_value", REQUIRED, LENGTH-FIXED }
    { 8, "negative_going_threshold_hysteresis_value", REQUIRED, LENGTH-FIXED }

Set Sensor Thresholds Request
-----------------------------

FIID Template: tmpl_cmd_set_sensor_thresholds_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 1, "set_lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "set_lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "set_lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "set_upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "set_upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "set_upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }

Set Sensor Thresholds Response
------------------------------

FIID Template: tmpl_cmd_set_sensor_thresholds_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Sensor Thresholds Request
-----------------------------

FIID Template: tmpl_cmd_get_sensor_thresholds_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

Get Sensor Thresholds Response
------------------------------

FIID Template: tmpl_cmd_get_sensor_thresholds_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 1, "readable_thresholds.lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "readable_thresholds.lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "readable_thresholds.lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "readable_thresholds.upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "readable_thresholds.upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "readable_thresholds.upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 8, "upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }

Set Sensor Event Enable Request
-------------------------------

FIID Template: tmpl_cmd_set_sensor_event_enable_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 4, "reserved", REQUIRED, LENGTH-FIXED }
    { 2, "event_message_action", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 16, "assertion_event_bitmask", OPTIONAL, LENGTH-FIXED }
    { 16, "deassertion_event_bitmask", OPTIONAL, LENGTH-FIXED }

Set Sensor Event Enable (Threshold) Request
-------------------------------------------

FIID Template: tmpl_cmd_set_sensor_event_enable_threshold_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 2, "event_message_action", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }

    { 1, "assertion_event_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved2", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved3", OPTIONAL, LENGTH-FIXED }


Set Sensor Event Enable (Discrete) Request
------------------------------------------

FIID Template: tmpl_cmd_set_sensor_event_enable_discrete_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 2, "event_message_action", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_7", OPTIONAL, LENGTH-FIXED }

    { 1, "assertion_event_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved2", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_7", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved3", OPTIONAL, LENGTH-FIXED }


Set Sensor Event Enable Response
--------------------------------

FIID Template: tmpl_cmd_set_sensor_event_enable_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Sensor Event Enable Request
-------------------------------

FIID Template: tmpl_cmd_get_sensor_event_enable_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

Get Sensor Event Enable Response
--------------------------------

FIID Template: tmpl_cmd_get_sensor_event_enable_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 6, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 16, "assertion_event_bitmask", OPTIONAL, LENGTH-FIXED }
    { 16, "deassertion_event_bitmask", OPTIONAL, LENGTH-FIXED }

Get Sensor Event Enable (Threshold) Response
--------------------------------------------

FIID Template: tmpl_cmd_get_sensor_event_enable_threshold_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

    { 6, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_for_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }

    { 1, "assertion_event_for_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_for_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved2", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_for_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_for_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_for_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved3", OPTIONAL, LENGTH-FIXED }


Get Sensor Event Enable (Discrete) Response
-------------------------------------------

FIID Template: tmpl_cmd_get_sensor_event_enable_discrete_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

    { 6, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "scanning_on_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_message_for_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_7", OPTIONAL, LENGTH-FIXED }

    { 1, "assertion_event_message_for_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "assertion_event_message_for_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved2", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_message_for_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_7", OPTIONAL, LENGTH-FIXED }

    { 1, "deassertion_event_message_for_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "deassertion_event_message_for_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved3", OPTIONAL, LENGTH-FIXED }


Re-arm Sensor Events Request
----------------------------

FIID Template: tmpl_cmd_re_arm_sensor_events_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 7, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "re_arm_all_event_status_from_this_sensor", REQUIRED, LENGTH-FIXED }
    { 16, "re_arm_assertion_event", OPTIONAL, LENGTH-FIXED }
    { 16, "re_arm_deassertion_event", OPTIONAL, LENGTH-FIXED }

Re-arm Sensor Events (Threshold) Request
----------------------------------------

FIID Template: tmpl_cmd_re_arm_sensor_events_threshold_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 7, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "re_arm_all_event_status_from_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved2", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_lower_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_non_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_non_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_critical_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_critical_going_high", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_non_recoverable_going_low", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_upper_non_recoverable_going_high", OPTIONAL, LENGTH-FIXED }
    { 4, "reserved3", OPTIONAL, LENGTH-FIXED }

Re-arm Sensor Events (Discrete) Request
---------------------------------------

FIID Template: tmpl_cmd_re_arm_sensor_events_discrete_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 7, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "re_arm_all_event_status_from_this_sensor", REQUIRED, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_7", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_assertion_event_for_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved2", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_0", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_1", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_2", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_3", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_4", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_5", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_6", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_7", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_8", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_9", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_10", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_11", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_12", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_13", OPTIONAL, LENGTH-FIXED }
    { 1, "re_arm_deassertion_event_for_state_bit_14", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved3", OPTIONAL, LENGTH-FIXED }

Re-arm Sensor Events Response
-----------------------------

FIID Template: tmpl_cmd_re_arm_sensor_events_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Sensor Event Status Request
-------------------------------

FIID Template: tmpl_cmd_get_sensor_event_status_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

Get Sensor Event Status Response
--------------------------------

FIID Template: tmpl_cmd_get_sensor_event_status_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 16, "assertion_event", REQUIRED, LENGTH-FIXED }
    { 16, "deassertion_event", REQUIRED, LENGTH-FIXED }

Get Sensor Event Status (Threshold) Response
--------------------------------------------

FIID Template: tmpl_cmd_get_sensor_event_status_threshold_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_condition_for_lower_non_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_lower_non_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_lower_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_lower_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_lower_non_recoverable_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_lower_non_recoverable_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_upper_non_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_upper_non_critical_going_high", REQUIRED, LENGTH-FIXED }

    { 1, "assertion_event_condition_for_upper_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_upper_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_upper_non_recoverable_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_condition_for_upper_non_recoverable_going_high", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }

    { 1, "deassertion_event_condition_for_lower_non_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_lower_non_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_lower_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_lower_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_lower_non_recoverable_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_lower_non_recoverable_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_upper_non_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_upper_non_critical_going_high", REQUIRED, LENGTH-FIXED }

    { 1, "deassertion_event_condition_for_upper_critical_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_upper_critical_going_high", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_upper_non_recoverable_going_low", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_condition_for_upper_non_recoverable_going_high", REQUIRED, LENGTH-FIXED }
    { 4, "reserved3", REQUIRED, LENGTH-FIXED }


Get Sensor Event Status (Discrete) Response
--------------------------------------------

FIID Template: tmpl_cmd_get_sensor_event_status_discrete_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_assertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "reserved2", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_deassertion_event", REQUIRED, LENGTH-FIXED }
    { 1, "reserved3", REQUIRED, LENGTH-FIXED }

Get Sensor Reading Request
--------------------------

FIID Template: tmpl_cmd_get_sensor_reading_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

Get Sensor Reading Response
---------------------------

FIID Template: tmpl_cmd_get_sensor_reading_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_event_bitmask1", REQUIRED, LENGTH-FIXED }
    { 7, "sensor_event_bitmask2", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved2", OPTIONAL, LENGTH-FIXED }

Get Sensor Reading (Threshold) Response
---------------------------------------

FIID Template: tmpl_cmd_get_sensor_reading_threshold_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_below_lower_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_below_lower_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_below_lower_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_above_upper_non_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_above_upper_critical_threshold", REQUIRED, LENGTH-FIXED }
    { 1, "at_or_above_upper_non_recoverable_threshold", REQUIRED, LENGTH-FIXED }
    { 2, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "reserved3", OPTIONAL, LENGTH-FIXED }

Get Sensor Reading (Discrete) Response
--------------------------------------

FIID Template: tmpl_cmd_get_sensor_reading_discrete_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 5, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "reading_state", REQUIRED, LENGTH-FIXED }
    { 1, "sensor_scanning", REQUIRED, LENGTH-FIXED }
    { 1, "all_event_messages", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_asserted", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_9_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_10_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_11_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_12_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_13_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "state_14_asserted", OPTIONAL, LENGTH-FIXED }
    { 1, "reserved2", OPTIONAL, LENGTH-FIXED }

Set Sensor Type Request
-----------------------

FIID Template: tmpl_cmd_set_sensor_type_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 7, "event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }

Set Sensor Type Response
------------------------

FIID Template: tmpl_cmd_set_sensor_type_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

Get Sensor Type Request
-----------------------

FIID Template: tmpl_cmd_get_sensor_type_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

Get Sensor Type Response
------------------------

FIID Template: tmpl_cmd_get_sensor_type_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 7, "event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "reserved", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status Request
-------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 8, "assertion_event_bitmask1", REQUIRED, LENGTH-FIXED }
    { 8, "assertion_event_bitmask2", REQUIRED, LENGTH-FIXED }
    { 8, "deassertion_event_bitmask1", REQUIRED, LENGTH-FIXED }
    { 8, "deassertion_event_bitmask2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status (Threshold) Request
-------------------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_threshold_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status (Discrete) Request
------------------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_discrete_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status (with Event Fields) Request
---------------------------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_event_fields_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 8, "assertion_event_bitmask1", REQUIRED, LENGTH-FIXED }
    { 8, "assertion_event_bitmask2", REQUIRED, LENGTH-FIXED }
    { 8, "deassertion_event_bitmask1", REQUIRED, LENGTH-FIXED }
    { 8, "deassertion_event_bitmask2", REQUIRED, LENGTH-FIXED }
    { 4, "offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 2, "event_data3_flag", REQUIRED, LENGTH-FIXED }
    { 2, "event_data2_flag", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status (Threshold with Event Fields) Request
-------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_threshold_event_fields_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_lower_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "assertion_event_upper_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 4, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_lower_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_critical_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_critical_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_low_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "deassertion_event_upper_non_recoverable_going_high_occurred", REQUIRED, LENGTH-FIXED }
    { 4, "reserved2", REQUIRED, LENGTH-FIXED }
    { 4, "offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 2, "event_data3_flag", REQUIRED, LENGTH-FIXED }
    { 2, "event_data2_flag", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status (Discrete with Event Fields) Request
------------------------------------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_discrete_event_fields_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }
    { 2, "sensor_reading_operation", REQUIRED, LENGTH-FIXED }
    { 2, "deassertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "assertion_bits_operation", REQUIRED, LENGTH-FIXED }
    { 2, "event_data_bytes_operation", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_reading", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_assertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "state_0_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_1_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_2_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_3_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_4_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_5_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_6_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_7_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_8_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_9_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_10_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_11_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_12_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_13_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "state_14_deassertion_event_occurred", REQUIRED, LENGTH-FIXED }
    { 1, "reserved1", REQUIRED, LENGTH-FIXED }
    { 4, "offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 2, "event_data3_flag", REQUIRED, LENGTH-FIXED }
    { 2, "event_data2_flag", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }

Set Sensor Reading and Event Status Response
--------------------------------------------

FIID Template: tmpl_cmd_set_sensor_reading_and_event_status_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_CMDS_TEMPLATES_H */
