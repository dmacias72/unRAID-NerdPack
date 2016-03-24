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

#ifndef IPMI_INTELDCMI_DRIVER_H
#define IPMI_INTELDCMI_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_INTELDCMI_DRIVER_DEVICE_DEFAULT    "/dev/dcmi"

#define IPMI_INTELDCMI_ERR_SUCCESS              0
#define IPMI_INTELDCMI_ERR_NULL                 1
#define IPMI_INTELDCMI_ERR_INVALID              2
#define IPMI_INTELDCMI_ERR_PARAMETERS           3
#define IPMI_INTELDCMI_ERR_PERMISSION           4
#define IPMI_INTELDCMI_ERR_DEVICE_NOT_FOUND     5
#define IPMI_INTELDCMI_ERR_IO_NOT_INITIALIZED   6
#define IPMI_INTELDCMI_ERR_OUT_OF_MEMORY        7
#define IPMI_INTELDCMI_ERR_DRIVER_TIMEOUT       8
#define IPMI_INTELDCMI_ERR_IPMI_ERROR           9
#define IPMI_INTELDCMI_ERR_SYSTEM_ERROR        10
#define IPMI_INTELDCMI_ERR_INTERNAL_ERROR      11
#define IPMI_INTELDCMI_ERR_ERRNUMRANGE         12

#define IPMI_INTELDCMI_FLAGS_DEFAULT           0x00000000

typedef struct ipmi_inteldcmi_ctx *ipmi_inteldcmi_ctx_t;

ipmi_inteldcmi_ctx_t ipmi_inteldcmi_ctx_create (void);
void ipmi_inteldcmi_ctx_destroy (ipmi_inteldcmi_ctx_t ctx);
int ipmi_inteldcmi_ctx_errnum (ipmi_inteldcmi_ctx_t ctx);
char *ipmi_inteldcmi_ctx_strerror (int errnum);
char *ipmi_inteldcmi_ctx_errormsg (ipmi_inteldcmi_ctx_t ctx);

int ipmi_inteldcmi_ctx_get_driver_device (ipmi_inteldcmi_ctx_t ctx, char **driver_device);
int ipmi_inteldcmi_ctx_get_flags (ipmi_inteldcmi_ctx_t ctx, unsigned int *flags);

int ipmi_inteldcmi_ctx_set_driver_device (ipmi_inteldcmi_ctx_t ctx, const char *driver_device);
int ipmi_inteldcmi_ctx_set_flags (ipmi_inteldcmi_ctx_t ctx, unsigned int flags);

int ipmi_inteldcmi_ctx_io_init (ipmi_inteldcmi_ctx_t ctx);

int ipmi_inteldcmi_cmd (ipmi_inteldcmi_ctx_t ctx,
                       uint8_t lun,
                       uint8_t net_fn,
                       fiid_obj_t obj_cmd_rq,
                       fiid_obj_t obj_cmd_rs);

int ipmi_inteldcmi_cmd_ipmb (ipmi_inteldcmi_ctx_t ctx,
                            uint8_t channel_number,
                            uint8_t rs_addr,
                            uint8_t lun,
                            uint8_t net_fn,
                            fiid_obj_t obj_cmd_rq,
                            fiid_obj_t obj_cmd_rs);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_INTELDCMI_DRIVER_H */
