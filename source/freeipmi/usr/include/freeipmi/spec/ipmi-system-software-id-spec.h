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

#ifndef IPMI_SYSTEM_SOFTWARE_ID_SPEC_H
#define IPMI_SYSTEM_SOFTWARE_ID_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Table 5-4 */

#define IPMI_SYSTEM_SOFTWARE_TYPE_BIOS_MIN 0x01
#define IPMI_SYSTEM_SOFTWARE_TYPE_BIOS_MAX 0x0F

#define IPMI_SYSTEM_SOFTWARE_TYPE_SMI_HANDLER_MIN 0x10
#define IPMI_SYSTEM_SOFTWARE_TYPE_SMI_HANDLER_MAX 0x1F

#define IPMI_SYSTEM_SOFTWARE_TYPE_SYSTEM_MANAGEMENT_SOFTWARE_MIN 0x20
#define IPMI_SYSTEM_SOFTWARE_TYPE_SYSTEM_MANAGEMENT_SOFTWARE_MAX 0x2F

#define IPMI_SYSTEM_SOFTWARE_TYPE_OEM_MIN 0x30
#define IPMI_SYSTEM_SOFTWARE_TYPE_OEM_MAX 0x3F

#define IPMI_SYSTEM_SOFTWARE_TYPE_REMOTE_CONSOLE_SOFTWARE_MIN 0x40
#define IPMI_SYSTEM_SOFTWARE_TYPE_REMOTE_CONSOLE_SOFTWARE_MAX 0x46

#define IPMI_SYSTEM_SOFTWARE_TYPE_TERMINAL_MODE_REMOTE_CONSOLE_SOFTWARE 0x47

#define IPMI_SYSTEM_SOFTWARE_TYPE_RESERVED_MIN 0x48

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_BIOS(__val) \
  (((__val + 1) >= IPMI_SYSTEM_SOFTWARE_TYPE_BIOS_MIN \
    && (__val) <= IPMI_SYSTEM_SOFTWARE_TYPE_BIOS_MAX) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_SMI_HANDLER(__val) \
  (((__val) >= IPMI_SYSTEM_SOFTWARE_TYPE_SMI_HANDLER_MIN \
    && (__val) <= IPMI_SYSTEM_SOFTWARE_TYPE_SMI_HANDLER_MAX) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_SYSTEM_MANAGEMENT_SOFTWARE(__val) \
  (((__val) >= IPMI_SYSTEM_SOFTWARE_TYPE_SYSTEM_MANAGEMENT_SOFTWARE_MIN \
    && (__val) <= IPMI_SYSTEM_SOFTWARE_TYPE_SYSTEM_MANAGEMENT_SOFTWARE_MAX) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_OEM(__val) \
  (((__val) >= IPMI_SYSTEM_SOFTWARE_TYPE_OEM_MIN \
    && (__val) <= IPMI_SYSTEM_SOFTWARE_TYPE_OEM_MAX) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_REMOTE_CONSOLE_SOFTWARE(__val) \
  (((__val) >= IPMI_SYSTEM_SOFTWARE_TYPE_REMOTE_CONSOLE_SOFTWARE_MIN \
    && (__val) <= IPMI_SYSTEM_SOFTWARE_TYPE_REMOTE_CONSOLE_SOFTWARE_MAX) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_TERMINAL_MODE_REMOTE_CONSOLE_SOFTWARE(__val) \
  (((__val) == IPMI_SYSTEM_SOFTWARE_TYPE_TERMINAL_MODE_REMOTE_CONSOLE_SOFTWARE)) ? 1 : 0)

#define IPMI_SYSTEM_SOFTWARE_TYPE_IS_RESERVED(__val) \
  (((__val) >= IPMI_SYSTEM_SOFTWARE_TYPE_RESERVED_MIN) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SYSTEM_SOFTWARE_ID_SPEC_H */
