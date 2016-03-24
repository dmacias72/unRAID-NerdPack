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
/*****************************************************************************\
 *  Copyright (C) 2007-2015 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2006-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-222073
 *
 *  This file is part of Ipmimonitoring, an IPMI sensor monitoring
 *  library.  For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmimonitoring is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmimonitoring is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmimonitoring.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMI_SDR_H
#define IPMI_SDR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>

#define IPMI_SDR_ERR_SUCCESS                                      0
#define IPMI_SDR_ERR_CONTEXT_NULL                                 1
#define IPMI_SDR_ERR_CONTEXT_INVALID                              2
#define IPMI_SDR_ERR_PARAMETERS                                   3
#define IPMI_SDR_ERR_OUT_OF_MEMORY                                4
#define IPMI_SDR_ERR_FILENAME_INVALID                             5
#define IPMI_SDR_ERR_FILESYSTEM                                   6
#define IPMI_SDR_ERR_PERMISSION                                   7
#define IPMI_SDR_ERR_CONTEXT_PERFORMING_OTHER_OPERATION           8
#define IPMI_SDR_ERR_CACHE_CREATE_CACHE_EXISTS                    9
#define IPMI_SDR_ERR_CACHE_CREATE_DUPLICATE_RECORD_ID             10
#define IPMI_SDR_ERR_CACHE_CREATE_INVALID_RECORD_LENGTH           11
#define IPMI_SDR_ERR_CACHE_CREATE_INVALID_RECORD_COUNT            12
#define IPMI_SDR_ERR_CACHE_READ_ALREADY_INITIALIZED               13
#define IPMI_SDR_ERR_CACHE_READ_INITIALIZATION                    14
#define IPMI_SDR_ERR_CACHE_READ_CACHE_DOES_NOT_EXIST              15
#define IPMI_SDR_ERR_CACHE_INVALID                                16
#define IPMI_SDR_ERR_CACHE_OUT_OF_DATE                            17
#define IPMI_SDR_ERR_STATS_NOT_COMPILED                           18
#define IPMI_SDR_ERR_PARSE_INVALID_SDR_RECORD                     19
#define IPMI_SDR_ERR_PARSE_INCOMPLETE_SDR_RECORD                  20
#define IPMI_SDR_ERR_PARSE_CANNOT_PARSE_OR_CALCULATE              21
#define IPMI_SDR_ERR_ERROR_RETURNED_IN_CALLBACK                   22
#define IPMI_SDR_ERR_NOT_FOUND                                    23
#define IPMI_SDR_ERR_IPMI_ERROR                                   24
#define IPMI_SDR_ERR_SYSTEM_ERROR                                 25
#define IPMI_SDR_ERR_OVERFLOW                                     26
#define IPMI_SDR_ERR_INTERNAL_ERROR                               27
#define IPMI_SDR_ERR_ERRNUMRANGE                                  28

#define IPMI_SDR_FLAGS_DEFAULT                   0x0000
#define IPMI_SDR_FLAGS_DEBUG_DUMP                0x0001

/* Flags just for cache creation
 *
 * OVERWRITE - overwrite any previously created cache.
 *
 * DUPLICATE_RECORD_ID - check for duplicate record IDs and return error if one is found. 
 *
 * ASSUME_MAX_SDR_RECORD_COUNT - If motherboard does not implement SDR
 * record reading properly, this workaround will allow code to not
 * fail out.
 */
#define IPMI_SDR_CACHE_CREATE_FLAGS_DEFAULT                     0x00
#define IPMI_SDR_CACHE_CREATE_FLAGS_OVERWRITE                   0x01
#define IPMI_SDR_CACHE_CREATE_FLAGS_DUPLICATE_RECORD_ID         0x02
#define IPMI_SDR_CACHE_CREATE_FLAGS_ASSUME_MAX_SDR_RECORD_COUNT 0x04

#define IPMI_SDR_SENSOR_NAME_FLAGS_DEFAULT                       0x00000000
#define IPMI_SDR_SENSOR_NAME_FLAGS_IGNORE_SHARED_SENSORS         0x00000001
/* applicable only to entity sensor names */
#define IPMI_SDR_SENSOR_NAME_FLAGS_ALWAYS_OUTPUT_INSTANCE_NUMBER 0x00000002

#define IPMI_SDR_MAX_RECORD_LENGTH                      261 /* 256 + header */

#define IPMI_SDR_MAX_SENSOR_NAME_LENGTH                 128

typedef struct ipmi_sdr_ctx *ipmi_sdr_ctx_t;

typedef void (*Ipmi_Sdr_Cache_Create_Callback)(uint8_t sdr_version,
					       uint16_t record_count,
					       uint32_t most_recent_addition_timestamp,
					       uint32_t most_recent_erase_timestamp,
					       uint16_t record_id,
					       void *data);

/* return != 0 to quit iteration, return val will be returned up
 * through original caller.  return < 0 will result in
 * IPMI_SDR_ERR_ERROR_RETURNED_IN_CALLBACK to bet set.
 *
 * Users should be mindful of the API calls they make will in a
 * callback.  Calls to some functions, such as ipmi_sdr_cache_first()
 * may change iteration behavior.
 */
typedef int (*Ipmi_Sdr_Cache_Iterate_Callback)(ipmi_sdr_ctx_t ctx,
					       uint8_t record_type,
					       const void *sdr_record,
					       unsigned int sdr_record_len,
					       void *data);

/*
 * SDR Cache Context and General functions
 */
ipmi_sdr_ctx_t ipmi_sdr_ctx_create (void);
void ipmi_sdr_ctx_destroy (ipmi_sdr_ctx_t ctx);
int ipmi_sdr_ctx_errnum (ipmi_sdr_ctx_t ctx);
char * ipmi_sdr_ctx_strerror (int errnum);
char * ipmi_sdr_ctx_errormsg (ipmi_sdr_ctx_t ctx);

int ipmi_sdr_ctx_get_flags (ipmi_sdr_ctx_t ctx, unsigned int *flags);
int ipmi_sdr_ctx_set_flags (ipmi_sdr_ctx_t ctx, unsigned int flags);
char *ipmi_sdr_ctx_get_debug_prefix (ipmi_sdr_ctx_t ctx);
int ipmi_sdr_ctx_set_debug_prefix (ipmi_sdr_ctx_t ctx, const char *debug_prefix);

/*
 * SDR Cache Creation Functions
 */
/* ipmi_sdr_cache_create
 * - callback called between every record that is cached
 */
int ipmi_sdr_cache_create (ipmi_sdr_ctx_t ctx,
                           ipmi_ctx_t ipmi_ctx,
                           const char *filename,
                           int cache_create_flags,
                           Ipmi_Sdr_Cache_Create_Callback create_callback,
                           void *create_callback_data);

/*
 * SDR Cache Reading Functions
 */

/* ipmi_sdr_cache_open
 *  - ipmi_ctx is optional
 * - if ipmi_ctx is specified, timestamps/version of the SDR will be
 *   checked for out-of-dateness
 */
int ipmi_sdr_cache_open (ipmi_sdr_ctx_t ctx,
                         ipmi_ctx_t ipmi_ctx,
                         const char *filename);

int ipmi_sdr_cache_sdr_version (ipmi_sdr_ctx_t ctx, uint8_t *sdr_version);
int ipmi_sdr_cache_record_count (ipmi_sdr_ctx_t ctx, uint16_t *record_count);
int ipmi_sdr_cache_most_recent_addition_timestamp (ipmi_sdr_ctx_t ctx,
                                                   uint32_t *most_recent_addition_timestamp);
int ipmi_sdr_cache_most_recent_erase_timestamp (ipmi_sdr_ctx_t ctx,
                                                uint32_t *most_recent_erase_timestamp);

int ipmi_sdr_cache_first (ipmi_sdr_ctx_t ctx);
int ipmi_sdr_cache_next (ipmi_sdr_ctx_t ctx);
int ipmi_sdr_cache_seek (ipmi_sdr_ctx_t ctx, unsigned int index);
int ipmi_sdr_cache_search_record_id (ipmi_sdr_ctx_t ctx, uint16_t record_id);
/* sensor owner id is 8bit field - 7 bit slave or system software id + 1 bit indicating type */
int ipmi_sdr_cache_search_sensor (ipmi_sdr_ctx_t ctx, uint8_t sensor_number, uint8_t sensor_owner_id);

/* return length of data read into buffer on success, -1 on error */
int ipmi_sdr_cache_record_read (ipmi_sdr_ctx_t ctx,
                                void *buf,
                                unsigned int buflen);

/* ipmi_sdr_cache_iterate 
 * - iterate through all SDR records calling callback for each one.
 * - if callback returns < 0, that will break iteration and return
 *   value is returned here.
 */
int ipmi_sdr_cache_iterate (ipmi_sdr_ctx_t ctx,
			    Ipmi_Sdr_Cache_Iterate_Callback iterate_callback,
			    void *iterate_callback_data);

int ipmi_sdr_cache_close (ipmi_sdr_ctx_t ctx);

/*
 * SDR stats functions
 *
 * After opening an SDR cache (i.e. ipmi_sdr_cache_open() has been
 * called), loop through the cache and compile data on the cache for
 * a variety of utility functions.
 */

int ipmi_sdr_stats_compile (ipmi_sdr_ctx_t ctx);

/* returns the number of unique entity instances for an entity id found
 * in the SDR
 */
int ipmi_sdr_stats_entity_instance_unique (ipmi_sdr_ctx_t ctx, uint8_t entity_id);

/*
 * SDR Record Parsing Functions
 *
 * For all parsing functions, if currently reading the SDR cache
 * (i.e. ipmi_sdr_cache_open() has been called), if sdr_record is NULL
 * and sdr_record_len is 0, the current sdr record in the iterator
 * will be used in parsing.
 *
 * See ipmi-sdr-oem.h for parsing OEM records.
 */

/* For all SDR records */
int ipmi_sdr_parse_record_id_and_type (ipmi_sdr_ctx_t ctx,
                                       const void *sdr_record,
                                       unsigned int sdr_record_len,
                                       uint16_t *record_id,
                                       uint8_t *record_type);

/* For Full, Compact, Event SDR records */
int ipmi_sdr_parse_sensor_owner_id (ipmi_sdr_ctx_t ctx,
                                    const void *sdr_record,
                                    unsigned int sdr_record_len,
                                    uint8_t *sensor_owner_id_type,
                                    uint8_t *sensor_owner_id);

/* For Full, Compact, Event SDR records */
int ipmi_sdr_parse_sensor_owner_lun (ipmi_sdr_ctx_t ctx,
                                     const void *sdr_record,
                                     unsigned int sdr_record_len,
                                     uint8_t *sensor_owner_lun,
                                     uint8_t *channel_number);

/* For Full, Compact, Event SDR records */
int ipmi_sdr_parse_sensor_number (ipmi_sdr_ctx_t ctx,
                                  const void *sdr_record,
                                  unsigned int sdr_record_len,
                                  uint8_t *sensor_number);

/* For Full, Compact, Event SDR, Generic Device Locator, Management Controller Device Locator SDR records */
int ipmi_sdr_parse_entity_id_instance_type (ipmi_sdr_ctx_t ctx,
                                            const void *sdr_record,
                                            unsigned int sdr_record_len,
                                            uint8_t *entity_id,
                                            uint8_t *entity_instance,
                                            uint8_t *entity_instance_type);

/* For Full, Compact, Event SDR records */
int ipmi_sdr_parse_sensor_type (ipmi_sdr_ctx_t ctx,
                                const void *sdr_record,
                                unsigned int sdr_record_len,
                                uint8_t *sensor_type);

/* For Full, Compact, Event SDR records */
int ipmi_sdr_parse_event_reading_type_code (ipmi_sdr_ctx_t ctx,
                                            const void *sdr_record,
                                            unsigned int sdr_record_len,
                                            uint8_t *event_reading_type_code);

/* For Full, Compact, Event SDR records */
/* return length of data read into buffer on success, -1 on error */
int ipmi_sdr_parse_id_string (ipmi_sdr_ctx_t ctx,
                              const void *sdr_record,
                              unsigned int sdr_record_len,
                              char *id_string,
                              unsigned int id_string_len);

/* For Full, Compact SDR records */
int ipmi_sdr_parse_sensor_units (ipmi_sdr_ctx_t ctx,
                                 const void *sdr_record,
                                 unsigned int sdr_record_len,
                                 uint8_t *sensor_units_percentage,
                                 uint8_t *sensor_units_modifier,
                                 uint8_t *sensor_units_rate,
                                 uint8_t *sensor_base_unit_type,
                                 uint8_t *sensor_modifier_unit_type);

/* For Full, Compact SDR records */
int ipmi_sdr_parse_sensor_capabilities (ipmi_sdr_ctx_t ctx,
                                        const void *sdr_record,
                                        unsigned int sdr_record_len,
                                        uint8_t *event_message_control_support,
                                        uint8_t *threshold_access_support,
                                        uint8_t *hysteresis_support,
                                        uint8_t *auto_re_arm_support,
                                        uint8_t *entity_ignore_support);

/* For Full, Compact SDR records */
int ipmi_sdr_parse_sensor_direction (ipmi_sdr_ctx_t ctx,
                                     const void *sdr_record,
                                     unsigned int sdr_record_len,
                                     uint8_t *sensor_direction);

/* For Full, Compact SDR records */
/* event reading type must indicate a discrete sensor */
int ipmi_sdr_parse_assertion_supported (ipmi_sdr_ctx_t ctx,
                                        const void *sdr_record,
                                        unsigned int sdr_record_len,
                                        uint8_t *event_state_0,
                                        uint8_t *event_state_1,
                                        uint8_t *event_state_2,
                                        uint8_t *event_state_3,
                                        uint8_t *event_state_4,
                                        uint8_t *event_state_5,
                                        uint8_t *event_state_6,
                                        uint8_t *event_state_7,
                                        uint8_t *event_state_8,
                                        uint8_t *event_state_9,
                                        uint8_t *event_state_10,
                                        uint8_t *event_state_11,
                                        uint8_t *event_state_12,
                                        uint8_t *event_state_13,
                                        uint8_t *event_state_14);

/* For Full, Compact SDR records */
/* event reading type must indicate a discrete sensor */
int ipmi_sdr_parse_deassertion_supported (ipmi_sdr_ctx_t ctx,
                                          const void *sdr_record,
                                          unsigned int sdr_record_len,
                                          uint8_t *event_state_0,
                                          uint8_t *event_state_1,
                                          uint8_t *event_state_2,
                                          uint8_t *event_state_3,
                                          uint8_t *event_state_4,
                                          uint8_t *event_state_5,
                                          uint8_t *event_state_6,
                                          uint8_t *event_state_7,
                                          uint8_t *event_state_8,
                                          uint8_t *event_state_9,
                                          uint8_t *event_state_10,
                                          uint8_t *event_state_11,
                                          uint8_t *event_state_12,
                                          uint8_t *event_state_13,
                                          uint8_t *event_state_14);

/* For Full SDR records */
/* event reading type must indicate a threshold sensor */
int ipmi_sdr_parse_threshold_assertion_supported (ipmi_sdr_ctx_t ctx,
                                                  const void *sdr_record,
                                                  unsigned int sdr_record_len,
                                                  uint8_t *lower_non_critical_going_low,
                                                  uint8_t *lower_non_critical_going_high,
                                                  uint8_t *lower_critical_going_low,
                                                  uint8_t *lower_critical_going_high,
                                                  uint8_t *lower_non_recoverable_going_low,
                                                  uint8_t *lower_non_recoverable_going_high,
                                                  uint8_t *upper_non_critical_going_low,
                                                  uint8_t *upper_non_critical_going_high,
                                                  uint8_t *upper_critical_going_low,
                                                  uint8_t *upper_critical_going_high,
                                                  uint8_t *upper_non_recoverable_going_low,
                                                  uint8_t *upper_non_recoverable_going_high);

/* For Full SDR records */
/* event reading type must indicate a threshold sensor */
int ipmi_sdr_parse_threshold_deassertion_supported (ipmi_sdr_ctx_t ctx,
                                                    const void *sdr_record,
                                                    unsigned int sdr_record_len,
                                                    uint8_t *lower_non_critical_going_low,
                                                    uint8_t *lower_non_critical_going_high,
                                                    uint8_t *lower_critical_going_low,
                                                    uint8_t *lower_critical_going_high,
                                                    uint8_t *lower_non_recoverable_going_low,
                                                    uint8_t *lower_non_recoverable_going_high,
                                                    uint8_t *upper_non_critical_going_low,
                                                    uint8_t *upper_non_critical_going_high,
                                                    uint8_t *upper_critical_going_low,
                                                    uint8_t *upper_critical_going_high,
                                                    uint8_t *upper_non_recoverable_going_low,
                                                    uint8_t *upper_non_recoverable_going_high);

/* For Full SDR records */
/* event reading type must indicate a threshold sensor */
int ipmi_sdr_parse_threshold_readable (ipmi_sdr_ctx_t ctx,
                                       const void *sdr_record,
                                       unsigned int sdr_record_len,
                                       uint8_t *lower_non_critical_threshold,
                                       uint8_t *lower_critical_threshold,
                                       uint8_t *lower_non_recoverable_threshold,
                                       uint8_t *upper_non_critical_threshold,
                                       uint8_t *upper_critical_threshold,
                                       uint8_t *upper_non_recoverable_threshold);

/* For Full SDR records */
/* event reading type must indicate a threshold sensor */
int ipmi_sdr_parse_threshold_settable (ipmi_sdr_ctx_t ctx,
                                       const void *sdr_record,
                                       unsigned int sdr_record_len,
                                       uint8_t *lower_non_critical_threshold,
                                       uint8_t *lower_critical_threshold,
                                       uint8_t *lower_non_recoverable_threshold,
                                       uint8_t *upper_non_critical_threshold,
                                       uint8_t *upper_critical_threshold,
                                       uint8_t *upper_non_recoverable_threshold);

/* For Full SDR records */
/* b_exponent - sometimes documented as k1 */
/* r_exponent - sometimes documented as k2 */
int ipmi_sdr_parse_sensor_decoding_data (ipmi_sdr_ctx_t ctx,
                                         const void *sdr_record,
                                         unsigned int sdr_record_len,
                                         int8_t *r_exponent,
                                         int8_t *b_exponent,
                                         int16_t *m,
                                         int16_t *b,
                                         uint8_t *linearization,
                                         uint8_t *analog_data_format);

/* For Full SDR records */
int ipmi_sdr_parse_sensor_reading_ranges_specified (ipmi_sdr_ctx_t ctx,
                                                    const void *sdr_record,
                                                    unsigned int sdr_record_len,
                                                    uint8_t *nominal_reading_specified,
                                                    uint8_t *normal_maximum_specified,
                                                    uint8_t *normal_minimum_specified);

/* For Full SDR records */
/* Results must be freed by user */
int ipmi_sdr_parse_sensor_reading_ranges (ipmi_sdr_ctx_t ctx,
                                          const void *sdr_record,
                                          unsigned int sdr_record_len,
                                          double **nominal_reading,
                                          double **normal_maximum,
                                          double **normal_minimum,
                                          double **sensor_maximum_reading,
                                          double **sensor_minimum_reading);

/* For Full SDR records */
/* Results must be freed by user */
int ipmi_sdr_parse_thresholds (ipmi_sdr_ctx_t ctx,
                               const void *sdr_record,
                               unsigned int sdr_record_len,
                               double **lower_non_critical_threshold,
                               double **lower_critical_threshold,
                               double **lower_non_recoverable_threshold,
                               double **upper_non_critical_threshold,
                               double **upper_critical_threshold,
                               double **upper_non_recoverable_threshold);


/* For Full SDR records */
int ipmi_sdr_parse_thresholds_raw (ipmi_sdr_ctx_t ctx,
                                   const void *sdr_record,
                                   unsigned int sdr_record_len,
                                   uint8_t *lower_non_critical_threshold,
                                   uint8_t *lower_critical_threshold,
                                   uint8_t *lower_non_recoverable_threshold,
                                   uint8_t *upper_non_critical_threshold,
                                   uint8_t *upper_critical_threshold,
                                   uint8_t *upper_non_recoverable_threshold);

/* For Full SDR records */
/* Results must be freed by user */
int ipmi_sdr_parse_tolerance (ipmi_sdr_ctx_t ctx,
                              const void *sdr_record,
                              unsigned int sdr_record_len,
                              double **tolerance);

/* For Full SDR records */
/* Result returned is in percentage */
/* Results must be freed by user */
int ipmi_sdr_parse_accuracy (ipmi_sdr_ctx_t ctx,
                             const void *sdr_record,
                             unsigned int sdr_record_len,
                             double **tolerance);

/* For Full SDR records */
int ipmi_sdr_parse_hysteresis (ipmi_sdr_ctx_t ctx,
                               const void *sdr_record,
                               unsigned int sdr_record_len,
                               uint8_t *positive_going_threshold_hysteresis,
                               uint8_t *negative_going_threshold_hysteresis);

/* For Compact SDR records */
int ipmi_sdr_parse_sensor_record_sharing (ipmi_sdr_ctx_t ctx,
                                          const void *sdr_record,
                                          unsigned int sdr_record_len,
                                          uint8_t *share_count,
                                          uint8_t *id_string_instance_modifier_type,
                                          uint8_t *id_string_instance_modifier_offset,
                                          uint8_t *entity_instance_sharing);

/* For Entity Association, Device Relative Entity Association SDR
   records */
int ipmi_sdr_parse_container_entity (ipmi_sdr_ctx_t ctx,
                                     const void *sdr_record,
                                     unsigned int sdr_record_len,
                                     uint8_t *container_entity_id,
                                     uint8_t *container_entity_instance);

/* For Generic Device Locator, FRU Device Locator, Management
   Controller Device Locator SDR records */
/* return length of data read into buffer on success, -1 on error */
int ipmi_sdr_parse_device_id_string (ipmi_sdr_ctx_t ctx,
                                     const void *sdr_record,
                                     unsigned int sdr_record_len,
                                     char *device_id_string,
                                     unsigned int device_id_string_len);

/* For Generic Device Locator, FRU Device Locator SDR records */
int ipmi_sdr_parse_device_type (ipmi_sdr_ctx_t ctx,
                                const void *sdr_record,
                                unsigned int sdr_record_len,
                                uint8_t *device_type,
                                uint8_t *device_type_modifier);

/* For Generic Device Locator SDR records */
int ipmi_sdr_parse_generic_device_locator_parameters (ipmi_sdr_ctx_t ctx,
                                                      const void *sdr_record,
                                                      unsigned int sdr_record_len,
                                                      uint8_t *device_access_address,
                                                      uint8_t *channel_number,
                                                      uint8_t *device_slave_address,
                                                      uint8_t *private_bus_id,
                                                      uint8_t *lun_for_master_write_read_command,
                                                      uint8_t *address_span,
                                                      uint8_t *oem);

/* For FRU Device Locator SDR records */
int ipmi_sdr_parse_fru_device_locator_parameters (ipmi_sdr_ctx_t ctx,
                                                  const void *sdr_record,
                                                  unsigned int sdr_record_len,
                                                  uint8_t *device_access_address,
                                                  uint8_t *logical_fru_device_device_slave_address,
                                                  uint8_t *private_bus_id,
                                                  uint8_t *lun_for_master_write_read_fru_command,
                                                  uint8_t *logical_physical_fru_device,
                                                  uint8_t *channel_number);

/* For FRU Device Locator SDR records */
int ipmi_sdr_parse_fru_entity_id_and_instance (ipmi_sdr_ctx_t ctx,
                                               const void *sdr_record,
                                               unsigned int sdr_record_len,
                                               uint8_t *fru_entity_id,
                                               uint8_t *fru_entity_instance);

/* For Management Controller Device Locator SDR records */
int ipmi_sdr_parse_management_controller_device_locator_parameters (ipmi_sdr_ctx_t ctx,
                                                                    const void *sdr_record,
                                                                    unsigned int sdr_record_len,
                                                                    uint8_t *device_slave_address,
                                                                    uint8_t *channel_number,
								    uint8_t *global_initialization_event_message_generation,
								    uint8_t *global_initialization_log_initialization_agent_errors,
								    uint8_t *global_initialization_controller_logs_initialization_agent_errors,
								    uint8_t *power_state_notification_controller,
								    uint8_t *power_state_notification_acpi_device_power_state_notification,
								    uint8_t *power_state_notification_acpi_system_power_state_notification,
								    uint8_t *device_capabilities_sensor_device,
								    uint8_t *device_capabilities_sdr_repository_device,
								    uint8_t *device_capabilities_sel_device,
								    uint8_t *device_capabilities_fru_inventory_device,
								    uint8_t *device_capabilities_ipmb_event_receiver,
								    uint8_t *device_capabilities_ipmb_event_generator,
								    uint8_t *device_capabilities_bridge,
								    uint8_t *device_capabilities_chassis_device);

/* For Management Controller Confirmation, OEM SDR records */
int ipmi_sdr_parse_manufacturer_id (ipmi_sdr_ctx_t ctx,
                                    const void *sdr_record,
                                    unsigned int sdr_record_len,
                                    uint32_t *manufacturer_id);

/* For Management Controller Confirmation SDR records */
int ipmi_sdr_parse_product_id (ipmi_sdr_ctx_t ctx,
                               const void *sdr_record,
                               unsigned int sdr_record_len,
                               uint16_t *product_id);

/* For OEM SDR records */
/* return length of data read into buffer on success, -1 on error */
int ipmi_sdr_parse_oem_data (ipmi_sdr_ctx_t ctx,
                             const void *sdr_record,
                             unsigned int sdr_record_len,
                             void *oem_data,
                             unsigned int oem_data_len);

/*
 * SDR Cache Utility Functions
 */

int ipmi_sdr_cache_delete (ipmi_sdr_ctx_t ctx, const char *filename);

/* ipmi_sensor_parse_sensor_name_string
 * - Wrapper that will return id_string or device_id_string dependent
 *   on SDR type.
 * - Based on flags, will deal with shared sensors and alter sensor
 *   name if necessary.
 * - if sdr_record is NULL and sdr_record_len is 0, the current sdr
 *   record in the iterator will be used in parsing.
 */
/* For Full, Compact, Event, Generic Device Locator, FRU Device
 * Locator, and Management Controller Device Locator SDR records
 */
/* returns length written into buffer on success, -1 on error */
int ipmi_sdr_parse_sensor_name (ipmi_sdr_ctx_t ctx,
				const void *sdr_record,
				unsigned int sdr_record_len,
				uint8_t sensor_number,
				unsigned int flags,
				char *buf,
				unsigned int buflen);

/* ipmi_sensor_parse_entity_sensor_name
 * - Creates sensor names with the entity id and instance for better
 *   names on some systems.
 * - For example, on some systems sensor ID strings are all called
 *   "Temp".  The entity ID and instance are needed to turn the name
 *   into "Processor 1 Temp" or "Processor 2 Temp".
 * - Based on flags, will deal with shared sensors and alter sensor
 *   name if necessary.
 * - if sdr_record is NULL and sdr_record_len is 0, the current sdr
 *   record in the iterator will be used in parsing.
 */
/* For Full, Compact, Event, Generic Device Locator, and Management
 * Controller Device Locator SDR records
 */
/* returns length written into buffer on success, -1 on error */
int ipmi_sdr_parse_entity_sensor_name (ipmi_sdr_ctx_t ctx,
				       const void *sdr_record,
				       unsigned int sdr_record_len,
				       uint8_t sensor_number,
				       unsigned int flags,
				       char *buf,
				       unsigned int buflen);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_H */
