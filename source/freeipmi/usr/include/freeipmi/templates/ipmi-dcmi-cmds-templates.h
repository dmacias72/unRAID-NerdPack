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
/*****************************************************************************\
 *  Copyright (C) 2009-2015 Lawrence Livermore National Security, LLC.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  LLNL-CODE-413270
 *
 *  This file is part of Ipmi-Dcmi, tools and libraries to support the
 *  data center manageability interface (DCMI).  For details, see
 *  http://www.llnl.gov/linux/.
 *
 *  Ipmi-Dcmi is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmi-Dcmi is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmi-Dcmi.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMI_DCMI_CMDS_TEMPLATES_H
#define IPMI_DCMI_CMDS_TEMPLATES_H

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

DCMI Rolling Average Time Period
--------------------------------

FIID Template: tmpl_dcmi_rolling_average_time_period

    { 6, "time_duration", REQUIRED, LENGTH-FIXED }
    { 2, "time_duration_units", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Capability Info Request
-------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Capability Info Response
--------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1024, "parameter_data", REQUIRED, LENGTH-VARIABLE }

DCMI Get DCMI Capability Info (Supported DCMI Capabilities) Response
--------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_supported_dcmi_capabilities_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1, "mandatory_platform_capabilities.identification_support", REQUIRED, LENGTH-FIXED }
    { 1, "mandatory_platform_capabilities.sel_logging", REQUIRED, LENGTH-FIXED }
    { 1, "mandatory_platform_capabilities.chassis_power", REQUIRED, LENGTH-FIXED }
    { 1, "mandatory_platform_capabilities.temperature_monitor", REQUIRED, LENGTH-FIXED }
    { 4, "mandatory_platform_capabilities.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "optional_platform_capabilities.power_management_monitoring_support", REQUIRED, LENGTH-FIXED }
    { 7, "optional_platform_capabilities.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.in_band_system_interface_channel_available", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.serial_tmode_available", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.out_of_band_secondary_lan_channel_available", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.out_of_band_primary_lan_channel_available", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.sol_supported", REQUIRED, LENGTH-FIXED }
    { 1, "manageability_access_capabilities.vlan_capable", REQUIRED, LENGTH-FIXED }
    { 2, "manageability_access_capabilities.reserved", REQUIRED, LENGTH-FIXED }

  Notes: Some fields not valid when parameter revision >= 2.  Please
  see DCMI specification for details.

DCMI Get DCMI Capability Info (Mandatory Platform Attributes) Response
----------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_mandatory_platform_attributes_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 12, "sel_attributes.number_of_sel_entries", REQUIRED, LENGTH-FIXED }
    { 1, "sel_attributes.record_level_sel_flush_upon_rollover", REQUIRED, LENGTH-FIXED }
    { 1, "sel_attributes.entire_sel_flush_upon_rollover", REQUIRED, LENGTH-FIXED }
    { 1, "sel_attributes.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "sel_attributes.sel_automatic_rollover_enabled", REQUIRED, LENGTH-FIXED }
    { 1, "identification_attributes.guid_support", REQUIRED, LENGTH-FIXED }
    { 1, "identification_attributes.dhcp_host_name_support", REQUIRED, LENGTH-FIXED }
    { 1, "identification_attributes.asset_tag_support", REQUIRED, LENGTH-FIXED }
    { 5, "identification_attributes.reserved", REQUIRED, LENGTH-FIXED }
    { 1, "temperature_monitoring.inlet_temperature", REQUIRED, LENGTH-FIXED }
    { 1, "temperature_monitoring.processors_temperature", REQUIRED, LENGTH-FIXED }
    { 1, "temperature_monitoring.baseboard_temperature", REQUIRED, LENGTH-FIXED }
    { 5, "temperature_monitoring.reserved", REQUIRED, LENGTH-FIXED }

  Notes: Some fields not valid when parameter revision >= 2.  Please
  see DCMI specification for details.

DCMI Get DCMI Capability Info (Optional Platform Attributes) Response
---------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_optional_platform_attributes_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1, "power_management_device_slave_address.reserved", REQUIRED, LENGTH-FIXED }
    { 7, "power_management_device_slave_address.slave_address", REQUIRED, LENGTH-FIXED }
    { 4, "power_management_controller_channel_number.device_revision", REQUIRED, LENGTH-FIXED }
    { 4, "power_management_controller_channel_number.channel_number", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Capability Info (Manageability Access Attributes) Response
------------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_manageability_access_attributes_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "mandatory_primary_lan_out_of_band_support_channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "optional_secondary_lan_out_of_band_support_channel_number", REQUIRED, LENGTH-FIXED }
    { 8, "optional_serial_out_of_band_tmode_capability_channel_number", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Capability Info (Enhanced System Power Statistics Attributes) Response
------------------------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_capability_info_enhanced_system_power_statistics_attributes_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_supported_rolling_average_time_periods", REQUIRED, LENGTH-FIXED }
    { 2048, "rolling_average_time_periods", OPTIONAL, LENGTH-VARIABLE }


DCMI Set DCMI Configuration Parameters Request
----------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 1024, "configuration_parameter_data", REQUIRED, LENGTH-VARIABLE }

DCMI Set DCMI Configuration Parameters Response
-----------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }

DCMI Set DCMI Configuration Parameters (Activate DHCP) Response
---------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_activate_dhcp_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "activate", REQUIRED, LENGTH-FIXED }

DCMI Set DCMI Configuration Parameters (Discovery Configuration) Response
-------------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_discovery_configuration_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 1, "option_12", REQUIRED, LENGTH-FIXED }
    { 1, "option_60_with_option_43", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "random_back_off", REQUIRED, LENGTH-FIXED }

DCMI Set DCMI Configuration Parameters (DHCP Timing 1) Response
---------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_1_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 8, "initial_timeout_interval", REQUIRED, LENGTH-FIXED }

DCMI Set DCMI Configuration Parameters (DHCP Timing 2) Response
---------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_2_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 16, "server_contact_timeout_interval", REQUIRED, LENGTH-FIXED }


DCMI Set DCMI Configuration Parameters (DHCP Timing 3) Response
---------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_3_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }
    { 16, "server_contact_retry_interval", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Configuration Parameters Request
----------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_selector", REQUIRED, LENGTH-FIXED }
    { 8, "set_selector", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Configuration Parameters Response
-----------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1024, "parameter_data", REQUIRED, LENGTH-VARIABLE }

DCMI Get DCMI Configuration Parameters (Discovery Configuration) Request
------------------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_discovery_configuration_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 1, "option_12", REQUIRED, LENGTH-FIXED }
    { 1, "option_60_with_option_43", REQUIRED, LENGTH-FIXED }
    { 5, "reserved", REQUIRED, LENGTH-FIXED }
    { 1, "random_back_off", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Configuration Parameters (DHCP Timing 1) Request
--------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_1_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 8, "initial_timeout_interval", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Configuration Parameters (DHCP Timing 2) Request
--------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_2_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 16, "server_contact_timeout_interval", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Configuration Parameters (DHCP Timing 3) Request
--------------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_3_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.major_version", REQUIRED, LENGTH-FIXED }
    { 8, "dcmi_specification_conformance.minor_version", REQUIRED, LENGTH-FIXED }
    { 8, "parameter_revision", REQUIRED, LENGTH-FIXED }
    { 16, "server_contact_retry_interval", REQUIRED, LENGTH-FIXED }

DCMI Get Asset Tag Request
--------------------------

FIID Template: tmpl_cmd_dcmi_get_asset_tag_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "offset_to_read", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_bytes_to_read", REQUIRED, LENGTH-FIXED }

DCMI Get Asset Tag Response
---------------------------

FIID Template: tmpl_cmd_dcmi_get_asset_tag_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_asset_tag_length", REQUIRED, LENGTH-FIXED }
    { 512, "data", OPTIONAL, LENGTH-VARIABLE }

DCMI Set Asset Tag Request
--------------------------

FIID Template: tmpl_cmd_dcmi_set_asset_tag_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "offset_to_write", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_bytes_to_write", REQUIRED, LENGTH-FIXED }
    { 512, "data", OPTIONAL, LENGTH-VARIABLE }

DCMI Set Asset Tag Response
---------------------------

FIID Template: tmpl_cmd_dcmi_set_asset_tag_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_asset_tag_length_written", REQUIRED, LENGTH-FIXED }

DCMI Get Management Controller Identifier String Request
--------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_management_controller_identifier_string_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "offset_to_read", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_bytes_to_read", REQUIRED, LENGTH-FIXED }

DCMI Get Management Controller Identifier String Response
---------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_get_management_controller_identifier_string_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_length", REQUIRED, LENGTH-FIXED }
    { 512, "data", OPTIONAL, LENGTH-VARIABLE }

DCMI Set Management Controller Identifier String Request
--------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_management_controller_identifier_string_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "offset_to_write", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_bytes_to_write", REQUIRED, LENGTH-FIXED }
    { 512, "data", OPTIONAL, LENGTH-VARIABLE }

DCMI Set Management Controller Identifier String Response
---------------------------------------------------------

FIID Template: tmpl_cmd_dcmi_set_management_controller_identifier_string_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_length_written", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Sensor Info Request
---------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_sensor_info_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_start", REQUIRED, LENGTH-FIXED }

DCMI Get DCMI Sensor Info Response
----------------------------------

FIID Template: tmpl_cmd_dcmi_get_dcmi_sensor_info_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_number_of_available_instances", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_record_ids_in_this_response", REQUIRED, LENGTH-FIXED }
    { 4096, "sdr_record_ids", OPTIONAL, LENGTH-VARIABLE }

  Notes: Record IDs LS byte first.

DCMI Get Power Reading Request
------------------------------

FIID Template: tmpl_cmd_dcmi_get_power_reading_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "mode", REQUIRED, LENGTH-FIXED }
    { 16, "reserved", REQUIRED, LENGTH-FIXED }

DCMI Get Power Reading Response
-------------------------------

FIID Template: tmpl_cmd_dcmi_get_power_reading_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 16, "current_power", REQUIRED, LENGTH-FIXED }
    { 16, "minimum_power_over_sampling_duration", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_power_over_sampling_duration", REQUIRED, LENGTH-FIXED }
    { 16, "average_power_over_sampling_duration", REQUIRED, LENGTH-FIXED }
    { 32, "time_stamp", REQUIRED, LENGTH-FIXED }
    { 32, "statistics_reporting_time_period", REQUIRED, LENGTH-FIXED }
    { 6, "power_reading_state.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "power_reading_state.power_measurement", REQUIRED, LENGTH-FIXED }
    { 1, "power_reading_state.reserved2", REQUIRED, LENGTH-FIXED }

DCMI Get Power Limit Request
----------------------------

FIID Template: tmpl_cmd_dcmi_get_power_limit_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 16, "reserved", REQUIRED, LENGTH-FIXED }

DCMI Get Power Limit Response
-----------------------------

FIID Template: tmpl_cmd_dcmi_get_power_limit_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 16, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "exception_actions", REQUIRED, LENGTH-FIXED }
    { 16, "power_limit_requested", REQUIRED, LENGTH-FIXED }
    { 32, "correction_time_limit", REQUIRED, LENGTH-FIXED }
    { 16, "reserved2", REQUIRED, LENGTH-FIXED }
    { 16, "management_application_statistics_sampling_period", REQUIRED, LENGTH-FIXED }

DCMI Set Power Limit Request
----------------------------

FIID Template: tmpl_cmd_dcmi_set_power_limit_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 24, "reserved1", REQUIRED, LENGTH-FIXED }
    { 8, "exception_actions", REQUIRED, LENGTH-FIXED }
    { 16, "power_limit_requested", REQUIRED, LENGTH-FIXED }
    { 32, "correction_time_limit", REQUIRED, LENGTH-FIXED }
    { 16, "reserved2", REQUIRED, LENGTH-FIXED }
    { 16, "management_application_statistics_sampling_period", REQUIRED, LENGTH-FIXED }

DCMI Set Power Limit Response
-----------------------------

FIID Template: tmpl_cmd_dcmi_set_power_limit_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }

DCMI Activate/Deactivate Power Limit Request
--------------------------------------------

FIID Template: tmpl_cmd_dcmi_activate_deactivate_power_limit_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "power_limit_activation", REQUIRED, LENGTH-FIXED }
    { 16, "reserved", REQUIRED, LENGTH-FIXED }

DCMI Activate/Deactivate Power Limit Response
---------------------------------------------

FIID Template: tmpl_cmd_dcmi_activate_deactivate_power_limit_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }

DCMI Get Thermal Limit Request
------------------------------

FIID Template: tmpl_cmd_dcmi_get_thermal_limit_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance", REQUIRED, LENGTH-FIXED }

DCMI Get Thermal Limit Response
-------------------------------

FIID Template: tmpl_cmd_dcmi_get_thermal_limit_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "temperature_limit", REQUIRED, LENGTH-FIXED }
    { 5, "exception_actions.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.log_event_to_sel_only", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.hard_power_off_system_and_log_event", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.reserved2", REQUIRED, LENGTH-FIXED }
    { 16, "exception_time", REQUIRED, LENGTH-FIXED }

DCMI Set Thermal Limit Request
------------------------------

FIID Template: tmpl_cmd_dcmi_set_thermal_limit_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 8, "temperature_limit", REQUIRED, LENGTH-FIXED }
    { 5, "exception_actions.reserved1", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.log_event_to_sel_only", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.hard_power_off_system_and_log_event", REQUIRED, LENGTH-FIXED }
    { 1, "exception_actions.reserved2", REQUIRED, LENGTH-FIXED }
    { 16, "exception_time", REQUIRED, LENGTH-FIXED }

DCMI Set Thermal Limit Response
-------------------------------

FIID Template: tmpl_cmd_dcmi_set_thermal_limit_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }


DCMI Get Temperature Reading Request
------------------------------------

FIID Template: tmpl_cmd_dcmi_get_temperature_reading_rq

    { 8, "cmd", REQUIRED, LENGTH-FIXED }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "sensor_type", REQUIRED, LENGTH-FIXED }
    { 8, "entity_id", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance", REQUIRED, LENGTH-FIXED }
    { 8, "entity_instance_start", REQUIRED, LENGTH-FIXED }

DCMI Get Temperature Reading Response
-------------------------------------

FIID Template: tmpl_cmd_dcmi_get_temperature_reading_rs

    { 8, "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8, "group_extension_identification", REQUIRED, LENGTH-FIXED }
    { 8, "total_number_of_available_instances", REQUIRED, LENGTH-FIXED }
    { 8, "number_of_sets_of_temperature_data", REQUIRED, LENGTH-FIXED }
    { 8, "temperature1", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature2", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature3", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature4", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature5", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature6", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature7", OPTIONAL, LENGTH-FIXED }
    { 8, "temperature8", OPTIONAL, LENGTH-FIXED }

  Notes: temperature fields are signed ints.

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DCMI_CMDS_TEMPLATES_H */
