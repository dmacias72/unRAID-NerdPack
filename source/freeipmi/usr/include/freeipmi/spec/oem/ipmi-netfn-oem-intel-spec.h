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

#ifndef IPMI_NETFN_OEM_INTEL_SPEC_H
#define IPMI_NETFN_OEM_INTEL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 */

/* achu: not official names, named based on use context */
#define IPMI_NET_FN_OEM_INTEL_GENERIC_RQ 0x30
#define IPMI_NET_FN_OEM_INTEL_GENERIC_RS 0x31

#define IPMI_NET_FN_OEM_INTEL_CONFIG_RQ 0x32
#define IPMI_NET_FN_OEM_INTEL_CONFIG_RS 0x33

#ifdef __cplusplus
}
#endif

#endif /* IPMI_NETFN_OEM_INTEL_SPEC_H */
