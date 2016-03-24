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

#ifndef IPMI_SOL_CONFIGURATION_PARAMETERS_SPEC_H
#define IPMI_SOL_CONFIGURATION_PARAMETERS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_SOL_CONFIGURATION_PARAMETER_SET_IN_PROGRESS                                  0
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_ENABLE                                       1
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_AUTHENTICATION                               2
#define IPMI_SOL_CONFIGURATION_PARAMETER_CHARACTER_ACCUMULATE_INTERVAL_AND_SEND_THRESHOLD 3
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_RETRY                                        4
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_NON_VOLATILE_BIT_RATE                        5
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_VOLATILE_BIT_RATE                            6
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_PAYLOAD_CHANNEL                              7
#define IPMI_SOL_CONFIGURATION_PARAMETER_SOL_PAYLOAD_PORT_NUMBER                          8
#define IPMI_SOL_CONFIGURATION_PARAMETER_OEM_MIN                                          192
#define IPMI_SOL_CONFIGURATION_PARAMETER_OEM_MAX                                          255

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SOL_CONFIGURATION_PARAMETER_SELECTOR_VALID(__parameter_selector) \
  ((((__parameter_selector) + 1) > (IPMI_SOL_CONFIGURATION_PARAMETER_SET_IN_PROGRESS + 1) \
    && (__parameter_selector) <= IPMI_SOL_CONFIGURATION_PARAMETER_SOL_PAYLOAD_PORT_NUMBER) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_SOL_CONFIGURATION_PARAMETER_SELECTOR_IS_OEM(__parameter_selector) \
  (((__parameter_selector) >= IPMI_SOL_CONFIGURATION_PARAMETER_OEM_MIN \
    && ((__parameter_selector) - 1) <= (IPMI_SOL_CONFIGURATION_PARAMETER_OEM_MAX - 1)) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_CONFIGURATION_PARAMETERS_SPEC_H */
