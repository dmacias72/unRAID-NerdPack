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

#ifndef IPMI_SENSOR_UTIL_H
#define IPMI_SENSOR_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/sdr/ipmi-sdr.h>

/* return length of string written into buffer on success, -1 on error */
int ipmi_get_threshold_message (uint8_t offset, char *buf, unsigned int buflen);

const char *ipmi_get_sensor_type_string (uint8_t sensor_type);

const char *ipmi_get_oem_sensor_type_string (uint8_t sensor_type,
                                             uint8_t event_reading_code,
                                             uint32_t manufacturer_id,
                                             uint16_t product_id);

/* returns length written into buffer on success, -1 on error */
int ipmi_sensor_units_string (uint8_t sensor_units_percentage,
                              uint8_t sensor_units_modifier,
                              uint8_t sensor_units_rate,
                              uint8_t sensor_base_unit_type,
                              uint8_t sensor_modifier_unit_type,
                              char *buf,
                              unsigned int buflen,
                              unsigned int abbreviated_units_flag);

/* b_exponent - sometimes documented as k1 */
/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_value (int8_t r_exponent,
                              int8_t b_exponent,
                              int16_t m,
                              int16_t b,
                              uint8_t linearization,
                              uint8_t analog_data_format,
                              uint8_t raw_data,
                              double *value);

/* b_exponent - sometimes documented as k1 */
/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_raw_value (int8_t r_exponent,
                                  int8_t b_exponent,
                                  int16_t m,
                                  int16_t b,
                                  uint8_t linearization,
                                  uint8_t analog_data_format,
                                  double value,
                                  uint8_t *raw_data);

/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_tolerance (int8_t r_exponent,
                                  int16_t m,
                                  uint8_t raw_data,
                                  uint8_t linearization,
                                  double *value);

/* accuracy returned as percentage */
int ipmi_sensor_decode_accuracy (uint16_t accuracy_raw,
                                 uint8_t accuracy_exp,
                                 double *value);

/* r_exponent - sometimes documented as k2 */
int ipmi_sensor_decode_resolution (int8_t r_exponent,
                                   int16_t m,
                                   double *value);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_UTIL_H */
