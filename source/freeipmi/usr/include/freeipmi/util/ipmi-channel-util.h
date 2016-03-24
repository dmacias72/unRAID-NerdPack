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

#ifndef IPMI_CHANNEL_UTIL_H
#define IPMI_CHANNEL_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/api/ipmi-api.h>

/* Get first channel found for medium type*/
int ipmi_get_channel_number (ipmi_ctx_t ctx,
                             uint8_t channel_medium_type,
                             uint8_t *channel_number);

/* Returns all channel numbers found for medium type, return value is
 * number of channel numbers returned.  If number of channel numbers
 * found exceeds channel_numbers_len, return is truncated.
 */
int ipmi_get_channel_numbers (ipmi_ctx_t ctx,
                              uint8_t channel_medium_type,
                              uint8_t *channel_numbers,
                              unsigned int channel_numbers_len);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_CHANNEL_UTIL_H */
