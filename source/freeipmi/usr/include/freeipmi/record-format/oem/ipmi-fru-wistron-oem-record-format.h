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

#ifndef IPMI_FRU_OEM_WISTRON_RECORD_FORMAT_H
#define IPMI_FRU_OEM_WISTRON_RECORD_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

/* 
 * see freeipmi/templates/ for template definitions 
 */

/*
 * Wistron / Dell Poweredge C6220
 */

/* achu: not official names, named based on use context */
#define IPMI_FRU_OEM_WISTRON_PROPRIETARY_STRING 0xC0

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_OEM_WISTRON_RECORD_FORMAT_H */
