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

#ifndef IPMI_AUTHENTICATION_TYPE_SPEC_H
#define IPMI_AUTHENTICATION_TYPE_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_AUTHENTICATION_TYPE_NONE                  0x00
#define IPMI_AUTHENTICATION_TYPE_MD2                   0x01
#define IPMI_AUTHENTICATION_TYPE_MD5                   0x02
#define IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY 0x04
#define IPMI_AUTHENTICATION_TYPE_OEM_PROP              0x05
#define IPMI_AUTHENTICATION_TYPE_RMCPPLUS              0x06

#define IPMI_AUTHENTICATION_TYPE_VALID(__authentication_type)                    \
  (((__authentication_type) == IPMI_AUTHENTICATION_TYPE_NONE                     \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_MD2                   \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_MD5                   \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_OEM_PROP              \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_RMCPPLUS) ? 1 : 0)

#define IPMI_1_5_AUTHENTICATION_TYPE_VALID(__authentication_type)                \
  (((__authentication_type) == IPMI_AUTHENTICATION_TYPE_NONE                     \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_MD2                   \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_MD5                   \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_STRAIGHT_PASSWORD_KEY \
    || (__authentication_type) == IPMI_AUTHENTICATION_TYPE_OEM_PROP) ? 1 : 0)

#define IPMI_2_0_AUTHENTICATION_TYPE_VALID(__authentication_type) \
  IPMI_AUTHENTICATION_TYPE_VALID ((__authentication_type))


#ifdef __cplusplus
}
#endif

#endif /* IPMI_AUTHENTICATION_TYPE_SPEC_H */
