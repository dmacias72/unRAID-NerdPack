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

#ifndef IPMI_IPMB_INTERFACE_H
#define IPMI_IPMB_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_IPMB_REQUESTER_SEQUENCE_NUMBER_MAX    0x3F /* 111111b */

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * object must be for the fill function's respective fiid
 * template.
 *
 * assemble/unassemble functions must be passed fiid objects of the
 * respective expected header/trailer templates.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_ipmb_msg_hdr_rq;
extern fiid_template_t tmpl_ipmb_msg_hdr_rs;
extern fiid_template_t tmpl_ipmb_msg_trlr;
extern fiid_template_t tmpl_ipmb_msg;

int fill_ipmb_msg_hdr (uint8_t rs_addr,
                       uint8_t net_fn,
                       uint8_t rs_lun,
                       uint8_t rq_addr,
                       uint8_t rq_lun,
                       uint8_t rq_seq,
                       fiid_obj_t obj_ipmb_msg_hdr);

/* returns length written to obj_ipmb_msg on success, -1 on error */
int assemble_ipmi_ipmb_msg (fiid_obj_t obj_ipmb_msg_hdr,
                            fiid_obj_t obj_cmd,
                            fiid_obj_t obj_ipmb_msg,
			    unsigned int flags);

/* returns 1 if fully unparsed, 0 if not, -1 on error */
int unassemble_ipmi_ipmb_msg (fiid_obj_t obj_ipmb_msg,
                              fiid_obj_t obj_ipmb_msg_hdr,
                              fiid_obj_t obj_cmd,
                              fiid_obj_t obj_ipmb_msg_trlr,
			      unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_IPMB_INTERFACE_H */
