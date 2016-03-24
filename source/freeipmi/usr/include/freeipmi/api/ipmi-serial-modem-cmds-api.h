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

#ifndef IPMI_SERIAL_MODEM_CMDS_API_H
#define IPMI_SERIAL_MODEM_CMDS_API_H

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

int ipmi_cmd_set_serial_modem_configuration (ipmi_ctx_t ctx,
                                             uint8_t channel_number,
                                             uint8_t parameter_selector,
                                             const void *configuration_parameter_data,
                                             unsigned int configuration_parameter_data_len,
                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_serial_modem_configuration_set_in_progress (ipmi_ctx_t ctx,
                                                             uint8_t channel_number,
                                                             uint8_t state,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_serial_modem_configuration_connection_mode (ipmi_ctx_t ctx,
                                                             uint8_t channel_number,
                                                             uint8_t basic_mode,
                                                             uint8_t ppp_mode,
                                                             uint8_t terminal_mode,
                                                             uint8_t connect_mode,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_serial_modem_configuration_ipmi_messaging_comm_settings (ipmi_ctx_t ctx,
                                                                          uint8_t channel_number,
                                                                          uint8_t dtr_hangup,
                                                                          uint8_t flow_control,
                                                                          uint8_t bit_rate,
                                                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_serial_modem_configuration_page_blackout_interval (ipmi_ctx_t ctx,
                                                                    uint8_t channel_number,
                                                                    uint8_t page_blackout_interval,
                                                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_serial_modem_configuration_call_retry_interval (ipmi_ctx_t ctx,
                                                                 uint8_t channel_number,
                                                                 uint8_t call_retry_interval,
                                                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_serial_modem_configuration (ipmi_ctx_t ctx,
                                             uint8_t channel_number,
                                             uint8_t get_parameter,
                                             uint8_t parameter_selector,
                                             uint8_t set_selector,
                                             uint8_t block_selector,
                                             fiid_obj_t obj_cmd_rs);


int ipmi_cmd_get_serial_modem_configuration_set_in_progress (ipmi_ctx_t ctx,
                                                             uint8_t channel_number,
                                                             uint8_t get_parameter,
                                                             uint8_t set_selector,
                                                             uint8_t block_selector,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_serial_modem_configuration_connection_mode (ipmi_ctx_t ctx,
                                                             uint8_t channel_number,
                                                             uint8_t get_parameter,
                                                             uint8_t set_selector,
                                                             uint8_t block_selector,
                                                             fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_serial_modem_configuration_ipmi_messaging_comm_settings (ipmi_ctx_t ctx,
                                                                          uint8_t channel_number,
                                                                          uint8_t get_parameter,
                                                                          uint8_t set_selector,
                                                                          uint8_t block_selector,
                                                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_serial_modem_configuration_page_blackout_interval (ipmi_ctx_t ctx,
                                                                    uint8_t channel_number,
                                                                    uint8_t get_parameter,
                                                                    uint8_t set_selector,
                                                                    uint8_t block_selector,
                                                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_serial_modem_configuration_call_retry_interval (ipmi_ctx_t ctx,
                                                                 uint8_t channel_number,
                                                                 uint8_t get_parameter,
                                                                 uint8_t set_selector,
                                                                 uint8_t block_selector,
                                                                 fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SERIAL_MODEM_CMDS_API_H */
