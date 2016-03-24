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

#ifndef IPMI_SENSOR_READ_H
#define IPMI_SENSOR_READ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/sdr/ipmi-sdr.h>

/* note: SENSOR_READING_UNAVAILABLE and SENSOR_SCANNING_DISABLED are
 * because of configuration of a sensor.  It is "ok" to some extent.
 * SENSOR_READING_CANNOT_BE_OBTAINED is due to a retrieval error.
 */

#define IPMI_SENSOR_READ_ERR_SUCCESS                                 0
#define IPMI_SENSOR_READ_ERR_CONTEXT_NULL                            1
#define IPMI_SENSOR_READ_ERR_CONTEXT_INVALID                         2
#define IPMI_SENSOR_READ_ERR_PARAMETERS                              3
#define IPMI_SENSOR_READ_ERR_OUT_OF_MEMORY                           4
#define IPMI_SENSOR_READ_ERR_SENSOR_READING_UNAVAILABLE              5
#define IPMI_SENSOR_READ_ERR_SENSOR_SCANNING_DISABLED                6
#define IPMI_SENSOR_READ_ERR_SENSOR_NON_ANALOG                       7
#define IPMI_SENSOR_READ_ERR_SENSOR_NON_LINEAR                       8
#define IPMI_SENSOR_READ_ERR_SENSOR_NOT_OWNED_BY_BMC                 9
#define IPMI_SENSOR_READ_ERR_SENSOR_IS_SYSTEM_SOFTWARE              10
#define IPMI_SENSOR_READ_ERR_SENSOR_CANNOT_BE_BRIDGED               11
#define IPMI_SENSOR_READ_ERR_SENSOR_READING_CANNOT_BE_OBTAINED      12
#define IPMI_SENSOR_READ_ERR_NODE_BUSY                              13
#define IPMI_SENSOR_READ_ERR_INVALID_SDR_RECORD_TYPE                14
#define IPMI_SENSOR_READ_ERR_SDR_ENTRY_ERROR                        15
#define IPMI_SENSOR_READ_ERR_IPMI_ERROR                             16
#define IPMI_SENSOR_READ_ERR_SYSTEM_ERROR                           17
#define IPMI_SENSOR_READ_ERR_OVERFLOW                               18
#define IPMI_SENSOR_READ_ERR_INTERNAL_ERROR                         19
#define IPMI_SENSOR_READ_ERR_ERRNUMRANGE                            20

#define IPMI_SENSOR_READ_FLAGS_DEFAULT                              0x0000
#define IPMI_SENSOR_READ_FLAGS_BRIDGE_SENSORS                       0x0001
#define IPMI_SENSOR_READ_FLAGS_DISCRETE_READING                     0x0002
#define IPMI_SENSOR_READ_FLAGS_IGNORE_SCANNING_DISABLED             0x0004
#define IPMI_SENSOR_READ_FLAGS_ASSUME_BMC_OWNER                     0x0008

typedef struct ipmi_sensor_read_ctx *ipmi_sensor_read_ctx_t;

/* Sensor Read Context Functions
 * - ipmi_ctx assumes ipmi opened and ready to go
 */
ipmi_sensor_read_ctx_t ipmi_sensor_read_ctx_create (ipmi_ctx_t ipmi_ctx);
void ipmi_sensor_read_ctx_destroy (ipmi_sensor_read_ctx_t ctx);
int ipmi_sensor_read_ctx_errnum (ipmi_sensor_read_ctx_t ctx);
char * ipmi_sensor_read_ctx_strerror (int errnum);
char * ipmi_sensor_read_ctx_errormsg (ipmi_sensor_read_ctx_t ctx);

/* Sensor read flag functions */
int ipmi_sensor_read_ctx_get_flags (ipmi_sensor_read_ctx_t ctx, unsigned int *flags);
int ipmi_sensor_read_ctx_set_flags (ipmi_sensor_read_ctx_t ctx, unsigned int flags);

/*
 * return 1 - reading a success (although for some sensor types, a
 * reading may not be returned. For example with discrete sensors, a
 * reading is not returned but a sensor_event_bitmask is.)
 *
 * return 0 - cannot obtain reading, but sensor_event_bitmask still
 * returned.  This is most common because the sensor cannot be
 * interpreted, b/c (for example) it is a non-analog or non-linear
 * sensor.  errnum will be set appropriately.
 *
 * return (-1) - error, neither a reading nor sensor_event_bitmask can
 * be returned.
 *
 * if reading returned, must be free'd by caller
 *
 * 'sensor_reading_raw' is optional and need not be specified.
 *
 * under return of 0 or 1, the sensor_reading_raw will be filled with the raw reading
 *
 * Notes:
 *
 * shared_sensor_number_offset used for sensor record sharing in compact
 * records.  If not used or not available, must be set to 0.
 */
int ipmi_sensor_read (ipmi_sensor_read_ctx_t ctx,
                      const void *sdr_record,
                      unsigned int sdr_record_len,
                      uint8_t shared_sensor_number_offset,
                      uint8_t *sensor_reading_raw,
                      double **sensor_reading,
                      uint16_t *sensor_event_bitmask);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_READ_H */
