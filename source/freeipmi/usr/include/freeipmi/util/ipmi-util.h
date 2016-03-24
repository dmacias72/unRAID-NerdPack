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

#ifndef IPMI_UTIL_H
#define IPMI_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

uint8_t ipmi_checksum (const void *buf, unsigned int buflen);

/* Call first time w/ checksum_initial 0, pass in result for subsequent calls */
uint8_t ipmi_checksum_incremental (const void *buf, unsigned int buflen, uint8_t checksum_initial);
/* Can pass NULL/0 for final buf/buflen */
uint8_t ipmi_checksum_final (const void *buf, unsigned int buflen, uint8_t checksum_initial);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_check_cmd (fiid_obj_t obj_cmd, uint8_t cmd);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_check_completion_code (fiid_obj_t obj_cmd, uint8_t completion_code);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_check_completion_code_success (fiid_obj_t obj_cmd);

int ipmi_get_random (void *buf, unsigned int buflen);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_is_ipmi_1_5_packet (const void *pkt, unsigned int pkt_len);

/* returns 1 on pass, 0 on fail, -1 on error */
int ipmi_is_ipmi_2_0_packet (const void *pkt, unsigned int pkt_len);

int ipmi_check_session_sequence_number_1_5_init (uint32_t *highest_received_sequence_number,
                                                 uint32_t *previously_received_list);

int ipmi_check_session_sequence_number_2_0_init (uint32_t *highest_received_sequence_number,
                                                 uint32_t *previously_received_list);

/* returns 1 if sequence number in range, 0 if not, -1 on error */
/* highest_received_sequence_number and previously_received_list updated on success */
/* set sequence_number_window to 0 for default */
int ipmi_check_session_sequence_number_1_5 (uint32_t session_sequence_number,
                                            uint32_t *highest_received_sequence_number,
                                            uint32_t *previously_received_list,
                                            unsigned int sequence_number_window);

/* returns 1 if sequence number in range, 0 if not, -1 on error */
/* highest_received_sequence_number and previously_received_list updated on success */
/* set sequence_number_window to 0 for default */
int ipmi_check_session_sequence_number_2_0 (uint32_t session_sequence_number,
                                            uint32_t *highest_received_sequence_number,
                                            uint32_t *previously_received_list,
                                            unsigned int sequence_number_window);

const char *ipmi_cmd_str (uint8_t net_fn, uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_UTIL_H */
