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

#ifndef IPMI_SEL_CMDS_H
#define IPMI_SEL_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SEL_GET_RECORD_ID_FIRST_ENTRY 0x0000
#define IPMI_SEL_GET_RECORD_ID_LAST_ENTRY  0xFFFF

#define IPMI_SEL_CLEAR_OPERATION_INITIATE_ERASE        0xAA
#define IPMI_SEL_CLEAR_OPERATION_GET_ERASURE_STATUS    0x0

#define IPMI_SEL_CLEAR_OPERATION_VALID(__val)          \
  (((__val) == IPMI_SEL_CLEAR_OPERATION_INITIATE_ERASE \
    || (__val) == IPMI_SEL_CLEAR_OPERATION_GET_ERASURE_STATUS) ? 1 : 0)

#define IPMI_SEL_CLEAR_ERASURE_IN_PROGRESS    0x0
#define IPMI_SEL_CLEAR_ERASE_COMPLETED        0x1

#define IPMI_SEL_READ_ENTIRE_RECORD_BYTES_TO_READ  0xFF

#define IPMI_SEL_TIME_UTC_OFFSET_MIN -1440
#define IPMI_SEL_TIME_UTC_OFFSET_MAX 1440

#define IPMI_SEL_TIME_UTC_OFFSET_UNSPECIFIED 0x07FF

#define IPMI_SEL_TIME_UTC_OFFSET_VALID(__val) \
  ((((__val) >= IPMI_SEL_TIME_UTC_OFFSET_MIN  \
     && (__val) <= IPMI_SEL_TIME_UTC_OFFSET_MAX) \
    || (__val) == IPMI_SEL_TIME_UTC_OFFSET_UNSPECIFIED) ? 1 : 0)

#define IPMI_AUXILIARY_LOG_TYPE_MCA  0x00
#define IPMI_AUXILIARY_LOG_TYPE_OEM1 0x01
#define IPMI_AUXILIARY_LOG_TYPE_OEM2 0x02

#define IPMI_AUXILIARY_LOG_TYPE_VALID(__val)   \
  (((__val) == IPMI_AUXILIARY_LOG_TYPE_MCA     \
    || (__val) == IPMI_AUXILIARY_LOG_TYPE_OEM1 \
    || (__val) == IPMI_AUXILIARY_LOG_TYPE_OEM2) ? 1 : 0)

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_get_sel_info_rq;
extern fiid_template_t tmpl_cmd_get_sel_info_rs;

extern fiid_template_t tmpl_cmd_get_sel_allocation_info_rq;
extern fiid_template_t tmpl_cmd_get_sel_allocation_info_rs;

extern fiid_template_t tmpl_cmd_reserve_sel_rq;
extern fiid_template_t tmpl_cmd_reserve_sel_rs;

extern fiid_template_t tmpl_cmd_get_sel_entry_rq;
extern fiid_template_t tmpl_cmd_get_sel_entry_rs;

extern fiid_template_t tmpl_cmd_delete_sel_entry_rq;
extern fiid_template_t tmpl_cmd_delete_sel_entry_rs;

extern fiid_template_t tmpl_cmd_clear_sel_rq;
extern fiid_template_t tmpl_cmd_clear_sel_rs;

extern fiid_template_t tmpl_cmd_get_sel_time_rq;
extern fiid_template_t tmpl_cmd_get_sel_time_rs;

extern fiid_template_t tmpl_cmd_set_sel_time_rq;
extern fiid_template_t tmpl_cmd_set_sel_time_rs;

extern fiid_template_t tmpl_cmd_get_sel_time_utc_offset_rq;
extern fiid_template_t tmpl_cmd_get_sel_time_utc_offset_rs;

extern fiid_template_t tmpl_cmd_set_sel_time_utc_offset_rq;
extern fiid_template_t tmpl_cmd_set_sel_time_utc_offset_rs;

extern fiid_template_t tmpl_cmd_get_auxiliary_log_status_rq;
extern fiid_template_t tmpl_cmd_get_auxiliary_log_status_rs;
extern fiid_template_t tmpl_cmd_get_auxiliary_log_status_mca_rs;
extern fiid_template_t tmpl_cmd_get_auxiliary_log_status_oem_rs;

extern fiid_template_t tmpl_cmd_set_auxiliary_log_status_rq;
extern fiid_template_t tmpl_cmd_set_auxiliary_log_status_rs;

int fill_cmd_get_sel_info (fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sel_allocation_info (fiid_obj_t obj_cmd_rq);

int fill_cmd_reserve_sel (fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sel_entry (uint16_t reservation_id,
                            uint16_t record_id,
                            uint8_t offset_into_record,
                            uint8_t bytes_to_read,
                            fiid_obj_t obj_cmd_rq);

int fill_cmd_delete_sel_entry (uint16_t reservation_id,
                               uint16_t record_id,
                               fiid_obj_t obj_cmd_rq);

int fill_cmd_clear_sel (uint16_t reservation_id,
                        uint8_t operation,
                        fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sel_time (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sel_time (uint32_t time, fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sel_time_utc_offset (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sel_time_utc_offset (int16_t offset, fiid_obj_t obj_cmd_rq);

int fill_cmd_get_auxiliary_log_status (uint8_t log_type,
                                       fiid_obj_t obj_cmd_rq);

int fill_cmd_set_auxiliary_log_status (uint8_t log_type,
                                       const void *log_data,
                                       unsigned int log_data_len,
                                       fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SEL_CMDS_H */
