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

#ifndef IPMI_API_H
#define IPMI_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/fiid/fiid.h>

/* ERROR CODE NOTES
 *
 * IPMI_ERR_BMC_BUSY vs IPMI_ERR_DRIVER_BUSY
 *
 * BMC_BUSY indicates the BMC cannot handle more requests, it is an
 * error typically from a completion code returned from the BMC.  The
 * DRIVER_BUSY error indicates a driver is too busy to handle
 * additional requests, the error does not come from the BMC.
 *
 * IPMI_ERR_MESSAGE_TIMEOUT
 *
 * message timeout is typical of bridging commands.  The
 * session/connection has not timed out and is fine, but a
 * bridging command could not get its bridged response back in a
 * reasonable timeframe.
 */

/* IPMI COMPLETION CODE / RMCPPLUS CODE MAPPING
 *
 * For most users, the high level error codes listed below will
 * suffice.  However, for those who want/need to see deeper IPMI
 * completion code or RMCPPlus errors, the following are mappings of
 * IPMI completion codes and RMCPPlus codes to their respective error
 * codes.
 *
 * Not that other factors outside of completion codes/RMCPPlus codes
 * could also lead to these IPMI errors.  For example, depending on
 * motherboard support of username types, a IPMI_ERR_USERNAME_INVALID
 * could be returned even though no IPMI error occurred.  In addition,
 * completion codes/RMCPPlus codes could map to different error codes,
 * depending on when the error occurred (such as during session
 * authentication vs. after authentication).
 *
 * (*) - Completion code is specific to an IPMI command
 *
 * IPMI_ERR_USERNAME_INVALID
 * - IPMI_COMP_CODE_GET_SESSION_CHALLENGE_INVALID_USERNAME (*)
 * - IPMI_COMP_CODE_GET_SESSION_CHALLENGE_NULL_USERNAME_NOT_ENABLED (*)
 *
 * IPMI_ERR_PASSWORD_INVALID
 * - RMCPPLUS_STATUS_INVALID_INTEGRITY_CHECK_VALUE
 *
 * IPMI_ERR_PRIVILEGE_LEVEL_INSUFFICIENT
 * - IPMI_COMP_CODE_INSUFFICIENT_PRIVILEGE_LEVEL
 *
 * IPMI_ERR_PRIVILEGE_LEVEL_CANNOT_BE_OBTAINED
 * - IPMI_COMP_CODE_ACTIVATE_SESSION_EXCEEDS_PRIVILEGE_LEVEL (*)
 * - IPMI_COMP_CODE_INSUFFICIENT_PRIVILEGE_LEVEL
 * - IPMI_COMP_CODE_SET_SESSION_PRIVILEGE_LEVEL_REQUESTED_LEVEL_NOT_AVAILABLE_FOR_USER (*)
 * - IPMI_COMP_CODE_SET_SESSION_PRIVILEGE_LEVEL_REQUESTED_LEVEL_EXCEEDS_USER_PRIVILEGE_LIMIT (*)
 * - RMCPPLUS_STATUS_INVALID_ROLE
 * - RMCPPLUS_STATUS_UNAUTHORIZED_ROLE_OR_PRIVILEGE_LEVEL_REQUESTED
 *
 * IPMI_ERR_CIPHER_SUITE_ID_UNAVAILABLE
 * - RMCPPLUS_STATUS_NO_CIPHER_SUITE_MATCH_WITH_PROPOSED_SECURITY_ALGORITHMS
 *
 * IPMI_ERR_MESSAGE_TIMEOUT
 * - IPMI_COMP_CODE_COMMAND_TIMEOUT
 *
 * IPMI_ERR_COMMAND_INVALID_OR_UNSUPPORTED
 * - IPMI_COMP_CODE_INVALID_COMMAND
 * - IPMI_COMP_CODE_COMMAND_INVALID_FOR_LUN  
 * - IPMI_COMP_CODE_REQUEST_DATA_LENGTH_INVALID
 * - IPMI_COMP_CODE_REQUEST_DATA_LENGTH_LIMIT_EXCEEDED
 * - IPMI_COMP_CODE_PARAMETER_OUT_OF_RANGE
 * - IPMI_COMP_CODE_INVALID_DATA_FIELD_IN_REQUEST
 *
 * IPMI_ERR_BMC_BUSY
 * - IPMI_COMP_CODE_NODE_BUSY
 * - IPMI_COMP_CODE_OUT_OF_SPACE
 * - IPMI_COMP_CODE_SDR_REPOSITORY_IN_UPDATE_MODE
 * - IPMI_COMP_CODE_DEVICE_IN_FIRMWARE_UPDATE_MODE
 * - IPMI_COMP_CODE_BMC_INITIALIZATION_IN_PROGRESS
 *
 * All other IPMI completion codes will map to IPMI_ERR_BAD_COMPLETION_CODE.
 * All other RMCPPlus codes will map to IPMI_ERR_BAD_RMCPPLUS_STATUS_CODE.
 */

enum ipmi_errnum
  {
    IPMI_ERR_SUCCESS = 0,
    IPMI_ERR_CTX_NULL = 1,
    IPMI_ERR_CTX_INVALID = 2,
    IPMI_ERR_PERMISSION = 3,
    IPMI_ERR_USERNAME_INVALID = 4,
    IPMI_ERR_PASSWORD_INVALID = 5,
    IPMI_ERR_K_G_INVALID = 6,
    IPMI_ERR_PRIVILEGE_LEVEL_INSUFFICIENT = 7,
    IPMI_ERR_PRIVILEGE_LEVEL_CANNOT_BE_OBTAINED = 8,
    IPMI_ERR_AUTHENTICATION_TYPE_UNAVAILABLE = 9,
    IPMI_ERR_CIPHER_SUITE_ID_UNAVAILABLE = 10,
    IPMI_ERR_PASSWORD_VERIFICATION_TIMEOUT = 11,
    IPMI_ERR_IPMI_2_0_UNAVAILABLE = 12,
    IPMI_ERR_CONNECTION_TIMEOUT = 13,
    IPMI_ERR_SESSION_TIMEOUT = 14,
    IPMI_ERR_DEVICE_ALREADY_OPEN = 15,
    IPMI_ERR_DEVICE_NOT_OPEN = 16,
    IPMI_ERR_DEVICE_NOT_SUPPORTED = 17,
    IPMI_ERR_DEVICE_NOT_FOUND = 18,
    IPMI_ERR_DRIVER_BUSY = 19,
    IPMI_ERR_DRIVER_TIMEOUT = 20,
    IPMI_ERR_MESSAGE_TIMEOUT = 21,
    IPMI_ERR_COMMAND_INVALID_FOR_SELECTED_INTERFACE = 22,
    IPMI_ERR_COMMAND_INVALID_OR_UNSUPPORTED = 23,
    IPMI_ERR_BAD_COMPLETION_CODE = 24,
    IPMI_ERR_BAD_RMCPPLUS_STATUS_CODE = 25,
    IPMI_ERR_NOT_FOUND = 26,
    IPMI_ERR_BMC_BUSY = 27,
    IPMI_ERR_OUT_OF_MEMORY = 28,
    IPMI_ERR_HOSTNAME_INVALID = 29,
    IPMI_ERR_PARAMETERS = 30,
    IPMI_ERR_DRIVER_PATH_REQUIRED = 31,
    IPMI_ERR_IPMI_ERROR = 32,
    IPMI_ERR_SYSTEM_ERROR = 33,
    IPMI_ERR_INTERNAL_ERROR = 34,
    IPMI_ERR_ERRNUMRANGE = 35,
  };
typedef enum ipmi_errnum ipmi_errnum_type_t;

enum ipmi_driver_type
{
  IPMI_DEVICE_UNKNOWN = 0,
  IPMI_DEVICE_LAN = 1,
  IPMI_DEVICE_LAN_2_0 = 2,
  IPMI_DEVICE_KCS = 3,
  IPMI_DEVICE_SMIC = 4,
  IPMI_DEVICE_BT = 5,
  IPMI_DEVICE_SSIF = 6,
  IPMI_DEVICE_OPENIPMI = 7,
  IPMI_DEVICE_SUNBMC = 8,
  IPMI_DEVICE_INTELDCMI = 9,
};
typedef enum ipmi_driver_type ipmi_driver_type_t;

#define IPMI_SESSION_TIMEOUT_DEFAULT                                        20000
#define IPMI_RETRANSMISSION_TIMEOUT_DEFAULT                                 1000

#define IPMI_WORKAROUND_FLAGS_DEFAULT                                       0x00000000

/* For use w/ ipmi_ctx_open_outofband() */
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_AUTHENTICATION_CAPABILITIES         0x00000001
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_ACCEPT_SESSION_ID_ZERO              0x00000002
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_FORCE_PERMSG_AUTHENTICATION         0x00000004
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_CHECK_UNEXPECTED_AUTHCODE           0x00000008
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_BIG_ENDIAN_SEQUENCE_NUMBER          0x00000010
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_NO_AUTH_CODE_CHECK                  0x00000020
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_NO_CHECKSUM_CHECK                   0x00000040

/* For use w/ ipmi_ctx_open_outofband_2_0() */
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_AUTHENTICATION_CAPABILITIES     0x00000001
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_INTEL_2_0_SESSION               0x00000002
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_SUPERMICRO_2_0_SESSION          0x00000004
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_SUN_2_0_SESSION                 0x00000008
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_OPEN_SESSION_PRIVILEGE          0x00000010
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_NON_EMPTY_INTEGRITY_CHECK_VALUE 0x00000020
#define IPMI_WORKAROUND_FLAGS_OUTOFBAND_2_0_NO_CHECKSUM_CHECK               0x00000040

/* For use w/ ipmi_ctx_open_inband() or ipmi_ctx_find_inband() */
#define IPMI_WORKAROUND_FLAGS_INBAND_ASSUME_IO_BASE_ADDRESS                 0x00000001
#define IPMI_WORKAROUND_FLAGS_INBAND_SPIN_POLL                              0x00000002

/* NONBLOCKING - for inband only, do no block if device busy.
 *
 * NOSESSION - for outofband only, do not create an IPMI session.
 * Useful for the few IPMI payloads that do not require a session for
 * an IPMI command to be sent (e.g. Get Channel Authentication
 * Capabilities, Get System GUID, PET Acknowledge).  Can only be set
 * during opening, not later using ipmi_ctx_set_flags().  If set, you
 * cannot call most IPMI payload functions, only those few that send
 * data without a session.
 * 
 * DEBUG_DUMP - for all interfaces
 *
 * NO_VALID_CHECK - do not check if IPMI response payloads are valid
 * (i.e. all required fields set).  Useful to workaround non-compliant
 * motherboards.  For example, if an IPMI payload did not return a
 * required flag in the payload, an error would be returned.  The
 * error might possibly be a session timeout, as no valid response
 * packet was ever received.  This flag would skip the checks for
 * valid fields and return the packet to the user.
 *
 * NO_LEGAL_CHECK - do no check if IPMI response payloads have
 * sufficient data (i.e. completion code fields) to be legal.  Useful
 * to work around non-compliant motherboards.  This flag is ignores
 * the legality of IPMI payloads greater than the NO_VALID_CHECK
 * option.  For example, NO_VALID_CHECK would still return an error if
 * an IPMI payload did not return a completion code in an IPMI
 * response.  The NO_LEGAL_CHECK would return such a packet to the
 * user without an error.  If the payload did not return a completion
 * code, the completion code will not be checked for.
 *
 * IGNORE_AUTHENTICATION_CODE - for IPMI 1.5 packets, do not check the
 * authentication code on response packets.  Useful to workaround
 * around non-compliant motherboards implementing invalid code/hashes.
 * Note that this is different than
 * IPMI_WORKAROUND_FLAGS_OUTOFBAND_NO_AUTH_CODE_CHECK above.  With the
 * workaround flag, all authentication codes will be ignored during
 * the entire IPMI session.  With this flag, specific packets can have
 * their authentication codes ignored.
 */

#define IPMI_FLAGS_DEFAULT                    0x00000000
#define IPMI_FLAGS_NONBLOCKING                0x00000001
#define IPMI_FLAGS_NOSESSION                  0x00000002
#define IPMI_FLAGS_DEBUG_DUMP                 0x00000010
#define IPMI_FLAGS_NO_VALID_CHECK             0x00000100
#define IPMI_FLAGS_NO_LEGAL_CHECK             0x00000200
#define IPMI_FLAGS_IGNORE_AUTHENTICATION_CODE 0x00000400

typedef struct ipmi_ctx *ipmi_ctx_t;

ipmi_ctx_t ipmi_ctx_create (void);

int ipmi_ctx_errnum (ipmi_ctx_t ctx);

char *ipmi_ctx_strerror (int errnum);

char *ipmi_ctx_errormsg (ipmi_ctx_t ctx);

int ipmi_ctx_get_flags (ipmi_ctx_t ctx, unsigned int *flags);

/* for changing flags mid-operation for corner cases */
int ipmi_ctx_set_flags (ipmi_ctx_t ctx, unsigned int flags);

/* For IPMI 1.5 sessions */
/* For session_timeout and retransmission_timeout, specify 0 for default */
int ipmi_ctx_open_outofband (ipmi_ctx_t ctx,
                             const char *hostname,
                             const char *username,
                             const char *password,
                             uint8_t authentication_type,
                             uint8_t privilege_level,
                             unsigned int session_timeout,
                             unsigned int retransmission_timeout,
                             unsigned int workaround_flags,
                             unsigned int flags);

/* For IPMI 2.0 sessions */
/* For session_timeout and retransmission_timeout, specify 0 for default */
int ipmi_ctx_open_outofband_2_0 (ipmi_ctx_t ctx,
                                 const char *hostname,
                                 const char *username,
                                 const char *password,
                                 const unsigned char *k_g,
                                 unsigned int k_g_len,
                                 uint8_t privilege_level,
                                 uint8_t cipher_suite_id,
                                 unsigned int session_timeout,
                                 unsigned int retransmission_timeout,
                                 unsigned int workaround_flags,
                                 unsigned int flags);

/* For inband sessions */
int ipmi_ctx_open_inband (ipmi_ctx_t ctx,
                          ipmi_driver_type_t driver_type,
                          int disable_auto_probe,
                          uint16_t driver_address,
                          uint8_t register_spacing,
                          const char *driver_device,
                          unsigned int workaround_flags,
                          unsigned int flags);

/* like ipmi_ctx_open_inband, but finds probes/discovers an inband device */
/* returns 1 on driver found, 0 on not found, -1 on error */
/* if specified, driver type returned in 'driver_type' */
int ipmi_ctx_find_inband (ipmi_ctx_t ctx,
                          ipmi_driver_type_t *driver_type,
                          int disable_auto_probe,
                          uint16_t driver_address,
                          uint8_t register_spacing,
                          const char *driver_device,
                          unsigned int workaround_flags,
                          unsigned int flags);

/* Set target channel and slave address so all ipmi_cmd() calls and
 * library API calls use ipmb.
 *
 * To set only one parameter, pass in NULL for the other parameter.
 * When only one parameter is passed, the other will be the default
 * target channel of IPMI_CHANNEL_NUMBER_PRIMARY_IPMB (0x0) or the
 * default rs_addr of IPMI_SLAVE_ADDRESS_BMC (0x20).
 *
 * To reset to defaults, pass in NULL for both parameters.
 *
 * Can only be called after device opened. 
 */ 
int ipmi_ctx_set_target (ipmi_ctx_t ctx, 
			 uint8_t *channel_number,
			 uint8_t *rs_addr);

int ipmi_ctx_get_target (ipmi_ctx_t ctx, 
			 uint8_t *channel_number,
			 uint8_t *rs_addr);

int ipmi_cmd (ipmi_ctx_t ctx,
              uint8_t lun,
              uint8_t net_fn,
              fiid_obj_t obj_cmd_rq,
              fiid_obj_t obj_cmd_rs);

/* convenience function to perform a single bridged IPMI command.
 * Will effectively call ipmi_ctx_set_target(), then ipmi_cmd(), then
 * will set targets back to prior originals.
 */
int ipmi_cmd_ipmb (ipmi_ctx_t ctx,
                   uint8_t channel_number,
                   uint8_t rs_addr,
                   uint8_t lun,
                   uint8_t net_fn,
                   fiid_obj_t obj_cmd_rq,
                   fiid_obj_t obj_cmd_rs);

/* for request/response, byte #1 = cmd */
/* for response, byte #2 (typically) = completion code */
/* returns length written into buf_fs on success, -1 on error */
int ipmi_cmd_raw (ipmi_ctx_t ctx,
                  uint8_t lun,
                  uint8_t net_fn,
                  const void *buf_rq,
                  unsigned int buf_rq_len,
                  void *buf_rs,
                  unsigned int buf_rs_len);

/* convenience function to perform a single bridged IPMI raw command.
 * Will effectively call ipmi_ctx_set_target(), then ipmi_cmd_raw(),
 * then will set targets back to prior originals.
 */
int ipmi_cmd_raw_ipmb (ipmi_ctx_t ctx,
		       uint8_t channel_number,
		       uint8_t rs_addr,
		       uint8_t lun,
		       uint8_t net_fn,
		       const void *buf_rq,
		       unsigned int buf_rq_len,
		       void *buf_rs,
		       unsigned int buf_rs_len);

int ipmi_ctx_close (ipmi_ctx_t ctx);

void ipmi_ctx_destroy (ipmi_ctx_t ctx);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_API_H */
