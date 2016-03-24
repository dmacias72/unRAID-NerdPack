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

#ifndef IPMI_EVENT_READING_TYPE_CODE_SPEC_H
#define IPMI_EVENT_READING_TYPE_CODE_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Table 42-1 */

#define IPMI_EVENT_READING_TYPE_CODE_UNSPECIFIED                         0x00
#define IPMI_EVENT_READING_TYPE_CODE_THRESHOLD                           0x01
#define IPMI_EVENT_READING_TYPE_CODE_TRANSITION_STATE                    0x02
#define IPMI_EVENT_READING_TYPE_CODE_STATE                               0x03
#define IPMI_EVENT_READING_TYPE_CODE_PREDICTIVE_FAILURE                  0x04
#define IPMI_EVENT_READING_TYPE_CODE_LIMIT                               0x05
#define IPMI_EVENT_READING_TYPE_CODE_PERFORMANCE                         0x06
#define IPMI_EVENT_READING_TYPE_CODE_TRANSITION_SEVERITY                 0x07
#define IPMI_EVENT_READING_TYPE_CODE_DEVICE_PRESENT                      0x08
#define IPMI_EVENT_READING_TYPE_CODE_DEVICE_ENABLED                      0x09
#define IPMI_EVENT_READING_TYPE_CODE_TRANSITION_AVAILABILITY             0x0A
#define IPMI_EVENT_READING_TYPE_CODE_REDUNDANCY                          0x0B
#define IPMI_EVENT_READING_TYPE_CODE_ACPI_POWER_STATE                    0x0C
#define IPMI_EVENT_READING_TYPE_CODE_SENSOR_SPECIFIC                     0x6F
#define IPMI_EVENT_READING_TYPE_CODE_OEM_MIN                             0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_MAX                             0x7F

#define IPMI_EVENT_READING_TYPE_CODE_IS_UNSPECIFIED(__val) \
  (((__val) == IPMI_EVENT_READING_TYPE_CODE_UNSPECIFIED) ? 1 : 0)

#define IPMI_EVENT_READING_TYPE_CODE_IS_THRESHOLD(__val) \
  (((__val) == IPMI_EVENT_READING_TYPE_CODE_THRESHOLD) ? 1 : 0)

#define IPMI_EVENT_READING_TYPE_CODE_IS_GENERIC(__val) \
  (((__val) >= IPMI_EVENT_READING_TYPE_CODE_TRANSITION_STATE \
    && (__val) <= IPMI_EVENT_READING_TYPE_CODE_ACPI_POWER_STATE) ? 1 : 0)

#define IPMI_EVENT_READING_TYPE_CODE_IS_SENSOR_SPECIFIC(__val) \
  (((__val) == IPMI_EVENT_READING_TYPE_CODE_SENSOR_SPECIFIC) ? 1 : 0)

#define IPMI_EVENT_READING_TYPE_CODE_IS_OEM(__val) \
  (((__val) >= IPMI_EVENT_READING_TYPE_CODE_OEM_MIN \
    && (__val) <= IPMI_EVENT_READING_TYPE_CODE_OEM_MAX) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_READING_TYPE_CODE_SPEC_H */
