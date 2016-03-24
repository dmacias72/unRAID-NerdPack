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

#ifndef IPMI_SLAVE_ADDRESS_OEM_WISTRON_SPEC_H
#define IPMI_SLAVE_ADDRESS_OEM_WISTRON_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Wistron / Dell Poweredge C6220
 */

/* achu: not official names, named based on use context */
#define IPMI_GENERATOR_ID_OEM_WISTRON_BIOS            0x01
#define IPMI_GENERATOR_ID_OEM_WISTRON_SMI             0x21
#define IPMI_GENERATOR_ID_OEM_WISTRON_ME              0x2C

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SLAVE_ADDRESS_OEM_WISTRON_SPEC_H */
