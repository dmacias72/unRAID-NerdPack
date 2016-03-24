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

#ifndef IPMI_CMD_OEM_INTEL_NODE_MANAGER_SPEC_H
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel Node Manager
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 * Intel S2600KP
 * Intel S2600WT2
 * Intel S2600WTT
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 * Quanta QSSC-S4R/Appro GB812X-CN
 */

/* IPMI_NET_FN_OEM_GROUP_RQ / IPMI_NET_FN_OEM_GROUP_RS */
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_ENABLE_DISABLE_NODE_MANAGER_POLICY_CONTROL 0xC0
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_POLICY                    0xC1
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_POLICY                    0xC2
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_POLICY_ALERT_THRESHOLDS   0xC3
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_POLICY_ALERT_THRESHOLDS   0xC4
/* legacy names */
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_ALERT_THRESHOLDS          IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_POLICY_ALERT_THRESHOLDS
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_ALERT_THRESHOLDS          IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_POLICY_ALERT_THRESHOLDS
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_POLICY_SUSPEND_PERIODS    0xC5
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_POLICY_SUSPEND_PERIODS    0xC6
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_RESET_NODE_MANAGER_STATISTICS              0xC7
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_STATISTICS                0xC8
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_CAPABILITIES              0xC9
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_VERSION                   0xCA
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_POWER_DRAW_RANGE          0xCB
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_TURBO_SYNCHRONIZATION_RATIO            0xCC
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_TURBO_SYNCHRONIZATION_RATIO            0xCD
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_SET_NODE_MANAGER_ALERT_DESTINATION         0xCE
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_NODE_MANAGER_ALERT_DESTINATION         0xCF
#define IPMI_CMD_OEM_INTEL_NODE_MANAGER_GET_LIMITING_POLICY_ID                     0xF2

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_OEM_INTEL_NODE_MANAGER_SPEC_H */
