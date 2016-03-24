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

#ifndef IPMI_SEL_H
#define IPMI_SEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/cmds/ipmi-sel-cmds.h>
#include <freeipmi/interpret/ipmi-interpret.h>
#include <freeipmi/sdr/ipmi-sdr.h>

#define IPMI_SEL_ERR_SUCCESS                                 0
#define IPMI_SEL_ERR_CONTEXT_NULL                            1
#define IPMI_SEL_ERR_CONTEXT_INVALID                         2
#define IPMI_SEL_ERR_PARAMETERS                              3
#define IPMI_SEL_ERR_OUT_OF_MEMORY                           4
#define IPMI_SEL_ERR_SDR_CACHE_ERROR                         5
#define IPMI_SEL_ERR_SEL_ENTRIES_NOT_LOADED                  6
#define IPMI_SEL_ERR_NO_SEL_ENTRIES                          7
#define IPMI_SEL_ERR_SEL_ENTRIES_LIST_END                    8
#define IPMI_SEL_ERR_INVALID_SEL_ENTRY                       9
#define IPMI_SEL_ERR_NOT_FOUND                              10 
#define IPMI_SEL_ERR_RESERVATION_CANCELED                   11
#define IPMI_SEL_ERR_INTERPRET_ERROR                        12 
#define IPMI_SEL_ERR_CALLBACK_ERROR                         13
#define IPMI_SEL_ERR_IPMI_ERROR                             14
#define IPMI_SEL_ERR_SYSTEM_ERROR                           15
#define IPMI_SEL_ERR_OVERFLOW                               16
#define IPMI_SEL_ERR_INTERNAL_ERROR                         17
#define IPMI_SEL_ERR_ERRNUMRANGE                            18

#define IPMI_SEL_FLAGS_DEFAULT                              0x0000
#define IPMI_SEL_FLAGS_DEBUG_DUMP                           0x0001
#define IPMI_SEL_FLAGS_ASSUME_SYTEM_EVENT_RECORDS           0x0002

#define IPMI_SEL_PARAMETER_INTERPRET_CONTEXT                0x0001
#define IPMI_SEL_PARAMETER_UTC_OFFSET                       0x0002

#define IPMI_SEL_STRING_FLAGS_DEFAULT                       0x0000
#define IPMI_SEL_STRING_FLAGS_VERBOSE                       0x0001
#define IPMI_SEL_STRING_FLAGS_IGNORE_UNAVAILABLE_FIELD      0x0002
#define IPMI_SEL_STRING_FLAGS_OUTPUT_NOT_AVAILABLE          0x0004
#define IPMI_SEL_STRING_FLAGS_DATE_USE_SLASH                0x0008
#define IPMI_SEL_STRING_FLAGS_DATE_MONTH_STRING             0x0010
#define IPMI_SEL_STRING_FLAGS_NON_ABBREVIATED_UNITS         0x0020
#define IPMI_SEL_STRING_FLAGS_ENTITY_SENSOR_NAMES           0x0040
#define IPMI_SEL_STRING_FLAGS_INTERPRET_OEM_DATA            0x0100
/* Timestamps are defined as localtime.  If there are UTC and
 * one wishes to output in localtime, this flag will do so.
 */
#define IPMI_SEL_STRING_FLAGS_UTC_TO_LOCALTIME              0x0200
/* Convert localtimes to UTC times, as it may be convenient
 * for certain purposes.
 */
#define IPMI_SEL_STRING_FLAGS_LOCALTIME_TO_UTC              0x0400
#define IPMI_SEL_STRING_FLAGS_LEGACY                        0x1000

#define IPMI_SEL_RECORD_TYPE_CLASS_SYSTEM_EVENT_RECORD               0x0
#define IPMI_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD            0x1
#define IPMI_SEL_RECORD_TYPE_CLASS_NON_TIMESTAMPED_OEM_RECORD        0x2
#define IPMI_SEL_RECORD_TYPE_CLASS_UNKNOWN                           0x3

#define IPMI_SEL_RECORD_ID_FIRST      IPMI_SEL_GET_RECORD_ID_FIRST_ENTRY
#define IPMI_SEL_RECORD_ID_LAST        IPMI_SEL_GET_RECORD_ID_LAST_ENTRY

typedef struct ipmi_sel_ctx *ipmi_sel_ctx_t;

typedef int (*Ipmi_Sel_Parse_Callback)(ipmi_sel_ctx_t ctx, void *callback_data);

/* 
 * SEL Context Functions
 */

/* ipmi_sel_ctx_create
 * - if specified, ipmi_ctx must be open and ready to go
 * - if NULL ipmi_ctx, SEL ctx cannot be used for SEL reading, only parsing records
 * - if specified, sdr_ctx cache must be open and ready for reading
 * - if NULL sdr_ctx, sdr won't be used
 */
ipmi_sel_ctx_t ipmi_sel_ctx_create (ipmi_ctx_t ipmi_ctx, ipmi_sdr_ctx_t sdr_ctx);
void ipmi_sel_ctx_destroy (ipmi_sel_ctx_t ctx);
int ipmi_sel_ctx_errnum (ipmi_sel_ctx_t ctx);
char * ipmi_sel_ctx_strerror (int errnum);
char * ipmi_sel_ctx_errormsg (ipmi_sel_ctx_t ctx);

/* SEL Parse flag functions and settings functions */
int ipmi_sel_ctx_get_flags (ipmi_sel_ctx_t ctx, unsigned int *flags);
int ipmi_sel_ctx_set_flags (ipmi_sel_ctx_t ctx, unsigned int flags);

/* for use w/ string parsing w/ IPMI_SEL_STRING_FLAGS_INTERPRET_OEM_DATA */
int ipmi_sel_ctx_get_manufacturer_id (ipmi_sel_ctx_t ctx, uint32_t *manufacturer_id);
int ipmi_sel_ctx_set_manufacturer_id (ipmi_sel_ctx_t ctx, uint32_t manufacturer_id);
int ipmi_sel_ctx_get_product_id (ipmi_sel_ctx_t ctx, uint16_t *product_id);
int ipmi_sel_ctx_set_product_id (ipmi_sel_ctx_t ctx, uint16_t product_id);
int ipmi_sel_ctx_get_ipmi_version (ipmi_sel_ctx_t ctx,
				   uint8_t *ipmi_version_major,
				   uint8_t *ipmi_vesion_minor);
int ipmi_sel_ctx_set_ipmi_version (ipmi_sel_ctx_t ctx,
				   uint8_t ipmi_version_major,
				   uint8_t ipmi_version_minor);
/* get/set parameters
 *
 * For misc uses.
 *
 * INTERPRET_CONTEXT - for use with %I - see below.  interpret_ctx
 * assumed loaded with whatever config desired for interpretation
 *
 * UTC_OFFSET - specific UTC offset to apply to timestamps (int)
 */
int ipmi_sel_ctx_get_parameter (ipmi_sel_ctx_t ctx,
				unsigned int parameter,
				void *ptr);

/* Pass NULL as ptr for default value */
int ipmi_sel_ctx_set_parameter (ipmi_sel_ctx_t ctx,
				unsigned int parameter,
				const void *ptr);

char *ipmi_sel_ctx_get_debug_prefix (ipmi_sel_ctx_t ctx);
int ipmi_sel_ctx_set_debug_prefix (ipmi_sel_ctx_t ctx, const char *debug_prefix);

/* determines separator between fields in string functions
 *
 * defaults to " | "
 */
char *ipmi_sel_ctx_get_separator (ipmi_sel_ctx_t ctx);
int ipmi_sel_ctx_set_separator (ipmi_sel_ctx_t ctx, const char *separator);

/* register/clear a reservation ID
 * - Almost all SEL operations use a reservation ID.  Generally
 *   speaking, it can be considered an advisory lock.  The same
 *   reservation ID can be used for all "read" operations and will only
 *   be canceled when some "write" operation has occurred on the SEL.
 *   This "write" operation could be a new SEL event, a SEL event that
 *   was deleted, etc.
 * - Normally, it is no big deal for a reservation ID to be canceled.
 *   The most normal circumstance is a new SEL event has been generated
 *   while reading the current list of SEL records.  Therefore, under
 *   most circumstances, this library will simple re-retrieve a
 *   reservation ID once it has noticed one has been canceled.
 * - These functions allow you to override the default functionality.
 *   You may inform the library to register a specific reservation ID
 *   and continue to use it for all SEL operations.  In the event that
 *   it has been canceled, a IPMI_SEL_ERR_RESERVATION_CANCELED
 *   errnum will be returned.
 * - These functions are predominantly useful for doing a set of
 *   operations and wanting to be informed of a possible race
 *   condition occurring.  For example, perhaps you wish to read all
 *   the SEL records, log them, then clear them.  There is a small
 *   window where a new SEL event could be generated, then cleared
 *   without the user knowing it ever existed.  Use of a fixed
 *   reservation ID would be a mechanism to notice this.
 * - In the event a reservation ID is canceled, it is up to the user
 *   to re-register a reservation ID, otherwise SEL operations will
 *   continue to default to grab its own reservation ID.
 * - In ipmi_sel_ctx_register_reservation_id(), an optional
 *   reservation_id can be passed to see what reservation ID was
 *   specifically registered.
 */
int ipmi_sel_ctx_register_reservation_id (ipmi_sel_ctx_t ctx, uint16_t *reservation_id);
int ipmi_sel_ctx_clear_reservation_id (ipmi_sel_ctx_t ctx);

/*
 * SEL Parse Functions
 */

/* ipmi_sel_parse and ipmi_sel_parse_record_ids
 * - callback is called after each SEL entry is parsed
 * - Returns the number of entries parsed
 */
int ipmi_sel_parse (ipmi_sel_ctx_t ctx,
                    uint16_t record_id_start,
                    uint16_t record_id_last,
                    Ipmi_Sel_Parse_Callback callback,
                    void *callback_data);

int ipmi_sel_parse_record_ids (ipmi_sel_ctx_t ctx,
                               uint16_t *record_ids,
                               unsigned int record_ids_len,
                               Ipmi_Sel_Parse_Callback callback,
                               void *callback_data);

/* SEL data retrieval functions after SEL is parsed
 *
 * seek_record_id moves the iterator to the closest record_id >= record_id
 * search_record_id finds the record id, will return NOT_FOUND if it can't be found
 */
int ipmi_sel_parse_first (ipmi_sel_ctx_t ctx);
int ipmi_sel_parse_next (ipmi_sel_ctx_t ctx);
int ipmi_sel_parse_sel_entry_count (ipmi_sel_ctx_t ctx);
int ipmi_sel_parse_seek_record_id (ipmi_sel_ctx_t ctx, uint16_t record_id);
int ipmi_sel_parse_search_record_id (ipmi_sel_ctx_t ctx, uint16_t record_id);

/* return length of data read into buffer on success, -1 on error */
int ipmi_sel_parse_read_record (ipmi_sel_ctx_t ctx,
                                void *buf,
                                unsigned int buflen);

/* SEL record parsing functions
 *
 * - if a sel_record is passed in, that sel_record is used for
 *   reading/parsing
 *
 * - if the sel_record is NULL sel_record_len is 0, the current sel
 *   parsed after ipmi_sel_parse() or ipmi_sel_parse_record_ids() is
 *   used.  It can be the record used within the iterator functions
 *   (i.e. ipmi_sel_parse_next()) or in callbacks.
 *
 * - will return IPMI_SEL_ERR_INVALID_SEL_ENTRY if current sel
 *   entry is not appropriate for data requested.
 */

/* record_id & record_type - works with all SEL record types */
int ipmi_sel_parse_read_record_id (ipmi_sel_ctx_t ctx,
				   const void *sel_record,
				   unsigned int sel_record_len,
				   uint16_t *record_id);

int ipmi_sel_parse_read_record_type (ipmi_sel_ctx_t ctx,
				     const void *sel_record,
				     unsigned int sel_record_len,
				     uint8_t *record_type);

/* timetamp - works with sel event and timestamped OEM record types */
int ipmi_sel_parse_read_timestamp (ipmi_sel_ctx_t ctx,
				   const void *sel_record,
				   unsigned int sel_record_len,
				   uint32_t *timestamp);

/* generator_id, event message format version, sensor type, sensor
 * number, event direction, event type code, and event data available
 * form system event record type
 */
int ipmi_sel_parse_read_generator_id (ipmi_sel_ctx_t ctx,
				      const void *sel_record,
				      unsigned int sel_record_len,
				      uint8_t *generator_id);

int ipmi_sel_parse_read_ipmb_device_lun (ipmi_sel_ctx_t ctx,
					 const void *sel_record,
					 unsigned int sel_record_len,
					 uint8_t *ipmb_device_lun);

int ipmi_sel_parse_read_channel_number (ipmi_sel_ctx_t ctx,
					const void *sel_record,
					unsigned int sel_record_len,
					uint8_t *channel_number);

int ipmi_sel_parse_read_event_message_format_version (ipmi_sel_ctx_t ctx,
						      const void *sel_record,
						      unsigned int sel_record_len,
						      uint8_t *event_message_format_version);

int ipmi_sel_parse_read_sensor_type (ipmi_sel_ctx_t ctx,
				     const void *sel_record,
				     unsigned int sel_record_len,
				     uint8_t *sensor_type);

int ipmi_sel_parse_read_sensor_number (ipmi_sel_ctx_t ctx,
				       const void *sel_record,
				       unsigned int sel_record_len,
				       uint8_t *sensor_number);

int ipmi_sel_parse_read_event_direction (ipmi_sel_ctx_t ctx,
					 const void *sel_record,
					 unsigned int sel_record_len,
					 uint8_t *event_direction);

int ipmi_sel_parse_read_event_type_code (ipmi_sel_ctx_t ctx,
					 const void *sel_record,
					 unsigned int sel_record_len,	
					 uint8_t *event_type_code);

int ipmi_sel_parse_read_event_data1 (ipmi_sel_ctx_t ctx,
				     const void *sel_record,
				     unsigned int sel_record_len,
				     uint8_t *event_data1);

int ipmi_sel_parse_read_event_data1_offset_from_event_reading_type_code (ipmi_sel_ctx_t ctx,
									 const void *sel_record,
									 unsigned int sel_record_len,
                                                                         uint8_t *event_data1_offset);

int ipmi_sel_parse_read_event_data1_event_data2_flag (ipmi_sel_ctx_t ctx,
						      const void *sel_record,
						      unsigned int sel_record_len,
                                                      uint8_t *event_data2_flag);

int ipmi_sel_parse_read_event_data1_event_data3_flag (ipmi_sel_ctx_t ctx,
						      const void *sel_record,
						      unsigned int sel_record_len,
                                                      uint8_t *event_data3_flag);

int ipmi_sel_parse_read_event_data2 (ipmi_sel_ctx_t ctx,
				     const void *sel_record,
				     unsigned int sel_record_len,
				     uint8_t *event_data2);

int ipmi_sel_parse_read_event_data3 (ipmi_sel_ctx_t ctx,
				     const void *sel_record,
				     unsigned int sel_record_len,
				     uint8_t *event_data3);

/* manufacturer_id - works with sel timestamped OEM record types */
int ipmi_sel_parse_read_manufacturer_id (ipmi_sel_ctx_t ctx,
					 const void *sel_record,
					 unsigned int sel_record_len,
					 uint32_t *manufacturer_id);

/* oem - works with sel timestamped and non-timestamped OEM record types */
/* return length of data read into buffer on success, -1 on error */
int ipmi_sel_parse_read_oem (ipmi_sel_ctx_t ctx,
			     const void *sel_record,
			     unsigned int sel_record_len,
			     void *buf,
			     unsigned int buflen);

/*
 * create a string output of the SEL entry.
 *
 * String format - availability for output dependent on SEL record
 * type.
 *
 * Available in all SEL record types
 *
 * %i - record ID in decimal
 * %I - event nominal vs. warning vs. critical interpretation [1]
 *
 * [1] - see libfreeipmi interpret library for information.  See
 * ipmi_sel_ctx_set_interpret_ctx().  If interpret context not
 * available, returns INTERPRET_ERROR.
 *
 * Available in SEL event and timestamped OEM SEL records
 *
 * %t - time in format H:M:S using 24 hour clock
 * %d - date in format D-M-YEAR
 *
 * Available in SEL event records
 *
 * %T - sensor type
 * %s - sensor name
 * %e - event data 1 string (usually offset from event/reading code type string)
 * %f - event data 2 string [2]
 * %h - event data 3 string
 * %c - combined event data 2 and event data 3 string [3]
 * %p - event data 2 previous state string [4]
 * %S - event data 2 severity string [4]
 * %E - combined event data 1, 2, and 3 string [5]
 * %k - event direction
 *
 * [2] - if a previous state and a severity state string are available
 * from a discrete sensor, they are concatenated with the defined
 * separator in between.
 *
 * [3] - for events where both event data 2 and event data 3 hold data
 * that must be combined for an effective output.  As an example, data
 * 2 holds a minor version number and data 3 holds a major version
 * number.  The combined output might print out "Version 1.2" instead
 * of a separated "Major Version 1 ; Minor Version 2" if you did them
 * separately.  If a combined output is not available or not
 * reasonable, event data 2 and event data 3 output will be output
 * separately with the defined separator between them
 * (e.g. effectively "%f ; %h").
 *
 * [4] - if event type code indicates a discrete sensor and event data 2
 * flag indicates a previous state and/or severity state is available.
 *
 * [5] - this can be loosely considered the equivalent of "%e" and
 * "%c" concatenated with the defined separator between them.
 * However, various corner cases will be handled for the user to
 * create a nicer output.  For example, "Foo ; NA" will never be
 * output.  This will be condensed into just "Foo".
 *
 * Available in timestamped OEM SEL records
 *
 * %m - manufacturer id
 *
 * Available in SEL timestamped and non-timestamped OEM record types
 *
 * %o - oem data in hex (or strings if interpreted OEM available)
 *
 * Available in all record types for certain manufacturers
 *
 * %O - output an OEM supplied string describing the event. [6]
 *
 * [6] On some motherboards, the vendor is capable of supplying a full
 * string describing the event data, in particular supplying strings
 * for OEM records and OEM event extensions.  Under the right
 * conditions, this output option may be used as a potential
 * replacement for %e, %f, %h, %c, and/or %E.  If an OEM supplied string
 * is not available, nothing will be output (with the exception of N/A
 * if the OUTPUT_NOT_AVAILABLE flag is set).  Currently, this output
 * option supports Fujitsu systems with iRMC S1/iRMC S2.
 *
 * Misc
 *
 * %% - percent sign
 *
 * flags
 *
 * VERBOSE
 *
 * Output slightly more verbose text for selected fields.  For example:
 *
 * - If a sensor does not have a name, output sensor number and
 *   generator id instead of just sensor number.
 * - If an event data string cannot be determined (i.e. it is OEM or
 *   not defined by IPMI), output both the data and event type code
 *   instead of just the event data.
 *
 * IGNORE_UNAVAILABLE_FIELD
 *
 * If a field is not available for output (for example, a timestamp field
 * in a SEL entry w/o a timestamp field), do not return an error.  Output
 * nothing.
 *
 * OUTPUT_NOT_AVAILABLE
 *
 * If a field is not available, do not output an empty string, output
 * "N/A" (sometimes must have IGNORE_UNAVAILABLE_FIELD set)
 *
 * DATE_USE_SLASH
 *
 * Use a '/' instead of hyphens when outputting the date.
 *
 * DATE_MONTH_STRING
 *
 * Output a month name (Jan, Feb, Mar, etc.) instead of the month
 * number when outputting the date.
 *
 * LEGACY
 *
 * Output strings in legacy format.
 *
 * Returns length of data written to buffer.  If >= buflen, no null
 * termination exists in buffer.
 */
int ipmi_sel_parse_read_record_string (ipmi_sel_ctx_t ctx,
				       const char *fmt,
				       const void *sel_record,
				       unsigned int sel_record_len,
				       char *buf,
				       unsigned int buflen,
				       unsigned int flags);

/*
 * SEL Utility functions
 */
int ipmi_sel_clear_sel (ipmi_sel_ctx_t ctx);

int ipmi_sel_delete_sel_entry (ipmi_sel_ctx_t ctx, uint16_t record_id);

int ipmi_sel_record_type_class (uint8_t record_type);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SEL_H */
