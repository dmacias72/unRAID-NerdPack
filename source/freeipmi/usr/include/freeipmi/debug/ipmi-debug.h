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

#ifndef IPMI_DEBUG_H
#define IPMI_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

extern fiid_template_t tmpl_unexpected_data;

int ipmi_obj_dump (int fd,
                   const char *prefix,
                   const char *hdr,
                   const char *trlr,
                   fiid_obj_t obj);

int ipmi_obj_dump_ipmb (int fd,
                        const char *prefix,
                        const char *hdr,
                        const char *trlr,
                        fiid_obj_t obj,
                        fiid_template_t tmpl_ipmb_msg_hdr,
                        fiid_template_t tmpl_ipmb_cmd);

int ipmi_dump_rmcp_packet (int fd,
                           const char *prefix,
                           const char *hdr,
                           const char *trlr,
                           const void *pkt,
                           unsigned int pkt_len,
                           fiid_template_t tmpl_cmd);

int ipmi_dump_kcs_packet (int fd,
                          const char *prefix,
                          const char *hdr,
                          const char *trlr,
                          const void *pkt,
                          unsigned int pkt_len,
                          fiid_template_t tmpl_cmd);

int ipmi_dump_kcs_packet_ipmb (int fd,
                               const char *prefix,
                               const char *hdr,
                               const char *trlr,
                               const void *pkt,
                               unsigned int pkt_len,
                               fiid_template_t tmpl_cmd,
                               fiid_template_t tmpl_ipmb_msg_hdr,
                               fiid_template_t tmpl_ipmb_cmd);

int ipmi_dump_ssif_packet (int fd,
                           const char *prefix,
                           const char *hdr,
                           const char *trlr,
                           const void *pkt,
                           unsigned int pkt_len,
                           fiid_template_t tmpl_cmd);

int ipmi_dump_lan_packet (int fd,
                          const char *prefix,
                          const char *hdr,
                          const char *trlr,
                          const void *pkt,
                          unsigned int pkt_len,
                          fiid_template_t tmpl_lan_msg_hdr,
                          fiid_template_t tmpl_cmd);

int ipmi_dump_lan_packet_ipmb (int fd,
                               const char *prefix,
                               const char *hdr,
                               const char *trlr,
                               const void *pkt,
                               unsigned int pkt_len,
                               fiid_template_t tmpl_lan_msg_hdr,
                               fiid_template_t tmpl_cmd,
                               fiid_template_t tmpl_ipmb_msg_hdr,
                               fiid_template_t tmpl_ipmb_cmd);

int ipmi_dump_rmcpplus_packet (int fd,
                               const char *prefix,
                               const char *hdr,
                               const char *trlr,
                               uint8_t authentication_algorithm,
                               uint8_t integrity_algorithm,
                               uint8_t confidentiality_algorithm,
                               const void *integrity_key,
                               unsigned int integrity_key_len,
                               const void *confidentiality_key,
                               unsigned int confidentiality_key_len,
                               const void *pkt,
                               unsigned int pkt_len,
                               fiid_template_t tmpl_lan_msg_hdr,
                               fiid_template_t tmpl_cmd);

int ipmi_dump_rmcpplus_packet_ipmb (int fd,
                                    const char *prefix,
                                    const char *hdr,
                                    const char *trlr,
                                    uint8_t authentication_algorithm,
                                    uint8_t integrity_algorithm,
                                    uint8_t confidentiality_algorithm,
                                    const void *integrity_key,
                                    unsigned int integrity_key_len,
                                    const void *confidentiality_key,
                                    unsigned int confidentiality_key_len,
                                    const void *pkt,
                                    unsigned int pkt_len,
                                    fiid_template_t tmpl_lan_msg_hdr,
                                    fiid_template_t tmpl_cmd,
                                    fiid_template_t tmpl_ipmb_msg_hdr,
                                    fiid_template_t tmpl_ipmb_cmd);

int ipmi_dump_sdr_record (int fd,
                          const char *prefix,
                          const char *hdr,
                          const char *trlr,
                          const void *sdr_record,
                          unsigned int sdr_record_len);

int ipmi_dump_hex (int fd,
                   const char *prefix,
                   const char *hdr,
                   const char *trlr,
                   const void *buf,
                   unsigned int buf_len);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_DEBUG_H */
