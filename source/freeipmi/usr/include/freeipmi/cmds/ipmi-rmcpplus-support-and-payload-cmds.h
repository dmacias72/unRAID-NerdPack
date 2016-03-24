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

#ifndef IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_H
#define IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

/* achu: 4 bit field is 1 based
 *
 * note that Get Payload Activation Status returns instance status for
 * 16 instances, which is not possible.
 */
#define IPMI_PAYLOAD_INSTANCE_MIN 1
#define IPMI_PAYLOAD_INSTANCE_MAX 15

#define IPMI_PAYLOAD_INSTANCE_VALID(__val) \
  (((__val) >= IPMI_PAYLOAD_INSTANCE_MIN   \
    || (__val) <= IPMI_PAYLOAD_INSTANCE_MAX) ? 1 : 0)

#define IPMI_SOL_STARTUP_HANDSHAKE_CTS_AND_DCD_SDR_ASSERTED   0x0
#define IPMI_SOL_STARTUP_HANDSHAKE_CTS_AND_DCD_SDR_DEASSERTED 0x1

#define IPMI_SOL_STARTUP_HANDSHAKE_CTS_AND_DCD_SDR_VALID(__val)    \
  (((__val) == IPMI_SOL_STARTUP_HANDSHAKE_CTS_AND_DCD_SDR_ASSERTED \
    || (__val) == IPMI_SOL_STARTUP_HANDSHAKE_CTS_AND_DCD_SDR_DEASSERTED) ? 1 : 0)

#define IPMI_SERIAL_MODEM_ALERTS_FAIL_WHILE_SOL_ACTIVE     0x0
#define IPMI_SERIAL_MODEM_ALERTS_DEFERRED_WHILE_SOL_ACTIVE 0x1
#define IPMI_SERIAL_MODEM_ALERTS_SUCCEED_WHILE_SOL_ACTIVE  0x2
#define IPMI_SERIAL_MODEM_ALERTS_RESERVED                  0x3

#define IPMI_SERIAL_MODEM_ALERTS_VALID(__val)                        \
  (((__val) == IPMI_SERIAL_MODEM_ALERTS_FAIL_WHILE_SOL_ACTIVE        \
    || (__val) == IPMI_SERIAL_MODEM_ALERTS_DEFERRED_WHILE_SOL_ACTIVE \
    || (__val) == IPMI_SERIAL_MODEM_ALERTS_SUCCEED_WHILE_SOL_ACTIVE) ? 1 : 0)

#define IPMI_TEST_MODE_ACTIVATED   0x1
#define IPMI_TEST_MODE_DEACTIVATED 0x0

#define IPMI_TEST_MODE_VALID(__val)     \
  (((__val) == IPMI_TEST_MODE_ACTIVATED \
    || (__val) == IPMI_TEST_MODE_DEACTIVATED) ? 1 : 0)

#define IPMI_ACTIVATE_PAYLOAD_WITH_AUTHENTICATION   0x1
#define IPMI_ACTIVATE_PAYLOAD_WITHOUT_AUTHENTICATION 0x0

#define IPMI_AUTHENTICATION_ACTIVATION_VALID(__val)      \
  (((__val) == IPMI_ACTIVATE_PAYLOAD_WITH_AUTHENTICATION \
    || (__val) == IPMI_ACTIVATE_PAYLOAD_WITHOUT_AUTHENTICATION) ? 1 : 0)

#define IPMI_ACTIVATE_PAYLOAD_WITH_ENCRYPTION   0x1
#define IPMI_ACTIVATE_PAYLOAD_WITHOUT_ENCRYPTION 0x0

#define IPMI_ENCRYPTION_ACTIVATION_VALID(__val)      \
  (((__val) == IPMI_ACTIVATE_PAYLOAD_WITH_ENCRYPTION \
    || (__val) == IPMI_ACTIVATE_PAYLOAD_WITHOUT_ENCRYPTION) ? 1 : 0)

#define IPMI_TEST_MODE_NOT_SUPPORTED 0x0
#define IPMI_TEST_MODE_ENABLED       0x1

#define IPMI_SUSPEND_ENCRYPTION                0x0
#define IPMI_RESUME_ENCRYPTION                 0x1
#define IPMI_REGENERATE_INITIALIZATION_VECTOR  0x2

#define IPMI_SUSPEND_RESUME_PAYLOAD_ENCRYPTION_OPERATION_VALID(__val) \
  (((__val) == IPMI_SUSPEND_ENCRYPTION                                \
    || (__val) == IPMI_RESUME_ENCRYPTION                              \
    || (__val) == IPMI_REGENERATE_INITIALIZATION_VECTOR) ? 1 : 0)

#define IPMI_SET_USER_PAYLOAD_OPERATION_ENABLE  0x00
#define IPMI_SET_USER_PAYLOAD_OPERATION_DISABLE 0x01

#define IPMI_SET_USER_PAYLOAD_OPERATION_VALID(__val)  \
  (((__val) == IPMI_SET_USER_PAYLOAD_OPERATION_ENABLE \
    || (__val) == IPMI_SET_USER_PAYLOAD_OPERATION_DISABLE) ? 1 : 0)

/* achu: See IPMI Spec Set User Payload Access command.  Enable may be
 * 0 or 1, and Disable may be 0 or 1 as well.
 */
#define IPMI_PAYLOAD_ACCESS_VALID(__val) \
  (((__val) == 0                         \
    || (__val) == 1) ? 1 : 0)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_activate_payload_rq;
extern fiid_template_t tmpl_cmd_activate_payload_sol_rq;
extern fiid_template_t tmpl_cmd_activate_payload_rs;
extern fiid_template_t tmpl_cmd_activate_payload_sol_rs;
extern fiid_template_t tmpl_cmd_deactivate_payload_rq;
extern fiid_template_t tmpl_cmd_deactivate_payload_rs;
extern fiid_template_t tmpl_cmd_suspend_resume_payload_encryption_rq;
extern fiid_template_t tmpl_cmd_suspend_resume_payload_encryption_rq;
extern fiid_template_t tmpl_cmd_get_payload_activation_status_rq;
extern fiid_template_t tmpl_cmd_get_payload_activation_status_rs;
extern fiid_template_t tmpl_cmd_get_payload_instance_info_rq;
extern fiid_template_t tmpl_cmd_get_payload_instance_info_rs;
extern fiid_template_t tmpl_cmd_set_user_payload_access_rq;
extern fiid_template_t tmpl_cmd_set_user_payload_access_rs;
extern fiid_template_t tmpl_cmd_get_user_payload_access_rq;
extern fiid_template_t tmpl_cmd_get_user_payload_access_rs;
extern fiid_template_t tmpl_cmd_get_channel_payload_support_rq;
extern fiid_template_t tmpl_cmd_get_channel_payload_support_rs;
extern fiid_template_t tmpl_cmd_get_channel_payload_version_rq;
extern fiid_template_t tmpl_cmd_get_channel_payload_version_rs;
extern fiid_template_t tmpl_cmd_get_channel_oem_payload_info_rq;
extern fiid_template_t tmpl_cmd_get_channel_oem_payload_info_rs;

int fill_cmd_activate_payload (uint8_t payload_type,
                               uint8_t payload_instance,
                               const void *auxiliary_request_data,
                               unsigned int auxiliary_request_data_len,
                               fiid_obj_t obj_cmd_rq);

int fill_cmd_activate_payload_sol (uint8_t payload_type,
                                   uint8_t payload_instance,
                                   uint8_t sol_startup_handshake,
                                   uint8_t shared_serial_alert_behavior,
                                   uint8_t test_mode,
                                   uint8_t authentication_activation,
                                   uint8_t encryption_activation,
                                   fiid_obj_t obj_cmd_rq);

int fill_cmd_deactivate_payload (uint8_t payload_type,
                                 uint8_t payload_instance,
                                 uint32_t payload_auxiliary_data,
                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_suspend_resume_payload_encryption (uint8_t payload_type,
                                                uint8_t payload_instance,
                                                uint8_t operation,
                                                fiid_obj_t obj_cmd_rq);

int fill_cmd_get_payload_activation_status (uint8_t payload_type,
                                            fiid_obj_t obj_cmd_rq);

int fill_cmd_get_payload_instance_info (uint8_t payload_type,
                                        uint8_t payload_instance,
                                        fiid_obj_t obj_cmd_rq);

int fill_cmd_set_user_payload_access (uint8_t channel_number,
                                      uint8_t user_id,
                                      uint8_t operation,
                                      uint8_t standard_payload_1,
                                      uint8_t standard_payload_2,
                                      uint8_t standard_payload_3,
                                      uint8_t standard_payload_4,
                                      uint8_t standard_payload_5,
                                      uint8_t standard_payload_6,
                                      uint8_t standard_payload_7,
                                      uint8_t oem_payload_0,
                                      uint8_t oem_payload_1,
                                      uint8_t oem_payload_2,
                                      uint8_t oem_payload_3,
                                      uint8_t oem_payload_4,
                                      uint8_t oem_payload_5,
                                      uint8_t oem_payload_6,
                                      uint8_t oem_payload_7,
                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_get_user_payload_access (uint8_t channel_number,
                                      uint8_t user_id,
                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_payload_support (uint8_t channel_number,
                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_payload_version (uint8_t channel_number,
                                          uint8_t payload_type,
                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_oem_payload_info (uint8_t channel_number,
                                           uint8_t payload_type,
                                           uint32_t oem_iana,
                                           uint16_t oem_payload_id,
                                           fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_RMCPPLUS_SUPPORT_AND_PAYLOAD_CMDS_H */
