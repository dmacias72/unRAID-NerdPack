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

#ifndef IPMI_BMC_WATCHDOG_TIMER_CMDS_H
#define IPMI_BMC_WATCHDOG_TIMER_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_BIOS_FRB2                        0x1
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_BIOS_POST                        0x2
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_OS_LOAD                          0x3
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_SMS_OS                           0x4
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_OEM                              0x5

#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_VALID(__x)        \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_BIOS_FRB2    \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_BIOS_POST \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_OS_LOAD   \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_SMS_OS    \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_OEM) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_STOP_TIMER_ENABLE                          0x0
#define IPMI_BMC_WATCHDOG_TIMER_STOP_TIMER_DISABLE                         0x1

#define IPMI_BMC_WATCHDOG_TIMER_STOP_TIMER_VALID(__x)  \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_STOP_TIMER_ENABLE \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_STOP_TIMER_DISABLE) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_LOG_ENABLE                                 0x0
#define IPMI_BMC_WATCHDOG_TIMER_LOG_DISABLE                                0x1

#define IPMI_BMC_WATCHDOG_TIMER_LOG_VALID(__x)  \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_LOG_ENABLE \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_LOG_DISABLE) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_NO_ACTION                   0x0
#define IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_HARD_RESET                  0x1
#define IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_POWER_DOWN                  0x2
#define IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_POWER_CYCLE                 0x3

#define IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_VALID(__x)         \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_NO_ACTION     \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_HARD_RESET \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_POWER_DOWN \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMEOUT_ACTION_POWER_CYCLE) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_NONE                 0x0
#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_SMI                  0x1
#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_NMI                  0x2
#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_MESSAGING_INTERRUPT  0x3

#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_VALID(__x)  \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_NONE   \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_SMI \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_NMI \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERRUPT_MESSAGING_INTERRUPT) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_EXPIRATION_CLEAR_TIMER_EXPIRATION_BIT  0x1
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_EXPIRATION_LEAVE_ALONE                 0x0

#define IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_EXPIRATION_VALID(__x)                      \
  (((__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_EXPIRATION_CLEAR_TIMER_EXPIRATION_BIT \
    || (__x) == IPMI_BMC_WATCHDOG_TIMER_TIMER_USE_EXPIRATION_LEAVE_ALONE) ? 1 : 0)

#define IPMI_BMC_WATCHDOG_TIMER_TIMER_STATE_RUNNING                        0x1
#define IPMI_BMC_WATCHDOG_TIMER_TIMER_STATE_STOPPED                        0x0

#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERVAL_MIN  0x00
#define IPMI_BMC_WATCHDOG_TIMER_PRE_TIMEOUT_INTERVAL_MAX  0xFF

#define IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MIN  0x0000
#define IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MAX  0xFFFF

#define IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MIN_SECONDS  IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MIN
#define IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MAX_SECONDS  (IPMI_BMC_WATCHDOG_TIMER_INITIAL_COUNTDOWN_MAX/10)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_reset_watchdog_timer_rq;
extern fiid_template_t tmpl_cmd_reset_watchdog_timer_rs;
extern fiid_template_t tmpl_cmd_set_watchdog_timer_rq;
extern fiid_template_t tmpl_cmd_set_watchdog_timer_rs;
extern fiid_template_t tmpl_cmd_get_watchdog_timer_rq;
extern fiid_template_t tmpl_cmd_get_watchdog_timer_rs;

int fill_cmd_reset_watchdog_timer (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_watchdog_timer (uint8_t timer_use,
                                 uint8_t stop_timer,
                                 uint8_t log,
                                 uint8_t timeout_action,
                                 uint8_t pre_timeout_interrupt,
                                 uint8_t pre_timeout_interval,
                                 uint8_t timer_use_expiration_flag_bios_frb2,
                                 uint8_t timer_use_expiration_flag_bios_post,
                                 uint8_t timer_use_expiration_flag_os_load,
                                 uint8_t timer_use_expiration_flag_sms_os,
                                 uint8_t timer_use_expiration_flag_oem,
                                 uint16_t initial_countdown_value,
                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_get_watchdog_timer (fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_BMC_WATCHDOG_TIMER_CMDS_H */
