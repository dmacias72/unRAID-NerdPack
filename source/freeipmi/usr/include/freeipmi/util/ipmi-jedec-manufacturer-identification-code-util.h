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

#ifndef IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_UTIL_H
#define IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

char *ipmi_jedec_manufacturer_id_search (uint8_t continuation_codes_count, uint8_t id);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_UTIL_H */
