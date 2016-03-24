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

#ifndef IPMI_SENSOR_TYPES_OEM_INTEL_SPEC_H
#define IPMI_SENSOR_TYPES_OEM_INTEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
 * Dell                                    *
 *******************************************/

/*
 * Dell Poweredge R610
 * Dell Poweredge R710
 * Dell Poweredge R720
 */

/* achu: names taken from code, are correct names? */
#define IPMI_SENSOR_TYPE_OEM_DELL_SYSTEM_PERFORMANCE_DEGRADATION_STATUS 0xC0
#define IPMI_SENSOR_TYPE_OEM_DELL_LINK_TUNING                           0xC1
#define IPMI_SENSOR_TYPE_OEM_DELL_NON_FATAL_ERROR                       0xC2
#define IPMI_SENSOR_TYPE_OEM_DELL_FATAL_IO_ERROR                        0xC3
#define IPMI_SENSOR_TYPE_OEM_DELL_UPGRADE                               0xC4

/*
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel SR1625
 * Quanta QSSC-S4R/Appro GB812X-CN
 * (Quanta motherboard contains Intel manufacturer ID)
 */

#define IPMI_SENSOR_TYPE_OEM_INTEL_SMI_TIMEOUT                  0xF3

/*
 * Quanta QSSC-S4R/Appro GB812X-CN
 * (Quanta motherboard contains Intel manufacturer ID)
 */
#define IPMI_SENSOR_TYPE_OEM_INTEL_POWER_THROTTLED              0xF3

/*
 * Intel S5000PAL
 */
#define IPMI_SENSOR_TYPE_OEM_INTEL_NMI_STATE                    0xC0

/*
 * Intel Windmill
 * (Quanta Winterfell)
 * (Wiwynn Windmill)
 */
#define IPMI_SENSOR_TYPE_OEM_INTEL_WINDMILL_ME_FW_HEALTH_SENSOR 0xDC

/* Used by many sensors */
#define IPMI_SENSOR_TYPE_OEM_INTEL_WINDMILL_GENERIC             0xC0

/*
 * Intel S2600KP                                                                                                                                                                                   
 * Intel S2600WT2                                                                                                                                                                                  
 * Intel S2600WTT  
 */
#define IPMI_SENSOR_TYPE_OEM_INTEL_E52600V3_IERR_RECOVERY_DUMP_INFO 0xD1

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_TYPES_OEM_INTEL_SPEC_H */
