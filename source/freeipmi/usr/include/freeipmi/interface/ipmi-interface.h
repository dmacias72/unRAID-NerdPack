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

#ifndef IPMI_INTERFACE_H
#define IPMI_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* NO_LEGAL_CHECK - do no check if IPMI response payloads have
 * sufficient data (i.e. completion code fields) to be legal.  Useful
 * to work around non-compliant motherboards.  Only applicable to
 * interface unassemble functions.
 */

#define IPMI_INTERFACE_FLAGS_DEFAULT        0x00000000
#define IPMI_INTERFACE_FLAGS_NO_LEGAL_CHECK 0x00000001

#ifdef __cplusplus
}
#endif

#endif /* IPMI_INTERFACE_H */
