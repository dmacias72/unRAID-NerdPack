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

#ifndef IPMI_OEM_INTEL_NODE_MANAGER_CMDS_API_H
#define IPMI_OEM_INTEL_NODE_MANAGER_CMDS_API_H

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

/*******************************************
 * Intel                                   *
 *******************************************/

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

int ipmi_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control (ipmi_ctx_t ctx,
                                                                                uint8_t target_channel_number,
                                                                                uint8_t target_slave_address,
                                                                                uint8_t target_lun,
                                                                                uint8_t policy_enable_disable,
                                                                                uint8_t domain_id,
                                                                                uint8_t policy_id,
                                                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_policy (ipmi_ctx_t ctx,
                                                             uint8_t target_channel_number,
                                                             uint8_t target_slave_address,
                                                             uint8_t target_lun,
                                                             uint8_t domain_id,
                                                             uint8_t policy_enabled,
                                                             uint8_t policy_id,
                                                             uint8_t policy_trigger_type,
                                                             uint8_t policy_configuration_action,
							     uint8_t aggressive_cpu_power_correction,
							     uint8_t policy_storage_option,
                                                             uint8_t policy_exception_actions_send_alert,
                                                             uint8_t policy_exception_actions_shutdown_system,
							     uint8_t policy_power_domain,
                                                             uint16_t policy_target_limit,
                                                             uint32_t correction_time_limit,
                                                             uint16_t policy_trigger_limit,
                                                             uint16_t statistics_reporting_period,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_policy_boot_time_policy (ipmi_ctx_t ctx,
									      uint8_t target_channel_number,
									      uint8_t target_slave_address,
									      uint8_t target_lun,
									      uint8_t domain_id,
									      uint8_t policy_enabled,
									      uint8_t policy_id,
									      uint8_t policy_trigger_type,
									      uint8_t policy_configuration_action,
									      uint8_t aggressive_cpu_power_correction,
									      uint8_t policy_storage_option,
									      uint8_t policy_exception_actions_send_alert,
									      uint8_t policy_exception_actions_shutdown_system,
									      uint8_t policy_power_domain,
									      uint8_t platform_booting_mode,
									      uint8_t cores_disabled,
									      uint32_t correction_time_limit,
									      uint16_t policy_trigger_limit,
									      uint16_t statistics_reporting_period,
									      fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_oem_intel_node_manager_get_node_manager_policy (ipmi_ctx_t ctx,
                                                             uint8_t target_channel_number,
                                                             uint8_t target_slave_address,
                                                             uint8_t target_lun,
                                                             uint8_t domain_id,
                                                             uint8_t policy_id,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds (ipmi_ctx_t ctx,
									      uint8_t target_channel_number,
									      uint8_t target_slave_address,
									      uint8_t target_lun,
									      uint8_t domain_id,
									      uint8_t policy_id,
									      uint16_t *alert_threshold1,
									      uint16_t *alert_threshold2,
									      uint16_t *alert_threshold3,
									      fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds (ipmi_ctx_t ctx,
									      uint8_t target_channel_number,
									      uint8_t target_slave_address,
									      uint8_t target_lun,
									      uint8_t domain_id,
									      uint8_t policy_id,
									      fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods (ipmi_ctx_t ctx,
                                                                             uint8_t target_channel_number,
                                                                             uint8_t target_slave_address,
                                                                             uint8_t target_lun,
                                                                             uint8_t domain_id,
                                                                             uint8_t policy_id,
                                                                             uint8_t *policy1_suspend_start_time,
                                                                             uint8_t *policy1_suspend_stop_time,
                                                                             uint8_t *policy1_suspend_period_recurrence_monday,
                                                                             uint8_t *policy1_suspend_period_recurrence_tuesday,
                                                                             uint8_t *policy1_suspend_period_recurrence_wednesday,
                                                                             uint8_t *policy1_suspend_period_recurrence_thursday,
                                                                             uint8_t *policy1_suspend_period_recurrence_friday,
                                                                             uint8_t *policy1_suspend_period_recurrence_saturday,
                                                                             uint8_t *policy1_suspend_period_recurrence_sunday,
                                                                             uint8_t *policy2_suspend_start_time,
                                                                             uint8_t *policy2_suspend_stop_time,
                                                                             uint8_t *policy2_suspend_period_recurrence_monday,
                                                                             uint8_t *policy2_suspend_period_recurrence_tuesday,
                                                                             uint8_t *policy2_suspend_period_recurrence_wednesday,
                                                                             uint8_t *policy2_suspend_period_recurrence_thursday,
                                                                             uint8_t *policy2_suspend_period_recurrence_friday,
                                                                             uint8_t *policy2_suspend_period_recurrence_saturday,
                                                                             uint8_t *policy2_suspend_period_recurrence_sunday,
                                                                             uint8_t *policy3_suspend_start_time,
                                                                             uint8_t *policy3_suspend_stop_time,
                                                                             uint8_t *policy3_suspend_period_recurrence_monday,
                                                                             uint8_t *policy3_suspend_period_recurrence_tuesday,
                                                                             uint8_t *policy3_suspend_period_recurrence_wednesday,
                                                                             uint8_t *policy3_suspend_period_recurrence_thursday,
                                                                             uint8_t *policy3_suspend_period_recurrence_friday,
                                                                             uint8_t *policy3_suspend_period_recurrence_saturday,
                                                                             uint8_t *policy3_suspend_period_recurrence_sunday,
                                                                             uint8_t *policy4_suspend_start_time,
                                                                             uint8_t *policy4_suspend_stop_time,
                                                                             uint8_t *policy4_suspend_period_recurrence_monday,
                                                                             uint8_t *policy4_suspend_period_recurrence_tuesday,
                                                                             uint8_t *policy4_suspend_period_recurrence_wednesday,
                                                                             uint8_t *policy4_suspend_period_recurrence_thursday,
                                                                             uint8_t *policy4_suspend_period_recurrence_friday,
                                                                             uint8_t *policy4_suspend_period_recurrence_saturday,
                                                                             uint8_t *policy4_suspend_period_recurrence_sunday,
                                                                             uint8_t *policy5_suspend_start_time,
                                                                             uint8_t *policy5_suspend_stop_time,
                                                                             uint8_t *policy5_suspend_period_recurrence_monday,
                                                                             uint8_t *policy5_suspend_period_recurrence_tuesday,
                                                                             uint8_t *policy5_suspend_period_recurrence_wednesday,
                                                                             uint8_t *policy5_suspend_period_recurrence_thursday,
                                                                             uint8_t *policy5_suspend_period_recurrence_friday,
                                                                             uint8_t *policy5_suspend_period_recurrence_saturday,
                                                                             uint8_t *policy5_suspend_period_recurrence_sunday,
                                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods (ipmi_ctx_t ctx,
                                                                             uint8_t target_channel_number,
                                                                             uint8_t target_slave_address,
                                                                             uint8_t target_lun,
                                                                             uint8_t domain_id,
                                                                             uint8_t policy_id,
                                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_reset_node_manager_statistics (ipmi_ctx_t ctx,
                                                                   uint8_t target_channel_number,
                                                                   uint8_t target_slave_address,
                                                                   uint8_t target_lun,
                                                                   uint8_t mode,
                                                                   uint8_t domain_id,
                                                                   uint8_t policy_id,
                                                                   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_node_manager_statistics (ipmi_ctx_t ctx,
                                                                 uint8_t target_channel_number,
                                                                 uint8_t target_slave_address,
                                                                 uint8_t target_lun,
                                                                 uint8_t mode,
                                                                 uint8_t domain_id,
                                                                 uint8_t policy_id,
                                                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_node_manager_capabilities (ipmi_ctx_t ctx,
                                                                   uint8_t target_channel_number,
                                                                   uint8_t target_slave_address,
                                                                   uint8_t target_lun,
                                                                   uint8_t domain_id,
                                                                   uint8_t policy_trigger_type,
                                                                   uint8_t policy_type,
								   uint8_t policy_power_domain,
                                                                   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_oem_intel_node_manager_get_node_manager_version (ipmi_ctx_t ctx,
                                                              uint8_t target_channel_number,
                                                              uint8_t target_slave_address,
                                                              uint8_t target_lun,
                                                              fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_power_draw_range (ipmi_ctx_t ctx,
                                                                       uint8_t target_channel_number,
                                                                       uint8_t target_slave_address,
                                                                       uint8_t target_lun,
                                                                       uint8_t domain_id,
                                                                       uint16_t minimum_power_draw,
                                                                       uint16_t maximum_power_draw,
                                                                       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_alert_destination (ipmi_ctx_t ctx,
                                                                        uint8_t target_channel_number,
                                                                        uint8_t target_slave_address,
                                                                        uint8_t target_lun,
                                                                        uint8_t channel_number,
                                                                        uint8_t alert_receiver_deactivation,
                                                                        uint8_t destination_information,
                                                                        uint8_t alert_string_selector,
                                                                        uint8_t send_alert_string,
                                                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_node_manager_alert_destination_ipmb (ipmi_ctx_t ctx,
                                                                             uint8_t target_channel_number,
                                                                             uint8_t target_slave_address,
                                                                             uint8_t target_lun,
                                                                             uint8_t channel_number,
                                                                             uint8_t alert_receiver_deactivation,
                                                                             uint8_t slave_address,
                                                                             uint8_t alert_string_selector,
                                                                             uint8_t send_alert_string,
                                                                             fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_oem_intel_node_manager_set_node_manager_alert_destination_lan (ipmi_ctx_t ctx,
                                                                            uint8_t target_channel_number,
                                                                            uint8_t target_slave_address,
                                                                            uint8_t target_lun,
                                                                            uint8_t channel_number,
                                                                            uint8_t alert_receiver_deactivation,
                                                                            uint8_t destination_selector,
                                                                            uint8_t alert_string_selector,
                                                                            uint8_t send_alert_string,
                                                                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_node_manager_alert_destination (ipmi_ctx_t ctx,
                                                                        uint8_t target_channel_number,
                                                                        uint8_t target_slave_address,
                                                                        uint8_t target_lun,
                                                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio (ipmi_ctx_t ctx,
								     uint8_t target_channel_number,
								     uint8_t target_slave_address,
								     uint8_t target_lun,
								     uint8_t cpu_socket_number,
								     uint8_t active_cores_configuration,
								     uint8_t turbo_ratio_limit,
								     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio (ipmi_ctx_t ctx,
								     uint8_t target_channel_number,
								     uint8_t target_slave_address,
								     uint8_t target_lun,
								     uint8_t cpu_socket_number,
								     uint8_t active_cores_configuration,
								     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_oem_intel_node_manager_get_limiting_policy_id (ipmi_ctx_t ctx,
							    uint8_t target_channel_number,
							    uint8_t target_slave_address,
							    uint8_t target_lun,
							    uint8_t domain_id,
							    fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OEM_INTEL_NODE_MANAGER_CMDS_API_H */
