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

#ifndef IPMI_CMD_OEM_SUN_MICROSYSTEMS_SPEC_H
#define IPMI_CMD_OEM_SUN_MICROSYSTEMS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Sun 4140
 */

/* IPMI_NET_FN_OEM_GROUP_RQ / IPMI_NET_FN_OEM_GROUP_RS */
#define IPMI_CMD_OEM_SUN_GET_LED 0x21
#define IPMI_CMD_OEM_SUN_SET_LED 0x22

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_SUN_MICROSYSTEMS_SPEC_H */
