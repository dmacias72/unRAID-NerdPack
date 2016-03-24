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

#ifndef IPMI_SOL_CMDS_H
#define IPMI_SOL_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SOL_CONFIGURATION_PARAMETERS_NO_SET_SELECTOR                            0x0
#define IPMI_SOL_CONFIGURATION_PARAMETERS_NO_BLOCK_SELECTOR                          0x0

#define IPMI_SOL_CONFIGURATION_PARAMETERS_SET_COMPLETE                              0x00
#define IPMI_SOL_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS                           0x01
#define IPMI_SOL_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE                          0x02

#define IPMI_SOL_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS_VALID(__value) \
  (((__value) == IPMI_SOL_CONFIGURATION_PARAMETERS_SET_COMPLETE          \
    || (__value) == IPMI_SOL_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS    \
    || (__value) == IPMI_SOL_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE) ? 1 : 0)

#define IPMI_SOL_SOL_DISABLE    0x0
#define IPMI_SOL_SOL_ENABLE     0x1

#define IPMI_SOL_SOL_ENABLE_VALID(__val) \
  (((__val) == IPMI_SOL_SOL_DISABLE      \
    || (__val) == IPMI_SOL_SOL_ENABLE) ? 1 : 0)

#define IPMI_SOL_FORCE_SOL_PAYLOAD_AUTHENTICATION             0x1
#define IPMI_SOL_AUTHENTICATION_CONTROLLED_BY_REMOTE_SOFTWARE 0x0

#define IPMI_SOL_FORCE_SOL_PAYLOAD_AUTHENTICATION_VALID(__val) \
  (((__val) == IPMI_SOL_FORCE_SOL_PAYLOAD_AUTHENTICATION       \
    || (__val) == IPMI_SOL_AUTHENTICATION_CONTROLLED_BY_REMOTE_SOFTWARE) ? 1 : 0)

#define IPMI_SOL_FORCE_SOL_PAYLOAD_ENCRYPTION                 0x1
#define IPMI_SOL_ENCRYPTION_CONTROLLED_BY_REMOTE_SOFTWARE     0x0

#define IPMI_SOL_FORCE_SOL_PAYLOAD_ENCRYPTION_VALID(__val) \
  (((__val) == IPMI_SOL_FORCE_SOL_PAYLOAD_ENCRYPTION       \
    || (__val) == IPMI_SOL_ENCRYPTION_CONTROLLED_BY_REMOTE_SOFTWARE) ? 1 : 0)

#define IPMI_SOL_BIT_RATE_SERIAL_BIT_RATE 0x0
#define IPMI_SOL_BIT_RATE_96_KBPS         0x6
#define IPMI_SOL_BIT_RATE_192_KBPS        0x7
#define IPMI_SOL_BIT_RATE_384_KBPS        0x8
#define IPMI_SOL_BIT_RATE_576_KBPS        0x9
#define IPMI_SOL_BIT_RATE_1152_KBPS       0xA

#define IPMI_SOL_BIT_RATE_VALID(__val)           \
  (((__val) == IPMI_SOL_BIT_RATE_SERIAL_BIT_RATE \
    || (__val) == IPMI_SOL_BIT_RATE_96_KBPS      \
    || (__val) == IPMI_SOL_BIT_RATE_192_KBPS     \
    || (__val) == IPMI_SOL_BIT_RATE_384_KBPS     \
    || (__val) == IPMI_SOL_BIT_RATE_576_KBPS     \
    || (__val) == IPMI_SOL_BIT_RATE_1152_KBPS) ? 1 : 0)

#define IPMI_GET_SOL_PARAMETER                          0x0
#define IPMI_GET_SOL_PARAMETER_REVISION_ONLY            0x1

#define IPMI_GET_SOL_PARAMETER_VALID(__val) \
  (((__val) == IPMI_GET_SOL_PARAMETER       \
    || (__val) == IPMI_GET_SOL_PARAMETER_REVISION_ONLY) ? 1 : 0)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_rs;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_set_in_progress_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_enable_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_authentication_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_character_accumulate_interval_and_send_threshold_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_retry_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_non_volatile_bit_rate_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_volatile_bit_rate_rq;
extern fiid_template_t tmpl_cmd_set_sol_configuration_parameters_sol_payload_port_number_rq;

extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_rq;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_set_in_progress_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_enable_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_authentication_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_character_accumulate_interval_and_send_threshold_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_retry_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_non_volatile_bit_rate_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_volatile_bit_rate_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_payload_channel_rs;
extern fiid_template_t tmpl_cmd_get_sol_configuration_parameters_sol_payload_port_number_rs;

int fill_cmd_set_sol_configuration_parameters (uint8_t channel_number,
                                               uint8_t parameter_selector,
                                               const void *configuration_parameter_data,
                                               unsigned int configuration_parameter_data_len,
                                               fiid_obj_t obj_data_rq);

int fill_cmd_set_sol_configuration_parameters_set_in_progress (uint8_t channel_number,
                                                               uint8_t state,
                                                               fiid_obj_t obj_data_rq);

int fill_cmd_set_sol_configuration_parameters_sol_enable (uint8_t channel_number,
                                                          uint8_t sol_enable,
                                                          fiid_obj_t obj_data_rq);

int fill_cmd_set_sol_configuration_parameters_sol_authentication (uint8_t channel_number,
                                                                  uint8_t sol_privilege_level,
                                                                  uint8_t force_sol_payload_authentication,
                                                                  uint8_t force_sol_payload_encryption,
                                                                  fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sol_configuration_parameters_character_accumulate_interval_and_send_threshold (uint8_t channel_number,
                                                                                                uint8_t character_accumulate_interval,
                                                                                                uint8_t character_send_threshold,
                                                                                                fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sol_configuration_parameters_sol_retry (uint8_t channel_number,
                                                         uint8_t retry_count,
                                                         uint8_t retry_interval,
                                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sol_configuration_parameters_sol_non_volatile_bit_rate (uint8_t channel_number,
                                                                         uint8_t bit_rate,
                                                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sol_configuration_parameters_sol_volatile_bit_rate (uint8_t channel_number,
                                                                     uint8_t bit_rate,
                                                                     fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sol_configuration_parameters_sol_payload_port_number (uint8_t channel_number,
                                                                       uint16_t port_number,
                                                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sol_configuration_parameters (uint8_t channel_number,
                                               uint8_t get_parameter,
                                               uint8_t parameter_selector,
                                               uint8_t set_selector,
                                               uint8_t block_selector,
                                               fiid_obj_t obj_data_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_CMDS_H */
