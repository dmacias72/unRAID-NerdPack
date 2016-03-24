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

#ifndef IPMI_PRIVILEGE_LEVEL_SPEC_H
#define IPMI_PRIVILEGE_LEVEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_PRIVILEGE_LEVEL_RESERVED      0x00
#define IPMI_PRIVILEGE_LEVEL_HIGHEST_LEVEL 0x00 /* IPMI 2.0 */
#define IPMI_PRIVILEGE_LEVEL_UNSPECIFIED   0x00 /* RMCP+ Cipher Suite Priv Config */
#define IPMI_PRIVILEGE_LEVEL_CALLBACK      0x01
#define IPMI_PRIVILEGE_LEVEL_USER          0x02
#define IPMI_PRIVILEGE_LEVEL_OPERATOR      0x03
#define IPMI_PRIVILEGE_LEVEL_ADMIN         0x04
#define IPMI_PRIVILEGE_LEVEL_OEM           0x05
#define IPMI_PRIVILEGE_LEVEL_NO_ACCESS     0x0F

#define IPMI_PRIVILEGE_LEVEL_VALID(__privilege_level)       \
  (((__privilege_level) == IPMI_PRIVILEGE_LEVEL_CALLBACK    \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_USER     \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_OPERATOR \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_ADMIN    \
    || (__privilege_level) == IPMI_PRIVILEGE_LEVEL_OEM) ? 1 : 0)

#define IPMI_1_5_PRIVILEGE_LEVEL_VALID(__privilege_level) \
  IPMI_PRIVILEGE_LEVEL_VALID (__privilege_level)

#define IPMI_2_0_PRIVILEGE_LEVEL_VALID(__privilege_level)     \
  (((__privilege_level) == IPMI_PRIVILEGE_LEVEL_HIGHEST_LEVEL \
    || IPMI_PRIVILEGE_LEVEL_VALID (__privilege_level)) ? 1 : 0)

#ifdef __cplusplus
}
#endif

#endif /* IPMI_PRIVILEGE_LEVEL_SPEC_H */
