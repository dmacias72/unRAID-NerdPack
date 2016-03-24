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

#ifndef IPMI_SENSOR_CMDS_API_H
#define IPMI_SENSOR_CMDS_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/fiid/fiid.h>

/* 
 * ipmi_cmd* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rs must be for the function's respective fiid template
 * response.
 *
 */

int ipmi_cmd_get_device_sdr_info (ipmi_ctx_t ctx,
				  uint8_t operation,
				  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_device_sdr (ipmi_ctx_t ctx,
			     uint16_t reservation_id,
			     uint16_t record_id,
			     uint8_t offset_into_record,
			     uint8_t bytes_to_read,
			     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_reserve_device_sdr_repository (ipmi_ctx_t ctx,
					    fiid_obj_t obj_cmd_rs);

/* achu: as of IPMI 2.0 hysteresis_mask reserved for future - write as 0xFF */
int ipmi_cmd_set_sensor_hysteresis (ipmi_ctx_t ctx,
                                    uint8_t sensor_number,
                                    uint8_t hysteresis_mask,
                                    uint8_t positive_going_threshold_hysteresis_value,
                                    uint8_t negative_going_threshold_hysteresis_value,
                                    fiid_obj_t obj_cmd_rs);

/* achu: as of IPMI 2.0 hysteresis_mask reserved for future - write as 0xFF */
int ipmi_cmd_get_sensor_hysteresis (ipmi_ctx_t ctx,
                                    uint8_t sensor_number,
                                    uint8_t hysteresis_mask,
                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sensor_thresholds (ipmi_ctx_t ctx,
                                    uint8_t sensor_number,
                                    const uint8_t *lower_non_critical_threshold,
                                    const uint8_t *lower_critical_threshold,
                                    const uint8_t *lower_non_recoverable_threshold,
                                    const uint8_t *upper_non_critical_threshold,
                                    const uint8_t *upper_critical_threshold,
                                    const uint8_t *upper_non_recoverable_threshold,
                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_thresholds (ipmi_ctx_t ctx,
                                    uint8_t sensor_number,
                                    fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sensor_event_enable (ipmi_ctx_t ctx,
                                      uint8_t sensor_number,
                                      uint8_t event_message_action,
                                      uint8_t scanning_on_this_sensor,
                                      uint8_t all_event_messages,
                                      uint16_t assertion_event_bitmask,
                                      uint16_t deassertion_event_bitmask,
                                      fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sensor_event_enable_threshold (ipmi_ctx_t ctx,
                                                uint8_t sensor_number,
                                                uint8_t event_message_action,
                                                uint8_t scanning_on_this_sensor,
                                                uint8_t all_event_messages,
                                                uint8_t assertion_event_lower_non_critical_going_low,
                                                uint8_t assertion_event_lower_non_critical_going_high,
                                                uint8_t assertion_event_lower_critical_going_low,
                                                uint8_t assertion_event_lower_critical_going_high,
                                                uint8_t assertion_event_lower_non_recoverable_going_low,
                                                uint8_t assertion_event_lower_non_recoverable_going_high,
                                                uint8_t assertion_event_upper_non_critical_going_low,
                                                uint8_t assertion_event_upper_non_critical_going_high,
                                                uint8_t assertion_event_upper_critical_going_low,
                                                uint8_t assertion_event_upper_critical_going_high,
                                                uint8_t assertion_event_upper_non_recoverable_going_low,
                                                uint8_t assertion_event_upper_non_recoverable_going_high,
                                                uint8_t deassertion_event_lower_non_critical_going_low,
                                                uint8_t deassertion_event_lower_non_critical_going_high,
                                                uint8_t deassertion_event_lower_critical_going_low,
                                                uint8_t deassertion_event_lower_critical_going_high,
                                                uint8_t deassertion_event_lower_non_recoverable_going_low,
                                                uint8_t deassertion_event_lower_non_recoverable_going_high,
                                                uint8_t deassertion_event_upper_non_critical_going_low,
                                                uint8_t deassertion_event_upper_non_critical_going_high,
                                                uint8_t deassertion_event_upper_critical_going_low,
                                                uint8_t deassertion_event_upper_critical_going_high,
                                                uint8_t deassertion_event_upper_non_recoverable_going_low,
                                                uint8_t deassertion_event_upper_non_recoverable_going_high,
                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sensor_event_enable_discrete (ipmi_ctx_t ctx,
                                               uint8_t sensor_number,
                                               uint8_t event_message_action,
                                               uint8_t scanning_on_this_sensor,
                                               uint8_t all_event_messages,
                                               uint8_t assertion_event_state_bit_0,
                                               uint8_t assertion_event_state_bit_1,
                                               uint8_t assertion_event_state_bit_2,
                                               uint8_t assertion_event_state_bit_3,
                                               uint8_t assertion_event_state_bit_4,
                                               uint8_t assertion_event_state_bit_5,
                                               uint8_t assertion_event_state_bit_6,
                                               uint8_t assertion_event_state_bit_7,
                                               uint8_t assertion_event_state_bit_8,
                                               uint8_t assertion_event_state_bit_9,
                                               uint8_t assertion_event_state_bit_10,
                                               uint8_t assertion_event_state_bit_11,
                                               uint8_t assertion_event_state_bit_12,
                                               uint8_t assertion_event_state_bit_13,
                                               uint8_t assertion_event_state_bit_14,
                                               uint8_t deassertion_event_state_bit_0,
                                               uint8_t deassertion_event_state_bit_1,
                                               uint8_t deassertion_event_state_bit_2,
                                               uint8_t deassertion_event_state_bit_3,
                                               uint8_t deassertion_event_state_bit_4,
                                               uint8_t deassertion_event_state_bit_5,
                                               uint8_t deassertion_event_state_bit_6,
                                               uint8_t deassertion_event_state_bit_7,
                                               uint8_t deassertion_event_state_bit_8,
                                               uint8_t deassertion_event_state_bit_9,
                                               uint8_t deassertion_event_state_bit_10,
                                               uint8_t deassertion_event_state_bit_11,
                                               uint8_t deassertion_event_state_bit_12,
                                               uint8_t deassertion_event_state_bit_13,
                                               uint8_t deassertion_event_state_bit_14,
                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_event_enable (ipmi_ctx_t ctx,
                                      uint8_t sensor_number,
                                      fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_event_enable_threshold (ipmi_ctx_t ctx,
                                                uint8_t sensor_number,
                                                fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_event_enable_discrete (ipmi_ctx_t ctx,
                                               uint8_t sensor_number,
                                               fiid_obj_t obj_cmd_rs);

int ipmi_cmd_re_arm_sensor_events (ipmi_ctx_t ctx,
				   uint8_t sensor_number,
				   uint8_t re_arm_all_event_status_from_this_sensor,
				   uint16_t *re_arm_assertion_event,
				   uint16_t *re_arm_deassertion_event,
				   fiid_obj_t obj_cmd_rs);

int ipmi_cmd_re_arm_sensor_events_ipmb (ipmi_ctx_t ctx,
					uint8_t channel_number,
					uint8_t slave_address,
					uint8_t lun,
					uint8_t sensor_number,
					uint8_t re_arm_all_event_status_from_this_sensor,
					uint16_t *re_arm_assertion_event,
					uint16_t *re_arm_deassertion_event,
					fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_reading (ipmi_ctx_t ctx,
                                 uint8_t sensor_number,
                                 fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_reading_ipmb (ipmi_ctx_t ctx,
                                      uint8_t channel_number,
                                      uint8_t slave_address,
                                      uint8_t lun,
                                      uint8_t sensor_number,
                                      fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_reading_threshold (ipmi_ctx_t ctx,
                                           uint8_t sensor_number,
                                           fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_sensor_reading_discrete (ipmi_ctx_t ctx,
                                          uint8_t sensor_number,
                                          fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_sensor_reading_and_event_status (ipmi_ctx_t ctx,
						  uint8_t sensor_number,
						  uint8_t sensor_reading_operation,
						  uint8_t deassertion_bits_operation,
						  uint8_t assertion_bits_operation,
						  uint8_t event_data_bytes_operation,
						  uint8_t sensor_reading,
						  uint16_t assertion_event_bitmask,
						  uint16_t deassertion_event_bitmask,
						  uint8_t event_data1,
						  uint8_t event_data2,
						  uint8_t event_data3,
						  fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_CMDS_API_H */
