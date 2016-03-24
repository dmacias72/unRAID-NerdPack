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

#ifndef IPMI_SERIAL_MODEM_CMDS_H
#define IPMI_SERIAL_MODEM_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SERIAL_MODEM_CONFIGURATION_NO_SET_SELECTOR                            0x0
#define IPMI_SERIAL_MODEM_CONFIGURATION_NO_BLOCK_SELECTOR                          0x0

#define IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_COMPLETE                   0x00
#define IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS                0x01
#define IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE               0x02

#define IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS_VALID(__value) \
  (((__value) == IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_COMPLETE          \
    || (__value) == IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_IN_PROGRESS    \
    || (__value) == IPMI_SERIAL_MODEM_CONFIGURATION_PARAMETERS_SET_COMMIT_WRITE) ? 1 : 0)

#define IPMI_BASIC_MODE_ENABLE                             0x1
#define IPMI_BASIC_MODE_DISABLE                            0x0

#define IPMI_BASIC_MODE_VALID(__val)  \
  (((__val) == IPMI_BASIC_MODE_ENABLE \
    || (__val) == IPMI_BASIC_MODE_DISABLE) ? 1 : 0)

#define IPMI_PPP_MODE_ENABLE                               0x1
#define IPMI_PPP_MODE_DISABLE                              0x0

#define IPMI_PPP_MODE_VALID(__val)  \
  (((__val) == IPMI_PPP_MODE_ENABLE \
    || (__val) == IPMI_PPP_MODE_DISABLE) ? 1 : 0)

#define IPMI_TERMINAL_MODE_ENABLE                          0x1
#define IPMI_TERMINAL_MODE_DISABLE                         0x0

#define IPMI_TERMINAL_MODE_VALID(__val)  \
  (((__val) == IPMI_TERMINAL_MODE_ENABLE \
    || (__val) == IPMI_TERMINAL_MODE_DISABLE) ? 1 : 0)

#define IPMI_CONNECT_MODE_DIRECT                           0x1
#define IPMI_CONNECT_MODE_MODEM                            0x0

#define IPMI_CONNECT_MODE_VALID(__val)  \
  (((__val) == IPMI_CONNECT_MODE_DIRECT \
    || (__val) == IPMI_CONNECT_MODE_MODEM) ? 1 : 0)

#define IPMI_DTR_HANGUP_ENABLE                             0x1
#define IPMI_DTR_HANGUP_DISABLE                            0x0

#define IPMI_DTR_HANGUP_VALID(__val)  \
  (((__val) == IPMI_DTR_HANGUP_ENABLE \
    || (__val) == IPMI_DTR_HANGUP_DISABLE) ? 1 : 0)

#define IPMI_FLOW_CONTROL_NO_FLOW_CONTROL                  0x0
#define IPMI_FLOW_CONTROL_RTS_CTS_FLOW_CONTROL             0x1
#define IPMI_FLOW_CONTROL_XON_XOFF_FLOW_CONTROL            0x2
#define IPMI_FLOW_CONTROL_RESERVED                         0x3

#define IPMI_FLOW_CONTROL_VALID(__val)                   \
  (((__val) == IPMI_FLOW_CONTROL_NO_FLOW_CONTROL         \
    || (__val) == IPMI_FLOW_CONTROL_RTS_CTS_FLOW_CONTROL \
    || (__val) == IPMI_FLOW_CONTROL_XON_XOFF_FLOW_CONTROL) ? 1 : 0)

#define IPMI_BIT_RATE_9600_BPS    0x6
#define IPMI_BIT_RATE_19200_BPS   0x7
#define IPMI_BIT_RATE_38400_BPS   0x8
#define IPMI_BIT_RATE_57600_BPS   0x9
#define IPMI_BIT_RATE_115200_BPS  0xA

#define IPMI_BIT_RATE_VALID(__val)        \
  (((__val) == IPMI_BIT_RATE_9600_BPS     \
    || (__val) == IPMI_BIT_RATE_19200_BPS \
    || (__val) == IPMI_BIT_RATE_38400_BPS \
    || (__val) == IPMI_BIT_RATE_57600_BPS \
    || (__val) == IPMI_BIT_RATE_115200_BPS) ? 1 : 0)

#define IPMI_GET_SERIAL_MODEM_PARAMETER                          0x0
#define IPMI_GET_SERIAL_MODEM_PARAMETER_REVISION_ONLY            0x1

#define IPMI_GET_SERIAL_MODEM_PARAMETER_VALID(__flag) \
  (((__flag) == IPMI_GET_SERIAL_MODEM_PARAMETER       \
    || (__flag) == IPMI_GET_SERIAL_MODEM_PARAMETER_REVISION_ONLY) ? 1 : 0)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_rq;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_rs;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_set_in_progress_rq;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_connection_mode_rq;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_ipmi_messaging_comm_settings_rq;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_page_blackout_interval_rq;
extern fiid_template_t tmpl_cmd_set_serial_modem_configuration_call_retry_interval_rq;

extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_rq;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_rs;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_set_in_progress_rs;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_connection_mode_rs;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_ipmi_messaging_comm_settings_rs;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_page_blackout_interval_rs;
extern fiid_template_t tmpl_cmd_get_serial_modem_configuration_call_retry_interval_rs;

int fill_cmd_set_serial_modem_configuration (uint8_t channel_number,
                                             uint8_t parameter_selector,
                                             const void *configuration_parameter_data,
                                             unsigned int configuration_parameter_data_len,
                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_set_serial_modem_configuration_set_in_progress (uint8_t channel_number,
                                                             uint8_t state,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_set_serial_modem_configuration_connection_mode (uint8_t channel_number,
                                                             uint8_t basic_mode,
                                                             uint8_t ppp_mode,
                                                             uint8_t terminal_mode,
                                                             uint8_t connect_mode,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_set_serial_modem_configuration_ipmi_messaging_comm_settings (uint8_t channel_number,
                                                                          uint8_t dtr_hangup,
                                                                          uint8_t flow_control,
                                                                          uint8_t bit_rate,
                                                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_set_serial_modem_configuration_page_blackout_interval (uint8_t channel_number,
                                                                    uint8_t page_blackout_interval,
                                                                    fiid_obj_t obj_cmd_rq);

int fill_cmd_set_serial_modem_configuration_call_retry_interval (uint8_t channel_number,
                                                                 uint8_t call_retry_interval,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_get_serial_modem_configuration (uint8_t channel_number,
                                             uint8_t parameter_type,
                                             uint8_t parameter_selector,
                                             uint8_t set_selector,
                                             uint8_t block_selector,
                                             fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SERIAL_MODEM_CMDS_H */
