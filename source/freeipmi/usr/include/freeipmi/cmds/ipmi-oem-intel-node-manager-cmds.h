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

#ifndef IPMI_OEM_INTEL_NODE_MANAGER_CMDS_H
#define IPMI_OEM_INTEL_NODE_MANAGER_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

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

#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_MIN 0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_MAX 0xF

#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_ENTIRE_PLATFORM         0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_CPU_SUBSYSTEM           0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_MEMORY_SUBSYSTEM        0x02
#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_RESERVED                0x03
#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_HIGH_POWER_IO_SUBSYSTEM 0x04

#define IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_ENTIRE_PLATFORM \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_CPU_SUBSYSTEM \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_MEMORY_SUBSYSTEM \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_DOMAIN_ID_HIGH_POWER_IO_SUBSYSTEM) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_GLOBAL_DISABLE_NODE_MANAGER_POLICY_CONTROL 0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_GLOBAL_ENABLE_NODE_MANAGER_POLICY_CONTROL  0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_DOMAIN_DISABLE_NODE_MANAGER_POLICIES   0x02
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_DOMAIN_ENABLE_NODE_MANAGER_POLITICES   0x03
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_POLICY_DISABLE_NODE_MANAGER_POLICIES   0x04
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_POLICY_ENABLE_NODE_MANAGER_POLITICES   0x05

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_VALID(__val)  \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_GLOBAL_DISABLE_NODE_MANAGER_POLICY_CONTROL \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_GLOBAL_ENABLE_NODE_MANAGER_POLICY_CONTROL \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_DOMAIN_DISABLE_NODE_MANAGER_POLICIES \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_DOMAIN_ENABLE_NODE_MANAGER_POLITICES \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_POLICY_DISABLE_NODE_MANAGER_POLICIES \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLE_DISABLE_PER_POLICY_ENABLE_NODE_MANAGER_POLITICES) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLED  0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_DISABLED 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLED_VALID(__val)         \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ENABLED               \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_DISABLED) ? 1 : 0)

/* Celsius */
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_NO_POLICY_TRIGGER                      0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_INLET_TEMPERATURE_LIMIT_POLICY_TRIGGER 0x1
/* 1/10 seconds units */
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_MISSING_POWER_READING_TIMEOUT          0x2
/* 1/10 seconds units */
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_TIME_AFTER_PLATFORM_RESET_TRIGGER      0x3
/* Only to domain 0 = Entire Platform */
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_BOOT_TIME_POLICY                       0x4

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_VALID(__val)    \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_NO_POLICY_TRIGGER \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_INLET_TEMPERATURE_LIMIT_POLICY_TRIGGER \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_MISSING_POWER_READING_TIMEOUT \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_TIME_AFTER_PLATFORM_RESET_TRIGGER \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TRIGGER_TYPE_BOOT_TIME_POLICY) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CONFIGURATION_ACTION_POLICY_POINTED_BY_POLICY_ID_SHALL_BE_REMOVED 0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CONFIGURATION_ACTION_ADD_POWER_POLICY                             0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CONFIGURATION_ACTION_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CONFIGURATION_ACTION_POLICY_POINTED_BY_POLICY_ID_SHALL_BE_REMOVED \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CONFIGURATION_ACTION_ADD_POWER_POLICY) ? 1 : 0)

/* achu: not in spec, assume it to be true */
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_EXCEPTION_ACTION_ENABLE  0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_EXCEPTION_ACTION_DISABLE 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_EXCEPTION_ACTION_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_EXCEPTION_ACTION_ENABLE \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_EXCEPTION_ACTION_DISABLE) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_PER_DOMAIN_NODE_MANAGER_POLICY_CONTROL_ENABLED  0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_PER_DOMAIN_NODE_MANAGER_POLICY_CONTROL_DISABLED 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_GLOBAL_NODE_MANAGER_POLICY_CONTROL_ENABLED  0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_GLOBAL_NODE_MANAGER_POLICY_CONTROL_DISABLED 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_CREATED_AND_MANAGED_BY_OTHER_MANAGEMENT     0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_NOT_CREATED_AND_MANAGED_BY_OTHER_MANAGEMENT 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_AUTOMATIC      0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_NON_AGGRESSIVE 0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_AGGRESSIVE     0x02

#define IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_AUTOMATIC \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_NON_AGGRESSIVE \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_AGGRESSIVE_CPU_POWER_CORRECTION_AGGRESSIVE) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_STORAGE_PERSISTENT_STORAGE 0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_STORAGE_VOLATILE_MEMORY    0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_STORAGE_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_STORAGE_PERSISTENT_STORAGE \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_STORAGE_VOLATILE_MEMORY) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_PLATFORM_BOOTING_MODE_BOOT_IN_POWER_OPTIMIZED_MODE       0
#define IPMI_OEM_INTEL_NODE_MANAGER_PLATFORM_BOOTING_MODE_BOOT_IN_PERFORMANCE_OPTIMIZED_MODE 1

#define IPMI_OEM_INTEL_NODE_MANAGER_PLATFORM_BOOTING_MODE_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_PLATFORM_BOOTING_MODE_BOOT_IN_POWER_OPTIMIZED_MODE \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_PLATFORM_BOOTING_MODE_BOOT_IN_PERFORMANCE_OPTIMIZED_MODE) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TYPE_POWER_CONTROL_POLICY 0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TYPE_VALID(__val)            \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_TYPE_POWER_CONTROL_POLICY) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_POWER_DOMAIN_POWER_PRIMARY_SIDE_POWER_DOMAIN 0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_POWER_DOMAIN_POWER_SECONDARY_SIDE_POWER_DOMAIN 0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_POWER_DOMAIN_VALID(__val)            \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_POWER_DOMAIN_POWER_PRIMARY_SIDE_POWER_DOMAIN \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_POLICY_POWER_DOMAIN_POWER_SECONDARY_SIDE_POWER_DOMAIN) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ALERT_THRESHOLDS_MAX 3

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_START_TIME_MIN 0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_START_TIME_MAX 239

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_START_TIME_VALID(__val) \
  ((((__val) + 1) >= (IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_START_TIME_MIN + 1) \
    && (__val) <= IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_START_TIME_MAX) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_STOP_TIME_MIN 0
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_STOP_TIME_MAX 240

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_STOP_TIME_VALID(__val) \
  ((((__val) + 1) >= (IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_STOP_TIME_MIN + 1) \
    && (__val) <= IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_STOP_TIME_MAX) ? 1 : 0)

/* achu: not in spec, assume it to be true */
#define IPMI_OEM_INTEL_NODE_MANAGER_REPEAT_THE_SUSPEND_PERIOD        0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_DO_NOT_REPEAT_THE_SUSPEND_PERIOD 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_SUSPEND_PERIOD_VALID(__val)         \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_REPEAT_THE_SUSPEND_PERIOD    \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_DO_NOT_REPEAT_THE_SUSPEND_PERIOD) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_SUSPEND_PERIODS_MAX 5

#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_RESET_GLOBAL_STATISTICS                   0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_PER_POLICY_STATISTICS                     0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_GLOBAL_HOST_UNHANDLED_REQUESTS_STATISTICS 0x1B
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_HOST_RESPONSE_TIME_STATISTICS             0x1C
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_CPU_THROTTLING_STATISTICS                 0x1D
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_MEMORY_THROTTLING_STATISTICS              0x1E
#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_HOST_COMMUNICATION_FAILURE_STATISTICS     0x1F

#define IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_VALID(__val)             \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_RESET_GLOBAL_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_PER_POLICY_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_GLOBAL_HOST_UNHANDLED_REQUESTS_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_HOST_RESPONSE_TIME_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_CPU_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_MEMORY_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_RESET_MODE_HOST_COMMUNICATION_FAILURE_STATISTICS) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_POWER_STATISTICS                      0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_INLET_TEMPERATURE_STATISTICS          0x02
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_THROTTLING_STATISTICS                 0x03
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_VOLUMETRIC_AIRFLOW_STATISTICS         0x04
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_OUTLET_AIRFLOW_TEMPERATURE_STATISTICS 0x05
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_CHASSIS_POWER_STATISTICS              0x06
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_POWER_STATISTICS                  0x11
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_TRIGGER_STATISTICS                0x12
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_THROTTLING_STATISTICS             0x13
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_UNHANDLED_REQUESTS_STATISTICS    0x1B
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_RESPONSE_TIME_STATISTICS         0x1C
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_CPU_THROTTLING_STATISTICS             0x1D
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_MEMORY_THROTTLING_STATISTICS          0x1E
#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_COMMUNICATION_FAILURE_STATISTICS 0x1F

#define IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_VALID(__val)        \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_POWER_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_INLET_TEMPERATURE_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_VOLUMETRIC_AIRFLOW_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_OUTLET_AIRFLOW_TEMPERATURE_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_CHASSIS_POWER_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_POWER_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_TRIGGER_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_PER_POLICY_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_UNHANDLED_REQUESTS_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_RESPONSE_TIME_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_CPU_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_MEMORY_THROTTLING_STATISTICS \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_STATISTICS_MODE_GLOBAL_HOST_COMMUNICATION_FAILURE_STATISTICS) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_GLOBAL_ADMINISTRATIVE_STATE_ENABLED   0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_GLOBAL_ADMINISTRATIVE_STATE_OTHERWISE 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_OPERATIONAL_STATE_ACTIVELY_MONITORING_DEFINED_TRIGGER 0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_OPERATIONAL_STATE_SUSPENDED                           0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_MEASUREMENTS_STATE_IN_PROGRESS 0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_MEASUREMENTS_STATE_SUSPENDED   0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ACTIVATION_STATE_TRIGGERED_AND_ACTIVELY_LIMITING_TARGET 0x1
#define IPMI_OEM_INTEL_NODE_MANAGER_POLICY_ACTIVATION_STATE_NOT_TRIGGERED                          0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_LIMITING_TYPE_PLATFORM_POWER_LIMITING 0 /* Legacy, no longer in 2.0 spec */
#define IPMI_OEM_INTEL_NODE_MANAGER_LIMITING_TYPE_CPU_POWER_LIMITING      1 /* Legacy, no longer in 2.0 spec */

#define IPMI_OEM_INTEL_NODE_MANAGER_LIMITING_BASED_ON_WALL_INPUT_POWER_PSU_INPUT_POWER           0
#define IPMI_OEM_INTEL_NODE_MANAGER_LIMITING_BASED_ON_DC_POWER_PSU_OUTPUT_POWER_OR_BLADED_SYSTEM 1

#define IPMI_OEM_INTEL_NODE_MANAGER_VERSION_1_0 0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_VERSION_1_5 0x02
#define IPMI_OEM_INTEL_NODE_MANAGER_VERSION_2_0 0x03
#define IPMI_OEM_INTEL_NODE_MANAGER_VERSION_2_5 0x04
#define IPMI_OEM_INTEL_NODE_MANAGER_VERSION_3_0 0x05

#define IPMI_OEM_INTEL_NODE_MANAGER_IPMI_INTERFACE_VERSION_1_0 0x01
#define IPMI_OEM_INTEL_NODE_MANAGER_IPMI_INTERFACE_VERSION_2_0 0x02
#define IPMI_OEM_INTEL_NODE_MANAGER_IPMI_INTERFACE_VERSION_3_0 0x03

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_REGISTER_ALERT_RECEIVER   0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_UNREGISTER_ALERT_RECEIVER 0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_VALID(__val) \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_REGISTER_ALERT_RECEIVER \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_UNREGISTER_ALERT_RECEIVER) ? 1 : 0)

/* legacy names */
#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_INFORMATION_OPERATION_REGISTER_ALERT_RECEIVER   IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_REGISTER_ALERT_RECEIVER
#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_INFORMATION_OPERATION_UNREGISTER_ALERT_RECEIVER IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_UNREGISTER_ALERT_RECEIVER

#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_INFORMATION_OPERATION_VALID(__val) \
  IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_VALID((__val))

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_USE_VOLATILE_ALERT_STRING 0x00

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_MIN 0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_MAX 0x7F

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_VALID(__val)  \
  ((((__val) + 1) >= (IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_MIN + 1) \
    && (__val) <= IPMI_OEM_INTEL_NODE_MANAGER_ALERT_STRING_SELECTOR_MAX) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_DONT_SEND_AN_ALERT_STRING                       0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_SEND_ALERT_STRING_IDENTIFIED_BY_STRING_SELECTOR 0x1

#define IPMI_OEM_INTEL_NODE_MANAGER_SEND_ALERT_STRING_VALID(__val)      \
  (((__val) == IPMI_OEM_INTEL_NODE_MANAGER_DONT_SEND_AN_ALERT_STRING    \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_SEND_ALERT_STRING_IDENTIFIED_BY_STRING_SELECTOR) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_CONFIGURATION_VALID   0x0
#define IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_CONFIGURATION_INVALID 0x1

/* legacy names */
#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_INFORMATION_OPERATION_CONFIGURATION_VALID   IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_CONFIGURATION_VALID
#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_INFORMATION_OPERATION_CONFIGURATION_INVALID IPMI_OEM_INTEL_NODE_MANAGER_ALERT_RECEIVER_DEACTIVATION_CONFIGURATION_INVALID

#define IPMI_OEM_INTEL_NODE_MANAGER_DESTINATION_SELECTOR_OPERATOR_USE_VOLATILE_DESTINATION_INFO 0x0

#define IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_MIN 0 
#define IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_MAX 7
#define IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_ALL_SOCKETS 0xFF

#define IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_VALID(__val) \
  ((((__val) >= IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_MIN   \
     && (__val) <= IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_MAX) \
    || (__val) == IPMI_OEM_INTEL_NODE_MANAGER_CPU_SOCKET_ALL_SOCKETS) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_ACTIVE_CORES_CONFIGURATION_RESERVED                                         0x00
#define IPMI_OEM_INTEL_NODE_MANAGER_ACTIVE_CORES_CONFIGURATION_APPLY_SETTINGS_TO_ALL_ACTIVE_CORES_CONFIGURATION 0xFF

#define IPMI_OEM_INTEL_NODE_MANAGER_SET_ACTIVE_CORES_CONFIGURATION_VALID(__val) \
  (((__val) != IPMI_OEM_INTEL_NODE_MANAGER_ACTIVE_CORES_CONFIGURATION_RESERVED \
    && ((__val) == IPMI_OEM_INTEL_NODE_MANAGER_ACTIVE_CORES_CONFIGURATION_APPLY_SETTINGS_TO_ALL_ACTIVE_CORES_CONFIGURATION \
	|| (__val) > 0)) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_GET_ACTIVE_CORES_CONFIGURATION_VALID(__val) \
  (((__val) != IPMI_OEM_INTEL_NODE_MANAGER_ACTIVE_CORES_CONFIGURATION_RESERVED) ? 1 : 0)

#define IPMI_OEM_INTEL_NODE_MANAGER_TURBO_RATIO_LIMIT_RESTORE_DEFAULT_SETTINGS 0x00

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */
 
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_boot_time_policy_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_reset_node_manager_statistics_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_reset_node_manager_statistics_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_statistics_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_statistics_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_capabilities_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_capabilities_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_version_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_version_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_power_draw_range_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_power_draw_range_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_ipmb_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_lan_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_alert_destination_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_node_manager_alert_destination_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio_rs;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_limiting_policy_id_rq;
extern fiid_template_t tmpl_cmd_oem_intel_node_manager_get_limiting_policy_id_rs;

int fill_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control (uint8_t policy_enable_disable,
                                                                                uint8_t domain_id,
                                                                                uint8_t policy_id,
                                                                                fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_policy (uint8_t domain_id,
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
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_policy_boot_time_policy (uint8_t domain_id,
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
									      fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_policy (uint8_t domain_id,
                                                             uint8_t policy_id,
                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds (uint8_t domain_id,
									      uint8_t policy_id,
									      uint16_t *alert_threshold1,
									      uint16_t *alert_threshold2,
									      uint16_t *alert_threshold3,
									      fiid_obj_t obj_cmd_rq);
 
int fill_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds (uint8_t domain_id,
									      uint8_t policy_id,
									      fiid_obj_t obj_cmd_rq);
  
int fill_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods (uint8_t domain_id,
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
                                                                             fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods (uint8_t domain_id,
                                                                             uint8_t policy_id,
                                                                             fiid_obj_t obj_cmd_rq);
  
int fill_cmd_oem_intel_node_manager_reset_node_manager_statistics (uint8_t mode,
                                                                   uint8_t domain_id,
                                                                   uint8_t policy_id,
                                                                   fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_statistics (uint8_t mode,
                                                                 uint8_t domain_id,
                                                                 uint8_t policy_id,
                                                                 fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_capabilities (uint8_t domain_id,
                                                                   uint8_t policy_trigger_type,
                                                                   uint8_t policy_type,
								   uint8_t policy_power_domain,
                                                                   fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_version (fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_power_draw_range (uint8_t domain_id,
                                                                       uint16_t minimum_power_draw,
                                                                       uint16_t maximum_power_draw,
                                                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_alert_destination (uint8_t channel_number,
                                                                        uint8_t alert_receiver_deactivation,
                                                                        uint8_t destination_information,
                                                                        uint8_t alert_string_selector,
                                                                        uint8_t send_alert_string,
                                                                        fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_node_manager_alert_destination_ipmb (uint8_t channel_number,
                                                                             uint8_t alert_receiver_deactivation,
                                                                             uint8_t slave_address,
                                                                             uint8_t alert_string_selector,
                                                                             uint8_t send_alert_string,
                                                                             fiid_obj_t obj_cmd_rq);
  
int fill_cmd_oem_intel_node_manager_set_node_manager_alert_destination_lan (uint8_t channel_number,
                                                                            uint8_t alert_receiver_deactivation,
                                                                            uint8_t destination_selector,
                                                                            uint8_t alert_string_selector,
                                                                            uint8_t send_alert_string,
                                                                            fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_node_manager_alert_destination (fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio (uint8_t cpu_socket_number,
								     uint8_t active_cores_configuration,
								     uint8_t turbo_ratio_limit,
								     fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio (uint8_t cpu_socket_number,
								     uint8_t active_cores_configuration,
								     fiid_obj_t obj_cmd_rq);

int fill_cmd_oem_intel_node_manager_get_limiting_policy_id (uint8_t domain_id,
							    fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OEM_INTEL_NODE_MANAGER_CMDS_H */
