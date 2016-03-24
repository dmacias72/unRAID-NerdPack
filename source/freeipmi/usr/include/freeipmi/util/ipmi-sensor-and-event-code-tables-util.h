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

#ifndef IPMI_SENSOR_AND_EVENT_CODE_TABLES_UTIL_H
#define IPMI_SENSOR_AND_EVENT_CODE_TABLES_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define IPMI_EVENT_READING_TYPE_CODE_CLASS_THRESHOLD                0x01
#define IPMI_EVENT_READING_TYPE_CODE_CLASS_GENERIC_DISCRETE         0x02
#define IPMI_EVENT_READING_TYPE_CODE_CLASS_SENSOR_SPECIFIC_DISCRETE 0x03
#define IPMI_EVENT_READING_TYPE_CODE_CLASS_OEM                      0x04
#define IPMI_EVENT_READING_TYPE_CODE_CLASS_UNKNOWN                  0x05

#define IPMI_GET_EVENT_MESSAGES_FLAGS_DEFAULT                    0x0000
#define IPMI_GET_EVENT_MESSAGES_FLAGS_SHORT                      0x0001
#define IPMI_GET_EVENT_MESSAGES_FLAGS_INTERPRET_OEM_DATA         0x0002
#define IPMI_GET_EVENT_MESSAGES_FLAGS_SENSOR_READING             0x0004
#define IPMI_GET_EVENT_MESSAGES_FLAGS_IGNORE_UNRECOGNIZED_EVENTS 0x0008

int ipmi_event_reading_type_code_class (uint8_t event_reading_type_code);

int ipmi_event_message_separator (const char *separator);

/* return length of string written into buffer on success, -1 on error */
int ipmi_get_generic_event_message (uint8_t event_reading_type_code,
                                    unsigned int offset,
                                    char *buf,
                                    unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* this function is for sensor specific messages, sensors with event
 * reading typo codes of 0x6F */
int ipmi_get_sensor_type_message (uint8_t sensor_type,
                                  unsigned int offset,
                                  char *buf,
                                  unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* identical to above but returns "short" strings when appropriate */
int ipmi_get_generic_event_message_short (uint8_t event_reading_type_code,
                                          unsigned int offset,
                                          char *buf,
                                          unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* identical to above but returns "short" strings when appropriate */
int ipmi_get_sensor_type_message_short (uint8_t sensor_type,
                                        unsigned int offset,
                                        char *buf,
                                        unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
int ipmi_get_event_data2_message (uint8_t sensor_type,
                                  unsigned int offset,
                                  uint8_t event_data2,
                                  char *buf,
                                  unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
int ipmi_get_event_data3_message (uint8_t sensor_type,
                                  unsigned int offset,
                                  uint8_t event_data2,
                                  uint8_t event_data3,
                                  char *buf,
                                  unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* this function is for OEM event reading type codes */
int ipmi_get_oem_generic_event_message (uint32_t manufacturer_id,
                                        uint16_t product_id,
                                        uint8_t event_reading_type_code,
                                        unsigned int offset,
                                        char *buf,
                                        unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* this function is for sensor specific messages, sensors with event
 * reading typo codes of 0x6F */
int ipmi_get_oem_sensor_type_message (uint32_t manufacturer_id,
                                      uint16_t product_id,
                                      uint8_t sensor_type,
				      uint8_t sensor_number,
                                      unsigned int offset,
                                      char *buf,
                                      unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* this function is for string mappings from vendors that are specific
 * to a event reading typo code and sensor type combination. */
int ipmi_get_oem_specific_message (uint32_t manufacturer_id,
                                   uint16_t product_id,
                                   uint8_t event_reading_type_code,
                                   uint8_t sensor_type,
                                   unsigned int offset,
                                   char *buf,
                                   unsigned int buflen);

/* return length of string written into buffer on success, -1 on error */
/* some vendors return values instead of event bitmasks in the 
 * sensor or SEL event, this is to handle this special case
 */
int ipmi_get_oem_event_bitmask_message (uint32_t manufacturer_id,
                                        uint16_t product_id,
                                        uint8_t event_reading_type_code,
                                        uint8_t sensor_type,
                                        uint16_t event_bitmask,
                                        char *buf,
                                        unsigned int buflen);

/* wrapper function to handle retrieval of an array of event messages.
 * The array is NULL pointer terminated.
 *
 * collectively wraps
 *
 * ipmi_get_generic_event_message()
 * ipmi_get_sensor_type_message()
 *
 * If flag IPMI_GET_EVENT_MESSAGES_FLAGS_SHORT is specified,
 * ipmi_get_generic_event_message_short() and
 * ipmi_get_sensor_type_message_short() are called respectively inplace
 * of ipmi_get_generic_event_message() and ipmi_get_sensor_type_message().
 *
 * If flag IPMI_GET_EVENT_MESSAGES_FLAGS_INTERPRET_OEM_DATA is
 * specified ipmi_get_oem_generic_event_message(),
 * ipmi_get_oem_sensor_type_message(), and
 * ipmi_get_oem_sensor_event_bitmask_message() are called respectively
 * if necessary.
 *
 * If flag IPMI_GET_EVENT_MESSAGES_FLAGS_SENSOR_READING is
 * specified ipmi_get_threshold_message() will be called for a
 * sensor_event_bitmask instead of ipmi_get_generic_event_message() if
 * it is a threshold sensor.  Primarily used for event messages
 * following a get sensor reading in which threshold event bitmasks
 * are slightly different.
 *
 * If flag IPMI_GET_EVENT_MESSAGES_FLAG_IGNORE_UNRECOGNIZED_EVENTS is
 * specified ipmi_get_threshold_message() will not store event strings
 * for unrecognized events.
 *
 * If there are no event messages, and 'no_event_message_string' is
 * non-NULL, it will be placed into 'event_messages' as the lone event
 * message.
 *
 * Returns 0 on success, -1 on error.  Number of messages allocated in
 * 'event_messages' is returned in 'event_messages_count'.
 *
 * User responsible for clearing memory created in 'event_messages'.
 */ 
int ipmi_get_event_messages (uint8_t event_reading_type_code,
                             uint8_t sensor_type, /* ignored if not relevant for event_reading_type_code */
			     uint8_t sensor_number, /* ignored if not relevant for event_reading_type_code or sensor_type */
                             uint16_t event_bitmask,
                             uint32_t manufacturer_id, /* ignored if INTERPRET_OEM_DATA not set */
                             uint16_t product_id, /* ignored if INTERPRET_OEM_DATA not set */
                             char ***event_messages,
                             unsigned int *event_messages_count,
                             const char *no_event_message_string,
                             unsigned int flags);
 
#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_AND_EVENT_CODE_TABLES_UTIL_H */
