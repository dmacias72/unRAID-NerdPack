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

#ifndef IPMI_SDR_OEM_INTEL_NODE_MANAGER_RECORD_FORMAT_TEMPLATES_H
#define IPMI_SDR_OEM_INTEL_NODE_MANAGER_RECORD_FORMAT_TEMPLATES_H

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

/*
 * Intel Node Manager
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 * Intel S2600KP
 * Intel S2600WT2
 * Intel S2600WTT
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 * Quanta QSSC-S4R/Appro GB812X-CN
 */

SDR OEM Intel Node Manager Record
---------------------------------

FIID Template: tmpl_sdr_oem_intel_node_manager_record

    /*********************
     * SDR Record Header *
     *********************/
    { 16, "record_id", REQUIRED, LENGTH-FIXED }
    { 4,  "sdr_version_major", REQUIRED, LENGTH-FIXED }
    { 4,  "sdr_version_minor", REQUIRED, LENGTH-FIXED }
    { 8,  "record_type", REQUIRED, LENGTH-FIXED }
    { 8,  "record_length", REQUIRED, LENGTH-FIXED }
    /********************
     * Record Key Bytes *
     ********************/
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "record_subtype", REQUIRED, LENGTH-FIXED }
    { 8,  "version_number", REQUIRED, LENGTH-FIXED }
    { 1,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 7,  "nm_device_slave_address", REQUIRED, LENGTH-FIXED }
    { 2,  "sensor_owner_lun", REQUIRED, LENGTH-FIXED }
    { 2,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 4,  "channel_number", REQUIRED, LENGTH-FIXED }
    { 8,  "nm_health_event_sensor_number", REQUIRED, LENGTH-FIXED }
    { 8,  "nm_exception_event_sensor_number", REQUIRED, LENGTH-FIXED }
    { 8,  "nm_operational_capabilities_sensor_number", REQUIRED, LENGTH-FIXED }
    { 8,  "nm_alert_threshold_exceeded_sensor_number", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_OEM_INTEL_NODE_MANAGER_RECORD_FORMAT_TEMPLATES_H */
