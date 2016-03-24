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

#ifndef IPMI_CHASSIS_CMDS_H
#define IPMI_CHASSIS_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_POWER_RESTORE_POLICY_POWERED_OFF_AFTER_AC_RETURNS              0x00
#define IPMI_POWER_RESTORE_POLICY_POWER_RESTORED_TO_STATE                   0x01
#define IPMI_POWER_RESTORE_POLICY_POWERS_UP_AFTER_AC_RETURNS                0x02
#define IPMI_POWER_RESTORE_POLICY_UNKNOWN                                   0x03

#define IPMI_SYSTEM_POWER_IS_ON  1
#define IPMI_SYSTEM_POWER_IS_OFF 0

#define IPMI_LAST_POWER_EVENT_AC_FAILED                                     0x00
#define IPMI_LAST_POWER_EVENT_POWER_DOWN_POWER_OVERLOAD                     0x01
#define IPMI_LAST_POWER_EVENT_POWER_DOWN_INTERLOCK_ACTIVATED                0x02
#define IPMI_LAST_POWER_EVENT_POWER_DOWN_POWER_FAULT                        0x03
#define IPMI_LAST_POWER_EVENT_POWER_ON_VIA_IPMI                             0x04
#define IPMI_LAST_POWER_EVENT_UNKNOWN                                       0x05

#define IPMI_CHASSIS_CONTROL_POWER_DOWN                                     0x00
#define IPMI_CHASSIS_CONTROL_POWER_UP                                       0x01
#define IPMI_CHASSIS_CONTROL_POWER_CYCLE                                    0x02
#define IPMI_CHASSIS_CONTROL_HARD_RESET                                     0x03
#define IPMI_CHASSIS_CONTROL_PULSE_DIAGNOSTIC_INTERRUPT                     0x04
#define IPMI_CHASSIS_CONTROL_INITIATE_SOFT_SHUTDOWN                         0x05

#define IPMI_CHASSIS_CONTROL_VALID(__chassis_control)                         \
  (((__chassis_control) == IPMI_CHASSIS_CONTROL_POWER_DOWN                    \
    || (__chassis_control) == IPMI_CHASSIS_CONTROL_POWER_UP                   \
    || (__chassis_control) == IPMI_CHASSIS_CONTROL_POWER_CYCLE                \
    || (__chassis_control) == IPMI_CHASSIS_CONTROL_HARD_RESET                 \
    || (__chassis_control) == IPMI_CHASSIS_CONTROL_PULSE_DIAGNOSTIC_INTERRUPT \
    || (__chassis_control) == IPMI_CHASSIS_CONTROL_INITIATE_SOFT_SHUTDOWN) ? 1 : 0)

#define IPMI_CHASSIS_FORCE_IDENTIFY_OFF                                     0x00
#define IPMI_CHASSIS_FORCE_IDENTIFY_ON                                      0x01

#define IPMI_CHASSIS_FORCE_IDENTIFY_VALID(__force_identify) \
  (((__force_identify) == IPMI_CHASSIS_FORCE_IDENTIFY_OFF   \
    || (__force_identify) == IPMI_CHASSIS_FORCE_IDENTIFY_ON) ? 1 : 0)

#define IPMI_CHASSIS_IDENTIFY_STATE_OFF                                     0x00
#define IPMI_CHASSIS_IDENTIFY_STATE_TEMPORARY_ON                            0x01
#define IPMI_CHASSIS_IDENTIFY_STATE_INDEFINITE_ON                           0x02

/* min is degenerate "off" case */
#define IPMI_CHASSIS_IDENTIFY_INTERVAL_MIN                                  0x00
#define IPMI_CHASSIS_IDENTIFY_INTERVAL_MAX                                  0xFF

/* min is degenerate "no delay" case */
#define IPMI_CHASSIS_POWER_CYCLE_INTERVAL_MIN                                  0x00
#define IPMI_CHASSIS_POWER_CYCLE_INTERVAL_MAX                                  0xFF

/* achu: it's backwards on buttons, I don't know why */
#define IPMI_CHASSIS_BUTTON_ENABLE                                          0x00
#define IPMI_CHASSIS_BUTTON_DISABLE                                         0x01

#define IPMI_CHASSIS_BUTTON_VALID(__button)  \
  (((__button) == IPMI_CHASSIS_BUTTON_ENABLE \
    || (__button) == IPMI_CHASSIS_BUTTON_DISABLE) ? 1 : 0)

#define IPMI_CHASSIS_BUTTON_DISABLE_ALLOWED                                 0x1
#define IPMI_CHASSIS_BUTTON_DISABLE_NOT_ALLOWED                             0x0

#define IPMI_POWER_RESTORE_POLICY_ALWAYS_STAY_POWERED_OFF                   0x00
#define IPMI_POWER_RESTORE_POLICY_RESTORE_POWER_TO_STATE_WHEN_AC_WAS_LOST   0x01
#define IPMI_POWER_RESTORE_POLICY_ALWAYS_POWER_UP_AFTER_AC_IS_LOST          0x02
#define IPMI_POWER_RESTORE_POLICY_NO_CHANGE                                 0x03

#define IPMI_POWER_RESTORE_POLICY_VALID(__policy)                                      \
  (((__policy) == IPMI_POWER_RESTORE_POLICY_NO_CHANGE                                  \
    || (__policy) == IPMI_POWER_RESTORE_POLICY_ALWAYS_POWER_UP_AFTER_AC_IS_LOST        \
    || (__policy) == IPMI_POWER_RESTORE_POLICY_RESTORE_POWER_TO_STATE_WHEN_AC_WAS_LOST \
    || (__policy) == IPMI_POWER_RESTORE_POLICY_ALWAYS_STAY_POWERED_OFF) ? 1 : 0)

#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_UNKNOWN                                  0x00
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_CHASSIS_CONTROL_COMMAND                  0x01
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_RESET_VIA_PUSHBUTTON                     0x02
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_POWER_UP_VIA_POWER_PUSHBUTTON            0x03
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_WATCHDOG_EXPIRATION                      0x04
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_OEM                                      0x05
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_AUTOMATIC_POWER_UP_ALWAYS_RESTORE        0x06
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_AUTOMATIC_POWER_UP_RESTORE_PREVIOUS      0x07
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_RESET_VIA_PEF                            0x08
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_POWER_CYCLE_VIA_PEF                      0x09
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_SOFT_RESET                               0x0A
#define IPMI_CHASSIS_SYSTEM_RESTART_CAUSE_POWER_UP_VIA_RTC                         0x0B

#define IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_VALID_UNLOCKED                   0x0
#define IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_INVALID_LOCKED                   0x1

#define IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_VALID_VALID(__value)    \
  (((__value) == IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_VALID_UNLOCKED \
    || (__value) == IPMI_SYSTEM_BOOT_OPTIONS_PARAMETER_INVALID_LOCKED) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTIONS_NO_SET_SELECTOR                            0x0
#define IPMI_SYSTEM_BOOT_OPTIONS_NO_BLOCK_SELECTOR                          0x0

#define IPMI_SYSTEM_BOOT_OPTION_SET_COMPLETE                              0x00
#define IPMI_SYSTEM_BOOT_OPTION_SET_IN_PROGRESS                           0x01
#define IPMI_SYSTEM_BOOT_OPTION_SET_COMMIT_WRITE                          0x02

#define IPMI_SYSTEM_BOOT_OPTION_SET_IN_PROGRESS_VALID(__value) \
  (((__value) == IPMI_SYSTEM_BOOT_OPTION_SET_COMPLETE          \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_SET_IN_PROGRESS    \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_SET_COMMIT_WRITE) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_INVALID                         0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_VALID                           0x01

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_VALID_FOR_NEXT_BOOT             0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_VALID_PERSISTENTLY              0x01

/* achu: below is not a typo, IPMI spec orders it 0x09, 0x08, 0x0B, 0x0F */
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_NO_OVERRIDE                                              0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_PXE                                                0x01
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_HARD_DRIVE                                         0x02
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_HARD_DRIVE_SAFE_MODE                               0x03
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_DIAGNOSTIC_PARTITION                               0x04
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_CD_DVD                                             0x05
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_BIOS_SETUP                                         0x06
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_FLOPPY_PRIMARY_REMOVEABLE_MEDIA 0x07
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_PRIMARY_REMOTE_MEDIA                               0x09
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_CD_DVD                          0x08
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_HARD_DRIVE                      0x0B
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_FLOPPY_REMOVEABLE_MEDIA                            0x0F

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_VALID(__boot_device)                                                       \
  (((__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_NO_OVERRIDE                                                 \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_PXE                                                \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_HARD_DRIVE                                         \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_HARD_DRIVE_SAFE_MODE                               \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_DIAGNOSTIC_PARTITION                               \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_CD_DVD                                             \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_BIOS_SETUP                                         \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_FLOPPY_PRIMARY_REMOVEABLE_MEDIA \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_PRIMARY_REMOTE_MEDIA                               \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_CD_DVD                          \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_REMOTELY_CONNECTED_HARD_DRIVE                      \
    || (__boot_device) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_DEVICE_FORCE_FLOPPY_REMOVEABLE_MEDIA) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_DEFAULT      0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_BIOS_SETTING IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_DEFAULT
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_SUPPRESS     0x01
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_ENABLE       0x02

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_VALID(__console_redirection)       \
  (((__console_redirection) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_DEFAULT     \
    || (__console_redirection) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_SUPPRESS \
    || (__console_redirection) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_CONSOLE_REDIRECTION_ENABLE) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_NO                                        0x00
#define IPMI_SYSTEM_BOOT_OPTION_YES                                       0x01

#define IPMI_SYSTEM_BOOT_OPTION_DISABLE                                   0x00
#define IPMI_SYSTEM_BOOT_OPTION_ENABLE                                    0x01

#define IPMI_SYSTEM_BOOT_OPTION_ENABLE_VALID(__value) \
  (((__value) == IPMI_SYSTEM_BOOT_OPTION_ENABLE       \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_DISABLE) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_TYPE_PC_COMPATIBLE         0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_TYPE_EFI                   0x01

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BIOS_BOOT_TYPE_VALID(__boot_type)    \
  (((__boot_type) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_TYPE_PC_COMPATIBLE \
    || (__boot_type) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_BOOT_TYPE_EFI) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_DEFAULT 0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_QUIET   0x01
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_VERBOSE 0x02

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_VALID(__verbosity)    \
  (((__verbosity) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_DEFAULT  \
    || (__verbosity) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_QUIET \
    || (__verbosity) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAG_FIRMWARE_BIOS_VERBOSITY_VERBOSE) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_UNSPECIFIED             0x00

#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_DISCOVERED              0X01
#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_UNDISCOVERED            0X00

#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_DISCOVERED_VALID(__value) \
  (((__value) == IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_DISCOVERED  \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_UNDISCOVERED) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_SCAN                    0X01
#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_DO_NOT_SCAN             0X00

#define IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_SCAN_VALID(__value) \
  (((__value) == IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_SCAN  \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_SERVICE_PARTITION_DO_NOT_SCAN) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_ACKNOWLEDGE                     0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_INFO_UNACKNOWLEDGE                   0x01

#define IPMI_SYSTEM_BOOT_OPTION_DONT_CLEAR_VALID_BIT                      0x01
#define IPMI_SYSTEM_BOOT_OPTION_CLEAR_VALID_BIT                           0x00

#define IPMI_SYSTEM_BOOT_OPTION_CLEAR_VALID_BIT_VALID(__value) \
  (((__value) == IPMI_SYSTEM_BOOT_OPTION_DONT_CLEAR_VALID_BIT  \
    || (__value) == IPMI_SYSTEM_BOOT_OPTION_CLEAR_VALID_BIT) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_RECOMENDED_AT_END_OF_POST  0x00
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_BMC                        0x01
#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_SYSTEM                     0x02

#define IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_BIOS_MUX_CONTROL_OVERRIDE_VALID(__bios_mux_control)      \
  (((__bios_mux_control) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_RECOMENDED_AT_END_OF_POST \
    || (__bios_mux_control) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_BMC                    \
    || (__bios_mux_control) == IPMI_SYSTEM_BOOT_OPTION_BOOT_FLAGS_SET_MUX_TO_SYSTEM) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_MIN 0x00
#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_MAX 0x31

#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_RANGE_MIN 0x01
#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_RANGE_MAX 0x15

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_VALID(__value) \
  ((((__value) + 1) >= (IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_MIN + 1) \
    && (__value) <= IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_MAX) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_RANGE_VALID(__value) \
  (((__value) >= IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_RANGE_MIN \
    && (__value) <= IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_RANGE_MAX) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_DEVICE_INSTANCE_SELECTOR_INTERNAL_BITMASK 0x10 

#define IPMI_SYSTEM_BOOT_OPTION_BLOCK_DATA_LEN_MAX 16

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */
 
extern fiid_template_t tmpl_cmd_get_chassis_capabilities_rq;
extern fiid_template_t tmpl_cmd_get_chassis_capabilities_rs;
extern fiid_template_t tmpl_cmd_get_chassis_status_rq;
extern fiid_template_t tmpl_cmd_get_chassis_status_rs;
extern fiid_template_t tmpl_cmd_chassis_control_rq;
extern fiid_template_t tmpl_cmd_chassis_control_rs;
extern fiid_template_t tmpl_cmd_chassis_identify_rq;
extern fiid_template_t tmpl_cmd_chassis_identify_rs;
extern fiid_template_t tmpl_cmd_set_front_panel_enables_rq;
extern fiid_template_t tmpl_cmd_set_front_panel_enables_rs;
extern fiid_template_t tmpl_cmd_set_power_restore_policy_rq;
extern fiid_template_t tmpl_cmd_set_power_restore_policy_rs;
extern fiid_template_t tmpl_cmd_set_power_cycle_interval_rq;
extern fiid_template_t tmpl_cmd_set_power_cycle_interval_rs;
extern fiid_template_t tmpl_cmd_get_system_restart_cause_rq;
extern fiid_template_t tmpl_cmd_get_system_restart_cause_rs;

extern fiid_template_t tmpl_cmd_set_system_boot_options_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_rs;
extern fiid_template_t tmpl_cmd_set_system_boot_options_set_in_progress_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_service_partition_selector_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_service_partition_scan_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_BMC_boot_flag_valid_bit_clearing_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_boot_info_acknowledge_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_boot_flags_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_boot_initiator_info_rq;
extern fiid_template_t tmpl_cmd_set_system_boot_options_boot_initiator_mailbox_rq;

extern fiid_template_t tmpl_cmd_get_system_boot_options_rq;
extern fiid_template_t tmpl_cmd_get_system_boot_options_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_set_in_progress_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_service_partition_selector_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_service_partition_scan_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_BMC_boot_flag_valid_bit_clearing_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_boot_info_acknowledge_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_boot_flags_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_boot_initiator_info_rs;
extern fiid_template_t tmpl_cmd_get_system_boot_options_boot_initiator_mailbox_rs;

extern fiid_template_t tmpl_cmd_get_power_on_hours_counter_rq;
extern fiid_template_t tmpl_cmd_get_power_on_hours_counter_rs;

int fill_cmd_get_chassis_capabilities (fiid_obj_t obj_cmd_rq);

int fill_cmd_get_chassis_status (fiid_obj_t obj_cmd_rq);

int fill_cmd_chassis_control (uint8_t chassis_control,
                              fiid_obj_t obj_cmd_rq);

int fill_cmd_chassis_identify (const uint8_t *identify_interval,
                               const uint8_t *force_identify,
                               fiid_obj_t obj_cmd_rq);

int fill_cmd_set_front_panel_enables (uint8_t disable_power_off_button_for_power_off_only,
                                      uint8_t disable_reset_button,
                                      uint8_t disable_diagnostic_interrupt_button,
                                      uint8_t disable_standby_button_for_entering_standby,
                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_set_power_restore_policy (uint8_t power_restore_policy,
                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_power_cycle_interval (uint8_t interval,
                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_get_system_restart_cause (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options (uint8_t parameter_selector,
                                      uint8_t parameter_valid,
                                      const void *configuration_parameter_data,
                                      unsigned int configuration_parameter_data_len,
                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_set_in_progress (uint8_t parameter_valid,
                                                      uint8_t state,
                                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_service_partition_selector (uint8_t parameter_valid,
                                                                 uint8_t service_partition_selector,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_service_partition_scan (uint8_t parameter_valid,
                                                             uint8_t service_partition_discovered,
                                                             uint8_t service_partition_scan,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_BMC_boot_flag_valid_bit_clearing (uint8_t parameter_valid,
                                                                       uint8_t dont_clear_on_power_up,
                                                                       uint8_t dont_clear_on_pushbutton_or_soft_reset,
                                                                       uint8_t dont_clear_on_watchdog_timeout,
                                                                       uint8_t dont_clear_on_chassis_control,
                                                                       uint8_t dont_clear_on_PEF,
                                                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_boot_info_acknowledge (uint8_t parameter_valid,
                                                            const uint8_t *bios_or_post_handled_boot_info,
                                                            const uint8_t *os_loader_handled_boot_info,
                                                            const uint8_t *os_or_service_partition_handled_boot_info,
                                                            const uint8_t *sms_handled_boot_info,
                                                            const uint8_t *oem_handled_boot_info,
                                                            fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_boot_flags (uint8_t parameter_valid,
                                                 uint8_t bios_boot_type,
                                                 uint8_t boot_flags_persistent,
                                                 uint8_t boot_flags_valid,
                                                 uint8_t lock_out_reset_button,
                                                 uint8_t screen_blank,
                                                 uint8_t boot_device,
                                                 uint8_t lock_keyboard,
                                                 uint8_t clear_cmos,
                                                 uint8_t console_redirection,
                                                 uint8_t lock_out_sleep_button,
                                                 uint8_t user_password_bypass,
                                                 uint8_t force_progress_event_traps,
                                                 uint8_t firmware_bios_verbosity,
                                                 uint8_t lock_out_via_power_button,
                                                 uint8_t bios_mux_control_override,
                                                 uint8_t bios_shared_mode_override,
                                                 uint8_t device_instance_selector,
                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_boot_initiator_info (uint8_t parameter_valid,
                                                          uint8_t boot_source_channel_number,
                                                          uint32_t session_id,
                                                          uint32_t boot_info_timestamp,
                                                          fiid_obj_t obj_cmd_rq);

int fill_cmd_set_system_boot_options_boot_initiator_mailbox (uint8_t parameter_valid,
                                                             uint8_t set_selector,
                                                             const void *block_data,
                                                             unsigned int block_data_length,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_get_system_boot_options (uint8_t parameter_selector,
                                      uint8_t set_selector,
                                      uint8_t block_selector,
                                      fiid_obj_t obj_cmd_rq);

int fill_cmd_get_power_on_hours_counter (fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CHASSIS_CMDS_H */
