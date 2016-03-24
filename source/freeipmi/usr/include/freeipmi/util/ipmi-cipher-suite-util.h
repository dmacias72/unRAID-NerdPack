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

#ifndef IPMI_CIPHER_SUITE_UTIL_H
#define IPMI_CIPHER_SUITE_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/interface/ipmi-rmcpplus-interface.h>

#define IPMI_CIPHER_SUITE_COMBINATION_VALID(__a, __i, __c)             \
  /* Cipher Suite 0 */                                                 \
  ((((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE                  \
     && (__i) == IPMI_INTEGRITY_ALGORITHM_NONE                         \
     && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE)                  \
    /* Cipher Suite 1 */                                               \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1          \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                     \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))          \
    /* Cipher Suite 2-5 */                                             \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1          \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96             \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128 \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128    \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40)))  \
    /* Cipher Suite 6 */                                               \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5           \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                     \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))          \
    /* Cipher Suite 7-10 */                                            \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5           \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128             \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128 \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128    \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40)))  \
    /* Cipher Suite 11-14 */                                           \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5           \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_MD5_128                  \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128 \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128    \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40)))  \
    /* Cipher Suite 15 */                                              \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256        \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                     \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))          \
    /* Cipher Suite 16-19 */                                           \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256        \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128          \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE           \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128 \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_128    \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_XRC4_40))) ) ? 1 : 0)

#define IPMI_CIPHER_SUITE_COMBINATION_SUPPORTED(__a, __i, __c)            \
  /* Cipher Suite 0 */                                                    \
  ((((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_NONE                     \
     && (__i) == IPMI_INTEGRITY_ALGORITHM_NONE                            \
     && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE)                     \
    /* Cipher Suite 1 */                                                  \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1             \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                        \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))             \
    /* Cipher Suite 2-3 */                                                \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA1             \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA1_96                \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE              \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128))) \
    /* Cipher Suite 6 */                                                  \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5              \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                        \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))             \
    /* Cipher Suite 7-8 */                                                \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5              \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_MD5_128                \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE              \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128))) \
    /* Cipher Suite 11-12 */                                              \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_MD5              \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_MD5_128                     \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE              \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128))) \
    /* Cipher Suite 15 */                                                 \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256           \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_NONE                        \
            && (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE))             \
    /* Cipher Suite 16-17 */                                              \
    || ((__a) == IPMI_AUTHENTICATION_ALGORITHM_RAKP_HMAC_SHA256           \
        && ((__i) == IPMI_INTEGRITY_ALGORITHM_HMAC_SHA256_128             \
            && ((__c) == IPMI_CONFIDENTIALITY_ALGORITHM_NONE              \
                || (__c) == IPMI_CONFIDENTIALITY_ALGORITHM_AES_CBC_128))) ) ? 1 : 0)

/* To avoid gcc warnings, add +1 in comparison */
/* achu: no macros here, cipher suite ids are numbers */
#define IPMI_CIPHER_SUITE_ID_SUPPORTED(__id) \
  ((((__id + 1) >= (0 + 1) && (__id) <= 3)   \
    || ((__id) >= 6 && (__id) <= 8)          \
    || ((__id) >= 11 && (__id) <= 12)        \
    || ((__id) >= 15 && (__id) <= 17)) ? 1 : 0)

int ipmi_cipher_suite_id_to_algorithms (uint8_t cipher_suite_id,
                                        uint8_t *authentication_algorithm,
                                        uint8_t *integrity_algorithm,
                                        uint8_t *confidentiality_algorithm);

int ipmi_algorithms_to_cipher_suite_id (uint8_t authentication_algorithm,
                                        uint8_t integrity_algorithm,
                                        uint8_t confidentiality_algorithm,
                                        uint8_t *cipher_suite_id);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CIPHER_SUITE_UTIL_H */
