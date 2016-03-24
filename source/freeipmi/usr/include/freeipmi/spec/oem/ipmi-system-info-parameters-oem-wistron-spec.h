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

#ifndef IPMI_SYSTEM_INFO_PARAMETERS_OEM_WISTRON_SPEC_H
#define IPMI_SYSTEM_INFO_PARAMETERS_OEM_WISTRON_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Wistron / Dell Poweredge C6220
 */

#define IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_ASSET_TAG    196
#define IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_SERVICE_TAG  197
#define IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_PRODUCT_NAME 209

#define IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_ASSET_TAG_MAX_LEN   20
#define IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_SERVICE_TAG_MAX_LEN 7 

/* Wistron System Info Parameter macros */

/* w/ IPMI_SYSTEM_INFO_PARAMETER_OEM_WISTRON_PRODUCT_NAME
 */
#define IPMI_OEM_WISTRON_SYSTEM_INFO_STRING_ENCODING_BITMASK 0xF
#define IPMI_OEM_WISTRON_SYSTEM_INFO_STRING_ENCODING_SHIFT   0

#define IPMI_OEM_WISTRON_SYSTEM_INFO_STRING_ENCODING_PRINTABLE_ASCII 0x0

/* 256 b/c length is 8 bit field */
#define IPMI_OEM_WISTRON_SYSTEM_INFO_MAX_STRING_BYTES 256

#ifdef __cplusplus
}
#endif
#endif /* IPMI_SYSTEM_INFO_PARAMETERS_SPEC_H */
