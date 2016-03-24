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

#ifndef IPMI_SENSOR_TYPES_SPEC_H
#define IPMI_SENSOR_TYPES_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_SENSOR_TYPE_RESERVED                            0x00
#define IPMI_SENSOR_TYPE_TEMPERATURE                         0x01
#define IPMI_SENSOR_TYPE_VOLTAGE                             0x02
#define IPMI_SENSOR_TYPE_CURRENT                             0x03
#define IPMI_SENSOR_TYPE_FAN                                 0x04
#define IPMI_SENSOR_TYPE_PHYSICAL_SECURITY                   0x05
#define IPMI_SENSOR_TYPE_PLATFORM_SECURITY_VIOLATION_ATTEMPT 0x06
#define IPMI_SENSOR_TYPE_PROCESSOR                           0x07
#define IPMI_SENSOR_TYPE_POWER_SUPPLY                        0x08
#define IPMI_SENSOR_TYPE_POWER_UNIT                          0x09
#define IPMI_SENSOR_TYPE_COOLING_DEVICE                      0x0A
#define IPMI_SENSOR_TYPE_OTHER_UNITS_BASED_SENSOR            0x0B
#define IPMI_SENSOR_TYPE_MEMORY                              0x0C
#define IPMI_SENSOR_TYPE_DRIVE_SLOT                          0x0D
#define IPMI_SENSOR_TYPE_POST_MEMORY_RESIZE                  0x0E
#define IPMI_SENSOR_TYPE_SYSTEM_FIRMWARE_PROGRESS            0x0F
#define IPMI_SENSOR_TYPE_EVENT_LOGGING_DISABLED              0x10
#define IPMI_SENSOR_TYPE_WATCHDOG1                           0x11
#define IPMI_SENSOR_TYPE_SYSTEM_EVENT                        0x12
#define IPMI_SENSOR_TYPE_CRITICAL_INTERRUPT                  0x13
#define IPMI_SENSOR_TYPE_BUTTON_SWITCH                       0x14
#define IPMI_SENSOR_TYPE_MODULE_BOARD                        0x15
#define IPMI_SENSOR_TYPE_MICROCONTROLLER_COPROCESSOR         0x16
#define IPMI_SENSOR_TYPE_ADD_IN_CARD                         0x17
#define IPMI_SENSOR_TYPE_CHASSIS                             0x18
#define IPMI_SENSOR_TYPE_CHIP_SET                            0x19
#define IPMI_SENSOR_TYPE_OTHER_FRU                           0x1A
#define IPMI_SENSOR_TYPE_CABLE_INTERCONNECT                  0x1B
#define IPMI_SENSOR_TYPE_TERMINATOR                          0x1C
#define IPMI_SENSOR_TYPE_SYSTEM_BOOT_INITIATED               0x1D
#define IPMI_SENSOR_TYPE_BOOT_ERROR                          0x1E
/* OS BOOT renamed Base OS Boot/Installation Status, but gonna keep legacy name for ease */
#define IPMI_SENSOR_TYPE_OS_BOOT                             0x1F
#define IPMI_SENSOR_TYPE_OS_CRITICAL_STOP                    0x20
#define IPMI_SENSOR_TYPE_SLOT_CONNECTOR                      0x21
#define IPMI_SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE             0x22
#define IPMI_SENSOR_TYPE_WATCHDOG2                           0x23
#define IPMI_SENSOR_TYPE_PLATFORM_ALERT                      0x24
#define IPMI_SENSOR_TYPE_ENTITY_PRESENCE                     0x25
#define IPMI_SENSOR_TYPE_MONITOR_ASIC_IC                     0x26
#define IPMI_SENSOR_TYPE_LAN                                 0x27
#define IPMI_SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH         0x28
#define IPMI_SENSOR_TYPE_BATTERY                             0x29
#define IPMI_SENSOR_TYPE_SESSION_AUDIT                       0x2A
#define IPMI_SENSOR_TYPE_VERSION_CHANGE                      0x2B
#define IPMI_SENSOR_TYPE_FRU_STATE                           0x2C
#define IPMI_SENSOR_TYPE_OEM_MIN                             0xC0
#define IPMI_SENSOR_TYPE_OEM_MAX                             0xFF

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SENSOR_TYPE_VALID(__sensor_type)              \
  ((((__sensor_type) + 1) >= (IPMI_SENSOR_TYPE_RESERVED + 1)    \
    && (__sensor_type) <= IPMI_SENSOR_TYPE_FRU_STATE) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_SENSOR_TYPE_IS_OEM(__sensor_type) \
  (((__sensor_type) >= IPMI_SENSOR_TYPE_OEM_MIN \
    && (((__sensor_type) - 1) <= (IPMI_SENSOR_TYPE_OEM_MAX - 1))) ? 1 : 0)

extern const char *const ipmi_sensor_types[];
extern const char *const ipmi_oem_sensor_type;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_TYPES_SPEC_H */
