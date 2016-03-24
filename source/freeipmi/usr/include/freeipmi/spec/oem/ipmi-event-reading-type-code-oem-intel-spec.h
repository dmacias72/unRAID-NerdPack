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

#ifndef IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_SPEC_H
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel S5500WB/Penguin Computing Relion 700
 */

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_PCIE_FATAL_SENSOR       0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_PCIE_CORRECTABLE_SENSOR 0x71
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QPI_CORRECTABLE_SENSOR  0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QPI_NON_FATAL_SENSOR    0x73
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QPI_FATAL_SENSOR        0x74

/* 
 * Quanta QSSC-S4R/Appro GB812X-CN
 * (Quanta motherboard contains Intel manufacturer ID)
 */
/* achu: Similar to above, but some events changed and some new ones,
 * so new macros to differentiate
 */ 
/* achu: not official names, named based on use context */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_PCIE_FATAL_SENSOR       0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_PCIE_CORRECTABLE_SENSOR 0x71
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_QPI_CORRECTABLE_SENSOR  0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_QPI_NON_FATAL_SENSOR    0x73
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_QPI_FATAL_SENSOR        0x74
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_CORRECTABLE_ERROR       0x76
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_QUANTA_QSSC_S4R_UNCORRECTABLE_ERROR     0x77

/*
 * Intel S2600JF/Appro 512X
 */
/* achu: some are similar to above, but different names, new events,
 * new numbers, so making new macros to differentiate */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_PCIE_FATAL_ERROR       0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_PCIE_CORRECTABLE_ERROR 0x71
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_QPI_CORRECTABLE_ERRORS 0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_OPI_FATAL_ERROR        0x73
/* continuation for IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_OPI_FATAL_ERROR for more offsets */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_OPI_FATAL_ERROR_2      0x74
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_CHIPSET_PROPRIETARY    0x75
/* continuation for IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_PCIE_FATAL_ERROR for more offsets */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_PCIE_FATAL_ERROR_2     0x76
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_QPI_LINK_WIDTH_REDUCED 0x77
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_S2600JF_MEMORY_ERROR_EXTENSION 0x7F

/*
 * Intel Windmill
 * (Quanta Winterfell)
 * (Wiwynn Windmill)
 */
/* achu: Like Intel Node Manager, but no Intel Node Manager on these nodes, so cut & paste to differentiate */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_WINDMILL_ME_FW_HEALTH_SENSOR    0x75
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_WINDMILL_OTHER_IIO_ERROR_SENSOR 0x70

/*
 * Intel S2600KP                                                                                                                                                                                   
 * Intel S2600WT2                                                                                                                                                                                  
 * Intel S2600WTT  
 */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_QPI_CORRECTABLE_ERROR          0x72
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_QPI_FATAL_ERROR                0x73
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_QPI_FATAL_ERROR_2              0x74
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_QPI_LINK_WIDTH_REDUCED         0x77

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_PCI_EXPRESS_FATAL_ERRORS       0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_PCI_EXPRESS_FATAL_ERRORS_2     0x76
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_PCI_EXPRESS_CORRECTABLE_ERRORS 0x71 

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_FIRMWARE_UPDATE_STATUS_SENSOR  0x70

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_BIOS_RECOVERY_START            0x70
#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_BIOS_RECOVERY_FINISH           0xF0

#define IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_E52600V3_IERR_RECOVERY_DUMP_INFO        0x70

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_READING_TYPE_CODE_OEM_INTEL_SPEC_H */
