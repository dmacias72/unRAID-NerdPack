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
/*****************************************************************************\
 *  Copyright (C) 2007-2015 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-232183
 *
 *  This file is part of Ipmi-fru, a tool used for retrieving
 *  motherboard field replaceable unit (FRU) information. For details,
 *  see http://www.llnl.gov/linux/.
 *
 *  Ipmi-fru is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmi-fru is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmi-fru.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMI_FRU_CHASSIS_TYPES_SPEC_H
#define IPMI_FRU_CHASSIS_TYPES_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

/*
 * achu:
 *
 * Not in IPMI spec.  In "Platform Management FRU Information Storage
 * Definition" document.
 *
 * Starting w/ FRU Revision 1.2, this table is defined by SMBIOS
 * specification, Table 16 - "System Enclosure or Chassis Types"
 */

#define IPMI_FRU_CHASSIS_TYPE_OTHER                 0x01
#define IPMI_FRU_CHASSIS_TYPE_UNKNOWN               0x02
#define IPMI_FRU_CHASSIS_TYPE_DESKTOP               0x03
#define IPMI_FRU_CHASSIS_TYPE_LOW_PROFILE_DESKTOP   0x04
#define IPMI_FRU_CHASSIS_TYPE_PIZZA_BOX             0x05
#define IPMI_FRU_CHASSIS_TYPE_MINI_TOWER            0x06
#define IPMI_FRU_CHASSIS_TYPE_TOWER                 0x07
#define IPMI_FRU_CHASSIS_TYPE_PORTABLE              0x08
#define IPMI_FRU_CHASSIS_TYPE_LAPTOP                0x09
#define IPMI_FRU_CHASSIS_TYPE_NOTEBOOK              0x0a
#define IPMI_FRU_CHASSIS_TYPE_HAND_HELD             0x0b
#define IPMI_FRU_CHASSIS_TYPE_DOCKING_STATION       0x0c
#define IPMI_FRU_CHASSIS_TYPE_ALL_IN_ONE            0x0d
#define IPMI_FRU_CHASSIS_TYPE_SUB_NOTEBOOK          0x0e
#define IPMI_FRU_CHASSIS_TYPE_SPACE_SAVING          0x0f
#define IPMI_FRU_CHASSIS_TYPE_LUNCH_BOX             0x10
#define IPMI_FRU_CHASSIS_TYPE_MAIN_SERVER_CHASSIS   0x11
#define IPMI_FRU_CHASSIS_TYPE_EXPANSION_CHASSIS     0x12
#define IPMI_FRU_CHASSIS_TYPE_SUBCHASSIS            0x13
#define IPMI_FRU_CHASSIS_TYPE_BUS_EXPANSION_CHASSIS 0x14
#define IPMI_FRU_CHASSIS_TYPE_PERIPHERAL_CHASSIS    0x15
#define IPMI_FRU_CHASSIS_TYPE_RAID_CHASSIS          0x16
#define IPMI_FRU_CHASSIS_TYPE_RACK_MOUNT_CHASSIS    0x17
#define IPMI_FRU_CHASSIS_TYPE_SEALED_CASE_PC        0x18
#define IPMI_FRU_CHASSIS_TYPE_MULTI_SYSTEM_CHASSIS  0x19
#define IPMI_FRU_CHASSIS_TYPE_COMPACT_PCI           0x1A
#define IPMI_FRU_CHASSIS_TYPE_ADVANCED_TCA          0x1B
#define IPMI_FRU_CHASSIS_TYPE_BLADE                 0x1C
#define IPMI_FRU_CHASSIS_TYPE_BLADE_ENCLOSURE       0x1D

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_FRU_CHASSIS_TYPE_VALID(__chassis_type) \
  (((__chassis_type + 1) >= (IPMI_FRU_CHASSIS_TYPE_OTHER + 1) \
    && (__chassis_type) <= IPMI_FRU_CHASSIS_TYPE_BLADE_ENCLOSURE) ? 1 : 0)

extern const char *const ipmi_fru_chassis_types[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_CHASSIS_TYPES_SPEC_H */
