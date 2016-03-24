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

#ifndef IPMI_ENTITY_IDS_SPEC_H
#define IPMI_ENTITY_IDS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_ENTITY_ID_UNSPECIFIED                               0x00
#define IPMI_ENTITY_ID_OTHER                                     0x01
#define IPMI_ENTITY_ID_UNKNOWN                                   0x02
#define IPMI_ENTITY_ID_PROCESSOR                                 0x03
#define IPMI_ENTITY_ID_DISK_OR_DISK_BAY                          0x04
#define IPMI_ENTITY_ID_PERIPHERAL_BAY                            0x05 /* "peripheral bay" in spec */
#define IPMI_ENTITY_ID_SYSTEM_MANAGEMENT_MODULE                  0x06
#define IPMI_ENTITY_ID_SYSTEM_BOARD                              0x07
#define IPMI_ENTITY_ID_MEMORY_MODULE                             0x08
#define IPMI_ENTITY_ID_PROCESSOR_MODULE                          0x09
#define IPMI_ENTITY_ID_POWER_SUPPLY                              0x0A
#define IPMI_ENTITY_ID_ADD_IN_CARD                               0x0B
#define IPMI_ENTITY_ID_FRONT_PANEL_BOARD                         0x0C
#define IPMI_ENTITY_ID_BACK_PANEL_BOARD                          0x0D
#define IPMI_ENTITY_ID_POWER_SYSTEM_BOARD                        0x0E
#define IPMI_ENTITY_ID_DRIVE_BACKPLANE                           0x0F
#define IPMI_ENTITY_ID_SYSTEM_INTERNAL_EXPANSION_BOARD           0x10
#define IPMI_ENTITY_ID_OTHER_SYSTEM_BOARD                        0x11
#define IPMI_ENTITY_ID_PROCESSOR_BOARD                           0x12
#define IPMI_ENTITY_ID_POWER_UNIT_POWER_DOMAIN                   0x13
#define IPMI_ENTITY_ID_POWER_MODULE_DC_TO_DC_CONVERTER           0x14
#define IPMI_ENTITY_ID_POWER_MANAGEMENT_POWER_DISTRIBUTION_BOARD 0x15
#define IPMI_ENTITY_ID_CHASSI_BACK_PANEL_BOARD                   0x16
#define IPMI_ENTITY_ID_SYSTEM_CHASSIS                            0x17
#define IPMI_ENTITY_ID_SUB_CHASSIS                               0x18
#define IPMI_ENTITY_ID_OTHER_CHASSIS_BOARD                       0x19
#define IPMI_ENTITY_ID_DISK_DRIVE_BAY                            0x1A
#define IPMI_ENTITY_ID_PERIPHERAL_BAY2                           0x1B /* "Peripheral Bay" in spec */
#define IPMI_ENTITY_ID_DEVICE_BAY                                0x1C
#define IPMI_ENTITY_ID_FAN_COOLING_DEVICE                        0x1D
#define IPMI_ENTITY_ID_COOLING_UNIT_COOLING_DOMAIN               0x1E /* see errata */
#define IPMI_ENTITY_ID_CABLE_INTERCONNECT                        0x1F
#define IPMI_ENTITY_ID_MEMORY_DEVICE                             0x20
#define IPMI_ENTITY_ID_SYSTEM_MANAGEMENT_SOFTWARE                0x21
#define IPMI_ENTITY_ID_SYSTEM_FIRMWARE                           0x22 /* see errata */
#define IPMI_ENTITY_ID_OPERATING_SYSTEM                          0x23
#define IPMI_ENTITY_ID_SYSTEM_BUS                                0x24
#define IPMI_ENTITY_ID_GROUP                                     0x25
#define IPMI_ENTITY_ID_REMOTE_MANAGEMENT_COMMUNICATION_DEVICE    0x26
#define IPMI_ENTITY_ID_EXTERNAL_ENVIRONMENT                      0x27
#define IPMI_ENTITY_ID_BATTERY                                   0x28   
#define IPMI_ENTITY_ID_PROCESSING_BLADE                          0x29
#define IPMI_ENTITY_ID_CONNECTIVITY_SWTICH                       0x2A
#define IPMI_ENTITY_ID_PROCESSOR_MEMORY_MODULE                   0x2B
#define IPMI_ENTITY_ID_IO_MODULE                                 0x2C
#define IPMI_ENTITY_ID_PROCESSOR_IO_MODULE                       0x2D
#define IPMI_ENTITY_ID_MANAGEMENT_CONTROLLER_FIRMWARE            0x2E
#define IPMI_ENTITY_ID_IPMI_CHANNEL                              0x2F
#define IPMI_ENTITY_ID_PCI_BUS                                   0x30
#define IPMI_ENTITY_ID_PCI_EXPRESS_BUS                           0x31
#define IPMI_ENTITY_ID_SCSI_BUS                                  0x32
#define IPMI_ENTITY_ID_SATA_SAS_BUS                              0x33
#define IPMI_ENTITY_ID_PROCESSOR_FRONT_SIDE_BUS                  0x34
#define IPMI_ENTITY_ID_REAL_TIME_CLOCK                           0x35
/* 0x36 - reserved */
/* achu:
 *
 * Ugh .. 0x37 is listed as air inlet in markup 4 spec, but not in
 * errata 4.  Initial assumption was that it was a typo.  Later, DCMI
 * v1.5 spec lits 0x37 is inlet temperature.
 *
 * So the assumption is it's not a typo now, we'll list 0x37 as
 * AIR_INLET "B"
 */
#define IPMI_ENTITY_ID_AIR_INLET_B                               0x37
/* 0x38 - 0x3F - reserved */
#define IPMI_ENTITY_ID_AIR_INLET                                 0x40
#define IPMI_ENTITY_ID_AIR_INLET_A                               IPMI_ENTITY_ID_AIR_INLET
#define IPMI_ENTITY_ID_PROCESSOR_CPU                             0x41 /* considered same as 0x03, to match DCMI */
#define IPMI_ENTITY_ID_BASEBOARD_MAIN_SYSTEM_BOARD               0x42 /* considered same as 0x07, to match DCMI */
#define IPMI_ENTITY_ID_CHASSIS_SPECIFIC_MIN                      0x90
#define IPMI_ENTITY_ID_CHASSIS_SPECIFIC_MAX                      0xAF
#define IPMI_ENTITY_ID_BOARD_SET_SPECIFIC_MIN                    0xB0
#define IPMI_ENTITY_ID_BOARD_SET_SPECIFIC_MAX                    0xCF
#define IPMI_ENTITY_ID_OEM_SYSTEM_INTEGRATOR_DEFINED_MIN         0xD0
#define IPMI_ENTITY_ID_OEM_SYSTEM_INTEGRATOR_DEFINED_MAX         0xFF

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_ENTITY_ID_VALID(__entity_id)                  \
  ((((__entity_id + 1) >= (IPMI_ENTITY_ID_UNSPECIFIED + 1) \
     && (__entity_id) <= IPMI_ENTITY_ID_REAL_TIME_CLOCK)   \
    || ((__entity_id) >= IPMI_ENTITY_ID_AIR_INLET          \
        && (__entity_id) <= IPMI_ENTITY_ID_BASEBOARD_MAIN_SYSTEM_BOARD)) ? 1 : 0)

#define IPMI_ENTITY_ID_IS_CHASSIS_SPECIFIC(__entity_id) \
  (((__entity_id) >= IPMI_ENTITY_ID_CHASSIS_SPECIFIC_MIN \
    && ((__entity_id) <= IPMI_ENTITY_ID_CHASSIS_SPECIFIC_MAX)) ? 1 : 0)

#define IPMI_ENTITY_ID_IS_BOARD_SET_SPECIFIC(__entity_id) \
  (((__entity_id) >= IPMI_ENTITY_ID_BOARD_SET_SPECIFIC_MIN \
    && ((__entity_id) <= IPMI_ENTITY_ID_BOARD_SET_SPECIFIC_MAX)) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_ENTITY_ID_IS_OEM_SYSTEM_INTEGRATOR_DEFINED(__entity_id) \
  (((__entity_id) >= IPMI_ENTITY_ID_OEM_SYSTEM_INTEGRATOR_DEFINED_MIN \
    && ((__entity_id - 1) <= (IPMI_ENTITY_ID_OEM_SYSTEM_INTEGRATOR_DEFINED_MAX - 1))) ? 1 : 0)

#define IPMI_ENTITY_INSTANCE_SYSTEM_RELATIVE_MIN 0x00
#define IPMI_ENTITY_INSTANCE_SYSTEM_RELATIVE_MAX 0x5F

#define IPMI_ENTITY_INSTANCE_DEVICE_RELATIVE_MIN 0x60
#define IPMI_ENTITY_INSTANCE_DEVICE_RELATIVE_MAX 0x7F

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_ENTITY_INSTANCE_SYSTEM_RELATIVE(__entity_instance) \
  (((__entity_instance + 1) >= (IPMI_ENTITY_INSTANCE_SYSTEM_RELATIVE_MIN + 1)) \
   && ((__entity_instance) >= IPMI_ENTITY_INSTANCE_SYSTEM_RELATIVE_MAX) ? 1 : 0)

#define IPMI_ENTITY_INSTANCE_DEVICE_RELATIVE(__entity_instance) \
  (((__entity_instance) >= IPMI_ENTITY_INSTANCE_DEVICE_RELATIVE_MIN)	\
   && ((__entity_instance) >= IPMI_ENTITY_INSTANCE_DEVICE_RELATIVE_MAX) ? 1 : 0)
  
extern const char *const ipmi_entity_ids[];
extern const char *const ipmi_entity_id_chassis_specific;
extern const char *const ipmi_entity_id_board_set_specific;
extern const char *const ipmi_entity_id_oem_system_integrator;

/* properly capitalize, for some entries if entity has an "or" or "/" remove it and pick one element, etc. */
extern const char *const ipmi_entity_ids_pretty[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_ENTITY_IDS_SPEC_H */
