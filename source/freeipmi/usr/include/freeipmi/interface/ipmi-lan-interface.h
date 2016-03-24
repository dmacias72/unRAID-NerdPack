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

#ifndef IPMI_LAN_INTERFACE_H
#define IPMI_LAN_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#include <sys/types.h>
#include <sys/socket.h>

#define IPMI_LAN_REQUESTER_SEQUENCE_NUMBER_MAX    0x3F /* 111111b */

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

extern fiid_template_t tmpl_lan_session_hdr;
extern fiid_template_t tmpl_lan_msg_hdr_rq;
extern fiid_template_t tmpl_lan_msg_hdr_rs;
extern fiid_template_t tmpl_lan_msg_trlr;

int fill_lan_session_hdr (uint8_t authentication_type,
                          uint32_t session_sequence_number,
                          uint32_t session_id,
                          fiid_obj_t obj_lan_session_hdr);

int fill_lan_msg_hdr (uint8_t rs_addr,
                      uint8_t net_fn,
                      uint8_t rs_lun,
                      uint8_t rq_seq,
                      fiid_obj_t obj_lan_msg_hdr);

/* returns length written to pkt on success, -1 on error */
int assemble_ipmi_lan_pkt (fiid_obj_t obj_rmcp_hdr,
                           fiid_obj_t obj_lan_session_hdr,
                           fiid_obj_t obj_lan_msg_hdr,
                           fiid_obj_t obj_cmd,
                           const void *authentication_code_data,
                           unsigned int authentication_code_data_len,
                           void *pkt,
                           unsigned int pkt_len,
			   unsigned int flags);

/* returns 1 if fully unparsed, 0 if not, -1 on error */
int unassemble_ipmi_lan_pkt (const void *pkt,
                             unsigned int pkt_len,
                             fiid_obj_t obj_rmcp_hdr,
                             fiid_obj_t obj_lan_session_hdr,
                             fiid_obj_t obj_lan_msg_hdr,
                             fiid_obj_t obj_cmd,
                             fiid_obj_t obj_lan_msg_trlr,
			     unsigned int flags);

/* returns length sent on success, -1 on error */
/* A few extra error checks, but nearly identical to system sendto() */
ssize_t ipmi_lan_sendto (int s,
                         const void *buf,
                         size_t len,
                         int flags,
                         const struct sockaddr *to,
                         socklen_t tolen);

/* returns length received on success, 0 on orderly shutdown, -1 on error */
/* A few extra error checks, but nearly identical to system recvfrom() */
ssize_t ipmi_lan_recvfrom (int s,
                           void *buf,
                           size_t len,
                           int flags,
                           struct sockaddr *from,
                           socklen_t *fromlen);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_LAN_INTERFACE_H */
