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

#ifndef IPMI_SEL_RECORD_FORMAT_TEMPLATES_H
#define IPMI_SEL_RECORD_FORMAT_TEMPLATES_H

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

SEL Record Header
-----------------

FIID Template: tmpl_sel_record_header

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }

SEL System Event Record
-----------------------

FIID Template: tmpl_sel_system_event_record

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 32, "timestamp", REQUIRED, LENGTH-FIXED }

    { 1, "generator_id.id_type", REQUIRED, LENGTH-FIXED }
    { 7, "generator_id.id", REQUIRED, LENGTH-FIXED }

    { 2, "ipmb_device_lun", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    { 8, "event_message_format_version", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    { 7, "event_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "event_dir", REQUIRED, LENGTH-FIXED }

    { 8, "event_data1", REQUIRED, LENGTH-FIXED }
    { 8, "event_data2", REQUIRED, LENGTH-FIXED }
    { 8, "event_data3", REQUIRED, LENGTH-FIXED }


SEL System Event Record (with Event Fields)
-------------------------------------------

FIID Template: tmpl_sel_system_event_record_event_fields

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 32, "timestamp", REQUIRED, LENGTH-FIXED }

    { 1, "generator_id.id_type", REQUIRED, LENGTH-FIXED }
    { 7, "generator_id.id", REQUIRED, LENGTH-FIXED }

    { 2, "ipmb_device_lun", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    { 8, "event_message_format_version", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    { 7, "event_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "event_dir", REQUIRED, LENGTH-FIXED }

    { 4, "offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 2, "event_data3_flag", REQUIRED, LENGTH-FIXED }
    { 2, "event_data2_flag", REQUIRED, LENGTH-FIXED }

    { 8, "event_data2", REQUIRED, LENGTH-FIXED }

    { 8, "event_data3", REQUIRED, LENGTH-FIXED }


SEL System Event Record (w/ Previous and Severity Offset fields)
----------------------------------------------------------------

FIID Template: tmpl_sel_system_event_record_discrete_previous_state_severity

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 32, "timestamp", REQUIRED, LENGTH-FIXED }

    { 1, "generator_id.id_type", REQUIRED, LENGTH-FIXED }
    { 7, "generator_id.id", REQUIRED, LENGTH-FIXED }

    { 2, "ipmb_device_lun", REQUIRED, LENGTH-FIXED }
    { 2, "reserved", REQUIRED, LENGTH-FIXED }
    { 4, "channel_number", REQUIRED, LENGTH-FIXED }

    { 8, "event_message_format_version", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_number", REQUIRED, LENGTH-FIXED }

    { 7, "event_type_code", REQUIRED, LENGTH-FIXED }
    { 1, "event_dir", REQUIRED, LENGTH-FIXED }

    { 4, "offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 2, "event_data3_flag", REQUIRED, LENGTH-FIXED }
    { 2, "event_data2_flag", REQUIRED, LENGTH-FIXED }

    { 4, "previous_offset_from_event_reading_type_code", REQUIRED, LENGTH-FIXED }
    { 4, "offset_from_severity_event_reading_type_code", REQUIRED, LENGTH-FIXED }

    { 8, "event_data3", REQUIRED, LENGTH-FIXED }


SEL Timestamped OEM Record
--------------------------

FIID Template: tmpl_sel_timestamped_oem_record

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 32, "timestamp", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 48, "oem_defined", REQUIRED, LENGTH-FIXED }

SEL Non-Timestamped OEM Record
------------------------------

FIID Template: tmpl_sel_non_timestamped_oem_record

    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 8, "record_type", REQUIRED, LENGTH-FIXED }
    { 104, "oem_defined", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SEL_RECORD_FORMAT_TEMPLATES_H */
