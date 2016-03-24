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

#ifndef IPMI_SUNBMC_DRIVER_H
#define IPMI_SUNBMC_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SUNBMC_DRIVER_DEVICE_DEFAULT      "/dev/bmc"

#define IPMI_SUNBMC_ERR_SUCCESS               0
#define IPMI_SUNBMC_ERR_NULL                  1
#define IPMI_SUNBMC_ERR_INVALID               2
#define IPMI_SUNBMC_ERR_PARAMETERS            3
#define IPMI_SUNBMC_ERR_PERMISSION            4
#define IPMI_SUNBMC_ERR_DEVICE_NOT_FOUND      5
#define IPMI_SUNBMC_ERR_DEVICE_NOT_SUPPORTED  6
#define IPMI_SUNBMC_ERR_IO_NOT_INITIALIZED    7
#define IPMI_SUNBMC_ERR_OUT_OF_MEMORY         8
#define IPMI_SUNBMC_ERR_DRIVER_TIMEOUT        9
#define IPMI_SUNBMC_ERR_IPMI_ERROR           10
#define IPMI_SUNBMC_ERR_SYSTEM_ERROR         11
#define IPMI_SUNBMC_ERR_INTERNAL_ERROR       12
#define IPMI_SUNBMC_ERR_ERRNUMRANGE          13

#define IPMI_SUNBMC_FLAGS_DEFAULT              0x00000000

typedef struct ipmi_sunbmc_ctx *ipmi_sunbmc_ctx_t;

ipmi_sunbmc_ctx_t ipmi_sunbmc_ctx_create (void);
void ipmi_sunbmc_ctx_destroy (ipmi_sunbmc_ctx_t ctx);
int ipmi_sunbmc_ctx_errnum (ipmi_sunbmc_ctx_t ctx);
char *ipmi_sunbmc_ctx_strerror (int errnum);
char *ipmi_sunbmc_ctx_errormsg (ipmi_sunbmc_ctx_t ctx);

int ipmi_sunbmc_ctx_get_driver_device (ipmi_sunbmc_ctx_t ctx, char **driver_device);
int ipmi_sunbmc_ctx_get_flags (ipmi_sunbmc_ctx_t ctx, unsigned int *flags);

int ipmi_sunbmc_ctx_set_driver_device (ipmi_sunbmc_ctx_t ctx, const char *driver_device);
int ipmi_sunbmc_ctx_set_flags (ipmi_sunbmc_ctx_t ctx, unsigned int flags);

int ipmi_sunbmc_ctx_io_init (ipmi_sunbmc_ctx_t ctx);

int ipmi_sunbmc_cmd (ipmi_sunbmc_ctx_t ctx,
                     uint8_t lun,
                     uint8_t net_fn,
                     fiid_obj_t obj_cmd_rq,
                     fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SUNBMC_DRIVER_H */
