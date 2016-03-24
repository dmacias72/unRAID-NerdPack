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

#ifndef IPMI_SDR_INTEL_NODE_MANAGER_OEM_H
#define IPMI_SDR_INTEL_NODE_MANAGER_OEM_H

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

/* return (1) - is oem intel node manager, fully parsed
 * return (0) - is not oem intel node manager
 * return (-1) - error
 */
int ipmi_sdr_oem_parse_intel_node_manager (ipmi_sdr_ctx_t ctx,
					   const void *sdr_record,
					   unsigned int sdr_record_len,
					   uint8_t *nm_device_slave_address,
                                           uint8_t *sensor_owner_lun,
                                           uint8_t *channel_number,
                                           uint8_t *nm_health_event_sensor_number,
                                           uint8_t *nm_exception_event_sensor_number,
                                           uint8_t *nm_operational_capabilities_sensor_number,
                                           uint8_t *nm_alert_threshold_exceeded_sensor_number);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SDR_INTEL_NODE_MANAGER_OEM_H */
