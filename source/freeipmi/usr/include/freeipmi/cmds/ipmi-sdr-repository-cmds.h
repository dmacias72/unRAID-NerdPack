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

#ifndef IPMI_SDR_REPOSITORY_CMDS_H
#define IPMI_SDR_REPOSITORY_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SDR_MODAL_NON_MODAL_REPOSITORY_UPDATE_OP_UNSPECIFIED    0x0
#define IPMI_SDR_NON_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED            0x1
#define IPMI_SDR_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED                0x2
#define IPMI_SDR_MODAL_NON_MODAL_REPOSITORY_UPDATE_OP_SUPPORTED      0x3

#define IPMI_SDR_IPMB_SLAVE_ADDRESS    0x0
#define IPMI_SDR_SYSTEM_SOFTWARE_ID    0x1

#define IPMI_SDR_RECORD_ID_FIRST 0x0000
#define IPMI_SDR_RECORD_ID_LAST  0xFFFF

#define IPMI_SDR_READ_ENTIRE_RECORD_BYTES_TO_READ  0xFF

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_get_sdr_repository_info_rq;
extern fiid_template_t tmpl_cmd_get_sdr_repository_info_rs;

extern fiid_template_t tmpl_cmd_get_sdr_repository_allocation_info_rq;
extern fiid_template_t tmpl_cmd_get_sdr_repository_allocation_info_rs;

extern fiid_template_t tmpl_cmd_reserve_sdr_repository_rq;
extern fiid_template_t tmpl_cmd_reserve_sdr_repository_rs;

extern fiid_template_t tmpl_cmd_get_sdr_rq;
extern fiid_template_t tmpl_cmd_get_sdr_rs;

extern fiid_template_t tmpl_cmd_get_sdr_repository_time_rq;
extern fiid_template_t tmpl_cmd_get_sdr_repository_time_rs;

extern fiid_template_t tmpl_cmd_set_sdr_repository_time_rq;
extern fiid_template_t tmpl_cmd_set_sdr_repository_time_rs;

int fill_cmd_get_repository_info (fiid_obj_t obj_cmd_rq);
int fill_cmd_get_repository_allocation_info (fiid_obj_t obj_cmd_rq);
int fill_cmd_reserve_sdr_repository (fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sdr (uint16_t reservation_id,
                      uint16_t record_id,
                      uint8_t offset_into_record,
                      uint8_t bytes_to_read,
                      fiid_obj_t obj_cmd_rq);

int fill_cmd_get_sdr_repository_time (fiid_obj_t obj_cmd_rq);

int fill_cmd_set_sdr_repository_time (uint32_t time, fiid_obj_t obj_cmd_rq);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_REPOSITORY_CMDS_H */
