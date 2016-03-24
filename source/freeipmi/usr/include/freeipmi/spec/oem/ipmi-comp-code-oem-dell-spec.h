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

#ifndef IPMI_COMP_CODE_OEM_DELL_SPEC_H
#define IPMI_COMP_CODE_OEM_DELL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Dell Poweredge R720
 */

/* w/ IPMI_CMD_OEM_DELL_GET_EXTENDED_CONFIGURATION
 * IPMI_CMD_OEM_DELL_SET_EXTENDED_CONFIGURATION
 * IPMI_CMD_OEM_DELL_SET_NIC_SELECTION_FAILOVER
 * IPMI_CMD_OEM_DELL_POWER_MONITORING_OVER_A_SPECIFIED_AVERAGING_INTERVAL2
 * IPMI_CMD_OEM_DELL_POWER_MONITORING_AVERAGING_INTERVAL_RANGE2
 * IPMI_CMD_SET_SYSTEM_INFO_PARAMETERS
 * IPMI_CMD_GET_SYSTEM_INFO_PARAMETERS
 */   
#define IPMI_COMP_CODE_OEM_DELL_NOT_LICENSED 0x6F
#define IPMI_COMP_CODE_OEM_DELL_NOT_LICENSED_STR \
  "Not licensed"

/* w/ IPMI_CMD_OEM_DELL_POWER_MONITORING_OVER_A_SPECIFIED_AVERAGING_INTERVAL2
 * IPMI_CMD_OEM_DELL_POWER_MONITORING_AVERAGING_INTERVAL_RANGE2
 */
#define IPMI_COMP_CODE_OEM_DELL_SUBSYSTEM_LEVEL_POWER_IS_NOT_SUPPORTED 0x81
#define IPMI_COMP_CODE_OEM_DELL_SUBSYSTEM_LEVEL_POWER_IS_NOT_SUPPORTED_STR \
  "subsystem-level power is not supported"

#ifdef __cplusplus
}
#endif

#endif /* IPMI_COMP_CODE_OEM_DELL_SPEC_H */
