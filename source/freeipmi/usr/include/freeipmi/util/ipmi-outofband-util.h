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

#ifndef IPMI_OUTOFBAND_UTIL_H
#define IPMI_OUTOFBAND_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

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

/* returns 1 on supported, 0 on not-supported, -1 on error */
/* obj_cmd must be get authentication capabilities response */
int ipmi_check_authentication_capabilities_authentication_type (uint8_t authentication_type,
                                                                fiid_obj_t obj_cmd);

/* returns 1 on supported, 0 on not-supported, -1 on error */
/* username NULL == no username */
/* password NULL == no password */
/* obj_cmd must be get authentication capabilities response */
/* note that length of fields unimportant, only NULL vs. non-NULL checked */
int ipmi_check_authentication_capabilities_username (const char *username,
                                                     const char *password,
                                                     fiid_obj_t obj_cmd);

/* returns 1 on supported, 0 on not-supported, -1 on error */
/* obj_cmd must be get authentication capabilities response */
int ipmi_check_authentication_capabilities_ipmi_2_0 (fiid_obj_t obj_cmd);

/* returns 1 on supported, 0 on not-supported, -1 on error */
/* k_g NULL == no k_g */
/* obj_cmd must be get authentication capabilities response */
/* note that length of fields unimportant, only NULL vs. non-NULL checked */
int ipmi_check_authentication_capabilities_k_g (const void *k_g,
                                                fiid_obj_t obj_cmd);

/* returns 1 on privilege level supported, 0 on not-supported, -1 on error */
/* obj_cmd must be open session response */
int ipmi_check_open_session_maximum_privilege (uint8_t privilege_level,
                                               fiid_obj_t obj_cmd);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OUTOFBAND_UTIL_H */
