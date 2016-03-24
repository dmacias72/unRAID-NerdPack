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

#ifndef IPMI_TIMESTAMP_SPEC_H
#define IPMI_TIMESTAMP_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_TIMESTAMP_UNSPECIFIED 0xFFFFFFFF

#define IPMI_TIMESTAMP_POST_INIT_MIN 0x00000000
#define IPMI_TIMESTAMP_POST_INIT_MAX 0x20000000

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_TIMESTAMP_POST_INIT(__timestamp) \
  ((((__timestamp + 1) >= (IPMI_TIMESTAMP_POST_INIT_MIN + 1) \
     && (__timestamp) <= IPMI_TIMESTAMP_POST_INIT_MAX)) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_TIMESTAMP_SPEC_H */
