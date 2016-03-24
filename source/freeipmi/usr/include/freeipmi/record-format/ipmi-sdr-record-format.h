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

#ifndef IPMI_SDR_RECORD_FORMAT_H
#define IPMI_SDR_RECORD_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

#define IPMI_SDR_FORMAT_FULL_SENSOR_RECORD                          0x01
#define IPMI_SDR_FORMAT_COMPACT_SENSOR_RECORD                       0x02
#define IPMI_SDR_FORMAT_EVENT_ONLY_RECORD                           0x03
#define IPMI_SDR_FORMAT_ENTITY_ASSOCIATION_RECORD                   0x08
#define IPMI_SDR_FORMAT_DEVICE_RELATIVE_ENTITY_ASSOCIATION_RECORD   0x09
#define IPMI_SDR_FORMAT_GENERIC_DEVICE_LOCATOR_RECORD               0x10
#define IPMI_SDR_FORMAT_FRU_DEVICE_LOCATOR_RECORD                   0x11
#define IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD 0x12
#define IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_CONFIRMATION_RECORD   0x13
#define IPMI_SDR_FORMAT_BMC_MESSAGE_CHANNEL_INFO_RECORD             0x14
#define IPMI_SDR_FORMAT_OEM_RECORD                                  0xC0

#define IPMI_SDR_FORMAT_TYPE_VALID(__val)                                     \
  (((__val) == IPMI_SDR_FORMAT_FULL_SENSOR_RECORD                             \
    || (__val) == IPMI_SDR_FORMAT_COMPACT_SENSOR_RECORD                       \
    || (__val) == IPMI_SDR_FORMAT_EVENT_ONLY_RECORD                           \
    || (__val) == IPMI_SDR_FORMAT_ENTITY_ASSOCIATION_RECORD                   \
    || (__val) == IPMI_SDR_FORMAT_DEVICE_RELATIVE_ENTITY_ASSOCIATION_RECORD   \
    || (__val) == IPMI_SDR_FORMAT_GENERIC_DEVICE_LOCATOR_RECORD               \
    || (__val) == IPMI_SDR_FORMAT_FRU_DEVICE_LOCATOR_RECORD                   \
    || (__val) == IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_DEVICE_LOCATOR_RECORD \
    || (__val) == IPMI_SDR_FORMAT_MANAGEMENT_CONTROLLER_CONFIRMATION_RECORD   \
    || (__val) == IPMI_SDR_FORMAT_BMC_MESSAGE_CHANNEL_INFO_RECORD             \
    || (__val) == IPMI_SDR_FORMAT_OEM_RECORD) ? 1 : 0)

#define IPMI_SDR_SENSOR_OWNER_ID_TYPE_IPMB_SLAVE_ADDRESS   0x0
#define IPMI_SDR_SENSOR_OWNER_ID_TYPE_SYSTEM_SOFTWARE_ID   0x1

#define IPMI_SDR_ANALOG_DATA_FORMAT_UNSIGNED      0x0
#define IPMI_SDR_ANALOG_DATA_FORMAT_1S_COMPLEMENT 0x1
#define IPMI_SDR_ANALOG_DATA_FORMAT_2S_COMPLEMENT 0x2
#define IPMI_SDR_ANALOG_DATA_FORMAT_NOT_ANALOG    0x3

#define IPMI_SDR_ANALOG_DATA_FORMAT_UNSIGNED_STRING          "unsigned"
#define IPMI_SDR_ANALOG_DATA_FORMAT_1S_COMPLEMENT_STRING     "1's complement (signed)"
#define IPMI_SDR_ANALOG_DATA_FORMAT_2S_COMPLEMENT_STRING     "2's complement (signed)"
#define IPMI_SDR_ANALOG_DATA_FORMAT_NOT_ANALOG_STRING        "Does not return analog (numeric) reading"

#define IPMI_SDR_ANALOG_DATA_FORMAT_VALID(__val)            \
  (((__val) == IPMI_SDR_ANALOG_DATA_FORMAT_UNSIGNED         \
    || (__val) == IPMI_SDR_ANALOG_DATA_FORMAT_1S_COMPLEMENT \
    || (__val) == IPMI_SDR_ANALOG_DATA_FORMAT_2S_COMPLEMENT) ? 1 : 0)

#define IPMI_SDR_MODIFIER_UNIT_NONE           0
#define IPMI_SDR_MODIFIER_UNIT_DIVIDE         1
#define IPMI_SDR_MODIFIER_UNIT_MULTIPLY       2

#define IPMI_SDR_MODIFIER_UNIT_VALID(__sensor_modifier_unit)     \
  (((__sensor_modifier_unit) == IPMI_SDR_MODIFIER_UNIT_NONE      \
    || (__sensor_modifier_unit) == IPMI_SDR_MODIFIER_UNIT_DIVIDE \
    || (__sensor_modifier_unit) == IPMI_SDR_MODIFIER_UNIT_MULTIPLY) ? 1 : 0)

#define IPMI_SDR_LINEARIZATION_LINEAR                0
#define IPMI_SDR_LINEARIZATION_LN                    1
#define IPMI_SDR_LINEARIZATION_LOG10                 2
#define IPMI_SDR_LINEARIZATION_LOG2                  3
#define IPMI_SDR_LINEARIZATION_E                     4
#define IPMI_SDR_LINEARIZATION_EXP10                 5
#define IPMI_SDR_LINEARIZATION_EXP2                  6
#define IPMI_SDR_LINEARIZATION_INVERSE               7
#define IPMI_SDR_LINEARIZATION_SQR                   8
#define IPMI_SDR_LINEARIZATION_CUBE                  9
#define IPMI_SDR_LINEARIZATION_SQRT                 10
#define IPMI_SDR_LINEARIZATION_CUBERT               11
#define IPMI_SDR_LINEARIZATION_NON_LINEAR         0x70
#define IPMI_SDR_LINEARIZATION_NON_LINEAR_OEM_MIN 0x71
#define IPMI_SDR_LINEARIZATION_NON_LINEAR_OEM_MAX 0x7F

#define IPMI_SDR_LINEARIZATION_LINEAR_STRING     "linear"
#define IPMI_SDR_LINEARIZATION_LN_STRING         "ln"
#define IPMI_SDR_LINEARIZATION_LOG10_STRING      "log10"
#define IPMI_SDR_LINEARIZATION_LOG2_STRING       "log2"
#define IPMI_SDR_LINEARIZATION_E_STRING          "e"
#define IPMI_SDR_LINEARIZATION_EXP10_STRING      "exp10"
#define IPMI_SDR_LINEARIZATION_EXP2_STRING       "exp2"
#define IPMI_SDR_LINEARIZATION_INVERSE_STRING    "1/x"
#define IPMI_SDR_LINEARIZATION_SQR_STRING        "sqr(x)"
#define IPMI_SDR_LINEARIZATION_CUBE_STRING       "cube(x)"
#define IPMI_SDR_LINEARIZATION_SQRT_STRING       "sqrt(x)"
#define IPMI_SDR_LINEARIZATION_CUBERT_STRING     "cube^-1(x)"
#define IPMI_SDR_LINEARIZATION_NON_LINEAR_STRING "non-linear"

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SDR_LINEARIZATION_IS_LINEAR(__sensor_linearization) \
  ((((__sensor_linearization) + 1) >= IPMI_SDR_LINEARIZATION_LN  \
    && (__sensor_linearization) <= IPMI_SDR_LINEARIZATION_CUBERT) ? 1 : 0)

#define IPMI_SDR_LINEARIZATION_IS_NON_LINEAR(__sensor_linearization) \
  (((__sensor_linearization) >= IPMI_SDR_LINEARIZATION_NON_LINEAR \
    && (__sensor_linearization) <=IPMI_SDR_LINEARIZATION_NON_LINEAR_OEM_MAX) ? 1 : 0)

#define IPMI_SDR_PERCENTAGE_NO  0
#define IPMI_SDR_PERCENTAGE_YES 1

#define IPMI_SDR_PERCENTAGE_VALID(__val) \
  (((__val) == IPMI_SDR_PERCENTAGE_NO    \
    || (__val) == IPMI_SDR_PERCENTAGE_YES) ? 1 : 0)

#define IPMI_SDR_PHYSICAL_ENTITY          0x0
#define IPMI_SDR_LOGICAL_CONTAINER_ENTITY 0x1

#define IPMI_SDR_SENSOR_SCANNING_ENABLED  0x1
#define IPMI_SDR_SENSOR_SCANNING_DISABLED 0x0

#define IPMI_SDR_EVENT_GENERATION_ENABLED  0x1
#define IPMI_SDR_EVENT_GENERATION_DISABLED 0x0

#define IPMI_SDR_SENSOR_AUTO_REARM_SUPPORT_MANUAL 0x0
#define IPMI_SDR_SENSOR_AUTO_REARM_SUPPORT_AUTO   0x1

#define IPMI_SDR_PER_EVENT_ENABLE_DISABLE_SUPPORT    0x0
#define IPMI_SDR_ENTIRE_SENSOR_ONLY                  0x1
#define IPMI_SDR_GLOBAL_DISABLE_ONLY                 0x2
#define IPMI_SDR_NO_EVENTS_FROM_SENSOR               0x3

#define IPMI_SDR_NO_THRESHOLDS_SUPPORT                   0x0
#define IPMI_SDR_READABLE_THRESHOLDS_SUPPORT             0x1
#define IPMI_SDR_READABLE_SETTABLE_THRESHOLDS_SUPPORT    0x2
#define IPMI_SDR_FIXED_UNREADABLE_THRESHOLDS_SUPPORT     0x3

#define IPMI_SDR_NO_HYSTERESIS_SUPPORT                   0x0
#define IPMI_SDR_READABLE_HYSTERESIS_SUPPORT             0x1
#define IPMI_SDR_READABLE_SETTABLE_HYSTERESIS_SUPPORT    0x2
#define IPMI_SDR_FIXED_UNREADABLE_HYSTERESIS_SUPPORT     0x3

#define IPMI_SDR_ANALOG_CHARACTERISTICS_NOMINAL_READING_SPECIFIED   0x1
#define IPMI_SDR_ANALOG_CHARACTERISTICS_NOMINAL_READING_UNSPECIFIED 0x0

#define IPMI_SDR_ANALOG_CHARACTERISTICS_NORMAL_MAX_SPECIFIED   0x1
#define IPMI_SDR_ANALOG_CHARACTERISTICS_NORMAL_MAX_UNSPECIFIED 0x0

#define IPMI_SDR_ANALOG_CHARACTERISTICS_NORMAL_MIN_SPECIFIED   0x1
#define IPMI_SDR_ANALOG_CHARACTERISTICS_NORMAL_MIN_UNSPECIFIED 0x0

#define IPMI_SDR_ID_STRING_INSTANCE_MODIFIER_TYPE_NUMERIC 0x0
#define IPMI_SDR_ID_STRING_INSTANCE_MODIFIER_TYPE_ALPHA   0x1

#define IPMI_SDR_SENSOR_DIRECTION_UNSPECIFIED 0x0
#define IPMI_SDR_SENSOR_DIRECTION_INPUT       0x1
#define IPMI_SDR_SENSOR_DIRECTION_OUTPUT      0x2
#define IPMI_SDR_SENSOR_DIRECTION_RESERVED    0x3

#define IPMI_SDR_ENTITY_INSTANCE_SAME_FOR_ALL_SHARED_RECORDS       0x0
#define IPMI_SDR_ENTITY_INSTANCE_INCREMENTS_FOR_EACH_SHARED_RECORD 0x1

#define IPMI_SDR_RECORD_NO_LINKED_ENTITY_ASSOCIATION_RECORDS_EXIST 0x0
#define IPMI_SDR_RECORD_LINKED_ENTITY_ASSOCIATION_RECORDS_EXIST    0x1

#define IPMI_SDR_CONTAINED_ENTITY_SPECIFIED_AS_LIST  0x0
#define IPMI_SDR_CONTAINED_ENTITY_SPECIFIED_AS_RANGE 0x1

#define IPMI_SDR_DEVICE_IS_NOT_A_LOGICAL_FRU_DEVICE 0x0
#define IPMI_SDR_DEVICE_IS_LOGICAL_FRU_DEVICE       0x1

#define IPMI_SDR_EVENT_MESSAGE_GENERATION_FROM_CONTROLLER_ENABLE       0x0
#define IPMI_SDR_EVENT_MESSAGE_GENERATION_FROM_CONTROLLER_DISABLE      0x1
#define IPMI_SDR_EVENT_MESSAGE_GENERATION_DO_NOT_INITIALIZE_CONTROLLER 0x2
#define IPMI_SDR_EVENT_MESSAGE_GENERATION_RESERVED                     0x3

#define IPMI_SDR_LOG_INITIALIZATION_AGENT_ERRORS_ENABLE  0x0
#define IPMI_SDR_LOG_INITIALIZATION_AGENT_ERRORS_DISABLE 0x1

#define IPMI_SDR_CONTROLLER_LOGS_INITIALIZATION_AGENT_ERRORS_ENABLE  0x0
#define IPMI_SDR_CONTROLLER_LOGS_INITIALIZATION_AGENT_ERRORS_DISABLE 0x1

#define IPMI_SDR_CONTROLLER_DYNAMIC 0x0
#define IPMI_SDR_CONTROLLER_STATIC  0x1

#define IPMI_SDR_ACPI_DEVICE_POWER_STATE_NOTIFICATION_REQUIRED     0x0
#define IPMI_SDR_NO_ACPI_DEVICE_POWER_STATE_NOTIFICATION_REQUIRED  0x1

#define IPMI_SDR_ACPI_SYSTEM_POWER_STATE_NOTIFICATION_REQUIRED     0x0
#define IPMI_SDR_NO_ACPI_SYSTEM_POWER_STATE_NOTIFICATION_REQUIRED  0x1

#define IPMI_SDR_MAX_ID_STRING_LENGTH        16
#define IPMI_SDR_MAX_DEVICE_ID_STRING_LENGTH 16

/* 
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_sdr_record_header;
extern fiid_template_t tmpl_sdr_full_sensor_record;
extern fiid_template_t tmpl_sdr_full_sensor_record_non_threshold_based_sensors;
extern fiid_template_t tmpl_sdr_full_sensor_record_threshold_based_sensors;
extern fiid_template_t tmpl_sdr_compact_sensor_record;
extern fiid_template_t tmpl_sdr_compact_sensor_record_non_threshold_based_sensors;
extern fiid_template_t tmpl_sdr_compact_sensor_record_threshold_based_sensors;
extern fiid_template_t tmpl_sdr_event_only_record;
extern fiid_template_t tmpl_sdr_entity_association_record;
extern fiid_template_t tmpl_sdr_device_relative_entity_association_record;
extern fiid_template_t tmpl_sdr_generic_device_locator_record;
extern fiid_template_t tmpl_sdr_fru_device_locator_record;
extern fiid_template_t tmpl_sdr_fru_device_locator_record_non_intelligent;
extern fiid_template_t tmpl_sdr_management_controller_device_locator_record;
extern fiid_template_t tmpl_sdr_management_controller_confirmation_record;
extern fiid_template_t tmpl_sdr_bmc_message_channel_info_record;
extern fiid_template_t tmpl_sdr_oem_record;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_RECORD_FORMAT_H */
