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

#ifndef IPMI_CHANNEL_SPEC_H
#define IPMI_CHANNEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_CHANNEL_NUMBER_PRIMARY_IPMB                0x0
#define IPMI_CHANNEL_NUMBER_IMPLEMENTATION_SPECIFIC_MIN 0x01 /* 0x01 to 0x07 */
#define IPMI_CHANNEL_NUMBER_IMPLEMENTATION_SPECIFIC_MAX 0x07 /* 0x01 to 0x07 */
#define IPMI_CHANNEL_NUMBER_RESERVED_MIN                0x0C /* 0x0C to 0x0D */
#define IPMI_CHANNEL_NUMBER_RESERVED_MAX                0x0D /* 0x0C to 0x0D */
#define IPMI_CHANNEL_NUMBER_PRESENT_IF                  0xE
#define IPMI_CHANNEL_NUMBER_CURRENT_CHANNEL             IPMI_CHANNEL_NUMBER_PRESENT_IF
#define IPMI_CHANNEL_NUMBER_SYSTEM_INTERFACE            0xF

#define IPMI_CHANNEL_NUMBERS_MAX                        16

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_CHANNEL_NUMBER_VALID(__channel_number)                   \
  ((((__channel_number + 1) >= (IPMI_CHANNEL_NUMBER_PRIMARY_IPMB + 1) \
     && (__channel_number) < IPMI_CHANNEL_NUMBER_RESERVED_MIN)        \
    || ((__channel_number) > IPMI_CHANNEL_NUMBER_RESERVED_MAX         \
        && (__channel_number) <= IPMI_CHANNEL_NUMBER_SYSTEM_INTERFACE)) ? 1 : 0)

#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED       0x0 /* 0x03, 0x0A to 0x1B */
#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_1     IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED
#define IPMI_CHANNEL_PROTOCOL_TYPE_IPMB           0x1
#define IPMI_CHANNEL_PROTOCOL_TYPE_ICMB_10        0x2
#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_2     0x0 /* 0x03, 0x0A to 0x1B */
#define IPMI_CHANNEL_PROTOCOL_TYPE_SMBUS_1X_2X    0x4
#define IPMI_CHANNEL_PROTOCOL_TYPE_KCS            0x5
#define IPMI_CHANNEL_PROTOCOL_TYPE_SMIC           0x6
#define IPMI_CHANNEL_PROTOCOL_TYPE_BT_10          0x7
#define IPMI_CHANNEL_PROTOCOL_TYPE_BT_15          0x8
#define IPMI_CHANNEL_PROTOCOL_TYPE_TMODE          0x9
#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_MIN   0x0A /* 0x03, 0x0A to 0x1B */
#define IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_MAX   0x1B /* 0x03, 0x0A to 0x1B */
#define IPMI_CHANNEL_PROTOCOL_TYPE_OEM_MIN        0x1C /* 0x1C to 0x1F */
#define IPMI_CHANNEL_PROTOCOL_TYPE_OEM_MAX        0x1F /* 0x1C to 0x1F */

#define IPMI_CHANNEL_PROTOCOL_TYPE_IS_RESERVED(__val)      \
  (((__val) == IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_1       \
    || (__val) == IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_2    \
    || ((__val) >= IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_MIN \
        && (__val) <= IPMI_CHANNEL_PROTOCOL_TYPE_RESERVED_MAX)) ? 1 : 0)

#define IPMI_CHANNEL_PROTOCOL_TYPE_IS_OEM(__val)  \
  (((__val) >= IPMI_CHANNEL_PROTOCOL_TYPE_OEM_MIN \
    && (__val) <= IPMI_CHANNEL_PROTOCOL_TYPE_OEM_MAX) ? 1 : 0)

#define IPMI_CHANNEL_MEDIUM_TYPE_RESERVED          0x0 /* 0x0D to 0x5F */
#define IPMI_CHANNEL_MEDIUM_TYPE_IPMB              0x1
#define IPMI_CHANNEL_MEDIUM_TYPE_ICMB_10           0x2
#define IPMI_CHANNEL_MEDIUM_TYPE_ICMB_09           0x3
#define IPMI_CHANNEL_MEDIUM_TYPE_LAN_802_3         0x4
#define IPMI_CHANNEL_MEDIUM_TYPE_RS232             0x5
#define IPMI_CHANNEL_MEDIUM_TYPE_OTHER_LAN         0x6
#define IPMI_CHANNEL_MEDIUM_TYPE_PCI_SMBUS         0x7
#define IPMI_CHANNEL_MEDIUM_TYPE_SMBUS_10_11       0x8
#define IPMI_CHANNEL_MEDIUM_TYPE_SMBUS_20          0x9
#define IPMI_CHANNEL_MEDIUM_TYPE_USB_1X            0xA
#define IPMI_CHANNEL_MEDIUM_TYPE_USB_2X            0xB
#define IPMI_CHANNEL_MEDIUM_TYPE_SYSTEM_INTERFACE  0xC
#define IPMI_CHANNEL_MEDIUM_TYPE_RESERVED_MIN      0x0D /* 0x0D to 0x59 */
#define IPMI_CHANNEL_MEDIUM_TYPE_RESERVED_MAX      0x59 /* 0x0D to 0x59 */
#define IPMI_CHANNEL_MEDIUM_TYPE_OEM_MIN           0x60 /* 0x60 to 0x7F */
#define IPMI_CHANNEL_MEDIUM_TYPE_OEM_MAX           0x7F /* 0x60 to 0x7F */

#define IPMI_CHANNEL_MEDIUM_TYPE_IS_RESERVED(__val)      \
  (((__val) == IPMI_CHANNEL_MEDIUM_TYPE_RESERVED         \
    || ((__val) >= IPMI_CHANNEL_MEDIUM_TYPE_RESERVED_MIN \
        && (__val) <= IPMI_CHANNEL_MEDIUM_TYPE_RESERVED_MAX)) ? 1 : 0)

#define IPMI_CHANNEL_MEDIUM_TYPE_IS_OEM(__val)  \
  (((__val) >= IPMI_CHANNEL_MEDIUM_TYPE_OEM_MIN \
    && (__val) <= IPMI_CHANNEL_MEDIUM_TYPE_OEM_MAX) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CHANNEL_SPEC_H */
