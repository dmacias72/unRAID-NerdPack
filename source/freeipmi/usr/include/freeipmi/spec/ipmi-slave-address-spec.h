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

#ifndef IPMI_SLAVE_ADDRESS_SPEC_H
#define IPMI_SLAVE_ADDRESS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
   Slave Addresses - 7 bits

   BIOS                                   0x00 to 0x0F
   SMI HANDLER                            0x10 to 0x1F
   System Management Software             0x20 to 0x2F
   OEM                                    0x30 to 0x3F
   Remote Console Software                0x40 to 0x46
   Terminal Mode Remote Console Software  0x47
 */

/*
   Software IDs - 8 bits, Least Significant Bit is 0x1

   BIOS                                   0x01 to 0x1F
   SMI HANDLER                            0x21 to 0x3F
   System Management Software             0x41 to 0x5F
   OEM                                    0x61 to 0x7F
   Remote Console Software                0x81 to 0x8D
   Terminal Mode Remote Console Software  0x8F
 */

#define IPMI_SLAVE_ADDRESS_BMC                          0x20
#define IPMI_LAN_SLAVE_ADDRESS_BMC                      IPMI_SLAVE_ADDRESS_BMC
#define IPMI_SSIF_SMBUS_SLAVE_ADDRESS                   0x42

#define IPMI_LAN_SOFTWARE_ID_REMOTE_CONSOLE_SOFTWARE    0x81

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SLAVE_ADDRESS_SPEC_H */
