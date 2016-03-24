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

#ifndef IPMI_KCS_INTERFACE_H
#define IPMI_KCS_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

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

extern fiid_template_t tmpl_hdr_kcs;

int fill_hdr_ipmi_kcs (uint8_t lun,
                       uint8_t fn,
                       fiid_obj_t obj_kcs_hdr);

/* returns length written to pkt on success, -1 on error */
int assemble_ipmi_kcs_pkt (fiid_obj_t obj_kcs_hdr,
                           fiid_obj_t obj_cmd,
                           void *pkt,
                           unsigned int pkt_len,
			   unsigned int flags);

/* returns 1 if fully unparsed, 0 if not, -1 on error */
int unassemble_ipmi_kcs_pkt (const void *pkt,
                             unsigned int pkt_len,
                             fiid_obj_t obj_kcs_hdr,
                             fiid_obj_t obj_cmd,
			     unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_KCS_INTERFACE_H */
