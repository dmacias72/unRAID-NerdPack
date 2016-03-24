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

#ifndef IPMI_CMD_OEM_FUJITSU_SPEC_H
#define IPMI_CMD_OEM_FUJITSU_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Fujitsu iRMC S1 / iRMC S2
 *
 * http://manuals.ts.fujitsu.com/file/4390/irmc_s2-en.pdf
 */
/* IPMI_NET_FN_OEM_GROUP_RQ / IPMI_NET_FN_OEM_GROUP_RS */
#define IPMI_CMD_OEM_FUJITSU_POWER         0x01
#define IPMI_CMD_OEM_FUJITSU_COMMUNICATION 0x02
#define IPMI_CMD_OEM_FUJITSU_FAN_TEST      0x10
#define IPMI_CMD_OEM_FUJITSU_BIOS          0xF1
#define IPMI_CMD_OEM_FUJITSU_SYSTEM        0xF5

/* IPMI_NET_FN_FIRMWARE_RQ / IPMI_NET_FN_FIRMWARE_RS */
#define IPMI_CMD_OEM_FUJITSU_SET_FIRMWARE_SELECTOR 0x04
#define IPMI_CMD_OEM_FUJITSU_GET_FIRMWARE_SELECTOR 0x05

/* IPMI_NET_FN_OEM_FUJITSU_GENERIC_RQ / IPMI_NET_FN_OEM_FUJITSU_GENERIC_RS */
#define IPMI_CMD_OEM_FUJITSU_GET_REMOTE_STORAGE_CONNECTION_OR_STATUS 0x19
#define IPMI_CMD_OEM_FUJITSU_SET_VIDEO_DISPLAY_ON_OFF                0x1A

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_FUJITSU_SPEC_H */
