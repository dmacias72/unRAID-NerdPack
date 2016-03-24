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

#ifndef IPMI_OEM_SUN_MICROSYSTEMS_SPEC_H
#define IPMI_OEM_SUN_MICROSYSTEMS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Sun 4140
 */

/* w/ IPMI_CMD_OEM_SUN_GET_LED / IPMI_CMD_OEM_SUN_SET_LED */
#define IPMI_OEM_SUN_LED_MODE_OFF     0
#define IPMI_OEM_SUN_LED_MODE_ON      1
#define IPMI_OEM_SUN_LED_MODE_STANDBY 2
#define IPMI_OEM_SUN_LED_MODE_SLOW    3
#define IPMI_OEM_SUN_LED_MODE_FAST    4

#define IPMI_OEM_SUN_LED_FORCE_GO_THRU_CONTROLLER     0
#define IPMI_OEM_SUN_LED_FORCE_DIRECTLY_ACCESS_DEVICE 1

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OEM_SUN_MICROSYSTEMS_SPEC_H */
