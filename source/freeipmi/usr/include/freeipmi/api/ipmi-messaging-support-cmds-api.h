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

#ifndef IPMI_MESSAGING_SUPPORT_CMDS_API_H
#define IPMI_MESSAGING_SUPPORT_CMDS_API_H

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

int ipmi_cmd_set_bmc_global_enables (ipmi_ctx_t ctx,
                                     uint8_t receive_message_queue_interrupt,
                                     uint8_t event_message_buffer_full_interrupt,
                                     uint8_t event_message_buffer,
                                     uint8_t system_event_logging,
                                     uint8_t oem_0,
                                     uint8_t oem_1,
                                     uint8_t oem_2,
                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_bmc_global_enables (ipmi_ctx_t ctx,
                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_clear_message_flags (ipmi_ctx_t ctx,
                                  uint8_t receive_message_queue,
                                  uint8_t event_message_buffer,
                                  uint8_t watchdog_pre_timeout_interrupt_flag,
                                  uint8_t oem_0,
                                  uint8_t oem_1,
                                  uint8_t oem_2,
                                  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_message_flags (ipmi_ctx_t ctx,
                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_enable_message_channel_receive (ipmi_ctx_t ctx,
                                             uint8_t channel_number,
                                             uint8_t channel_operation,
                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_message (ipmi_ctx_t ctx,
                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_send_message (ipmi_ctx_t ctx,
                           uint8_t channel_number,
                           uint8_t message_authentication,
                           uint8_t message_encryption,
                           uint8_t tracking_operation,
                           const void *message_data,
                           unsigned int message_data_len,
                           fiid_obj_t obj_cmd_rs);

int ipmi_cmd_read_event_message_buffer (ipmi_ctx_t ctx,
                                        fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_interface_capabilities (ipmi_ctx_t ctx,
                                                uint8_t system_interface,
                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_interface_capabilities_ssif (ipmi_ctx_t ctx,
                                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_interface_capabilities_kcs (ipmi_ctx_t ctx,
                                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_bt_interface_capabilities (ipmi_ctx_t ctx,
                                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_master_write_read (ipmi_ctx_t ctx,
                                uint8_t bus_type,
                                uint8_t bus_id,
                                uint8_t channel_number,
                                uint8_t slave_address,
                                uint8_t read_count,
                                const void *data,
                                unsigned int data_len,
                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_channel_authentication_capabilities (ipmi_ctx_t ctx,
                                                      uint8_t channel_number,
                                                      uint8_t maximum_privilege_level,
                                                      uint8_t get_ipmi_v20_extended_data,
                                                      fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_guid (ipmi_ctx_t ctx, fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters (ipmi_ctx_t ctx,
                                         uint8_t parameter_selector,
                                         const void *configuration_parameter_data,
                                         unsigned int configuration_parameter_data_len,
                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_set_in_progress (ipmi_ctx_t ctx,
                                                         uint8_t state,
                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_system_firmware_version_first_set (ipmi_ctx_t ctx,
                                                                           uint8_t set_selector,
                                                                           uint8_t encoding,
                                                                           uint8_t string_length,
                                                                           const void *string_block,
                                                                           unsigned int string_block_length,
                                                                           fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_system_firmware_version (ipmi_ctx_t ctx,
                                                                 uint8_t set_selector,
                                                                 const void *string_block,
                                                                 unsigned int string_block_length,
                                                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_system_name_first_set (ipmi_ctx_t ctx,
                                                               uint8_t set_selector,
                                                               uint8_t encoding,
                                                               uint8_t string_length,
                                                               const void *string_block,
                                                               unsigned int string_block_length,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_system_name (ipmi_ctx_t ctx,
                                                     uint8_t set_selector,
                                                     const void *string_block,
                                                     unsigned int string_block_length,
                                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_primary_operating_system_name_first_set (ipmi_ctx_t ctx,
                                                                                 uint8_t set_selector,
                                                                                 uint8_t encoding,
                                                                                 uint8_t string_length,
                                                                                 const void *string_block,
                                                                                 unsigned int string_block_length,
                                                                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_primary_operating_system_name (ipmi_ctx_t ctx,
                                                                       uint8_t set_selector,
                                                                       const void *string_block,
                                                                       unsigned int string_block_length,
                                                                       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_operating_system_name_first_set (ipmi_ctx_t ctx,
                                                                         uint8_t set_selector,
                                                                         uint8_t encoding,
                                                                         uint8_t string_length,
                                                                         const void *string_block,
                                                                         unsigned int string_block_length,
                                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_operating_system_name (ipmi_ctx_t ctx,
                                                               uint8_t set_selector,
                                                               const void *string_block,
                                                               unsigned int string_block_length,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_present_os_version_number_first_set (ipmi_ctx_t ctx,
									     uint8_t set_selector,
									     uint8_t encoding,
									     uint8_t string_length,
									     const void *string_block,
									     unsigned int string_block_length,
									     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_present_os_version_number (ipmi_ctx_t ctx,
								   uint8_t set_selector,
								   const void *string_block,
								   unsigned int string_block_length,
								   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_bmc_url_first_set (ipmi_ctx_t ctx,
							   uint8_t set_selector,
							   uint8_t encoding,
							   uint8_t string_length,
							   const void *string_block,
							   unsigned int string_block_length,
							   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_bmc_url (ipmi_ctx_t ctx,
						 uint8_t set_selector,
						 const void *string_block,
						 unsigned int string_block_length,
						 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_base_os_hypervisor_url_first_set (ipmi_ctx_t ctx,
									  uint8_t set_selector,
									  uint8_t encoding,
									  uint8_t string_length,
									  const void *string_block,
									  unsigned int string_block_length,
									  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_system_info_parameters_base_os_hypervisor_url (ipmi_ctx_t ctx,
								uint8_t set_selector,
								const void *string_block,
								unsigned int string_block_length,
								fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters (ipmi_ctx_t ctx,
                                         uint8_t get_parameter,
                                         uint8_t parameter_selector,
                                         uint8_t set_selector,
                                         uint8_t block_selector,
                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_set_in_progress (ipmi_ctx_t ctx,
                                                         uint8_t get_parameter,
                                                         uint8_t set_selector,
                                                         uint8_t block_selector,
                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_system_firmware_version_first_set (ipmi_ctx_t ctx,
                                                                           uint8_t get_parameter,
                                                                           uint8_t set_selector,
                                                                           uint8_t block_selector,
                                                                           fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_system_firmware_version (ipmi_ctx_t ctx,
                                                                 uint8_t get_parameter,
                                                                 uint8_t set_selector,
                                                                 uint8_t block_selector,
                                                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_system_name_first_set (ipmi_ctx_t ctx,
                                                               uint8_t get_parameter,
                                                               uint8_t set_selector,
                                                               uint8_t block_selector,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_system_name (ipmi_ctx_t ctx,
                                                     uint8_t get_parameter,
                                                     uint8_t set_selector,
                                                     uint8_t block_selector,
                                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_primary_operating_system_name_first_set (ipmi_ctx_t ctx,
                                                                                 uint8_t get_parameter,
                                                                                 uint8_t set_selector,
                                                                                 uint8_t block_selector,
                                                                                 fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_get_system_info_parameters_primary_operating_system_name (ipmi_ctx_t ctx,
                                                                       uint8_t get_parameter,
                                                                       uint8_t set_selector,
                                                                       uint8_t block_selector,
                                                                       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_operating_system_name_first_set (ipmi_ctx_t ctx,
                                                                         uint8_t get_parameter,
                                                                         uint8_t set_selector,
                                                                         uint8_t block_selector,
                                                                         fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_get_system_info_parameters_operating_system_name (ipmi_ctx_t ctx,
                                                               uint8_t get_parameter,
                                                               uint8_t set_selector,
                                                               uint8_t block_selector,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_present_os_version_number_first_set (ipmi_ctx_t ctx,
									     uint8_t get_parameter,
									     uint8_t set_selector,
									     uint8_t block_selector,
									     fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_get_system_info_parameters_present_os_version_number (ipmi_ctx_t ctx,
								   uint8_t get_parameter,
								   uint8_t set_selector,
								   uint8_t block_selector,
								   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_bmc_url_first_set (ipmi_ctx_t ctx,
							   uint8_t get_parameter,
							   uint8_t set_selector,
							   uint8_t block_selector,
							   fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_get_system_info_parameters_bmc_url (ipmi_ctx_t ctx,
						 uint8_t get_parameter,
						 uint8_t set_selector,
						 uint8_t block_selector,
						 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_system_info_parameters_base_os_hypervisor_url_first_set (ipmi_ctx_t ctx,
									  uint8_t get_parameter,
									  uint8_t set_selector,
									  uint8_t block_selector,
									  fiid_obj_t obj_cmd_rs);
  
int ipmi_cmd_get_system_info_parameters_base_os_hypervisor_url (ipmi_ctx_t ctx,
								uint8_t get_parameter,
								uint8_t set_selector,
								uint8_t block_selector,
								fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_session_challenge (ipmi_ctx_t ctx,
                                    uint8_t authentication_type,
                                    const char *user_name,
                                    unsigned int user_name_len,
                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_activate_session (ipmi_ctx_t ctx,
                               uint8_t authentication_type,
                               uint8_t maximum_privilege_level,
                               const void *challenge_string,
                               unsigned int challenge_string_len,
                               uint32_t initial_outbound_sequence_number,
                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_session_privilege_level (ipmi_ctx_t ctx,
                                          uint8_t privilege_level,
                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_close_session (ipmi_ctx_t ctx,
                            uint32_t session_id,
                            uint8_t *session_handle,
                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_channel_access (ipmi_ctx_t ctx,
                                 uint8_t channel_number,
                                 uint8_t ipmi_messaging_access_mode,
                                 uint8_t user_level_authentication,
                                 uint8_t per_message_authentication,
                                 uint8_t pef_alerting,
                                 uint8_t channel_access_set,
                                 uint8_t channel_privilege_level_limit,
                                 uint8_t channel_privilege_level_limit_set,
                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_channel_access (ipmi_ctx_t ctx,
                                 uint8_t channel_number,
                                 uint8_t channel_access_get,
                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_channel_info (ipmi_ctx_t ctx,
                               uint8_t channel_number,
                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_channel_security_keys (ipmi_ctx_t ctx,
                                        uint8_t channel_number,
                                        uint8_t operation,
                                        uint8_t key_id,
                                        const void *key_value,
                                        unsigned int key_value_len,
                                        fiid_obj_t obj_cmd_rq);

int ipmi_cmd_set_user_access (ipmi_ctx_t ctx,
                              uint8_t channel_number,
                              uint8_t user_ipmi_messaging,
                              uint8_t user_link_authentication,
                              uint8_t user_restricted_to_callback,
                              uint8_t change_bits_in_byte,
                              uint8_t user_id,
                              uint8_t user_privilege_level_limit,
                              uint8_t user_session_number_limit,
                              fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_user_access (ipmi_ctx_t ctx,
                              uint8_t channel_number,
                              uint8_t user_id,
                              fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_user_name (ipmi_ctx_t ctx,
                            uint8_t user_id,
                            const char *user_name,
                            unsigned int user_name_len,
                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_user_name (ipmi_ctx_t ctx,
                            uint8_t user_id,
                            fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_user_password (ipmi_ctx_t ctx,
                                uint8_t user_id,
                                uint8_t password_size,
                                uint8_t operation,
                                const char *password,
                                unsigned int password_len,
                                fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_MESSAGING_SUPPORT_CMDS_API_H */
