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

#ifndef IPMI_DCMI_CMDS_API_H
#define IPMI_DCMI_CMDS_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/fiid/fiid.h>

/* 
 * ipmi_cmd* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rs must be for the function's respective fiid template
 * response.
 *
 */

int ipmi_cmd_dcmi_get_dcmi_capability_info (ipmi_ctx_t ctx,
                                            uint8_t parameter_selector,
                                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_capability_info_supported_dcmi_capabilities (ipmi_ctx_t ctx,
                                                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_capability_info_mandatory_platform_attributes (ipmi_ctx_t ctx,
                                                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_capability_info_optional_platform_attributes (ipmi_ctx_t ctx,
                                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_capability_info_manageability_access_attributes (ipmi_ctx_t ctx,
                                                                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_capability_info_enhanced_system_power_statistics_attributes (ipmi_ctx_t ctx,
                                                                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_dcmi_configuration_parameters (ipmi_ctx_t ctx,
						     uint8_t parameter_selector,
						     uint8_t set_selector,
						     const void *configuration_parameter_data,
						     unsigned int configuration_parameter_data_len,
						     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_dcmi_configuration_parameters_activate_dhcp (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   uint8_t activate,
								   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_dcmi_configuration_parameters_discovery_configuration (ipmi_ctx_t ctx,
									     uint8_t set_selector,
									     uint8_t option_12,
									     uint8_t option_60_with_option_43,
									     uint8_t random_back_off,
									     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_1 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   uint8_t initial_timeout_interval,
								   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_2 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   uint16_t server_contact_timeout_interval,
								   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_set_dcmi_configuration_parameters_dhcp_timing_3 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   uint16_t server_contact_retry_interval,
								   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_configuration_parameters (ipmi_ctx_t ctx,
						     uint8_t parameter_selector,
						     uint8_t set_selector,
						     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_configuration_parameters_discovery_configuration (ipmi_ctx_t ctx,
									     uint8_t set_selector,
									     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_1 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_2 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_get_dcmi_configuration_parameters_dhcp_timing_3 (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_asset_tag (ipmi_ctx_t ctx,
                                 uint8_t offset_to_read,
                                 uint8_t number_of_bytes_to_read,
                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_asset_tag (ipmi_ctx_t ctx,
                                 uint8_t offset_to_write,
                                 uint8_t number_of_bytes_to_write,
                                 const void *data,
                                 unsigned int data_len,
                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_management_controller_identifier_string (ipmi_ctx_t ctx,
                                                               uint8_t offset_to_read,
                                                               uint8_t number_of_bytes_to_read,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_management_controller_identifier_string (ipmi_ctx_t ctx,
                                                               uint8_t offset_to_write,
                                                               uint8_t number_of_bytes_to_write,
                                                               const void *data,
                                                               unsigned int data_len,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_dcmi_sensor_info (ipmi_ctx_t ctx,
                                        uint8_t sensor_type,
                                        uint8_t entity_id,
                                        uint8_t entity_instance,
                                        uint8_t entity_instance_start,
                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_power_reading (ipmi_ctx_t ctx,
                                     uint8_t mode,
                                     uint8_t mode_attributes,
                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_power_limit (ipmi_ctx_t ctx,
                                   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_set_power_limit (ipmi_ctx_t ctx,
                                   uint8_t exception_actions,
                                   uint16_t power_limit_requested,
                                   uint32_t correction_time_limit,
                                   uint16_t management_application_statistics_sampling_period,
                                   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_dcmi_activate_deactivate_power_limit (ipmi_ctx_t ctx,
                                                   uint8_t power_limit_activation,
                                                   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_thermal_limit (ipmi_ctx_t ctx,
				     uint8_t entity_id,
				     uint8_t entity_instance,
				     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_set_thermal_limit (ipmi_ctx_t ctx,
				     uint8_t entity_id,
				     uint8_t entity_instance,
				     uint8_t temperature_limit,
				     uint8_t exception_actions_log_event_to_sel_only,
				     uint8_t exception_actions_hard_power_off_system_and_log_event,
				     uint16_t exception_time,
				     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_dcmi_get_temperature_reading (ipmi_ctx_t ctx,
					   uint8_t sensor_type,
					   uint8_t entity_id,
					   uint8_t entity_instance,
					   uint8_t entity_instance_start,
					   fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DCMI_CMDS_API_H */
