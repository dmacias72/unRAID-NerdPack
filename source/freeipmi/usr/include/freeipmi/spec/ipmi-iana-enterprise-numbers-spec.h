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

#ifndef IPMI_IANA_ENTERPRISE_NUMBERS_SPEC_H
#define IPMI_IANA_ENTERPRISE_NUMBERS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Convenience macros, will be added as needed in code */
#define IPMI_IANA_ENTERPRISE_ID_IBM                       2
#define IPMI_IANA_ENTERPRISE_ID_HP                       11
#define IPMI_IANA_ENTERPRISE_ID_SUN_MICROSYSTEMS         42
#define IPMI_IANA_ENTERPRISE_ID_INTEL                   343
#define IPMI_IANA_ENTERPRISE_ID_DELL                    674
#define IPMI_IANA_ENTERPRISE_ID_MAGNUM_TECHNOLOGIES    5593
#define IPMI_IANA_ENTERPRISE_ID_QUANTA                 7244
#define IPMI_IANA_ENTERPRISE_ID_FUJITSU               10368
#define IPMI_IANA_ENTERPRISE_ID_PEPPERCON             10437
#define IPMI_IANA_ENTERPRISE_ID_SUPERMICRO            10876
#define IPMI_IANA_ENTERPRISE_ID_WISTRON               11161
#define IPMI_IANA_ENTERPRISE_ID_INVENTEC              20569

/* Workarounds for motherboards with invalid enterprise IDs */
#define IPMI_IANA_ENTERPRISE_ID_SUPERMICRO_WORKAROUND 47488

/* As of this writing min = 0, max = 34214 */

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_IANA_ENTERPRISE_ID_VALID(__iana_enterprise_id) \
  (((__iana_enterprise_id + 1) >= (0 + 1)                   \
    && (__iana_enterprise_id) <= 44603) ? 1 : 0)

#define IPMI_IANA_ENTERPRISE_ID_RECOGNIZED(__iana_enterprise_id) \
  (IPMI_IANA_ENTERPRISE_ID_VALID((__iana_enterprise_id)) \
   || (__iana_enterprise_id) == IPMI_IANA_ENTERPRISE_ID_SUPERMICRO_WORKAROUND)

/* Some fields can be NULL if they were not assigned/removed by IANA */
/* consider using ipmi_iana_enerprise_numbers_string() function to
 * handle some workaround situations this array will not have.
 */
extern const char *const ipmi_iana_enterprise_numbers[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_IANA_ENTERPRISE_NUMBERS_SPEC_H */
