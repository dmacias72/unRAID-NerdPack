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

#ifndef IPMI_CIPHER_SUITE_RECORD_FORMAT_TEMPLATES_H
#define IPMI_CIPHER_SUITE_RECORD_FORMAT_TEMPLATES_H

#ifdef __cplusplus
extern "C" {
#endif

/* This header file is for documentation only */

#if 0

Please see fiid.h for details concerning the fiid interface.

The following list the configurable fields of individual packet/record
templates in FreeIPMI.  Each field is listed as a list of the
following.

{ bits, "field name", field flag, field flag, ... }

bits - indicates the number of bits in the field

field name - indicates the name of the field, used for getting/setting
             fields in the fiid API.

field flags - flags indicating qualities of the field.  The following
              qualities may exist for each field.

    REQUIRED - field is required for the packet/record
    OPTIONAL - field is optional for the packet/record

    LENGTH-FIXED - field length is fixed at the number of bits listed

    LENGTH-VARIABLE - field length is variable for the number of bits
                      listed

    MAKES-PACKET-SUFFICIENT - indicates field or fields are
                              "sufficient" to make a packet/record valid
                              and not malformed, but not necessarily a
                              complete packet/record.

Cipher Suite Record Header
--------------------------

FIID Template: tmpl_cipher_suite_record_header

    { 6, "record_format", REQUIRED, LENGTH-FIXED }
    { 2, "tag_bits", REQUIRED, LENGTH-FIXED }

Cipher Suite Record
-------------------

FIID Template: tmpl_cipher_suite_record

    { 6, "record_format", REQUIRED, LENGTH-FIXED }
    { 2, "tag_bits", REQUIRED, LENGTH-FIXED }
    { 8, "cipher_suite_id", REQUIRED, LENGTH-FIXED }
    { 6, "authentication_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "authentication_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }
    { 6, "integrity_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "integrity_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }
    { 6, "confidentiality_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "confidentiality_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }

OEM Cipher Suite Record
-----------------------

FIID Template: tmpl_oem_cipher_suite_record

    { 6, "record_format", REQUIRED, LENGTH-FIXED }
    { 2, "tag_bits", REQUIRED, LENGTH-FIXED }
    { 8, "oem_cipher_suite_id", REQUIRED, LENGTH-FIXED }
    { 24, "oem_iana", REQUIRED, LENGTH-FIXED }
    { 6, "authentication_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "authentication_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }
    { 6, "integrity_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "integrity_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }
    { 6, "confidentiality_algorithm", REQUIRED, LENGTH-FIXED }
    { 2, "confidentiality_algorithm_tag_bits", REQUIRED, LENGTH-FIXED }

#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CIPHER_SUITE_RECORD_FORMAT_TEMPLATES_H */
