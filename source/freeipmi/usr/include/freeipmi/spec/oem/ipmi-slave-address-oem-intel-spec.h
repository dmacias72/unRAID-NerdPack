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

#ifndef IPMI_SLAVE_ADDRESS_OEM_INTEL_SPEC_H
#define IPMI_SLAVE_ADDRESS_OEM_INTEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel S5500WB/Penguin Computing Relion 700
 */
#define IPMI_GENERATOR_ID_OEM_INTEL_BIOS_SMI_HANDLER   0x33
#define IPMI_GENERATOR_ID_OEM_INTEL_ME_FIRMWARE        0x2C
#define IPMI_GENERATOR_ID_OEM_INTEL_HSC_FIRMWARE       0xC0

/*
 * Quanta QSSC-S4R/Appro GB812X-CN
 * (Quanta motherboard contains Intel manufacturer ID)
 */
#define IPMI_GENERATOR_ID_OEM_INTEL_QUANTA_QSSC_S4R_BIOS_POST 0x33

/*
 * Intel S2600JF/Appro 512X
 */
#define IPMI_GENERATOR_ID_OEM_INTEL_S2600JF_BIOS_POST          0x01
#define IPMI_GENERATOR_ID_OEM_INTEL_S2600JF_BIOS_SMI_HANDLER   0x33

/*
 * Intel S2600KP                                                                                                                                                                                   
 * Intel S2600WT2                                                                                                                                                                                  
 * Intel S2600WTT  
 */
#define IPMI_GENERATOR_ID_OEM_INTEL_E52600V3_BIOS_POST          0x01
#define IPMI_GENERATOR_ID_OEM_INTEL_E52600V3_BIOS_SMI_HANDLER   0x33

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SLAVE_ADDRESS_OEM_INTEL_SPEC_H */
