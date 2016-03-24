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

#ifndef IPMI_RMCPPLUS_INTERFACE_H
#define IPMI_RMCPPLUS_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#include <sys/types.h>
#include <sys/socket.h>

/**************************
* IPMI 2.0 Payload Types *
**************************/

#define IPMI_PAYLOAD_TYPE_IPMI                            0x00
#define IPMI_PAYLOAD_TYPE_SOL                             0x01
#define IPMI_PAYLOAD_TYPE_OEM_EXPLICIT                    0x02
#define IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_REQUEST   0x10
#define IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE  0x11
#define IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_1                  0x12
#define IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2                  0x13
#define IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_3                  0x14
#define IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4                  0x15
/* 20h - 27h - OEM */
/* all other reserved */

#define IPMI_PAYLOAD_TYPE_VALID(__payload_type)                             \
  (((__payload_type) == IPMI_PAYLOAD_TYPE_IPMI                              \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_SOL                            \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_OEM_EXPLICIT                   \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_REQUEST  \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_1                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_3                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4) ? 1 : 0)

#define IPMI_PAYLOAD_TYPE_SESSION_SETUP(__payload_type)                     \
  (((__payload_type) == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_REQUEST     \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RMCPPLUS_OPEN_SESSION_RESPONSE \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_1                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_2                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_3                 \
    || (__payload_type) == IPMI_PAYLOAD_TYPE_RAKP_MESSAGE_4) ? 1 : 0)

/**************************
* IPMI 2.0 Payload Flags *
**************************/
#define IPMI_PAYLOAD_FLAG_UNENCRYPTED                      0x0
#define IPMI_PAYLOAD_FLAG_ENCRYPTED                        0x1
#define IPMI_PAYLOAD_FLAG_UNAUTHENTICATED                  0x0
#define IPMI_PAYLOAD_FLAG_AUTHENTICATED                    0x1

#define IPMI_PAYLOAD_ENCRYPTED_FLAG_VALID(__payload_flag) \
  (((__payload_flag) == IPMI_PAYLOAD_FLAG_UNENCRYPTED     \
    || (__payload_flag) == IPMI_PAYLOAD_FLAG_ENCRYPTED) ? 1 : 0)

#define IPMI_PAYLOAD_AUTHENTICATED_FLAG_VALID(__payload_flag) \
  (((__payload_flag) == IPMI_PAYLOAD_FLAG_UNENCRYPTED         \
    || (__payload_flag) == IPMI_PAYLOAD_FLAG_ENCRYPTED) ? 1 : 0)

/*********************************************
* IPMI 2.0 Authentication Algorithm Numbers *
*********************************************/

#define IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE           0x00
#define IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1      0x01
#define IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5       0x02
#define IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256    0x03
/* C0h - FFh - OEM */
/* all other reserved */

#define IPMI_AUTHENTICATION_ALGORITHM_VALID(__algorithm)             \
  (((__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE         \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1 \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5  \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256) ? 1 : 0)

#define IPMI_AUTHENTICATION_ALGORITHM_SUPPORTED(__algorithm)         \
  (((__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE         \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1 \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5  \
    || (__algorithm) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256) ? 1 : 0)

/****************************************
* IPMI 2.0 Integrity Algorithm Numbers *
****************************************/

#define IPMI_INTEGRITY_ALGORITHM_NONE                     0x00
#define IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96             0x01
#define IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128             0x02
#define IPMI_INTEGRITY_ALGORITHM_MD5_128                  0x03
#define IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128          0x04
/* C0h - FFh - OEM */
/* all other reserved */

#define IPMI_INTEGRITY_ALGORITHM_VALID(__algorithm)           \
  (((__algorithm) == IPMI_INTEGRITY_ALGORITHM_NONE            \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96 \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128 \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_MD5_128      \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128) ? 1 : 0)

#define IPMI_INTEGRITY_ALGORITHM_SUPPORTED(__algorithm)       \
  (((__algorithm) == IPMI_INTEGRITY_ALGORITHM_NONE            \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96 \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128 \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_MD5_128      \
    || (__algorithm) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128) ? 1 : 0)

/**********************************************
* IPMI 2.0 Confidentiality Algorithm Numbers *
**********************************************/

#define IPMI_CONFIDENTIALITY_ALGORITHM_NONE               0x00
#define IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128        0x01
#define IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128           0x02
#define IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40            0x03
/* 30h - 3Fh - OEM */
/* all other reserved */

#define IPMI_CONFIDENTIALITY_ALGORITHM_VALID(__algorithm)           \
  (((__algorithm) ==  IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
    || (__algorithm) ==  IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128 \
    || (__algorithm) ==  IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128    \
    || (__algorithm) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40) ? 1 : 0)

#define IPMI_CONFIDENTIALITY_ALGORITHM_SUPPORTED(__algorithm)       \
  (((__algorithm) ==  IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
    || (__algorithm) ==  IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128) ? 1 : 0)

/***************************************
* IPMI 2.0 Misc Flags and Definitions *
***************************************/

#define IPMI_AUTHENTICATION_PAYLOAD_TYPE                  0x00
#define IPMI_AUTHENTICATION_PAYLOAD_LENGTH                0x08
#define IPMI_INTEGRITY_PAYLOAD_TYPE                       0x01
#define IPMI_INTEGRITY_PAYLOAD_LENGTH                     0x08
#define IPMI_CONFIDENTIALITY_PAYLOAD_TYPE                 0x02
#define IPMI_CONFIDENTIALITY_PAYLOAD_LENGTH               0x08

#define IPMI_USER_NAME_PRIVILEGE_LOOKUP                   0x0
#define IPMI_NAME_ONLY_LOOKUP                             0x1

#define IPMI_USER_NAME_LOOKUP_VALID(__username_lookup_flag)     \
  (((__username_lookup_flag) == IPMI_USER_NAME_PRIVILEGE_LOOKUP \
    || (__username_lookup_flag) == IPMI_NAME_ONLY_LOOKUP) ? 1 : 0)

#define IPMI_REMOTE_CONSOLE_RANDOM_NUMBER_LENGTH          16
#define IPMI_MANAGED_SYSTEM_RANDOM_NUMBER_LENGTH          16
#define IPMI_MANAGED_SYSTEM_GUID_LENGTH                   16

#define IPMI_NEXT_HEADER                                  0x07

#define IPMI_INTEGRITY_PAD_MULTIPLE                       4
#define IPMI_INTEGRITY_PAD_DATA                           0xFF

#define IPMI_MAX_PAYLOAD_LENGTH                           65536
/* achu: b/c ipmi_msg_len is 2 bytes */

#define IPMI_HMAC_SHA1_DIGEST_LENGTH                      20
#define IPMI_HMAC_MD5_DIGEST_LENGTH                       16
#define IPMI_MD5_DIGEST_LENGTH                            16
#define IPMI_HMAC_SHA1_96_DIGEST_LENGTH                   12
#define IPMI_HMAC_SHA256_DIGEST_LENGTH                    32

#define IPMI_HMAC_SHA1_96_AUTHENTICATION_CODE_LENGTH      12
#define IPMI_HMAC_MD5_128_AUTHENTICATION_CODE_LENGTH      16
#define IPMI_MD5_128_AUTHENTICATION_CODE_LENGTH           16
#define IPMI_HMAC_SHA256_128_AUTHENTICATION_CODE_LENGTH   16

/* Refer to table 22-19 */
/* XXX - Errata 4 defines SHA256 but not cipher suite IDs */
/* achu: Intel support says Cipher Suite 15-19 maps to 1-5 using
 * SHA256 instead of SHA1 and SHA256-128 instead of SHA1-96.
 */
/* Cipher Suite 17 confirmed via DCMI 1.1 specification */
#define IPMI_CIPHER_SUITE_ID_MIN                          0
#define IPMI_CIPHER_SUITE_ID_MAX                          19

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

extern fiid_template_t tmpl_rmcpplus_session_hdr;
extern fiid_template_t tmpl_rmcpplus_session_trlr;

extern fiid_template_t tmpl_rmcpplus_payload;

extern fiid_template_t tmpl_rmcpplus_open_session_request;
extern fiid_template_t tmpl_rmcpplus_open_session_response;
extern fiid_template_t tmpl_rmcpplus_rakp_message_1;
extern fiid_template_t tmpl_rmcpplus_rakp_message_2;
extern fiid_template_t tmpl_rmcpplus_rakp_message_3;
extern fiid_template_t tmpl_rmcpplus_rakp_message_4;

/* ipmi_rmcpplus_init
 *
 * Must be called first to initialize crypt libs.  In threaded
 * programs, must be called before threads are created.
 *
 * If errno returned == EPERM, underlying crypt library incompatible.
 *
 * Returns 0 on success, -1 on error.
 */
int ipmi_rmcpplus_init (void);

int fill_rmcpplus_session_hdr (uint8_t payload_type,
                               uint8_t payload_authenticated,
                               uint8_t payload_encrypted,
                               uint32_t oem_iana,
                               uint16_t oem_payload_id,
                               uint32_t session_id,
                               uint32_t session_sequence_number,
                               fiid_obj_t obj_rmcpplus_session_hdr);

int fill_rmcpplus_session_trlr (fiid_obj_t obj_rmcpplus_session_trlr);

int fill_rmcpplus_payload (const void *confidentiality_header,
                           unsigned int confidentiality_header_len,
                           const void *payload_data,
                           unsigned int payload_data_len,
                           const void *confidentiality_trailer,
                           unsigned int confidentiality_trailer_len,
                           fiid_obj_t obj_cmd_rq);

int fill_rmcpplus_open_session (uint8_t message_tag,
                                uint8_t requested_maximum_privilege_level,
                                uint32_t remote_console_session_id,
                                uint8_t authentication_algorithm,
                                uint8_t integrity_algorithm,
                                uint8_t confidentiality_algorithm,
                                fiid_obj_t obj_cmd_rq);

int fill_rmcpplus_rakp_message_1 (uint8_t message_tag,
                                  uint32_t managed_system_session_id,
                                  const void *remote_console_random_number,
                                  unsigned int remote_console_random_number_len,
                                  uint8_t requested_maximum_privilege_level,
                                  uint8_t name_only_lookup_flag,
                                  const char *username,
                                  unsigned int username_len,
                                  fiid_obj_t obj_cmd_rq);

int fill_rmcpplus_rakp_message_3 (uint8_t message_tag,
                                  uint8_t rmcpplus_status_code,
                                  uint32_t managed_system_session_id,
                                  const void *key_exchange_authentication_code,
                                  unsigned int key_exchange_authentication_code_len,
                                  fiid_obj_t obj_cmd_rq);

/* returns length written to pkt on success, -1 on error */
int assemble_ipmi_rmcpplus_pkt (uint8_t authentication_algorithm,
                                uint8_t integrity_algorithm,
                                uint8_t confidentiality_algorithm,
                                const void *integrity_key,
                                unsigned int integrity_key_len,
                                const void *confidentiality_key,
                                unsigned int confidentiality_key_len,
                                const void *authentication_code_data,
                                unsigned int authentication_code_data_len,
                                fiid_obj_t obj_rmcp_hdr,
                                fiid_obj_t obj_rmcpplus_session_hdr,
                                fiid_obj_t obj_lan_msg_hdr,
                                fiid_obj_t obj_cmd,
                                fiid_obj_t obj_rmcpplus_session_trlr,
                                void *pkt,
                                unsigned int pkt_len,
				unsigned int flags);

/* returns 1 if fully unparsed, 0 if not, -1 on error */
int unassemble_ipmi_rmcpplus_pkt (uint8_t authentication_algorithm,
                                  uint8_t integrity_algorithm,
                                  uint8_t confidentiality_algorithm,
                                  const void *integrity_key,
                                  unsigned int integrity_key_len,
                                  const void *confidentiality_key,
                                  unsigned int confidentiality_key_len,
                                  const void *pkt,
                                  unsigned int pkt_len,
                                  fiid_obj_t obj_rmcp_hdr,
                                  fiid_obj_t obj_rmcpplus_session_hdr,
                                  fiid_obj_t obj_rmcpplus_payload,
                                  fiid_obj_t obj_lan_msg_hdr,
                                  fiid_obj_t obj_cmd,
                                  fiid_obj_t obj_lan_msg_trlr,
                                  fiid_obj_t obj_rmcpplus_session_trlr,
				  unsigned int flags);

/* returns length sent on success, -1 on error */
/* A few extra error checks, but nearly identical to system sendto() */
ssize_t ipmi_rmcpplus_sendto (int s,
			      const void *buf,
			      size_t len,
			      int flags,
			      const struct sockaddr *to,
			      socklen_t tolen);

/* returns length received on success, 0 on orderly shutdown, -1 on error */
/* A few extra error checks, but nearly identical to system recvfrom() */
ssize_t ipmi_rmcpplus_recvfrom (int s,
				void *buf,
				size_t len,
				int flags,
				struct sockaddr *from,
				socklen_t *fromlen);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_RMCPPLUS_INTERFACE_H */
