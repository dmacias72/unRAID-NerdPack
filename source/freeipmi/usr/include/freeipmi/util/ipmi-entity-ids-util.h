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

#ifndef IPMI_ENTITY_IDS_H
#define IPMI_ENTITY_IDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

const char *ipmi_get_entity_id_string (uint8_t entity_id);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_ENTITY_IDS_H */
