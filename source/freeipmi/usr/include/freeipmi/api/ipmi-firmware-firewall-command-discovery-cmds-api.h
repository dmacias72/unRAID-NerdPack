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

#ifndef IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_API_H
#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/fiid/fiid.h>

/* 
 * ipmi_cmd* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rs must be for the function's respective fiid template
 * response.
 *
 */

int ipmi_cmd_get_netfn_support (ipmi_ctx_t ctx, 
				uint8_t channel_number,
				fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_command_support (ipmi_ctx_t ctx, 
				  uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_command_sub_function_support (ipmi_ctx_t ctx, 
					       uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t net_fn_data,
					       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_configurable_commands (ipmi_ctx_t ctx, 
					uint8_t channel_number,
					uint8_t net_fn,
					uint8_t operation,
					uint8_t lun,
					uint32_t net_fn_data,
					fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_configurable_command_sub_functions (ipmi_ctx_t ctx, 
						     uint8_t channel_number,
						     uint8_t net_fn,
						     uint8_t lun,
						     uint8_t command,
						     uint32_t net_fn_data,
						     fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_command_enables (ipmi_ctx_t ctx, 
				  uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint8_t *enable_disable_bitmask,
				  unsigned int enable_disable_bitmask_len,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_command_enables (ipmi_ctx_t ctx, 
				  uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_command_sub_function_enables (ipmi_ctx_t ctx, 
					       uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t sub_function_enables1,
					       uint32_t *sub_function_enables2,
					       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_command_sub_function_enables_defining_body_code (ipmi_ctx_t ctx, 
								  uint8_t channel_number,
								  uint8_t net_fn,
								  uint8_t lun,
								  uint8_t command,
								  uint8_t defining_body_code,
								  uint32_t sub_function_enables1,
								  uint32_t *sub_function_enables2,
								  fiid_obj_t obj_cmd_rs);

int ipmi_cmd_set_command_sub_function_enables_oem_iana (ipmi_ctx_t ctx, 
							uint8_t channel_number,
							uint8_t net_fn,
							uint8_t lun,
							uint8_t command,
							uint32_t oem_iana,
							uint32_t sub_function_enables1,
							uint32_t *sub_function_enables2,
							fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_command_sub_function_enables (ipmi_ctx_t ctx, 
					       uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t net_fn_data,
					       fiid_obj_t obj_cmd_rs);

int ipmi_cmd_get_oem_netfn_iana_support (ipmi_ctx_t ctx, 
					 uint8_t channel_number,
					 uint8_t net_fn,
					 uint8_t list_index,
					 fiid_obj_t obj_cmd_rs);


#ifdef __cplusplus
}
#endif

#endif /* IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_API_H */
