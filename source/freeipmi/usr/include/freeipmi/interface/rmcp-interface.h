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


#ifndef RMCP_INTERFACE_H
#define RMCP_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define RMCP_VERSION_1_0              0x06 /* RMCP Version 1.0 */

#define RMCP_AUX_BUS_SHUNT            0x26F /* 623 */
#define RMCP_PRIMARY_RMCP_PORT        RMCP_AUX_BUS_SHUNT

#define RMCP_SECURE_AUX_BUS           0x298 /* 664 */
#define RMCP_SECONDARY_RMCP_PORT      RMCP_SECURE_AUX_BUS

#define RMCP_HDR_SEQ_NUM_NO_RMCP_ACK  0xFF

#define RMCP_HDR_MESSAGE_CLASS_BIT_RMCP_NORMAL   0x0
#define RMCP_HDR_MESSAGE_CLASS_BIT_RMCP_ACK      0x1

#define RMCP_HDR_MESSAGE_CLASS_ASF   0x06
#define RMCP_HDR_MESSAGE_CLASS_IPMI  0x07
#define RMCP_HDR_MESSAGE_CLASS_OEM   0x08

#define RMCP_HDR_MESSAGE_CLASS_VALID(__message_class)   \
  (((__message_class) == RMCP_HDR_MESSAGE_CLASS_ASF     \
    || (__message_class) == RMCP_HDR_MESSAGE_CLASS_IPMI \
    || (__message_class) == RMCP_HDR_MESSAGE_CLASS_OEM) ? 1 : 0)

#define RMCP_ASF_IANA_ENTERPRISE_NUM    0x11BE /* 4542 */

#define RMCP_ASF_MESSAGE_TYPE_PRESENCE_PING 0x80
#define RMCP_ASF_MESSAGE_TYPE_PRESENCE_PONG 0x40

#define RMCP_ASF_MESSAGE_TAG_MAX 0xFE

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

extern fiid_template_t tmpl_rmcp_hdr;

int fill_rmcp_hdr (uint8_t message_class, fiid_obj_t obj_rmcp_hdr);

int fill_rmcp_hdr_ipmi (fiid_obj_t obj_rmcp_hdr);

int fill_rmcp_hdr_asf (fiid_obj_t obj_rmcp_hdr);

/* returns length written to pkt on success, -1 on error */
int assemble_rmcp_pkt (fiid_obj_t obj_rmcp_hdr,
                       fiid_obj_t obj_cmd,
                       void *pkt,
                       unsigned int pkt_len,
		       unsigned int flags);

/* returns 1 if fully unparsed, 0 if not, -1 on error */
int unassemble_rmcp_pkt (const void *pkt,
                         unsigned int pkt_len,
                         fiid_obj_t obj_rmcp_hdr,
                         fiid_obj_t obj_cmd,
			 unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif /* RMCP_INTERFACE_H */
