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

#ifndef IPMI_FRU_INFORMATION_RECORD_FORMAT_H
#define IPMI_FRU_INFORMATION_RECORD_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

/*
 * achu:
 *
 * Not in IPMI spec.  In "Platform Management FRU Information Storage
 * Definition" document.
 */

#define IPMI_FRU_COMMON_HEADER_FORMAT_VERSION         0x01
#define IPMI_FRU_CHASSIS_INFO_AREA_FORMAT_VERSION     0x01
#define IPMI_FRU_BOARD_INFO_AREA_FORMAT_VERSION       0x01
#define IPMI_FRU_PRODUCT_INFO_AREA_FORMAT_VERSION     0x01
#define IPMI_FRU_MULTIRECORD_AREA_FORMAT_VERSION      0x02

#define IPMI_FRU_MULTIRECORD_AREA_TYPE_POWER_SUPPLY_INFORMATION       0x00
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_DC_OUTPUT                      0x01
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_DC_LOAD                        0x02
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_MANAGEMENT_ACCESS_RECORD       0x03
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_BASE_COMPATIBILITY_RECORD      0x04
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_COMPATIBILITY_RECORD  0x05
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_FIXED_SMBUS_DEVICE_RECORD  0x06
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_LEGACY_DEVICE_ALERTS       0x07
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_ASF_REMOTE_CONTROL             0x08
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_DC_OUTPUT             0x09
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_DC_LOAD               0x0A
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_NVM_EXPRESS_MIN                0x0B
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_NVM_EXPRESS_MAX                0x0F
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MIN                        0xC0
#define IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MAX                        0xFF

#define IPMI_FRU_MULTIRECORD_AREA_TYPE_VALID(__multirecord_area_type)                    \
  (((__multirecord_area_type) >= IPMI_FRU_MULTIRECORD_AREA_TYPE_POWER_SUPPLY_INFORMATION \
    && (__multirecord_area_type) <= IPMI_FRU_MULTIRECORD_AREA_TYPE_EXTENDED_DC_LOAD) ? 1 : 0)

#define IPMI_FRU_MULTIRECORD_AREA_TYPE_IS_NVM_EXPRESS(__multirecord_area_type)  \
  (((__multirecord_area_type) >= IPMI_FRU_MULTIRECORD_AREA_TYPE_NVM_EXPRESS_MIN \
    && (__multirecord_area_type) <= IPMI_FRU_MULTIRECORD_AREA_TYPE_NVM_EXPRESS_MAX) ? 1 : 0)

#define IPMI_FRU_MULTIRECORD_AREA_TYPE_IS_OEM(__multirecord_area_type)  \
  (((__multirecord_area_type) >= IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MIN \
    && (__multirecord_area_type) <= IPMI_FRU_MULTIRECORD_AREA_TYPE_OEM_MAX) ? 1 : 0)

#define IPMI_FRU_MFG_DATE_TIME_UNSPECIFIED 0x000000 

#define IPMI_FRU_ONE_PULSE_PER_ROTATION  0x0
#define IPMI_FRU_TWO_PULSES_PER_ROTATION 0x1

#define IPMI_FRU_PEAK_CAPACITY_UNSPECIFIED 0xFFF

#define IPMI_FRU_VOLTAGE_12V      0x0
#define IPMI_FRU_VOLTAGE_MINUS12V 0x1
#define IPMI_FRU_VOLTAGE_5V       0x2
#define IPMI_FRU_VOLTAGE_3_3V     0x3

#define IPMI_FRU_PREDICTIVE_FAIL_PIN_IS_PASS_FAIL 0x0

#define IPMI_FRU_CURRENT_UNITS_10MA  0x0
#define IPMI_FRU_CURRENT_UNITS_100MA 0x1

#define IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_MANAGEMENT_URL     0x01
#define IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_NAME               0x02
#define IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_PING_ADDRESS       0x03
#define IPMI_FRU_SUB_RECORD_TYPE_COMPONENT_MANAGEMENT_URL  0x04
#define IPMI_FRU_SUB_RECORD_TYPE_COMPONENT_NAME            0x05
#define IPMI_FRU_SUB_RECORD_TYPE_COMPONENT_PING_ADDRESS    0x06
#define IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_UNIQUE_ID          0x07

#define IPMI_FRU_SUB_RECORD_TYPE_VALID(__sub_record_type)                 \
  (((__sub_record_type) >= IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_MANAGEMENT_URL \
    && (__sub_record_type) <= IPMI_FRU_SUB_RECORD_TYPE_SYSTEM_UNIQUE_ID) ? 1 : 0)

#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_BINARY          0x00
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_BCD             0x01
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_SIXBIT_ASCII    0x02
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_LANGUAGE_CODE   0x03
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_MASK            0xC0
#define IPMI_FRU_TYPE_LENGTH_TYPE_CODE_SHIFT           0x06
#define IPMI_FRU_TYPE_LENGTH_NUMBER_OF_DATA_BYTES_MASK 0x3F

#define IPMI_FRU_BCD_DIGIT_MIN                         0x0
#define IPMI_FRU_BCD_DIGIT_MAX                         0x9
#define IPMI_FRU_BCD_SPACE                             0xA
#define IPMI_FRU_BCD_DASH                              0xB
#define IPMI_FRU_BCD_PERIOD                            0xC

#define IPMI_FRU_SENTINEL_VALUE                        0xC1

/* 
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_fru_common_header;
extern fiid_template_t tmpl_fru_info_area_header;
extern fiid_template_t tmpl_fru_multirecord_area_header;
extern fiid_template_t tmpl_fru_power_supply_information;
extern fiid_template_t tmpl_fru_dc_output;
extern fiid_template_t tmpl_fru_dc_load;
extern fiid_template_t tmpl_fru_management_access_record;
extern fiid_template_t tmpl_fru_base_compatibility_record;
extern fiid_template_t tmpl_fru_extended_compatibility_record;
extern fiid_template_t tmpl_fru_extended_dc_output;
extern fiid_template_t tmpl_fru_extended_dc_load;
extern fiid_template_t tmpl_fru_oem_record;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_INFORMATION_RECORD_FORMAT_H */
