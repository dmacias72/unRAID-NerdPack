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

#ifndef IPMI_OEM_IBM_SPEC_H
#define IPMI_OEM_IBM_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IBM x3455/x3755
 */

/* w/ IPMI_CMD_OEM_IBM_GET_LED */

#define IPMI_OEM_IBM_LED_STATE_INACTIVE                  0x0

#define IPMI_OEM_IBM_LED_ACTIVE_BY_LED                   0x1
#define IPMI_OEM_IBM_LED_ACTIVE_BY_SENSOR                0x2
#define IPMI_OEM_IBM_LED_ACTIVE_BY_USER                  0x3
#define IPMI_OEM_IBM_LED_ACTIVE_BY_BIOS_OR_ADMINISTRATOR 0x4

#define IPMI_OEM_IBM_LED_X3455_LOCATION          0x1

#define IPMI_OEM_IBM_LED_X3755_CPU               0x0010
#define IPMI_OEM_IBM_LED_X3755_CPU1              0x0030
#define IPMI_OEM_IBM_LED_X3755_CPU2              0x0031
#define IPMI_OEM_IBM_LED_X3755_CPU3              0x0032
#define IPMI_OEM_IBM_LED_X3755_CPU4              0x0033

#define IPMI_OEM_IBM_LED_X3755_CPU1_BOARD        0x00B8
#define IPMI_OEM_IBM_LED_X3755_CPU2_BOARD        0x00B9
#define IPMI_OEM_IBM_LED_X3755_CPU3_BOARD        0x00BA
#define IPMI_OEM_IBM_LED_X3755_CPU4_BOARD        0x00BB

#define IPMI_OEM_IBM_LED_X3755_DIMM_1            0x0060
#define IPMI_OEM_IBM_LED_X3755_DIMM_2            0x0061
#define IPMI_OEM_IBM_LED_X3755_DIMM_3            0x0062 
#define IPMI_OEM_IBM_LED_X3755_DIMM_4            0x0063
#define IPMI_OEM_IBM_LED_X3755_DIMM_5            0x0064
#define IPMI_OEM_IBM_LED_X3755_DIMM_6            0x0065
#define IPMI_OEM_IBM_LED_X3755_DIMM_7            0x0066
#define IPMI_OEM_IBM_LED_X3755_DIMM_8            0x0067
#define IPMI_OEM_IBM_LED_X3755_DIMM_9            0x0068
#define IPMI_OEM_IBM_LED_X3755_DIMM_10           0x0069
#define IPMI_OEM_IBM_LED_X3755_DIMM_11           0x006A
#define IPMI_OEM_IBM_LED_X3755_DIMM_12           0x006B
#define IPMI_OEM_IBM_LED_X3755_DIMM_13           0x006C
#define IPMI_OEM_IBM_LED_X3755_DIMM_14           0x006D
#define IPMI_OEM_IBM_LED_X3755_DIMM_15           0x006E
#define IPMI_OEM_IBM_LED_X3755_DIMM_16           0x006F
#define IPMI_OEM_IBM_LED_X3755_DIMM_17           0x00C0
#define IPMI_OEM_IBM_LED_X3755_DIMM_18           0x00C1
#define IPMI_OEM_IBM_LED_X3755_DIMM_19           0x00C2
#define IPMI_OEM_IBM_LED_X3755_DIMM_20           0x00C3
#define IPMI_OEM_IBM_LED_X3755_DIMM_21           0x00C4
#define IPMI_OEM_IBM_LED_X3755_DIMM_22           0x00C5
#define IPMI_OEM_IBM_LED_X3755_DIMM_23           0x00C6
#define IPMI_OEM_IBM_LED_X3755_DIMM_24           0x00C7
#define IPMI_OEM_IBM_LED_X3755_DIMM_25           0x00C8
#define IPMI_OEM_IBM_LED_X3755_DIMM_26           0x00C9
#define IPMI_OEM_IBM_LED_X3755_DIMM_27           0x00CA
#define IPMI_OEM_IBM_LED_X3755_DIMM_28           0x00CB
#define IPMI_OEM_IBM_LED_X3755_DIMM_29           0x00CC
#define IPMI_OEM_IBM_LED_X3755_DIMM_30           0x00CD
#define IPMI_OEM_IBM_LED_X3755_DIMM_31           0x00CE
#define IPMI_OEM_IBM_LED_X3755_DIMM_32           0x00CF

#define IPMI_OEM_IBM_LED_X3755_FAN               0x0014
#define IPMI_OEM_IBM_LED_X3755_FAN_1             0x0050
#define IPMI_OEM_IBM_LED_X3755_FAN_2             0x0051
#define IPMI_OEM_IBM_LED_X3755_FAN_3             0x0052
#define IPMI_OEM_IBM_LED_X3755_FAN_4             0x0053
#define IPMI_OEM_IBM_LED_X3755_FAN_5             0x0054
#define IPMI_OEM_IBM_LED_X3755_FAN_6             0x0055
#define IPMI_OEM_IBM_LED_X3755_FAN_7             0x0056
#define IPMI_OEM_IBM_LED_X3755_FAN_8             0x0057

#define IPMI_OEM_IBM_LED_X3755_PCI               0x0020
#define IPMI_OEM_IBM_LED_X3755_PCI_1             0x0070
#define IPMI_OEM_IBM_LED_X3755_PCI_2             0x0071
#define IPMI_OEM_IBM_LED_X3755_PCI_3             0x0072
#define IPMI_OEM_IBM_LED_X3755_PCI_4             0x0073
#define IPMI_OEM_IBM_LED_X3755_PCI_5             0x0074
#define IPMI_OEM_IBM_LED_X3755_PCI_6             0x0075

#define IPMI_OEM_IBM_LED_X3755_SERVERAID_8K_BATT 0x00D0
#define IPMI_OEM_IBM_LED_X3755_SERVERAID_8K_ERR  0x00D1

#define IPMI_OEM_IBM_LED_X3755_ALERT             0x00D9
#define IPMI_OEM_IBM_LED_X3755_BK_BLUE           0x00D8
#define IPMI_OEM_IBM_LED_X3755_BOARD             0x000E
#define IPMI_OEM_IBM_LED_X3755_CNFG              0x0006
#define IPMI_OEM_IBM_LED_X3755_DASD              0x0013
#define IPMI_OEM_IBM_LED_X3755_FAULT             0x0000
#define IPMI_OEM_IBM_LED_X3755_HTX               0x00B0
#define IPMI_OEM_IBM_LED_X3755_INFO              0x0003
#define IPMI_OEM_IBM_LED_X3755_LOCATION          0x0001
#define IPMI_OEM_IBM_LED_X3755_MEM               0x0015
#define IPMI_OEM_IBM_LED_X3755_NMI               0x0019
#define IPMI_OEM_IBM_LED_X3755_OVERSPEC          0x001B
#define IPMI_OEM_IBM_LED_X3755_RAID              0x000F
#define IPMI_OEM_IBM_LED_X3755_SEER              0x000B
#define IPMI_OEM_IBM_LED_X3755_SP                0x001E
#define IPMI_OEM_IBM_LED_X3755_TEMP              0x001C
#define IPMI_OEM_IBM_LED_X3755_VRM               0x0011
 
#define IPMI_OEM_IBM_LED_X3755_UNKNOWN1          0x0040
#define IPMI_OEM_IBM_LED_X3755_UNKNOWN2          0x0041
#define IPMI_OEM_IBM_LED_X3755_UNKNOWN3          0x0047

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OEM_IBM_SPEC_H */
