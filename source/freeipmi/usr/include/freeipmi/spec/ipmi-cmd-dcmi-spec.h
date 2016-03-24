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
/*****************************************************************************\
 *  Copyright (C) 2009-2015 Lawrence Livermore National Security, LLC.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  LLNL-CODE-413270
 *
 *  This file is part of Ipmi-Dcmi, tools and libraries to support the
 *  data center manageability interface (DCMI).  For details, see
 *  http://www.llnl.gov/linux/.
 *
 *  Ipmi-Dcmi is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmi-Dcmi is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmi-Dcmi.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMI_CMD_DCMI_SPEC_H
#define IPMI_CMD_DCMI_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_CMD_DCMI_GET_DCMI_CAPABILITY_INFO                    0x01
#define IPMI_CMD_DCMI_GET_POWER_READING                           0x02
#define IPMI_CMD_DCMI_GET_POWER_LIMIT                             0x03
#define IPMI_CMD_DCMI_SET_POWER_LIMIT                             0x04
#define IPMI_CMD_DCMI_ACTIVATE_DEACTIVATE_POWER_LIMIT             0x05
#define IPMI_CMD_DCMI_GET_ASSET_TAG                               0x06
#define IPMI_CMD_DCMI_GET_DCMI_SENSOR_INFO                        0x07
#define IPMI_CMD_DCMI_SET_ASSET_TAG                               0x08
#define IPMI_CMD_DCMI_GET_MANAGEMENT_CONTROLLER_IDENTIFIER_STRING 0x09
#define IPMI_CMD_DCMI_SET_MANAGEMENT_CONTROLLER_IDENTIFIER_STRING 0x0A
#define IPMI_CMD_DCMI_SET_THERMAL_LIMIT                           0x0B
#define IPMI_CMD_DCMI_GET_THERMAL_LIMIT                           0x0C
#define IPMI_CMD_DCMI_GET_TEMPERATURE_READING                     0x10
#define IPMI_CMD_DCMI_SET_DCMI_CONFIGURATION_PARAMETERS           0x12
#define IPMI_CMD_DCMI_GET_DCMI_CONFIGURATION_PARAMETERS           0x13

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CMD_DCMI_SPEC_H */
