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

#ifndef IPMI_SEL_RECORD_FORMAT_H
#define IPMI_SEL_RECORD_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

#define IPMI_V1_0_EVENT_MESSAGE_FORMAT 0x03
#define IPMI_V1_5_EVENT_MESSAGE_FORMAT 0x04

#define IPMI_SEL_RECORD_TYPE_SYSTEM_EVENT_RECORD 0x02

#define IPMI_SEL_RECORD_TYPE_TIMESTAMPED_OEM_MIN 0xC0
#define IPMI_SEL_RECORD_TYPE_TIMESTAMPED_OEM_MAX 0xDF

#define IPMI_SEL_RECORD_TYPE_NON_TIMESTAMPED_OEM_MIN 0xE0
#define IPMI_SEL_RECORD_TYPE_NON_TIMESTAMPED_OEM_MAX 0xFF

#define IPMI_SEL_RECORD_TYPE_IS_EVENT(__record_type) \
  (((__record_type) == IPMI_SEL_RECORD_TYPE_SYSTEM_EVENT_RECORD) ? 1 : 0)

#define IPMI_SEL_RECORD_TYPE_IS_TIMESTAMPED_OEM(__record_type) \
  (((__record_type) >= IPMI_SEL_RECORD_TYPE_TIMESTAMPED_OEM_MIN \
    && (__record_type) <= IPMI_SEL_RECORD_TYPE_TIMESTAMPED_OEM_MAX) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_SEL_RECORD_TYPE_IS_NON_TIMESTAMPED_OEM(__record_type) \
  (((__record_type) >= IPMI_SEL_RECORD_TYPE_NON_TIMESTAMPED_OEM_MIN \
    && (((__record_type) - 1) <= (IPMI_SEL_RECORD_TYPE_NON_TIMESTAMPED_OEM_MAX - 1))) ? 1 : 0)

#define IPMI_SEL_RECORD_TYPE_VALID(__record_type)                  \
  ((IPMI_SEL_RECORD_TYPE_IS_EVENT((__record_type))                 \
    || IPMI_SEL_RECORD_TYPE_IS_TIMESTAMPED_OEM((__record_type))    \
    || IPMI_SEL_RECORD_TYPE_IS_NON_TIMESTAMPED_OEM((__record_type))) ? 1 : 0)

#define IPMI_SEL_RECORD_ASSERTION_EVENT   0x0
#define IPMI_SEL_RECORD_DEASSERTION_EVENT 0x1

#define IPMI_SEL_RECORD_EVENT_DIRECTION_VALID(__event_direction) \
  (((__event_direction) == IPMI_SEL_RECORD_ASSERTION_EVENT \
    || (__event_direction) == IPMI_SEL_RECORD_DEASSERTION_EVENT) ? 1 : 0)

/* Refer to Table 29-6 */
#define IPMI_SEL_EVENT_DATA_UNSPECIFIED_BYTE                        0x0
#define IPMI_SEL_EVENT_DATA_TRIGGER_READING                         0x1
#define IPMI_SEL_EVENT_DATA_TRIGGER_THRESHOLD_VALUE                 0x1
#define IPMI_SEL_EVENT_DATA_PREVIOUS_STATE_OR_SEVERITY              0x1
#define IPMI_SEL_EVENT_DATA_OEM_CODE                                0x2
#define IPMI_SEL_EVENT_DATA_SENSOR_SPECIFIC_EVENT_EXTENSION_CODE    0x3

#define IPMI_SEL_RECORD_UNSPECIFIED_EVENT  0xFF
#define IPMI_SEL_RECORD_UNSPECIFIED_OFFSET 0x0F

#define IPMI_SEL_RECORD_MAX_RECORD_LENGTH  16

/* 
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_sel_record_header;

extern fiid_template_t tmpl_sel_system_event_record;
extern fiid_template_t tmpl_sel_system_event_record_event_fields;
extern fiid_template_t tmpl_sel_system_event_record_discrete_previous_state_severity;
extern fiid_template_t tmpl_sel_timestamped_oem_record;
extern fiid_template_t tmpl_sel_non_timestamped_oem_record;

extern fiid_template_t tmpl_threshold_event_data;
extern fiid_template_t tmpl_discrete_event_data;
extern fiid_template_t tmpl_oem_event_data;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SEL_RECORD_FORMAT_H */
