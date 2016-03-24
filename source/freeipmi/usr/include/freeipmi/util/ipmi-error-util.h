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

#ifndef IPMI_ERROR_UTIL_H
#define IPMI_ERROR_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_ERR_STR_MAX_LEN                 2048

/* returns 0 on success, -1 on error */
int ipmi_completion_code_strerror_r (uint8_t cmd,
                                     uint8_t netfn,
                                     uint8_t comp_code,
                                     char *errstr,
                                     size_t len);

/* returns 0 on success, -1 on error */
int ipmi_completion_code_strerror_cmd_r (fiid_obj_t obj_cmd,
                                         uint8_t netfn,
                                         char *errstr,
                                         size_t len);

/* returns 0 on success, -1 on error */
int ipmi_rmcpplus_status_strerror_r (uint8_t rmcpplus_status_code,
                                     char *errstr,
                                     size_t len);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_ERROR_UTIL_H */
