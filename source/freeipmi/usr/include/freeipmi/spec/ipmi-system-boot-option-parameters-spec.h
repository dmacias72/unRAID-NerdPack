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

#ifndef IPMI_SYSTEM_BOOT_OPTION_PARAMETERS_SPEC_H
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETERS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SET_IN_PROGRESS                  0x0
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SERVICE_PARTITION_SELECTOR       0x1
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SERVICE_PARTITION_SCAN           0x2
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BMC_BOOT_FLAG_VALID_BIT_CLEARING 0x3
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_INFO_ACKNOWLEDGE            0x4
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_FLAGS                       0x5
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_INITIATOR_INFO              0x6
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_INITIATOR_MAILBOX           0x7

/* Add +1 to avoid compiler warnings */
#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SELECTOR_VALID(__parameter_selector)              \
  ((((__parameter_selector + 1)) > (IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SET_IN_PROGRESS+1) && \
    (__parameter_selector) <= IPMI_SYSTEM_BOOT_OPTION_PARAMETER_BOOT_INITIATOR_MAILBOX) ? 1 : 0)

#define IPMI_SYSTEM_BOOT_OPTION_PARAMETER_SELECTOR_IS_OEM(__parameter_selector) \
  (((__parameter_selector) >= 96 && (__parameter_selector) <= 127) ? 1 : 0)

#ifdef __cplusplus
}
#endif
#endif /* IPMI_SYSTEM_BOOT_OPTION_PARAMETERS_SPEC_H */
