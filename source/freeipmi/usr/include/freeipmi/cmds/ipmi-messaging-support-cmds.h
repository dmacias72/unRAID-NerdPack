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

#ifndef IPMI_MESSAGING_SUPPORT_CMDS_H
#define IPMI_MESSAGING_SUPPORT_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_MAX_USER_NAME_LENGTH           16
#define IPMI_1_5_MAX_PASSWORD_LENGTH        16
#define IPMI_2_0_MAX_PASSWORD_LENGTH        20
#define IPMI_MAX_PASSWORD_LENGTH            IPMI_2_0_MAX_PASSWORD_LENGTH
#define IPMI_CHALLENGE_STRING_LENGTH        16
#define IPMI_MAX_K_R_LENGTH                 20
#define IPMI_MAX_K_G_LENGTH                 20

#define IPMI_BMC_GLOBAL_ENABLES_ENABLED     0x1
#define IPMI_BMC_GLOBAL_ENALBES_DISABLED    0x0

#define IPMI_BMC_GLOBAL_ENABLES_VALID(__val) \
  (((__val) == IPMI_BMC_GLOBAL_ENABLES_ENABLED \
    || (__val) == IPMI_BMC_GLOBAL_ENALBES_DISABLED) ? 1 : 0)

#define IPMI_MESSAGE_FLAGS_CLEAR            0x1
#define IPMI_MESSAGE_FLAGS_DONT_CLEAR       0x0

#define IPMI_MESSAGE_FLAGS_VALID(__val) \
  (((__val) == IPMI_MESSAGE_FLAGS_CLEAR \
    || (__val) == IPMI_MESSAGE_FLAGS_DONT_CLEAR) ? 1 : 0)

#define IPMI_CHANNEL_OPERATION_DISABLE_CHANNEL                  0x00
#define IPMI_CHANNEL_OPERATION_ENABLE_CHANNEL                   0x01
#define IPMI_CHANNEL_OPERATION_GET_CHANNEL_ENABLE_DISABLE_STATE 0x02

#define IPMI_CHANNEL_OPERATION_VALID(__val)             \
  (((__val) == IPMI_CHANNEL_OPERATION_DISABLE_CHANNEL   \
    || (__val) == IPMI_CHANNEL_OPERATION_ENABLE_CHANNEL \
    || (__val) == IPMI_CHANNEL_OPERATION_GET_CHANNEL_ENABLE_DISABLE_STATE) ? 1 : 0)

#define IPMI_CHANNEL_DISABLED 0x00
#define IPMI_CHANNEL_ENABLED  0x01

#define IPMI_SEND_MESSAGE_WITH_AUTHENTICATION         0x1
#define IPMI_SEND_MESSAGE_AUTHENTICATION_NOT_REQUIRED 0x0

#define IPMI_SEND_MESSAGE_AUTHENTICATION_VALID(__val) \
  (((__val) == IPMI_SEND_MESSAGE_WITH_AUTHENTICATION  \
    || (__val) == IPMI_SEND_MESSAGE_AUTHENTICATION_NOT_REQUIRED) ? 1 : 0)

#define IPMI_SEND_MESSAGE_WITH_ENCRYPTION         0x1
#define IPMI_SEND_MESSAGE_ENCRYPTION_NOT_REQUIRED 0x0

#define IPMI_SEND_MESSAGE_ENCRYPTION_VALID(__val) \
  (((__val) == IPMI_SEND_MESSAGE_WITH_ENCRYPTION  \
    || (__val) == IPMI_SEND_MESSAGE_ENCRYPTION_NOT_REQUIRED) ? 1 : 0)

#define IPMI_SEND_MESSAGE_TRACKING_OPERATION_NO_TRACKING      0x0
#define IPMI_SEND_MESSAGE_TRACKING_OPERATION_TRACKING_REQUEST 0x1
#define IPMI_SEND_MESSAGE_TRACKING_OPERATION_SEND_RAW         0x2

#define IPMI_SEND_MESSAGE_TRACKING_VALID(__val)                         \
  (((__val) == IPMI_SEND_MESSAGE_TRACKING_OPERATION_NO_TRACKING         \
    || (__val) == IPMI_SEND_MESSAGE_TRACKING_OPERATION_TRACKING_REQUEST \
    || (__val) == IPMI_SEND_MESSAGE_TRACKING_OPERATION_SEND_RAW) ? 1 : 0)

#define IPMI_SYSTEM_INTERFACE_SSIF          0x00
#define IPMI_SYSTEM_INTERFACE_KCS           0x01
#define IPMI_SYSTEM_INTERFACE_SMIC          0x02

#define IPMI_SYSTEM_INTERFACE_VALID(__val)  \
  (((__val) == IPMI_SYSTEM_INTERFACE_SSIF   \
    || (__val) == IPMI_SYSTEM_INTERFACE_KCS \
    || (__val) == IPMI_SYSTEM_INTERFACE_SMIC) ? 1 : 0)

#define IPMI_SSIF_SYSTEM_INTERFACE_VERSION_1            0x0

#define IPMI_SSIF_SYSTEM_INTERFACE_IMPLEMENTS_PEC       0x1
#define IPMI_SSIF_SYSTEM_INTERFACE_DOES_NOT_SUPPORT_PEC 0x0

#define IPMI_SSIF_SYSTEM_INTERFACE_TRANSACTION_SUPPORT_SINGLE_PART_READS_WRITES_SUPPORTED                   0x0
#define IPMI_SSIF_SYSTEM_INTERFACE_TRANSACTION_SUPPORT_MULTI_PART_READS_WRITES_SUPPORTED_START_AND_END_ONLY 0x1
#define IPMI_SSIF_SYSTEM_INTERFACE_TRANSACTION_SUPPORT_MULTI_PART_READS_WRITES_SUPPORTED_START_MIDDLE_END   0x2

#define IPMI_KCS_SYSTEM_INTERFACE_VERSION_1             0x0

#define IPMI_BUS_TYPE_PUBLIC  0x0
#define IPMI_BUS_TYPE_PRIVATE 0x1

#define IPMI_BUS_TYPE_VALID(__bus_type) \
  (((__bus_type) == IPMI_BUS_TYPE_PUBLIC \
    || (__bus_type) == IPMI_BUS_TYPE_PRIVATE) ? 1 : 0)

#define IPMI_GET_IPMI_V20_EXTENDED_DATA     0x01
#define IPMI_GET_IPMI_V15_DATA              0x00

#define IPMI_GET_IPMI_DATA_VALID(__val)        \
  (((__val) == IPMI_GET_IPMI_V20_EXTENDED_DATA \
    || (__val) == IPMI_GET_IPMI_V15_DATA) ? 1 : 0)

#define IPMI_GET_SYSTEM_INFO_PARAMETER                 0x0
#define IPMI_GET_SYSTEM_INFO_PARAMETER_REVISION_ONLY   0x1

#define IPMI_GET_SYSTEM_INFO_PARAMETER_VALID(__val) \
  (((__val) == IPMI_GET_SYSTEM_INFO_PARAMETER       \
    || (__val) == IPMI_GET_SYSTEM_INFO_PARAMETER_REVISION_ONLY) ? 1 : 0)

#define IPMI_SYSTEM_INFO_PARAMETERS_NO_SET_SELECTOR                            0x0
#define IPMI_SYSTEM_INFO_PARAMETERS_NO_BLOCK_SELECTOR                          0x0

#define IPMI_SYSTEM_INFO_PARAMETERS_SET_COMPLETE                              0x00
#define IPMI_SYSTEM_INFO_PARAMETERS_SET_IN_PROGRESS                           0x01
#define IPMI_SYSTEM_INFO_PARAMETERS_SET_COMMIT_WRITE                          0x02

#define IPMI_SYSTEM_INFO_PARAMETERS_SET_IN_PROGRESS_VALID(__value) \
  (((__value) == IPMI_SYSTEM_INFO_PARAMETERS_SET_COMPLETE          \
    || (__value) == IPMI_SYSTEM_INFO_PARAMETERS_SET_IN_PROGRESS    \
    || (__value) == IPMI_SYSTEM_INFO_PARAMETERS_SET_COMMIT_WRITE) ? 1 : 0)

#define IPMI_SYSTEM_INFO_ENCODING_ASCII_LATIN1         0x0
#define IPMI_SYSTEM_INFO_ENCODING_UTF_8                0x1
#define IPMI_SYSTEM_INFO_ENCODING_UNICODE              0x2

#define IPMI_SYSTEM_INFO_ENCODING_VALID(__val) \
  (((__val) == IPMI_SYSTEM_INFO_ENCODING_ASCII_LATIN1 \
    || (__val) == IPMI_SYSTEM_INFO_ENCODING_UTF_8 \
    || (__val) == IPMI_SYSTEM_INFO_ENCODING_UNICODE) ? 1 : 0)

#define IPMI_SYSTEM_INFO_FIRST_SET_STRING_LEN_MAX      14
#define IPMI_SYSTEM_INFO_SET_STRING_LEN_MAX            16
#define IPMI_SYSTEM_INFO_STRING_LEN_MAX               255

#define IPMI_LIST_ALGORITHMS_BY_CIPHER_SUITE 0x1
#define IPMI_LIST_SUPPORTED_ALGORITHMS       0x0

#define IPMI_LIST_ALGORITHM_TYPE_VALID(__val)       \
  (((__val) == IPMI_LIST_ALGORITHMS_BY_CIPHER_SUITE \
    || (__val) == IPMI_LIST_SUPPORTED_ALGORITHMS) ? 1 : 0)

#define IPMI_MESSAGING_ACCESS_MODE_DISABLED            0x0
#define IPMI_MESSAGING_ACCESS_MODE_PRE_BOOT_ONLY       0x1
#define IPMI_MESSAGING_ACCESS_MODE_ALWAYS_AVAILABLE    0x2
#define IPMI_MESSAGING_ACCESS_MODE_SHARED              0x3

#define IPMI_MESSAGING_ACCESS_MODE_VALID(__access_mode)               \
  (((__access_mode) == IPMI_MESSAGING_ACCESS_MODE_DISABLED            \
    || (__access_mode) == IPMI_MESSAGING_ACCESS_MODE_PRE_BOOT_ONLY    \
    || (__access_mode) == IPMI_MESSAGING_ACCESS_MODE_ALWAYS_AVAILABLE \
    || (__access_mode) == IPMI_MESSAGING_ACCESS_MODE_SHARED) ? 1 : 0)

#define IPMI_USER_LEVEL_AUTHENTICATION_ENABLE     0x0
#define IPMI_USER_LEVEL_AUTHENTICATION_DISABLE    0x1

#define IPMI_USER_LEVEL_AUTHENTICATION_VALID(__val)  \
  (((__val) == IPMI_USER_LEVEL_AUTHENTICATION_ENABLE \
    || (__val) == IPMI_USER_LEVEL_AUTHENTICATION_DISABLE) ? 1 : 0)

#define IPMI_PER_MESSAGE_AUTHENTICATION_ENABLE     0x0
#define IPMI_PER_MESSAGE_AUTHENTICATION_DISABLE    0x1

#define IPMI_PER_MESSAGE_AUTHENTICATION_VALID(__val)  \
  (((__val) == IPMI_PER_MESSAGE_AUTHENTICATION_ENABLE \
    || (__val) == IPMI_PER_MESSAGE_AUTHENTICATION_DISABLE) ? 1 : 0)

#define IPMI_PEF_ALERTING_ENABLE     0x0
#define IPMI_PEF_ALERTING_DISABLE    0x1

#define IPMI_PEF_ALERTING_VALID(__val)  \
  (((__val) == IPMI_PEF_ALERTING_ENABLE \
    || (__val) == IPMI_PEF_ALERTING_DISABLE) ? 1 : 0)

#define IPMI_CHANNEL_ACCESS_NO_CHANGE           0x0
#define IPMI_CHANNEL_ACCESS_SET_NON_VOLATILE    0x1
#define IPMI_CHANNEL_ACCESS_SET_VOLATILE        0x2
#define IPMI_CHANNEL_ACCESS_RESERVED            0x3

#define IPMI_CHANNEL_ACCESS_VALID(__access_mode)               \
  (((__access_mode) == IPMI_CHANNEL_ACCESS_NO_CHANGE           \
    || (__access_mode) == IPMI_CHANNEL_ACCESS_SET_NON_VOLATILE \
    || (__access_mode) == IPMI_CHANNEL_ACCESS_SET_VOLATILE) ? 1 : 0)

#define IPMI_PRIVILEGE_LEVEL_LIMIT_NO_CHANGE           0x0
#define IPMI_PRIVILEGE_LEVEL_LIMIT_SET_NON_VOLATILE    0x1
#define IPMI_PRIVILEGE_LEVEL_LIMIT_SET_VOLATILE        0x2
#define IPMI_PRIVILEGE_LEVEL_LIMIT_RESERVED            0x3

#define IPMI_PRIVILEGE_LEVEL_LIMIT_SET_VALID(__privilege_level_limit)           \
  (((__privilege_level_limit) == IPMI_PRIVILEGE_LEVEL_LIMIT_NO_CHANGE           \
    || (__privilege_level_limit) == IPMI_PRIVILEGE_LEVEL_LIMIT_SET_NON_VOLATILE \
    || (__privilege_level_limit) == IPMI_PRIVILEGE_LEVEL_LIMIT_SET_VOLATILE) ? 1 : 0)

#define IPMI_CHANNEL_ACCESS_GET_NON_VOLATILE    0x1
#define IPMI_CHANNEL_ACCESS_GET_VOLATILE        0x2

#define IPMI_CHANNEL_ACCESS_GET_VALID(__val)        \
  (((__val) == IPMI_CHANNEL_ACCESS_GET_NON_VOLATILE \
    || (__val) == IPMI_CHANNEL_ACCESS_GET_VOLATILE) ? 1 : 0)

#define IPMI_USER_RESTRICTED_TO_CALLBACK_ENABLE     0x1
#define IPMI_USER_RESTRICTED_TO_CALLBACK_DISABLE    0x0

#define IPMI_USER_RESTRICTED_TO_CALLBACK_VALID(__val)  \
  (((__val) == IPMI_USER_RESTRICTED_TO_CALLBACK_ENABLE \
    || (__val) == IPMI_USER_RESTRICTED_TO_CALLBACK_DISABLE) ? 1 : 0)

#define IPMI_PRIVILEGE_LEVEL_LIMIT_VALID(__privilege_level) \
  (((__privilege_level) == IPMI_PRIVILEGE_LEVEL_CALLBACK    \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_USER     \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_OPERATOR \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_ADMIN    \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_OEM      \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_NO_ACCESS) ? 1 : 0)

#define IPMI_USER_LINK_AUTHENTICATION_ENABLE     0x1
#define IPMI_USER_LINK_AUTHENTICATION_DISABLE    0x0

#define IPMI_USER_LINK_AUTHENTICATION_VALID(__val)  \
  (((__val) == IPMI_USER_LINK_AUTHENTICATION_ENABLE \
    || (__val) == IPMI_USER_LINK_AUTHENTICATION_DISABLE) ? 1 : 0)

#define IPMI_USER_IPMI_MESSAGING_ENABLE     0x1
#define IPMI_USER_IPMI_MESSAGING_DISABLE    0x0

#define IPMI_USER_IPMI_MESSAGING_VALID(__val)  \
  (((__val) == IPMI_USER_IPMI_MESSAGING_ENABLE \
    || (__val) == IPMI_USER_IPMI_MESSAGING_DISABLE) ? 1 : 0)

#define IPMI_CHANGE_BITS_YES   0x1
#define IPMI_CHANGE_BITS_NO    0x0

#define IPMI_CHANGE_BITS_VALID(__val)  \
  (((__val) == IPMI_CHANGE_BITS_YES \
    || (__val) == IPMI_CHANGE_BITS_NO) ? 1 : 0)

#define IPMI_SESSION_SUPPORT_SESSION_LESS   0x00
#define IPMI_SESSION_SUPPORT_SINGLE_SESSION 0x01
#define IPMI_SESSION_SUPPORT_MULTI_SESSION  0x02
#define IPMI_SESSION_SUPPORT_SESSION_BASED  0x03

#define IPMI_CHANNEL_SECURITY_KEYS_OPERATION_READ_KEY 0x0
#define IPMI_CHANNEL_SECURITY_KEYS_OPERATION_SET_KEY  0x1
#define IPMI_CHANNEL_SECURITY_KEYS_OPERATION_LOCK_KEY 0x2

#define IPMI_CHANNEL_SECURITY_KEYS_OPERATION_VALID(__val)      \
  (((__val) == IPMI_CHANNEL_SECURITY_KEYS_OPERATION_READ_KEY   \
    || (__val) == IPMI_CHANNEL_SECURITY_KEYS_OPERATION_SET_KEY \
    || (__val) == IPMI_CHANNEL_SECURITY_KEYS_OPERATION_LOCK_KEY) ? 1 : 0)

#define IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_R    0x0
#define IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_G    0x1

#define IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_VALID(__val) \
  (((__val) == IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_R   \
    || (__val) == IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_G) ? 1 : 0)

#define IPMI_CHANNEL_SECURITY_KEYS_LOCK_STATUS_KEY_IS_NOT_LOCKABLE 0x0
#define IPMI_CHANNEL_SECURITY_KEYS_LOCK_STATUS_KEY_IS_LOCKED       0x1
#define IPMI_CHANNEL_SECURITY_KEYS_LOCK_STATUS_KEY_IS_UNLOCKED     0x2

#define IPMI_PASSWORD_OPERATION_DISABLE_USER     0x0
#define IPMI_PASSWORD_OPERATION_ENABLE_USER      0x1
#define IPMI_PASSWORD_OPERATION_SET_PASSWORD     0x2
#define IPMI_PASSWORD_OPERATION_TEST_PASSWORD    0x3

#define IPMI_PASSWORD_OPERATION_VALID(__operation)           \
  (((__operation) == IPMI_PASSWORD_OPERATION_DISABLE_USER    \
    || (__operation) == IPMI_PASSWORD_OPERATION_ENABLE_USER  \
    || (__operation) == IPMI_PASSWORD_OPERATION_SET_PASSWORD \
    || (__operation) == IPMI_PASSWORD_OPERATION_TEST_PASSWORD) ? 1 : 0)

#define IPMI_PASSWORD_SIZE_16_BYTES 0x0
#define IPMI_PASSWORD_SIZE_20_BYTES 0x1

#define IPMI_PASSWORD_SIZE_VALID(__password_size)    \
  (((__password_size) == IPMI_PASSWORD_SIZE_16_BYTES \
    || (__password_size) == IPMI_PASSWORD_SIZE_20_BYTES) ? 1 : 0)

#define IPMI_USER_ID_ENABLE_STATUS_UNSPECIFIED 0x0
#define IPMI_USER_ID_ENABLE_STATUS_ENABLED     0x1
#define IPMI_USER_ID_ENABLE_STATUS_DISABLED    0x2

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_set_bmc_global_enables_rq;
extern fiid_template_t tmpl_cmd_set_bmc_global_enables_rs;
extern fiid_template_t tmpl_cmd_get_bmc_global_enables_rq;
extern fiid_template_t tmpl_cmd_get_bmc_global_enables_rs;

extern fiid_template_t tmpl_cmd_clear_message_flags_rq;
extern fiid_template_t tmpl_cmd_clear_message_flags_rs;
extern fiid_template_t tmpl_cmd_get_message_flags_rq;
extern fiid_template_t tmpl_cmd_get_message_flags_rs;
extern fiid_template_t tmpl_cmd_enable_message_channel_receive_rq;
extern fiid_template_t tmpl_cmd_enable_message_channel_receive_rs;
extern fiid_template_t tmpl_cmd_get_message_rq;
extern fiid_template_t tmpl_cmd_get_message_rs;
extern fiid_template_t tmpl_cmd_send_message_rq;
extern fiid_template_t tmpl_cmd_send_message_rs;
extern fiid_template_t tmpl_cmd_read_event_message_buffer_rq;
extern fiid_template_t tmpl_cmd_read_event_message_buffer_rs;

extern fiid_template_t tmpl_cmd_get_system_interface_capabilities_rq;
extern fiid_template_t tmpl_cmd_get_system_interface_capabilities_rs;
extern fiid_template_t tmpl_cmd_get_system_interface_capabilities_ssif_rs;
extern fiid_template_t tmpl_cmd_get_system_interface_capabilities_kcs_rs;
extern fiid_template_t tmpl_cmd_get_bt_interface_capabilities_rq;
extern fiid_template_t tmpl_cmd_get_bt_interface_capabilities_rs;
extern fiid_template_t tmpl_cmd_master_write_read_rq;
extern fiid_template_t tmpl_cmd_master_write_read_rs;

extern fiid_template_t tmpl_cmd_get_channel_authentication_capabilities_rq;
extern fiid_template_t tmpl_cmd_get_channel_authentication_capabilities_rs;

extern fiid_template_t tmpl_cmd_get_system_guid_rq;
extern fiid_template_t tmpl_cmd_get_system_guid_rs;
extern fiid_template_t tmpl_cmd_get_device_guid_format_rs;

extern fiid_template_t tmpl_cmd_set_system_info_parameters_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_rs;

extern fiid_template_t tmpl_cmd_set_system_info_parameters_set_in_progress_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_system_firmware_version_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_system_firmware_version_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_system_name_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_system_name_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_primary_operating_system_name_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_primary_operating_system_name_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_operating_system_name_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_operating_system_name_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_present_os_version_number_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_present_os_version_number_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_bmc_url_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_bmc_url_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_base_os_hypervisor_url_first_set_rq;
extern fiid_template_t tmpl_cmd_set_system_info_parameters_base_os_hypervisor_url_rq;

extern fiid_template_t tmpl_cmd_get_system_info_parameters_rq;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_rs;

extern fiid_template_t tmpl_cmd_get_system_info_parameters_set_in_progress_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_system_firmware_version_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_system_firmware_version_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_system_name_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_system_name_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_primary_operating_system_name_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_primary_operating_system_name_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_operating_system_name_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_operating_system_name_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_present_os_version_number_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_present_os_version_number_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_bmc_url_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_bmc_url_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_base_os_hypervisor_url_first_set_rs;
extern fiid_template_t tmpl_cmd_get_system_info_parameters_base_os_hypervisor_url_rs;

extern fiid_template_t tmpl_cmd_get_channel_cipher_suites_rq;
extern fiid_template_t tmpl_cmd_get_channel_cipher_suites_rs;

extern fiid_template_t tmpl_cmd_get_session_challenge_rq;
extern fiid_template_t tmpl_cmd_get_session_challenge_rs;
extern fiid_template_t tmpl_cmd_activate_session_rq;
extern fiid_template_t tmpl_cmd_activate_session_rs;
extern fiid_template_t tmpl_cmd_set_session_privilege_level_rq;
extern fiid_template_t tmpl_cmd_set_session_privilege_level_rs;
extern fiid_template_t tmpl_cmd_close_session_rq;
extern fiid_template_t tmpl_cmd_close_session_rs;

extern fiid_template_t tmpl_cmd_set_channel_access_rq;
extern fiid_template_t tmpl_cmd_set_channel_access_rs;
extern fiid_template_t tmpl_cmd_get_channel_access_rq;
extern fiid_template_t tmpl_cmd_get_channel_access_rs;
extern fiid_template_t tmpl_cmd_get_channel_info_rq;
extern fiid_template_t tmpl_cmd_get_channel_info_rs;

extern fiid_template_t tmpl_cmd_set_channel_security_keys_rq;
extern fiid_template_t tmpl_cmd_set_channel_security_keys_rs;
extern fiid_template_t tmpl_cmd_set_user_access_rq;
extern fiid_template_t tmpl_cmd_set_user_access_rs;
extern fiid_template_t tmpl_cmd_get_user_access_rq;
extern fiid_template_t tmpl_cmd_get_user_access_rs;

extern fiid_template_t tmpl_cmd_set_user_name_rq;
extern fiid_template_t tmpl_cmd_set_user_name_rs;

extern fiid_template_t tmpl_cmd_get_user_name_rq;
extern fiid_template_t tmpl_cmd_get_user_name_rs;

extern fiid_template_t tmpl_cmd_set_user_password_rq;
extern fiid_template_t tmpl_cmd_set_user_password_rs;

int fill_cmd_set_bmc_global_enables (uint8_t receive_message_queue_interrupt,
                                     uint8_t event_message_buffer_full_interrupt,
                                     uint8_t event_message_buffer,
                                     uint8_t system_event_logging,
                                     uint8_t oem_0,
                                     uint8_t oem_1,
                                     uint8_t oem_2,
                                     fiid_obj_t obj_cmd_rq);

int fill_cmd_get_bmc_global_enables (fiid_obj_t obj_cmd_rq);

int fill_cmd_clear_message_flags (uint8_t receive_message_queue,
                                  uint8_t event_message_buffer,
                                  uint8_t watchdog_pre_timeout_interrupt_flag,
                                  uint8_t oem_0,
                                  uint8_t oem_1,
                                  uint8_t oem_2,
                                  fiid_obj_t obj_cmd_rq);

int fill_cmd_get_message_flags (fiid_obj_t obj_cmd_rq);

int fill_cmd_enable_message_channel_receive (uint8_t channel_number,
                                             uint8_t channel_operation,
                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_get_message (fiid_obj_t obj_cmd_rq);

int fill_cmd_send_message (uint8_t channel_number,
                           uint8_t message_authentication,
                           uint8_t message_encryption,
                           uint8_t tracking_operation,
                           const void *message_data,
                           unsigned int message_data_len,
                           fiid_obj_t obj_cmd_rq);

int fill_cmd_read_event_message_buffer (fiid_obj_t obj_cmd_rq);

int fill_cmd_get_system_interface_capabilities (uint8_t system_interface,
                                                fiid_obj_t obj_cmd_rq);

int fill_cmd_get_bt_interface_capabilities (fiid_obj_t obj_cmd_rq);

int fill_cmd_master_write_read (uint8_t bus_type,
                                uint8_t bus_id,
                                uint8_t channel_number,
                                uint8_t slave_address,
                                uint8_t read_count,
                                const void *data,
                                unsigned int data_len,
                                fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_authentication_capabilities (uint8_t channel_number,
                                                      uint8_t maximum_privilege_level,
                                                      uint8_t get_ipmi_v20_extended_data,
                                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_get_system_guid (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters (uint8_t parameter_selector,
                                         const void *configuration_parameter_data,
                                         unsigned int configuration_parameter_data_len,
                                         fiid_obj_t obj_cmd_rq);
  
int fill_cmd_set_system_info_parameters_set_in_progress (uint8_t state,
                                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_system_firmware_version_first_set (uint8_t set_selector,
                                                                           uint8_t encoding,
                                                                           uint8_t string_length,
                                                                           const void *string_block,
                                                                           unsigned int string_block_length,
                                                                           fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_system_firmware_version (uint8_t set_selector,
                                                                 const void *string_block,
                                                                 unsigned int string_block_length,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_system_name_first_set (uint8_t set_selector,
                                                               uint8_t encoding,
                                                               uint8_t string_length,
                                                               const void *string_block,
                                                               unsigned int string_block_length,
                                                               fiid_obj_t obj_cmd_rq);
  
int fill_cmd_set_system_info_parameters_system_name (uint8_t set_selector,
                                                     const void *string_block,
                                                     unsigned int string_block_length,
                                                     fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_primary_operating_system_name_first_set (uint8_t set_selector,
                                                                                 uint8_t encoding,
                                                                                 uint8_t string_length,
                                                                                 const void *string_block,
                                                                                 unsigned int string_block_length,
                                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_primary_operating_system_name (uint8_t set_selector,
                                                                       const void *string_block,
                                                                       unsigned int string_block_length,
                                                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_operating_system_name_first_set (uint8_t set_selector,
                                                                         uint8_t encoding,
                                                                         uint8_t string_length,
                                                                         const void *string_block,
                                                                         unsigned int string_block_length,
                                                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_operating_system_name (uint8_t set_selector,
                                                               const void *string_block,
                                                               unsigned int string_block_length,
                                                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_present_os_version_number_first_set (uint8_t set_selector,
									     uint8_t encoding,
									     uint8_t string_length,
									     const void *string_block,
									     unsigned int string_block_length,
									     fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_present_os_version_number (uint8_t set_selector,
								   const void *string_block,
								   unsigned int string_block_length,
								   fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_bmc_url_first_set (uint8_t set_selector,
							   uint8_t encoding,
							   uint8_t string_length,
							   const void *string_block,
							   unsigned int string_block_length,
							   fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_bmc_url (uint8_t set_selector,
						 const void *string_block,
						 unsigned int string_block_length,
						 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_base_os_hypervisor_url_first_set (uint8_t set_selector,
									  uint8_t encoding,
									  uint8_t string_length,
									  const void *string_block,
									  unsigned int string_block_length,
									  fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_info_parameters_base_os_hypervisor_url (uint8_t set_selector,
								const void *string_block,
								unsigned int string_block_length,
								fiid_obj_t obj_cmd_rq);
  
int fill_cmd_get_system_info_parameters (uint8_t get_parameter,
                                         uint8_t parameter_selector,
                                         uint8_t set_selector,
                                         uint8_t block_selector,
                                         fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_cipher_suites (uint8_t channel_number,
                                        uint8_t payload_type,
                                        uint8_t list_index,
                                        uint8_t list_algorithm_type,
                                        fiid_obj_t obj_cmd_rq);

int fill_cmd_get_session_challenge (uint8_t authentication_type,
                                    const char *user_name,
                                    unsigned int user_name_len,
                                    fiid_obj_t obj_cmd_rq);

int fill_cmd_activate_session (uint8_t authentication_type,
                               uint8_t maximum_privilege_level,
                               const void *challenge_string,
                               unsigned int challenge_string_len,
                               uint32_t initial_outbound_sequence_number,
                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_session_privilege_level (uint8_t privilege_level,
                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_close_session (uint32_t session_id,
                            uint8_t *session_handle,
                            fiid_obj_t obj_cmd_rq);

int fill_cmd_set_channel_access (uint8_t channel_number,
                                 uint8_t ipmi_messaging_access_mode,
                                 uint8_t user_level_authentication,
                                 uint8_t per_message_authentication,
                                 uint8_t pef_alerting,
                                 uint8_t channel_access_set,
                                 uint8_t channel_privilege_level_limit,
                                 uint8_t channel_privilege_level_limit_set,
                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_access (uint8_t channel_number,
                                 uint8_t channel_access_get,
                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_get_channel_info (uint8_t channel_number, fiid_obj_t obj_cmd_rq);

int fill_cmd_set_channel_security_keys (uint8_t channel_number,
                                        uint8_t operation,
                                        uint8_t key_id,
                                        const void *key_value,
                                        unsigned int key_value_len,
                                        fiid_obj_t obj_cmd_rq);

int fill_cmd_set_user_access (uint8_t channel_number,
                              uint8_t user_ipmi_messaging,
                              uint8_t user_link_authentication,
                              uint8_t user_restricted_to_callback,
                              uint8_t change_bits_in_byte,
                              uint8_t user_id,
                              uint8_t user_privilege_level_limit,
                              uint8_t user_session_limit,
                              fiid_obj_t obj_cmd_rq);

int fill_cmd_get_user_access (uint8_t channel_number,
                              uint8_t user_id,
                              fiid_obj_t obj_cmd_rq);

int fill_cmd_set_user_name (uint8_t user_id,
                            const char *user_name,
                            unsigned int user_name_len,
                            fiid_obj_t obj_cmd_rq);

int fill_cmd_get_user_name (uint8_t user_id, fiid_obj_t obj_cmd_rq);

int fill_cmd_set_user_password (uint8_t user_id,
                                uint8_t password_size,
                                uint8_t operation,
                                const char *password,
                                unsigned int password_len,
                                fiid_obj_t obj_cmd_rq);


#ifdef __cplusplus
}
#endif

#endif /* IPMI_MESSAGING_SUPPORT_CMDS_H */
