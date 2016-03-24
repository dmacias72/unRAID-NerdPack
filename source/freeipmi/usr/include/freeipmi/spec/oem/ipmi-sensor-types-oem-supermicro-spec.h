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

#ifndef IPMI_SENSOR_TYPES_OEM_SUPERMICRO_SPEC_H
#define IPMI_SENSOR_TYPES_OEM_SUPERMICRO_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Supermicro X7DBR-3 (X7DBR_3)
 * Supermicro X7DB8
 * Supermicro X8DTN
 * Supermicro X7SBI-LN4 (X7SBI_LN4)
 * Supermicro X8DTH
 * Supermicro X8DTG
 * Supermicro X8DTU
 * Supermicro X8DT3-LN4F (X8DT3_LN4F)
 * Supermicro X8DTU-6+ (X8DTU_6PLUS)
 * Supermicro X8DTL
 * Supermicro X8DTL-3F (X8DTL_3F)
 * Supermicro X8SIL-F  (X8SIL_F)
 * Supermicro X9SCL
 * Supermicro X9SCM
 * Supermicro X8DTN+-F (X8DTNPLUS_F)
 * Supermicro X8SIE
 * Supermicro X9SCA-F-O (X9SCA-F-O)
 * Supermicro H8DGU-F (H8DGU_F)
 * Supermicro X9DRi-F (X9DRI_F)
 * Supermicro X9DRI-LN4F+ (X9DRI_LN4F_PLUS)
 * Supermicro X9SPU-F-O (X9SPU-F-O)
 * Supermicro X9SCM-iiF (X9SCM_IIF)
 */
/* achu: not official names, named based on use context */
#define IPMI_SENSOR_TYPE_OEM_SUPERMICRO_CPU_TEMP 0xC0 

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_TYPES_OEM_SUPERMICRO_SPEC_H */
