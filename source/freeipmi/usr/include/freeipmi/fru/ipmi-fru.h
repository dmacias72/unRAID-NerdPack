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

#ifndef IPMI_FRU_H
#define IPMI_FRU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>

#define IPMI_FRU_ERR_SUCCESS                                 0
#define IPMI_FRU_ERR_CONTEXT_NULL                            1
#define IPMI_FRU_ERR_CONTEXT_INVALID                         2
#define IPMI_FRU_ERR_PARAMETERS                              3
#define IPMI_FRU_ERR_DEVICE_ID_NOT_OPEN                      4
#define IPMI_FRU_ERR_DEVICE_ID_ALREADY_OPEN                  5
#define IPMI_FRU_ERR_NO_FRU_INFORMATION                      6
#define IPMI_FRU_ERR_FRU_AREA_LENGTH_INVALID                 7
#define IPMI_FRU_ERR_COMMON_HEADER_CHECKSUM_INVALID          8
#define IPMI_FRU_ERR_CHASSIS_INFO_AREA_CHECKSUM_INVALID      9
#define IPMI_FRU_ERR_BOARD_INFO_AREA_CHECKSUM_INVALID       10
#define IPMI_FRU_ERR_PRODUCT_INFO_AREA_CHECKSUM_INVALID     11
#define IPMI_FRU_ERR_MULTIRECORD_AREA_CHECKSUM_INVALID      12
#define IPMI_FRU_ERR_COMMON_HEADER_FORMAT_INVALID           13
#define IPMI_FRU_ERR_CHASSIS_INFO_AREA_FORMAT_INVALID       14
#define IPMI_FRU_ERR_BOARD_INFO_AREA_FORMAT_INVALID         15
#define IPMI_FRU_ERR_PRODUCT_INFO_AREA_FORMAT_INVALID       16
#define IPMI_FRU_ERR_MULTIRECORD_AREA_FORMAT_INVALID        17
#define IPMI_FRU_ERR_FRU_INFORMATION_INCONSISTENT           18
#define IPMI_FRU_ERR_FRU_LANGUAGE_CODE_NOT_SUPPORTED        19
#define IPMI_FRU_ERR_FRU_INVALID_BCD_ENCODING               20
#define IPMI_FRU_ERR_FRU_SENTINEL_VALUE_NOT_FOUND           21
#define IPMI_FRU_ERR_NOT_AVAILABLE_FOR_THIS_RECORD          22
#define IPMI_FRU_ERR_OVERFLOW                               23
#define IPMI_FRU_ERR_OUT_OF_MEMORY                          24
#define IPMI_FRU_ERR_DEVICE_BUSY                            25
#define IPMI_FRU_ERR_IPMI_ERROR                             26
#define IPMI_FRU_ERR_SYSTEM_ERROR                           27
#define IPMI_FRU_ERR_INTERNAL_ERROR                         28
#define IPMI_FRU_ERR_ERRNUMRANGE                            29

#define IPMI_FRU_FLAGS_DEFAULT                              0x0000
#define IPMI_FRU_FLAGS_DEBUG_DUMP                           0x0001
#define IPMI_FRU_FLAGS_SKIP_CHECKSUM_CHECKS                 0x0002
#define IPMI_FRU_FLAGS_INTERPRET_OEM_DATA                   0x0004
/* Do not parse FRU inventory information like normal
 * - iterator functions no longer serve purpose
 * - ipmi_fru_read_data_area will read as much data as in 
 *   can into buffer.
 */
#define IPMI_FRU_FLAGS_READ_RAW                             0x0008

#define IPMI_FRU_AREA_TYPE_CHASSIS_INFO_AREA                          0
#define IPMI_FRU_AREA_TYPE_BOARD_INFO_AREA                            1
#define IPMI_FRU_AREA_TYPE_PRODUCT_INFO_AREA                          2
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_POWER_SUPPLY_INFORMATION       3
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_DC_OUTPUT                      4
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_DC_LOAD                        5
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_MANAGEMENT_ACCESS_RECORD       6
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_BASE_COMPATABILITY_RECORD      7
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_COMPATABILITY_RECORD  8
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_FIXED_SMBUS_DEVICE_RECORD  9
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_LEGACY_DEVICE_ALERTS      10
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_ASF_REMOTE_CONTROL            11
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_DC_OUTPUT            12
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_EXTENDED_DC_LOAD              13
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_NVM_EXPRESS                   14
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_OEM                           15
#define IPMI_FRU_AREA_TYPE_MULTIRECORD_UNKNOWN                       16
#define IPMI_FRU_AREA_TYPE_RAW_DATA                                  17

/* multirecord length field is 1 byte => max 256 chars.  Round up to
 * 512 for good measure.
 */
#define IPMI_FRU_AREA_TYPE_LENGTH_FIELD_MAX                         512

/* length field is 6 bits = 64 bytes of text, x2 b/c could be hex
 * output, x2 because of possible space in between hex output and 'h'
 * at end of hex output, x2 for extra measure.  This length is
 * sufficient for 6-bit ASCII as well, since you have 4 chars / 3
 * bytes.
 */
#define IPMI_FRU_AREA_STRING_MAX                                    512

/* 16 bit field for length */
#define IPMI_FRU_AREA_SIZE_MAX                                    65536

struct ipmi_fru_field
{
  uint8_t type_length_field[IPMI_FRU_AREA_TYPE_LENGTH_FIELD_MAX];
  /* store length of data stored in buffer */
  unsigned int type_length_field_length;
};

typedef struct ipmi_fru_field ipmi_fru_field_t;

typedef struct ipmi_fru_ctx *ipmi_fru_ctx_t;

/* FRU Parse Context Functions
 * - if specified, ipmi_ctx must be open and ready to go
 * - if NULL ipmi_ctx, FRU ctx cannot be used for FRU reading, only parsing records
 */
ipmi_fru_ctx_t ipmi_fru_ctx_create (ipmi_ctx_t ipmi_ctx);
void ipmi_fru_ctx_destroy (ipmi_fru_ctx_t ctx);
int ipmi_fru_ctx_errnum (ipmi_fru_ctx_t ctx);
char * ipmi_fru_ctx_strerror (int errnum);
char * ipmi_fru_ctx_errormsg (ipmi_fru_ctx_t ctx);

/* FRU Parse flag functions */
int ipmi_fru_ctx_get_flags (ipmi_fru_ctx_t ctx, unsigned int *flags);
int ipmi_fru_ctx_set_flags (ipmi_fru_ctx_t ctx, unsigned int flags);
/* for use w/ IPMI_FRU_FLAGS_INTERPRET_OEM_DATA */
int ipmi_fru_ctx_get_manufacturer_id (ipmi_fru_ctx_t ctx, uint32_t *manufacturer_id);
int ipmi_fru_ctx_set_manufacturer_id (ipmi_fru_ctx_t ctx, uint32_t manufacturer_id);
/* for use w/ IPMI_FRU_FLAGS_INTERPRET_OEM_DATA */
int ipmi_fru_ctx_get_product_id (ipmi_fru_ctx_t ctx, uint16_t *product_id);
int ipmi_fru_ctx_set_product_id (ipmi_fru_ctx_t ctx, uint16_t product_id);
char *ipmi_fru_ctx_get_debug_prefix (ipmi_fru_ctx_t ctx);
int ipmi_fru_ctx_set_debug_prefix (ipmi_fru_ctx_t ctx, const char *debug_prefix);

/* FRU data retrieval setup functions */
int ipmi_fru_open_device_id (ipmi_fru_ctx_t ctx, uint8_t fru_device_id);
int ipmi_fru_close_device_id (ipmi_fru_ctx_t ctx);

/* FRU data iterator functions */
int ipmi_fru_first (ipmi_fru_ctx_t ctx);
/* returns 1 if iterator can continue, 0 if at end, -1 on error */
int ipmi_fru_next (ipmi_fru_ctx_t ctx);

/* area read will not include record headers */
/* utiliize area_type and area_length in/out parameters for later parsing */
/* if reading in raw mode, read as much data as you can into buffer
 * - area_length will return total size of data that exists
 * - area_type will return IPMI_FRU_AREA_TYPE_RAW_DATA
 */
int ipmi_fru_read_data_area (ipmi_fru_ctx_t ctx,
			     unsigned int *area_type,
			     unsigned int *area_length,
			     void *areabuf,
			     unsigned int areabuflen);

/* most useful for OEM record handling, will error if not at a multirecord area */
int ipmi_fru_read_multirecord_record_type_id (ipmi_fru_ctx_t ctx,
					      uint8_t *record_type_id);
                         
/* FRU area parsing */
/* Functions assume record headers have been stripped out */

int ipmi_fru_chassis_info_area (ipmi_fru_ctx_t ctx,
				const void *areabuf,
				unsigned int areabuflen,
				uint8_t *chassis_type,
				ipmi_fru_field_t *chassis_part_number,
				ipmi_fru_field_t *chassis_serial_number,
				ipmi_fru_field_t *chassis_custom_fields,
				unsigned int chassis_custom_fields_len);

/* mfg_date_time returned in seconds since unix epoch, not FRU defined epoch */
int ipmi_fru_board_info_area (ipmi_fru_ctx_t ctx,
			      const void *areabuf,
			      unsigned int areabuflen,
			      uint8_t *language_code,
			      uint32_t *mfg_date_time,
			      ipmi_fru_field_t *board_manufacturer,
			      ipmi_fru_field_t *board_product_name,
			      ipmi_fru_field_t *board_serial_number,
			      ipmi_fru_field_t *board_part_number,
			      ipmi_fru_field_t *board_fru_file_id,
			      ipmi_fru_field_t *board_custom_fields,
			      unsigned int chassis_custom_fields_len);

int ipmi_fru_product_info_area (ipmi_fru_ctx_t ctx,
				const void *areabuf,
				unsigned int areabuflen,
				uint8_t *language_code,
				ipmi_fru_field_t *product_manufacturer_name,
				ipmi_fru_field_t *product_name,
				ipmi_fru_field_t *product_part_model_number,
				ipmi_fru_field_t *product_version,
				ipmi_fru_field_t *product_serial_number,
				ipmi_fru_field_t *product_asset_tag,
				ipmi_fru_field_t *product_fru_file_id,
				ipmi_fru_field_t *product_custom_fields,
				unsigned int product_custom_fields_len);

/* 10 mV multipliers factored in return voltages */
/* FRU Revision 1.2 renamed ac_dropout_tolerance to input_dropout_tolerance, are identical */
int ipmi_fru_multirecord_power_supply_information (ipmi_fru_ctx_t ctx,
						   const void *areabuf,
						   unsigned int areabuflen,
						   unsigned int *overall_capacity,
						   unsigned int *peak_va,
						   unsigned int *inrush_current,
						   unsigned int *inrush_interval,
						   int *low_end_input_voltage_range_1,
						   int *high_end_input_voltage_range_1,
						   int *low_end_input_voltage_range_2,
						   int *high_end_input_voltage_range_2,
						   unsigned int *low_end_input_frequency_range,
						   unsigned int *high_end_input_frequency_range,
						   unsigned int *ac_dropout_tolerance,
						   unsigned int *predictive_fail_support,
						   unsigned int *power_factor_correction,
						   unsigned int *autoswitch,
						   unsigned int *hot_swap_support,
						   unsigned int *tachometer_pulses_per_rotation_predictive_fail_polarity,
						   unsigned int *peak_capacity,
						   unsigned int *hold_up_time,
						   unsigned int *voltage_1,
						   unsigned int *voltage_2,
						   unsigned int *total_combined_wattage,
						   unsigned int *predictive_fail_tachometer_lower_threshold);

/* 10 mV multipliers factored in return voltages */
int ipmi_fru_multirecord_dc_output (ipmi_fru_ctx_t ctx,
				    const void *areabuf,
				    unsigned int areabuflen,
				    unsigned int *output_number,
				    unsigned int *standby,
				    int *nominal_voltage,
				    int *maximum_negative_voltage_deviation,
				    int *maximum_positive_voltage_deviation,
				    unsigned int *ripple_and_noise_pk_pk,
				    unsigned int *minimum_current_draw,
				    unsigned int *maximum_current_draw);

/* 10 mV multipliers factored in return voltages */
int ipmi_fru_multirecord_dc_load (ipmi_fru_ctx_t ctx,
				  const void *areabuf,
				  unsigned int areabuflen,
				  unsigned int *output_number,
				  unsigned int *standby,
				  int *nominal_voltage,
				  int *specd_minimum_voltage,
				  int *specd_maximum_voltage,
				  unsigned int *specd_ripple_and_noise_pk_pk,
				  unsigned int *minimum_current_load,
				  unsigned int *maximum_current_load);

int ipmi_fru_multirecord_management_access_record (ipmi_fru_ctx_t ctx,
						   const void *areabuf,
						   unsigned int areabuflen,
						   uint8_t *sub_record_type,
						   void *sub_record_data,
						   unsigned int *sub_record_data_len);
  
int ipmi_fru_multirecord_base_compatibility_record (ipmi_fru_ctx_t ctx,
						    const void *areabuf,
						    unsigned int areabuflen,
						    uint32_t *manufacturer_id,
						    unsigned int *entity_id_code,
						    unsigned int *compatibility_base,
						    unsigned int *compatibility_code_start_value,
						    uint8_t *code_range_mask,
						    unsigned int *code_range_mask_len);

int ipmi_fru_multirecord_extended_compatibility_record (ipmi_fru_ctx_t ctx,
							const void *areabuf,
							unsigned int areabuflen,
							uint32_t *manufacturer_id,
							unsigned int *entity_id_code,
							unsigned int *compatibility_base,
							unsigned int *compatibility_code_start_value,
							uint8_t *code_range_mask,
							unsigned int *code_range_mask_len);

/* 10 mV multipliers factored in return voltages */
/* draw in mA units, already factoring in current_units */
int ipmi_fru_multirecord_extended_dc_output (ipmi_fru_ctx_t ctx,
					     const void *areabuf,
					     unsigned int areabuflen,
					     unsigned int *output_number,
					     unsigned int *current_units,
					     unsigned int *standby,
					     int *nominal_voltage,
					     int *maximum_negative_voltage_deviation,
					     int *maximum_positive_voltage_deviation,
					     unsigned int *ripple_and_noise_pk_pk,
					     unsigned int *minimum_current_draw,
					     unsigned int *maximum_current_draw);

/* 10 mV multipliers factored in return voltages */
/* load in mA units, already factoring in current_units */
int ipmi_fru_multirecord_extended_dc_load (ipmi_fru_ctx_t ctx,
					   const void *areabuf,
					   unsigned int areabuflen,
					   unsigned int *output_number,
					   unsigned int *current_units,
					   unsigned int *standby,
					   int *nominal_voltage,
					   int *specd_minimum_voltage,
					   int *specd_maximum_voltage,
					   unsigned int *specd_ripple_and_noise_pk_pk,
					   unsigned int *minimum_current_load,
					   unsigned int *maximum_current_load);

int ipmi_fru_multirecord_oem_record (ipmi_fru_ctx_t ctx,
				     const void *areabuf,
				     unsigned int areabuflen,
				     uint32_t *manufacturer_id,
				     void *oem_data,
				     unsigned int *oem_data_len);

/* FRU utility functions */
/* Typically pass in buffer and length from ipmi_fru_field_t
 * after info area is parsed.  strbuflen is an in/out value.  input
 * indicates length of buffer, output indicates bytes written to
 * buffer.
 */
int ipmi_fru_type_length_field_to_string (ipmi_fru_ctx_t ctx,
					  const uint8_t *type_length_buf,
					  unsigned int type_length_buflen,
					  uint8_t language_code,
					  char *strbuf,
					  unsigned int *strbuflen);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_H */
