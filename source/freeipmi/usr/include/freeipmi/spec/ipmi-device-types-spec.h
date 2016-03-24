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

#ifndef IPMI_DEVICE_TYPES_SPEC_H
#define IPMI_DEVICE_TYPES_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Note that the macros are not in sequential order, per spec table 43-12 */

#define IPMI_DEVICE_TYPE_DS1624_TEMPERATURE_SENSOR_EEPROM_OR_EQUIVALENT               0x02  
#define IPMI_DEVICE_TYPE_DS1621_TEMPERATURE_SENSOR_OR_EQUIVALENT                      0x03
#define IPMI_DEVICE_TYPE_LM75_TEMPERATURE_SENSOR_OR_EQUIVALENT                        0x04
#define IPMI_DEVICE_TYPE_HECETA_ASIC_OR_SIMILAR                                       0x05
#define IPMI_DEVICE_TYPE_EEPROM_24C01_OR_EQUIVALENT                                   0x08
#define IPMI_DEVICE_TYPE_EEPROM_24C02_OR_EQUIVALENT                                   0x09
#define IPMI_DEVICE_TYPE_EEPROM_24C04_OR_EQUIVALENT                                   0x0A
#define IPMI_DEVICE_TYPE_EEPROM_24C08_OR_EQUIVALENT                                   0x0B
#define IPMI_DEVICE_TYPE_EEPROM_24C16_OR_EQUIVALENT                                   0x0C
#define IPMI_DEVICE_TYPE_EEPROM_24C17_OR_EQUIVALENT                                   0x0D
#define IPMI_DEVICE_TYPE_EEPROM_24C32_OR_EQUIVALENT                                   0x0E
#define IPMI_DEVICE_TYPE_EEPROM_24C64_OR_EQUIVALENT                                   0x0F
#define IPMI_DEVICE_TYPE_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER            0x10
#define IPMI_DEVICE_TYPE_PCF_8570_256_BYTE_RAM_OR_EQUIVALENT                          0x14
#define IPMI_DEVICE_TYPE_PCF_8573_CLOCK_CALENDAR_OR_EQUIVALENT                        0x15
#define IPMI_DEVICE_TYPE_PCF_8574A_IO_PORT_OR_EQUIVALENT                              0x16
#define IPMI_DEVICE_TYPE_PCF_8583_CLOCK_CALENDAR_OR_EQUIVALENT                        0x17
#define IPMI_DEVICE_TYPE_PCF_8593_CLOCK_CALENDAR_OR_EQUIVALENT                        0x18
#define IPMI_DEVICE_TYPE_CLOCK_CALENDAR_TYPE_NOT_SPECIFIED                            0x19
#define IPMI_DEVICE_TYPE_PCF_8591_AD_DA_CONVERTER_OR_EQUIVALENT                       0x1A
#define IPMI_DEVICE_TYPE_IO_PORT_SPECIFIC_DEVICE_NOT_SPECIFIED                        0x1B
#define IPMI_DEVICE_TYPE_AD_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED                   0x1C
#define IPMI_DEVICE_TYPE_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED                   0x1D
#define IPMI_DEVICE_TYPE_AD_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED                0x1E
#define IPMI_DEVICE_TYPE_LCD_CONTROLLER_DRIVER_SPECIFIC_DEVICE_NOT_SPECIFIED          0x1F
#define IPMI_DEVICE_TYPE_CORE_LOGIC_DEVICE_SPECIFIC_DEVICE_NOT_SPECIFIED              0x20
#define IPMI_DEVICE_TYPE_LMC6874_INTELLIGENT_BATTERY_CONTROLLER_OR_EQUIVALENT         0x21
#define IPMI_DEVICE_TYPE_INTELLIGENT_BATTERY_CONTROLLER_SPECIFIC_DEVICE_NOT_SPECIFIED 0x22
#define IPMI_DEVICE_TYPE_COMBO_MANAGEMENT_ASIC_SPECIFIC_DEVICE_NOT_SPECIFIED          0x23
#define IPMI_DEVICE_TYPE_MAXIM_1617_TEMPERATURE_SENSOR                                0x24
#define IPMI_DEVICE_TYPE_OTHER_UNSPECIFIED_DEVICE                                     0xBF
#define IPMI_DEVICE_TYPE_OEM_MIN                                                      0xC0
#define IPMI_DEVICE_TYPE_OEM_MAX                                                      0xFF

#define IPMI_DEVICE_TYPE_MODIFIER_DS1624_TEMPERATURE_SENSOR_EEPROM_OR_EQUIVALENT_UNSPECIFIED 0x00

#define IPMI_DEVICE_TYPE_MODIFIER_DS1621_TEMPERATURE_SENSOR_OR_EQUIVALENT_UNSPECIFIED        0x00

#define IPMI_DEVICE_TYPE_MODIFIER_LM75_TEMPERATURE_SENSOR_OR_EQUIVALENT_UNSPECIFIED          0x00

#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_HECETA_1 0x00
#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_HECETA_2 0x01
#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_LM80     0x02
#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_HECETA_3 0x03
#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_HECETA_4 0x04
#define IPMI_DEVICE_TYPE_MODIFIER_HECETA_ASIC_OR_SIMILAR_HECETA_5 0x05

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C01_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C01_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C01_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C01_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C02_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C02_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C02_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C02_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C04_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C04_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C04_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C04_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C08_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C08_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C08_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C08_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C16_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C16_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C16_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C16_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C17_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C17_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C17_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C17_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C32_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C32_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C32_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C32_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* PI = processor information */
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C64_OR_EQUIVALENT_UNSPECIFIED                           0x00
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C64_OR_EQUIVALENT_DIMM_MEMORY_ID                        0x01
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C64_OR_EQUIVALENT_IPMI_FRU_INVENTORY                    0x02
#define IPMI_DEVICE_TYPE_MODIFIER_EEPROM_24C64_OR_EQUIVALENT_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM 0x03

/* achu: not a typo, 00h and 0x02 are same.  00h for backwards compatability, see spec */
#define IPMI_DEVICE_TYPE_MODIFIER_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER_IPMI_FRU_INVENTORY_BACKWARDS_COMPATABILITY 0x00
#define IPMI_DEVICE_TYPE_MODIFIER_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER_DIMM_MEMORY_ID                             0x01
#define IPMI_DEVICE_TYPE_MODIFIER_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER_IPMI_FRU_INVENTORY                         0x02
#define IPMI_DEVICE_TYPE_MODIFIER_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER_SYSTEM_PROCESSOR_CARTRIDGE_FRU_PI_ROM      0x03
#define IPMI_DEVICE_TYPE_MODIFIER_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER_UNSPECIFIED                                0xFF

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8570_256_BYTE_RAM_OR_EQUIVALENT_UNSPECIFIED                          0x00

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8573_CLOCK_CALENDAR_OR_EQUIVALENT_UNSPECIFIED                        0x00

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8574A_IO_PORT_OR_EQUIVALENT_UNSPECIFIED                              0x00

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8583_CLOCK_CALENDAR_OR_EQUIVALENT_UNSPECIFIED                        0x00

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8593_CLOCK_CALENDAR_OR_EQUIVALENT_UNSPECIFIED                        0x00

#define IPMI_DEVICE_TYPE_MODIFIER_CLOCK_CALENDAR_TYPE_NOT_SPECIFIED_UNSPECIFIED                            0x00

#define IPMI_DEVICE_TYPE_MODIFIER_PCF_8591_AD_DA_CONVERTER_OR_EQUIVALENT_UNSPECIFIED                       0x00

#define IPMI_DEVICE_TYPE_MODIFIER_IO_PORT_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED                        0x00

#define IPMI_DEVICE_TYPE_MODIFIER_AD_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED                   0x00

#define IPMI_DEVICE_TYPE_MODIFIER_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED                   0x00

#define IPMI_DEVICE_TYPE_MODIFIER_AD_DA_CONVERTER_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED                0x00

#define IPMI_DEVICE_TYPE_MODIFIER_LCD_CONTROLLER_DRIVER_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED          0x00

#define IPMI_DEVICE_TYPE_MODIFIER_CORE_LOGIC_DEVICE_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED              0x00

#define IPMI_DEVICE_TYPE_MODIFIER_LMC6874_INTELLIGENT_BATTERY_CONTROLLER_OR_EQUIVALENT_UNSPECIFIED         0x00

#define IPMI_DEVICE_TYPE_MODIFIER_INTELLIGENT_BATTERY_CONTROLLER_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED 0x00

#define IPMI_DEVICE_TYPE_MODIFIER_COMBO_MANAGEMENT_ASIC_SPECIFIC_DEVICE_NOT_SPECIFIED_UNSPECIFIED          0x00

#define IPMI_DEVICE_TYPE_MODIFIER_MAXIM_1617_TEMPERATURE_SENSOR_UNSPECIFIED                                0x00

#define IPMI_DEVICE_TYPE_MODIFIER_OTHER_UNSPECIFIED_DEVICE_UNSPECIFIED                                     0x00

#define IPMI_DEVICE_TYPE_VALID(__device_type) \
  ((((__device_type) >= IPMI_DEVICE_TYPE_DS1624_TEMPERATURE_SENSOR_EEPROM_OR_EQUIVALENT \
     && (__device_type) <= IPMI_DEVICE_TYPE_HECETA_ASIC_OR_SIMILAR) \
    || ((__device_type) >= IPMI_DEVICE_TYPE_EEPROM_24C01_OR_EQUIVALENT \
        && (__device_type) <= IPMI_DEVICE_TYPE_FRU_INVENTORY_DEVICE_BEHIND_MANAGEMENT_CONTROLLER) \
    || ((__device_type) >= IPMI_DEVICE_TYPE_PCF_8570_256_BYTE_RAM_OR_EQUIVALENT \
        && (__device_type) <= IPMI_DEVICE_TYPE_MAXIM_1617_TEMPERATURE_SENSOR) \
    || (__device_type) == IPMI_DEVICE_TYPE_OTHER_UNSPECIFIED_DEVICE) ? 1 : 0)

/* To avoid gcc warnings, subtract -1 in comparison */
#define IPMI_DEVICE_TYPE_IS_OEM(__device_type) \
  (((__device_type) >= IPMI_DEVICE_TYPE_OEM_MIN \
    && (((__device_type) - 1) <= (IPMI_DEVICE_TYPE_OEM_MAX - 1))) ? 1 : 0)

/*
 * String arrays for above
 */

extern const char *const ipmi_device_types[];
extern const char *const ipmi_oem_device_type;

extern const char * const ipmi_device_type_modifier_ds1624_temperature_sensor_eeprom_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_ds1624_temperature_sensor_eeprom_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_ds1621_temperature_sensor_eeprom_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_ds1621_temperature_sensor_eeprom_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_lm75_temperature_sensor_eeprom_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_lm75_temperature_sensor_eeprom_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_heceta_asic_or_similar[];
extern unsigned int ipmi_device_type_modifier_heceta_asic_or_similar_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c01_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c01_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c02_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c02_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c04_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c04_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c08_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c08_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c16_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c16_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c17_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c17_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c32_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c32_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_eeprom_24c64_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_eeprom_24c64_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_fru_inventory_device_behind_management_controller[];
extern unsigned int ipmi_device_type_modifier_fru_inventory_device_behind_management_controller_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8570_256_byte_ram_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8570_256_byte_ram_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8573_clock_calendar_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8573_clock_calendar_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8574a_io_port_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8574a_io_port_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8583_clock_calendar_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8583_clock_calendar_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8593_clock_calendar_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8593_clock_calendar_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_clock_calendar_type_not_specified[];
extern unsigned int ipmi_device_type_modifier_clock_calendar_type_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_pcf_8591_ad_da_converter_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_pcf_8591_ad_da_converter_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_io_port_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_io_port_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_ad_converter_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_ad_converter_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_da_converter_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_da_converter_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_ad_da_converter_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_ad_da_converter_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_lcd_controller_driver_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_lcd_controller_driver_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_core_logic_device_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_core_logic_device_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_lmc6874_intelligent_battery_controller_or_equivalent[];
extern unsigned int ipmi_device_type_modifier_lmc6874_intelligent_battery_controller_or_equivalent_max_index;

extern const char * const ipmi_device_type_modifier_intelligent_battery_controller_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_intelligent_battery_controller_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_combo_management_asic_specific_device_not_specified[];
extern unsigned int ipmi_device_type_modifier_combo_management_asic_specific_device_not_specified_max_index;

extern const char * const ipmi_device_type_modifier_maxim_1617_temperature_sensor[];
extern unsigned int ipmi_device_type_modifier_maxim_1617_temperature_sensor_max_index;

extern const char * const ipmi_device_type_modifier_other_unspecified_device[];
extern unsigned int ipmi_device_type_modifier_other_unspecified_device_max_index;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DEVICE_TYPES_SPEC_H */
