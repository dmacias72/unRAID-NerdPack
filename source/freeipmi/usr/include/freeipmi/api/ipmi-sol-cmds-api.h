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

#ifndef IPMI_SOL_CMDS_API_H
#define IPMI_SOL_CMDS_API_H

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

int ipmi_cmd_set_sol_configuration_parameters (ipmi_ctx_t ctx,
                                               uint8_t channel_number,
                                               uint8_t parameter_selector,
                                               const void *configuration_parameter_data,
                                               unsigned int configuration_parameter_data_len,
                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_set_in_progress (ipmi_ctx_t ctx,
                                                               uint8_t channel_number,
                                                               uint8_t state,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_enable (ipmi_ctx_t ctx,
                                                          uint8_t channel_number,
                                                          uint8_t sol_enable,
                                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_authentication (ipmi_ctx_t ctx,
                                                                  uint8_t channel_number,
                                                                  uint8_t sol_privilege_level,
                                                                  uint8_t force_sol_payload_authentication,
                                                                  uint8_t force_sol_payload_encryption,
                                                                  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_character_accumulate_interval_and_send_threshold (ipmi_ctx_t ctx,
                                                                                                uint8_t channel_number,
                                                                                                uint8_t character_accumulate_interval,
                                                                                                uint8_t character_send_threshold,
                                                                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_retry (ipmi_ctx_t ctx,
                                                         uint8_t channel_number,
                                                         uint8_t retry_count,
                                                         uint8_t retry_interval,
                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_non_volatile_bit_rate (ipmi_ctx_t ctx,
                                                                         uint8_t channel_number,
                                                                         uint8_t bit_rate,
                                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_volatile_bit_rate (ipmi_ctx_t ctx,
                                                                     uint8_t channel_number,
                                                                     uint8_t bit_rate,
                                                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sol_configuration_parameters_sol_payload_port_number (ipmi_ctx_t ctx,
                                                                       uint8_t channel_number,
                                                                       uint16_t port_number,
                                                                       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters (ipmi_ctx_t ctx,
                                               uint8_t channel_number,
                                               uint8_t get_parameter,
                                               uint8_t parameter_selector,
                                               uint8_t set_selector,
                                               uint8_t block_selector,
                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_set_in_progress (ipmi_ctx_t ctx,
                                                               uint8_t channel_number,
                                                               uint8_t get_parameter,
                                                               uint8_t set_selector,
                                                               uint8_t block_selector,
                                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_enable (ipmi_ctx_t ctx,
                                                          uint8_t channel_number,
                                                          uint8_t get_parameter,
                                                          uint8_t set_selector,
                                                          uint8_t block_selector,
                                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_authentication (ipmi_ctx_t ctx,
                                                                  uint8_t channel_number,
                                                                  uint8_t get_parameter,
                                                                  uint8_t set_selector,
                                                                  uint8_t block_selector,
                                                                  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_character_accumulate_interval_and_send_threshold (ipmi_ctx_t ctx,
                                                                                                uint8_t channel_number,
                                                                                                uint8_t get_parameter,
                                                                                                uint8_t set_selector,
                                                                                                uint8_t block_selector,
                                                                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_retry (ipmi_ctx_t ctx,
                                                         uint8_t channel_number,
                                                         uint8_t get_parameter,
                                                         uint8_t set_selector,
                                                         uint8_t block_selector,
                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_non_volatile_bit_rate (ipmi_ctx_t ctx,
                                                                         uint8_t channel_number,
                                                                         uint8_t get_parameter,
                                                                         uint8_t set_selector,
                                                                         uint8_t block_selector,
                                                                         fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_volatile_bit_rate (ipmi_ctx_t ctx,
                                                                     uint8_t channel_number,
                                                                     uint8_t get_parameter,
                                                                     uint8_t set_selector,
                                                                     uint8_t block_selector,
                                                                     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_payload_channel (ipmi_ctx_t ctx,
                                                                   uint8_t channel_number,
                                                                   uint8_t get_parameter,
                                                                   uint8_t set_selector,
                                                                   uint8_t block_selector,
                                                                   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sol_configuration_parameters_sol_payload_port_number (ipmi_ctx_t ctx,
                                                                       uint8_t channel_number,
                                                                       uint8_t get_parameter,
                                                                       uint8_t set_selector,
                                                                       uint8_t block_selector,
                                                                       fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_CMDS_API_H */
