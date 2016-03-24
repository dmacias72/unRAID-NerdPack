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

#ifndef IPMI_PEF_CONFIGURATION_PARAMETERS_SPEC_H
#define IPMI_PEF_CONFIGURATION_PARAMETERS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_PEF_CONFIGURATION_PARAMETER_SET_IN_PROGRESS                        0
#define IPMI_PEF_CONFIGURATION_PARAMETER_PEF_CONTROL                            1
#define IPMI_PEF_CONFIGURATION_PARAMETER_PEF_ACTION_GLOBAL_CONTROL              2
#define IPMI_PEF_CONFIGURATION_PARAMETER_PEF_STARTUP_DELAY                      3
#define IPMI_PEF_CONFIGURATION_PARAMETER_PEF_ALERT_STARTUP_DELAY                4
#define IPMI_PEF_CONFIGURATION_PARAMETER_NUMBER_OF_EVENT_FILTERS                5
#define IPMI_PEF_CONFIGURATION_PARAMETER_EVENT_FILTER_TABLE                     6
#define IPMI_PEF_CONFIGURATION_PARAMETER_EVENT_FILTER_TABLE_DATA_1              7
#define IPMI_PEF_CONFIGURATION_PARAMETER_NUMBER_OF_ALERT_POLICY_ENTRIES         8
#define IPMI_PEF_CONFIGURATION_PARAMETER_ALERT_POLICY_TABLE                     9
#define IPMI_PEF_CONFIGURATION_PARAMETER_SYSTEM_GUID                           10
#define IPMI_PEF_CONFIGURATION_PARAMETER_NUMBER_OF_ALERT_STRINGS               11
#define IPMI_PEF_CONFIGURATION_PARAMETER_ALERT_STRING_KEYS                     12
#define IPMI_PEF_CONFIGURATION_PARAMETER_ALERT_STRINGS                         13
#define IPMI_PEF_CONFIGURATION_PARAMETER_NUMBER_OF_GROUP_CONTROL_TABLE_ENTRIES 14
#define IPMI_PEF_CONFIGURATION_PARAMETER_GROUP_CONTROL_TABLE                   15
#define IPMI_PEF_CONFIGURATION_PARAMETER_OEM_MIN                               96
#define IPMI_PEF_CONFIGURATION_PARAMETER_OEM_MAX                               127

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_PEF_CONFIGURATION_PARAMETER_SELECTOR_VALID(__parameter_selector)         \
  ((((__parameter_selector) + 1) > (IPMI_PEF_CONFIGURATION_PARAMETER_SET_IN_PROGRESS + 1) \
    && (__parameter_selector) <= IPMI_PEF_CONFIGURATION_PARAMETER_GROUP_CONTROL_TABLE) ? 1 : 0)

#define IPMI_PEF_CONFIGURATION_PARAMETER_SELECTOR_IS_OEM(__parameter_selector) \
  (((__parameter_selector) >= IPMI_PEF_CONFIGURATION_PARAMETER_OEM_MIN \
    && (__parameter_selector) <= IPMI_PEF_CONFIGURATION_PARAMETER_OEM_MAX) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif
