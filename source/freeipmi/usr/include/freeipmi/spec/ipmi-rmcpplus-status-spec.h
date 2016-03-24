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


#ifndef IPMI_RMCPPLUS_STATUS_SPEC_H
#define IPMI_RMCPPLUS_STATUS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* RMCP+ and RAKP Message Status Codes
   -------------------------------- */
#define RMCPPLUS_STATUS_NO_ERRORS                                                        0x00
#define RMCPPLUS_STATUS_NO_ERRORS_STR \
  "No errors."

#define RMCPPLUS_STATUS_INSUFFICIENT_RESOURCES_TO_CREATE_A_SESSION                       0x01
#define RMCPPLUS_STATUS_INSUFFICIENT_RESOURCES_TO_CREATE_A_SESSION_STR \
  "Insufficient resources to create a session."

#define RMCPPLUS_STATUS_INVALID_SESSION_ID                                               0x02
#define RMCPPLUS_STATUS_INVALID_SESSION_ID_STR \
  "Invalid Session ID."

#define RMCPPLUS_STATUS_INVALID_PAYLOAD_TYPE                                             0x03
#define RMCPPLUS_STATUS_INVALID_PAYLOAD_TYPE_STR \
  "Invalid payload type."

#define RMCPPLUS_STATUS_INVALID_AUTHENTICATION_ALGORITHM                                 0x04
#define RMCPPLUS_STATUS_INVALID_AUTHENTICATION_ALGORITHM_STR \
  "Invalid authentication algorithm."

#define RMCPPLUS_STATUS_INVALID_INTEGRITY_ALGORITHM                                      0x05
#define RMCPPLUS_STATUS_INVALID_INTEGRITY_ALGORITHM_STR \
  "Invalid integrity algorithm."

#define RMCPPLUS_STATUS_NO_MATCHING_AUTHENTICATION_PAYLOAD                               0x06
#define RMCPPLUS_STATUS_NO_MATCHING_AUTHENTICATION_PAYLOAD_STR \
  "No matching authentication payload."

#define RMCPPLUS_STATUS_NO_MATCHING_INTEGRITY_PAYLOAD                                    0x07
#define RMCPPLUS_STATUS_NO_MATCHING_INTEGRITY_PAYLOAD_STR \
  "No mathing integrity payload."

#define RMCPPLUS_STATUS_INACTIVE_SESSION_ID                                              0x08
#define RMCPPLUS_STATUS_INACTIVE_SESSION_ID_STR \
  "Inactive Session ID"

#define RMCPPLUS_STATUS_INVALID_ROLE                                                     0x09
#define RMCPPLUS_STATUS_INVALID_ROLE_STR \
  "Invalid role."

#define RMCPPLUS_STATUS_UNAUTHORIZED_ROLE_OR_PRIVILEGE_LEVEL_REQUESTED                   0x0A
#define RMCPPLUS_STATUS_UNAUTHORIZED_ROLE_OR_PRIVILEGE_LEVEL_REQUESTED_STR \
  "Unauthorized role or privelege level requested."

#define RMCPPLUS_STATUS_INSUFFICIENT_RESOURCES_TO_CREATE_A_SESSION_AT_THE_REQUESTED_TIME 0x0B
#define RMCPPLUS_STATUS_INSUFFICIENT_RESOURCES_TO_CREATE_A_SESSION_AT_THE_REQUESTED_TIME_STR \
  "Insufficient resources to create a session at the requested time."

#define RMCPPLUS_STATUS_INVALID_NAME_LENGTH                                              0x0C
#define RMCPPLUS_STATUS_INVALID_NAME_LENGTH_STR \
  "Invalid name length."

#define RMCPPLUS_STATUS_UNAUTHORIZED_NAME                                                0x0D
#define RMCPPLUS_STATUS_UNAUTHORIZED_NAME_STR \
  "Unauthorized name."

#define RMCPPLUS_STATUS_UNAUTHORIZED_GUID                                                0x0E
#define RMCPPLUS_STATUS_UNAUTHORIZED_GUID_STR       \
  "Unauthorized GUID. (GUID that BMC submitted in " \
  "RAKP Message 2 was not accepted by remote console)."

#define RMCPPLUS_STATUS_INVALID_INTEGRITY_CHECK_VALUE                                    0x0F
#define RMCPPLUS_STATUS_INVALID_INTEGRITY_CHECK_VALUE_STR \
  "Invalid integrity check value."

#define RMCPPLUS_STATUS_INVALID_CONFIDENTIALITY_ALGORITHM                                0x10
#define RMCPPLUS_STATUS_INVALID_CONFIDENTIALITY_ALGORITHM_STR \
  "Invalid confidentiality algorithm."

#define RMCPPLUS_STATUS_NO_CIPHER_SUITE_MATCH_WITH_PROPOSED_SECURITY_ALGORITHMS          0x11
#define RMCPPLUS_STATUS_NO_CIPHER_SUITE_MATCH_WITH_PROPOSED_SECURITY_ALGORITHMS_STR \
  "No Cipher Suite match with proposed security algorithms."

#define RMCPPLUS_STATUS_ILLEGAL_OR_UNRECOGNIZED_PARAMETER                                0x12
#define RMCPPLUS_STATUS_ILLEGAL_OR_UNRECOGNIZED_PARAMETER_STR \
  "Illegal or Unrecognized parameter."
/* Reserved - all others */

/* To avoid gcc warnings, add +1 in comparison */
#define RMCPPLUS_STATUS_VALID(__status)                                          \
  (((__status + 1) >= RMCPPLUS_STATUS_INSUFFICIENT_RESOURCES_TO_CREATE_A_SESSION \
    && (__status) <= RMCPPLUS_STATUS_ILLEGAL_OR_UNRECOGNIZED_PARAMETER) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_RMCPPLUS_STATUS_SPEC_H */
