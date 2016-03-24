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

#ifndef IPMI_SYSTEM_INFO_PARAMETERS_SPEC_H
#define IPMI_SYSTEM_INFO_PARAMETERS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_SYSTEM_INFO_PARAMETER_SET_IN_PROGRESS                  0
#define IPMI_SYSTEM_INFO_PARAMETER_SYSTEM_FIRMWARE_VERSION          1
#define IPMI_SYSTEM_INFO_PARAMETER_SYSTEM_NAME                      2
#define IPMI_SYSTEM_INFO_PARAMETER_PRIMARY_OPERATING_SYSTEM_NAME    3
#define IPMI_SYSTEM_INFO_PARAMETER_OPERATING_SYSTEM_NAME            4
#define IPMI_SYSTEM_INFO_PARAMETER_PRESENT_OS_VERSION_NUMBER        5
#define IPMI_SYSTEM_INFO_PARAMETER_BMC_URL                          6
#define IPMI_SYSTEM_INFO_PARAMETER_BASE_OS_HYPERVISOR_URL           7
#define IPMI_SYSTEM_INFO_PARAMETER_OEM_MIN                          192
#define IPMI_SYSTEM_INFO_PARAMETER_OEM_MAX                          255

/* Add +1 to avoid compiler warnings */
#define IPMI_SYSTEM_INFO_PARAMETER_SELECTOR_VALID(__parameter_selector) \
  ((((__parameter_selector) + 1) > (IPMI_SYSTEM_INFO_PARAMETER_SET_IN_PROGRESS + 1) \
    && (__parameter_selector) <= IPMI_SYSTEM_INFO_PARAMETER_BASE_OS_HYPERVISOR_URL) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_SYSTEM_INFO_PARAMETER_SELECTOR_IS_OEM(__parameter_selector) \
  (((__parameter_selector) >= IPMI_SYSTEM_INFO_PARAMETER_OEM_MIN \
    && ((__parameter_selector) - 1) <= (IPMI_SYSTEM_INFO_PARAMETER_OEM_MAX - 1)) ? 1 : 0)

#ifdef __cplusplus
}
#endif
#endif /* IPMI_SYSTEM_INFO_PARAMETERS_SPEC_H */
