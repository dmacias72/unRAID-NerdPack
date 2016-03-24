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

#ifndef IPMI_LOCATE_H
#define IPMI_LOCATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define IPMI_LOCATE_PATH_MAX                1024

#define IPMI_ADDRESS_SPACE_ID_SYSTEM_MEMORY 0x00
#define IPMI_ADDRESS_SPACE_ID_SYSTEM_IO     0x01
#define IPMI_ADDRESS_SPACE_ID_SMBUS         0x04

#define IPMI_LOCATE_ERR_SUCCESS              0
#define IPMI_LOCATE_ERR_NULL                 1
#define IPMI_LOCATE_ERR_INVALID              2
#define IPMI_LOCATE_ERR_PARAMETERS           3
#define IPMI_LOCATE_ERR_PERMISSION           4
#define IPMI_LOCATE_ERR_OUT_OF_MEMORY        5
#define IPMI_LOCATE_ERR_SYSTEM_ERROR         6
#define IPMI_LOCATE_ERR_INTERNAL_ERROR       7
#define IPMI_LOCATE_ERR_ERRNUMRANGE          8

typedef struct ipmi_locate_ctx *ipmi_locate_ctx_t;

enum ipmi_locate_driver_type
  {
    IPMI_LOCATE_DRIVER_NONE = 0,
    IPMI_LOCATE_DRIVER_DEFAULTS = 1,
    IPMI_LOCATE_DRIVER_SMBIOS = 2,
    IPMI_LOCATE_DRIVER_ACPI = 3,
    IPMI_LOCATE_DRIVER_PCI = 4,
    IPMI_LOCATE_DRIVER_DMIDECODE = 5
  };
typedef enum ipmi_locate_driver_type ipmi_locate_driver_type_t;

#define IPMI_LOCATE_DRIVER_VALID(__val)       \
  (((__val) == IPMI_LOCATE_DRIVER_NONE        \
    || (__val) == IPMI_LOCATE_DRIVER_DEFAULTS \
    || (__val) == IPMI_LOCATE_DRIVER_SMBIOS   \
    || (__val) == IPMI_LOCATE_DRIVER_ACPI     \
    || (__val) == IPMI_LOCATE_DRIVER_PCI      \
    || (__val) == IPMI_LOCATE_DRIVER_DMIDECODE) ? 1 : 0)

enum ipmi_interface_type
  {
    IPMI_INTERFACE_RESERVED = 0,
    IPMI_INTERFACE_KCS = 1,
    IPMI_INTERFACE_SMIC = 2,
    IPMI_INTERFACE_BT = 3,
    IPMI_INTERFACE_SSIF = 4,
  };
typedef enum ipmi_interface_type ipmi_interface_type_t;

#define IPMI_INTERFACE_TYPE_VALID(__val) \
  (((__val) == IPMI_INTERFACE_KCS        \
    || (__val) == IPMI_INTERFACE_SMIC    \
    || (__val) == IPMI_INTERFACE_BT      \
    || (__val) == IPMI_INTERFACE_SSIF) ? 1 : 0)

struct ipmi_locate_info
{
  uint8_t ipmi_version_major;
  uint8_t ipmi_version_minor;
  ipmi_locate_driver_type_t locate_driver_type;
  ipmi_interface_type_t interface_type;   /* KCS, SMIC, BT, SSIF */
  char driver_device[IPMI_LOCATE_PATH_MAX];
  uint8_t address_space_id;    /* Memory mapped, IO mapped, SMBus*/
  uint64_t driver_address;
  uint8_t register_spacing;   /* Register spacing in bytes */
};

ipmi_locate_ctx_t ipmi_locate_ctx_create (void);
void ipmi_locate_ctx_destroy (ipmi_locate_ctx_t ctx);
int ipmi_locate_ctx_errnum (ipmi_locate_ctx_t ctx);
char *ipmi_locate_ctx_strerror (int errnum);
char *ipmi_locate_ctx_errormsg (ipmi_locate_ctx_t ctx);

int ipmi_locate_get_device_info (ipmi_locate_ctx_t ctx,
                                 ipmi_interface_type_t type,
                                 struct ipmi_locate_info *info);

/* Identical to ipmi_locate_get_device_info() but will NOT return
 * defaults if no device info is found.
 */
int ipmi_locate_discover_device_info (ipmi_locate_ctx_t ctx,
                                      ipmi_interface_type_t type,
                                      struct ipmi_locate_info *info);

int ipmi_locate_smbios_get_device_info (ipmi_locate_ctx_t ctx,
                                        ipmi_interface_type_t type,
                                        struct ipmi_locate_info *info);

int ipmi_locate_pci_get_device_info (ipmi_locate_ctx_t ctx,
                                     ipmi_interface_type_t type,
                                     struct ipmi_locate_info *info);

int ipmi_locate_acpi_spmi_get_device_info (ipmi_locate_ctx_t ctx,
                                           ipmi_interface_type_t interface_type,
                                           struct ipmi_locate_info *info);

int ipmi_locate_defaults_get_device_info (ipmi_locate_ctx_t ctx,
                                          ipmi_interface_type_t type,
                                          struct ipmi_locate_info *info);

int ipmi_locate_dmidecode_get_device_info (ipmi_locate_ctx_t ctx,
                                           ipmi_interface_type_t type,
                                           struct ipmi_locate_info *info);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_LOCATE_H */
