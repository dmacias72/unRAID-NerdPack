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

#ifndef IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_HP_SPEC_H
#define IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_HP_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 * HP Proliant DL160 G8
 */

#define IPMI_OEM_HP_UID_LIGHT_ON       0x00
#define IPMI_OEM_HP_UID_LIGHT_OFF      0x01
#define IPMI_OEM_HP_UID_LIGHT_BLINKING 0x02

#define IPMI_OEM_HP_HEALTH_LED_GREEN   0x00
#define IPMI_OEM_HP_HEALTH_LED_AMBER   0x01 
#define IPMI_OEM_HP_HEALTH_LED_RED     0x02 

/*
 * String arrays for above
 */

extern const char * const ipmi_oem_hp_uid_light[];
extern unsigned int ipmi_oem_hp_uid_light_max_index;

extern const char * const ipmi_oem_hp_health_led[];
extern unsigned int ipmi_oem_hp_health_led_max_index;


#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_AND_EVENT_CODE_TABLES_OEM_HP_SPEC_H */
