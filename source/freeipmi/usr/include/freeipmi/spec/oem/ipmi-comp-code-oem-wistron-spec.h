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

#ifndef IPMI_COMP_CODE_OEM_WISTRON_SPEC_H
#define IPMI_COMP_CODE_OEM_WISTRON_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Wistron / Dell Poweredge C6220
 */

/* IPMI_CMD_OEM_WISTRON_GET_CHASSIS_LED_STATUS */
#define IPMI_COMP_CODE_OEM_WISTON_GET_CHASSIS_LED_STATUS_NOT_YET_RECEIVED_ANY_INFORMATION_FROM_SATELLITE_CONTROLLER 0x80
#define IPMI_COMP_CODE_OEM_WISTON_GET_CHASSIS_LED_STATUS_NOT_YET_RECEIVED_ANY_INFORMATION_FROM_SATELLITE_CONTROLLER_STR \
  "Not yet received any information from Satellite Controller"

#define IPMI_COMP_CODE_OEM_WISTON_GET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_NOT_REPORTING_FOR_MORE_THAN_10_CONSECUTIVE_SECONDS 0x81
#define IPMI_COMP_CODE_OEM_WISTON_GET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_NOT_REPORTING_FOR_MORE_THAN_10_CONSECUTIVE_SECONDS_STR \
  "Satellite Controller Not Reporting for more than 10 consecutive seconds, but SC was alive before"

/* IPMI_CMD_OEM_WISTRON_SET_CHASSIS_LED_STATUS */
#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_NOT_YET_RECEIVED_ANY_INFORMATION_FROM_SATELLITE_CONTROLLER 0x80
#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_NOT_YET_RECEIVED_ANY_INFORMATION_FROM_SATELLITE_CONTROLLER_STR \
  "Not yet received any information from Satellite Controller"

#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_NOT_REPORTING_FOR_MORE_THAN_10_CONSECUTIVE_SECONDS 0x81
#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_NOT_REPORTING_FOR_MORE_THAN_10_CONSECUTIVE_SECONDS_STR \
  "Satellite Controller Not Reporting for more than 10 consecutive seconds, but SC was alive before"

#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_DOES_NOT_SUPPORT_CHASSIS_LED_REQUESTED 0x82
#define IPMI_COMP_CODE_OEM_WISTON_SET_CHASSIS_LED_STATUS_SATELLITE_CONTROLLER_DOES_NOT_SUPPORT_CHASSIS_LED_REQUESTED_STR \
  "Satellite Controller does not support one or many chassis LED requested"

/* IPMI_CMD_OEM_WISTRON_GET_CHASSIS_POWER_READINGS */
#define IPMI_COMP_CODE_OEM_WISTRON_GET_CHASSIS_POWER_READINGS_BMC_HAS_NOT_YET_RECEIVED_ANY_COMMANDS_FROM_SC 0x81
#define IPMI_COMP_CODE_OEM_WISTRON_GET_CHASSIS_POWER_READINGS_BMC_HAS_NOT_YET_RECEIVED_ANY_COMMANDS_FROM_SC_STR \
  "BMC has not yet received any commands from SC"

/* achu: spec says "timeout" I'm going to say "timedout" */
#define IPMI_COMP_CODE_OEM_WISTRON_GET_CHASSIS_POWER_READINGS_SC_HAS_TIMEDOUT 0x82
#define IPMI_COMP_CODE_OEM_WISTRON_GET_CHASSIS_POWER_READINGS_SC_HAS_TIMEDOUT_STR \
  "BMC has received Set Chassis Power Readings/Set Sensor Info from SC, but SC has timedout and is considered offline now."

#ifdef __cplusplus
}
#endif

#endif /* IPMI_COMP_CODE_OEM_WISTRON_SPEC_H */
