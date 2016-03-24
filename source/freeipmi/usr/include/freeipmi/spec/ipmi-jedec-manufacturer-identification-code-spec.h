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

#ifndef IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_SPEC_H
#define IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define IPMI_JEDEC_MANUFACTURER_CONTINUATION_CODES_MIN 0
#define IPMI_JEDEC_MANUFACTURER_CONTINUATION_CODES_MAX 8

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_JEDEC_MANUFACTURER_CONTINUATION_CODES_VALID(__manufacturer_continuation_codes) \
  (((__manufacturer_continuation_codes + 1) >= (IPMI_JEDEC_MANUFACTURER_CONTINUATION_CODES_MIN + 1)  \
    && (__manufacturer_continuation_codes) <= IPMI_JEDEC_MANUFACTURER_CONTINUATION_CODES_MAX) ? 1 : 0)

struct ipmi_jedec_manufacturer_id_pair {
  uint8_t id;
  char *str;
};

extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank1[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank2[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank3[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank4[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank5[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank6[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank7[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank8[];
extern const struct ipmi_jedec_manufacturer_id_pair ipmi_jedec_manufacturer_id_bank9[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_JEDEC_MANUFACTURER_IDENTIFICATION_CODE_SPEC_H */
