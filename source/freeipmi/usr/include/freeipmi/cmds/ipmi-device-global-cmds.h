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

#ifndef IPMI_DEVICE_GLOBAL_CMDS_H
#define IPMI_DEVICE_GLOBAL_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_DEVICE_ID_UNSPECIFIED        0x00
#define IPMI_MANUFACTURER_ID_UNSPECIFIED  0x000000
#define IPMI_MANUFACTURER_ID_RESERVED     0x0FFFFF

#define IPMI_1_5_MAJOR_VERSION 1
#define IPMI_1_5_MINOR_VERSION 5

#define IPMI_2_0_MAJOR_VERSION 2
#define IPMI_2_0_MINOR_VERSION 0

#define IPMI_SELF_TEST_RESULT_NO_ERROR                                               0x55
#define IPMI_SELF_TEST_RESULT_SELF_TEST_FUNCTION_NOT_IMPLEMENTED_IN_THIS_CONTROLLER  0x56
#define IPMI_SELF_TEST_RESULT_CORRUPTED_OR_INACCESSIBLE_DATA_OR_DEVICES              0x57
#define IPMI_SELF_TEST_RESULT_FATAL_HARDWARE_ERROR                                   0x58

#define IPMI_ACPI_SYSTEM_POWER_STATE_S0_G0          0x00
#define IPMI_ACPI_SYSTEM_POWER_STATE_S1             0x01
#define IPMI_ACPI_SYSTEM_POWER_STATE_S2             0x02
#define IPMI_ACPI_SYSTEM_POWER_STATE_S3             0x03
#define IPMI_ACPI_SYSTEM_POWER_STATE_S4             0x04
#define IPMI_ACPI_SYSTEM_POWER_STATE_S5_G2          0x05
#define IPMI_ACPI_SYSTEM_POWER_STATE_S4_S5          0x06
#define IPMI_ACPI_SYSTEM_POWER_STATE_G3             0x07
#define IPMI_ACPI_SYSTEM_POWER_STATE_SLEEPING       0x08
#define IPMI_ACPI_SYSTEM_POWER_STATE_G1_SLEEPING    0x09
#define IPMI_ACPI_SYSTEM_POWER_STATE_OVERRIDE       0x0A
#define IPMI_ACPI_SYSTEM_POWER_STATE_LEGACY_ON      0x20
#define IPMI_ACPI_SYSTEM_POWER_STATE_LEGACY_OFF     0x21
#define IPMI_ACPI_SYSTEM_POWER_STATE_UNKNOWN        0x2A
#define IPMI_ACPI_SYSTEM_POWER_STATE_NO_CHANGE      0x7F

#define IPMI_ACPI_SYSTEM_POWER_STATE_VALID(__acpi_system_power_state)          \
  (((__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S0_G0          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S1          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S2          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S3          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S4          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S5_G2       \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_S4_S5       \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_G3          \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_SLEEPING    \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_G1_SLEEPING \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_OVERRIDE    \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_LEGACY_ON   \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_LEGACY_OFF  \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_UNKNOWN     \
    || (__acpi_system_power_state) == IPMI_ACPI_SYSTEM_POWER_STATE_NO_CHANGE) ? 1 : 0)

#define IPMI_ACPI_SET_SYSTEM_POWER_STATE_SET_SYSTEM_POWER_STATE       0x1
#define IPMI_ACPI_SET_SYSTEM_POWER_STATE_DONT_SET_SYSTEM_POWER_STATE  0x0

#define IPMI_ACPI_SET_SYSTEM_POWER_STATE_VALID(__set_system_power_state)                  \
  (((__set_system_power_state) == IPMI_ACPI_SET_SYSTEM_POWER_STATE_SET_SYSTEM_POWER_STATE \
    || (__set_system_power_state) == IPMI_ACPI_SET_SYSTEM_POWER_STATE_DONT_SET_SYSTEM_POWER_STATE) ? 1 : 0)

#define IPMI_ACPI_DEVICE_POWER_STATE_D0             0x00
#define IPMI_ACPI_DEVICE_POWER_STATE_D1             0x01
#define IPMI_ACPI_DEVICE_POWER_STATE_D2             0x02
#define IPMI_ACPI_DEVICE_POWER_STATE_D3             0x03
#define IPMI_ACPI_DEVICE_POWER_STATE_UNKNOWN        0x2A
#define IPMI_ACPI_DEVICE_POWER_STATE_NO_CHANGE      0x7F

#define IPMI_ACPI_DEVICE_POWER_STATE_VALID(__acpi_device_power_state)      \
  (((__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_D0         \
    || (__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_D1      \
    || (__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_D2      \
    || (__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_D3      \
    || (__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_UNKNOWN \
    || (__acpi_device_power_state) == IPMI_ACPI_DEVICE_POWER_STATE_NO_CHANGE) ? 1 : 0)

#define IPMI_ACPI_SET_DEVICE_POWER_STATE_SET_DEVICE_POWER_STATE       0x1
#define IPMI_ACPI_SET_DEVICE_POWER_STATE_DONT_SET_DEVICE_POWER_STATE  0x0

#define IPMI_ACPI_SET_DEVICE_POWER_STATE_VALID(__set_device_power_state)                  \
  (((__set_device_power_state) == IPMI_ACPI_SET_DEVICE_POWER_STATE_SET_DEVICE_POWER_STATE \
    || (__set_device_power_state) == IPMI_ACPI_SET_DEVICE_POWER_STATE_DONT_SET_DEVICE_POWER_STATE) ? 1 : 0)

#define IPMI_SYSTEM_GUID_LENGTH 16

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_get_device_id_rq;
extern fiid_template_t tmpl_cmd_get_device_id_rs;

extern fiid_template_t tmpl_cmd_cold_reset_rq;
extern fiid_template_t tmpl_cmd_cold_reset_rs;

extern fiid_template_t tmpl_cmd_warm_reset_rq;
extern fiid_template_t tmpl_cmd_warm_reset_rs;

extern fiid_template_t tmpl_cmd_get_self_test_results_rq;
extern fiid_template_t tmpl_cmd_get_self_test_results_rs;

extern fiid_template_t tmpl_cmd_set_acpi_power_state_rq;
extern fiid_template_t tmpl_cmd_set_acpi_power_state_rs;

extern fiid_template_t tmpl_cmd_get_acpi_power_state_rq;
extern fiid_template_t tmpl_cmd_get_acpi_power_state_rs;

extern fiid_template_t tmpl_cmd_get_device_guid_rq;
extern fiid_template_t tmpl_cmd_get_device_guid_rs;
extern fiid_template_t tmpl_cmd_get_device_guid_format_rs;

int fill_cmd_get_device_id (fiid_obj_t obj_cmd_rq);
int fill_cmd_cold_reset (fiid_obj_t obj_cmd_rq);
int fill_cmd_warm_reset (fiid_obj_t obj_cmd_rq);
int fill_cmd_set_acpi_power_state (uint8_t system_power_state_enumeration,
                                   uint8_t set_system_power_state,
                                   uint8_t device_power_state_enumeration,
                                   uint8_t set_device_power_state,
                                   fiid_obj_t obj_cmd_rq);
int fill_cmd_get_acpi_power_state (fiid_obj_t obj_cmd_rq);
int fill_cmd_get_self_test_results (fiid_obj_t obj_cmd_rq);
int fill_cmd_get_device_guid (fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DEVICE_GLOBAL_CMDS_H */
