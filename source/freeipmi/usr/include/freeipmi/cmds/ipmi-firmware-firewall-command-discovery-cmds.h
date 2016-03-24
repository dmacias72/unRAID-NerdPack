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

#ifndef IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_H
#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_NETFN_LUN_SUPPORT_NO_COMMANDS_SUPPORTED                   0x0
#define IPMI_NETFN_LUN_SUPPORT_COMMANDS_FOLLOW_BASE_IPMI_SPECIFICATION 0x1
#define IPMI_NETFN_LUN_SUPPORT_COMMANDS_EXIST_ON_LUN                   0x2

#define IPMI_NETFN_PAIR_IS_NOT_USED 0x0
#define IPMI_NETFN_PAIR_IS_USED     0x1

#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_OPERATION_00H_TO_7FH 0x0
#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_OPERATION_80H_TO_FFH 0x1

#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_OPERATION_VALID(__val) \
  (((__val) == IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_OPERATION_00H_TO_7FH \
    || (__val) == IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_OPERATION_80H_TO_FFH) ? 1 : 0)

/* achu: Yes, this one is backwards.  I don't know why */
#define IPMI_COMMAND_AVAILABLE   0x0
#define IPMI_COMMAND_UNAVAILABLE 0x1

/* achu: Yes, this one is backwards.  I don't know why */
#define IPMI_SUB_FUNCTION_AVAILABLE   0x0
#define IPMI_SUB_FUNCTION_UNAVAILABLE 0x1

#define IPMI_COMMAND_NOT_CONFIGURABLE        0x0
#define IPMI_COMMAND_CAN_BE_ENABLED_DISABLED 0x1

#define IPMI_SUB_FUNCTION_NOT_CONFIGURABLE        0x0
#define IPMI_SUB_FUNCTION_CAN_BE_ENABLED_DISABLED 0x1

#define IPMI_COMMAND_DISABLED_OR_NOT_SUPPORTED 0x0
#define IPMI_COMMAND_ENABLED                   0x1

#define IPMI_SUB_FUNCTION_DISABLED_OR_NOT_SUPPORTED 0x0
#define IPMI_SUB_FUNCTION_ENABLED                   0x1

#define IPMI_SPECIFICATION_TYPE_IPMI 0x0
#define IPMI_SPECIFICATION_TYPE_IPMB 0x1
#define IPMI_SPECIFICATION_TYPE_ICMB 0x2

#define IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_ENABLE_DISABLE_BITMASK_LEN 16

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_get_netfn_support_rq;
extern fiid_template_t tmpl_cmd_get_netfn_support_rs;

extern fiid_template_t tmpl_cmd_get_command_support_rq;
extern fiid_template_t tmpl_cmd_get_command_support_rs;
extern fiid_template_t tmpl_cmd_get_command_sub_function_support_rq;
extern fiid_template_t tmpl_cmd_get_command_sub_function_support_specification_errata_rs;
extern fiid_template_t tmpl_cmd_get_command_sub_function_support_extension_errata_rs;

extern fiid_template_t tmpl_cmd_get_configurable_commands_rq;
extern fiid_template_t tmpl_cmd_get_configurable_commands_rs;
extern fiid_template_t tmpl_cmd_get_configurable_command_sub_functions_rq;
extern fiid_template_t tmpl_cmd_get_configurable_command_sub_functions_rs;

extern fiid_template_t tmpl_cmd_set_command_enables_rq;
extern fiid_template_t tmpl_cmd_set_command_enables_rs;
extern fiid_template_t tmpl_cmd_get_command_enables_rq;
extern fiid_template_t tmpl_cmd_get_command_enables_rs;

extern fiid_template_t tmpl_cmd_set_command_sub_function_enables_rq;
extern fiid_template_t tmpl_cmd_set_command_sub_function_enables_defining_body_code_rq;
extern fiid_template_t tmpl_cmd_set_command_sub_function_enables_oem_iana_rq;
extern fiid_template_t tmpl_cmd_set_command_sub_function_enables_rs;

extern fiid_template_t tmpl_cmd_get_command_sub_function_enables_rq;
extern fiid_template_t tmpl_cmd_get_command_sub_function_enables_rs;

extern fiid_template_t tmpl_cmd_get_oem_netfn_iana_support_rq;
extern fiid_template_t tmpl_cmd_get_oem_netfn_iana_support_rs;

int fill_cmd_get_netfn_support (uint8_t channel_number,
				fiid_obj_t obj_cmd_rq);

int fill_cmd_get_command_support (uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rq);

int fill_cmd_get_command_sub_function_support (uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t net_fn_data,
					       fiid_obj_t obj_cmd_rq);

int fill_cmd_get_configurable_commands (uint8_t channel_number,
					uint8_t net_fn,
					uint8_t operation,
					uint8_t lun,
					uint32_t net_fn_data,
					fiid_obj_t obj_cmd_rq);

int fill_cmd_get_configurable_command_sub_functions (uint8_t channel_number,
						     uint8_t net_fn,
						     uint8_t lun,
						     uint8_t command,
						     uint32_t net_fn_data,
						     fiid_obj_t obj_cmd_rq);

int fill_cmd_set_command_enables (uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint8_t *enable_disable_bitmask,
				  unsigned int enable_disable_bitmask_len,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rq);

int fill_cmd_get_command_enables (uint8_t channel_number,
				  uint8_t net_fn,
				  uint8_t operation,
				  uint8_t lun,
				  uint32_t net_fn_data,
				  fiid_obj_t obj_cmd_rq);

int fill_cmd_set_command_sub_function_enables (uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t sub_function_enables1,
					       uint32_t *sub_function_enables2,
					       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_command_sub_function_enables_defining_body_code (uint8_t channel_number,
								  uint8_t net_fn,
								  uint8_t lun,
								  uint8_t command,
								  uint8_t defining_body_code,
								  uint32_t sub_function_enables1,
								  uint32_t *sub_function_enables2,
								  fiid_obj_t obj_cmd_rq);

int fill_cmd_set_command_sub_function_enables_oem_iana (uint8_t channel_number,
							uint8_t net_fn,
							uint8_t lun,
							uint8_t command,
							uint32_t oem_iana,
							uint32_t sub_function_enables1,
							uint32_t *sub_function_enables2,
							fiid_obj_t obj_cmd_rq);

int fill_cmd_get_command_sub_function_enables (uint8_t channel_number,
					       uint8_t net_fn,
					       uint8_t lun,
					       uint8_t command,
					       uint32_t net_fn_data,
					       fiid_obj_t obj_cmd_rq);

int fill_cmd_get_oem_netfn_iana_support (uint8_t channel_number,
					 uint8_t net_fn,
					 uint8_t list_index,
					 fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FIRMWARE_FIREWALL_COMMAND_DISCOVERY_CMDS_H */
