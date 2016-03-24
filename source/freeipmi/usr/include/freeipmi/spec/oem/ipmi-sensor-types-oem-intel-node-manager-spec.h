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

#ifndef IPMI_SENSOR_TYPES_OEM_INTEL_NODE_MANAGER_SPEC_H
#define IPMI_SENSOR_TYPES_OEM_INTEL_NODE_MANAGER_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel Node Manager
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 * Intel S2600KP
 * Intel S2600WT2
 * Intel S2600WTT
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 * Quanta QSSC-S4R/Appro GB812X-CN
 */

#define IPMI_SENSOR_TYPE_OEM_INTEL_NODE_MANAGER 0xDC

#define IPMI_SENSOR_TYPE_OEM_INTEL_NODE_MANAGER_THERMAL_SENSOR_ON_DIMM 0x28

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_TYPES_OEM_INTEL_NODE_MANAGER_SPEC_H */
