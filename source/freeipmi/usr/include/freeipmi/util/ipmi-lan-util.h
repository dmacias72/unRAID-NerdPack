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

#ifndef IPMI_LAN_UTIL_H
#define IPMI_LAN_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_session_sequence_number (fiid_obj_t obj_lan_session_hdr,
                                            uint32_t session_sequence_number);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_session_id (fiid_obj_t obj_lan_session_hdr,
                               uint32_t session_id);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_session_authentication_code (fiid_obj_t obj_lan_session_hdr_rs,
                                                fiid_obj_t obj_lan_msg_hdr_rs,
                                                fiid_obj_t obj_cmd,
                                                fiid_obj_t obj_lan_msg_trlr_rs,
                                                uint8_t authentication_type,
                                                const void *authentication_code_data,
                                                unsigned int authentication_code_data_len);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_packet_session_authentication_code (const void *pkt,
                                                       unsigned int pkt_len,
                                                       uint8_t authentication_type,
                                                       const void *authentication_code_data,
                                                       unsigned int authentication_code_data_len);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_net_fn (fiid_obj_t obj_lan_msg_hdr, uint8_t net_fn);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_rq_seq (fiid_obj_t obj_lan_msg_hdr, uint8_t rq_seq);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_checksum (fiid_obj_t obj_lan_msg_hdr,
                             fiid_obj_t obj_cmd,
                             fiid_obj_t obj_lan_msg_trlr);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_lan_check_packet_checksum (const void *pkt, unsigned int pkt_len);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_LAN_UTIL_H */
