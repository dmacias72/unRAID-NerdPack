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

#ifndef IPMI_CIPHER_SUITE_RECORD_FORMAT_H
#define IPMI_CIPHER_SUITE_RECORD_FORMAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

/* Notes:
   Refer to IPMI 2.0 spec Table 22-18.
 */

#define IPMI_CIPHER_SUITE_TAG_BITS_AUTHENTICATION_ALGORITHM   0x0
#define IPMI_CIPHER_SUITE_TAG_BITS_INTEGRITY_ALGORITHM        0x1
#define IPMI_CIPHER_SUITE_TAG_BITS_CONFIDENTIALITY_ALGORITHM  0x2
#define IPMI_CIPHER_SUITE_TAG_BITS_RECORD                     0x3

#define IPMI_CIPHER_SUITE_RECORD_FORMAT_STANDARD              0x00
#define IPMI_CIPHER_SUITE_RECORD_FORMAT_OEM                   0x01

#define IPMI_CIPHER_SUITE_RECORD_FORMAT_VALID(__val)    \
  (((__val) == IPMI_CIPHER_SUITE_RECORD_FORMAT_STANDARD \
    || (__val) == IPMI_CIPHER_SUITE_RECORD_FORMAT_OEM) ? 1 : 0)

#define IPMI_CIPHER_SUITE_TAG_BITS_VALID(__val)                        \
  (((__val) == IPMI_CIPHER_SUITE_TAG_BITS_AUTHENTICATION_ALGORITHM     \
    || (__val) == IPMI_CIPHER_SUITE_TAG_BITS_INTEGRITY_ALGORITHM       \
    || (__val) == IPMI_CIPHER_SUITE_TAG_BITS_CONFIDENTIALITY_ALGORITHM \
    || (__val) == IPMI_CIPHER_SUITE_TAG_BITS_RECORD) ? 1 : 0)

/* 
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cipher_suite_record_header;
extern fiid_template_t tmpl_cipher_suite_record;
extern fiid_template_t tmpl_oem_cipher_suite_record;

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CIPHER_SUITE_RECORD_FORMAT_H */
