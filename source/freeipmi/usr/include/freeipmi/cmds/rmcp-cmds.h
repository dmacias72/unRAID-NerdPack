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


#ifndef RMCP_CMDS_H
#define RMCP_CMDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_cmd_rq must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_cmd_asf_presence_ping;
extern fiid_template_t tmpl_cmd_asf_presence_pong;

/* MESSAGE_TAG:
   achu: Consecutive ping messages should use different message tags,
   ranging from 0x00 to 0xFE.  This is because the RMCP consumers may
   optionally discard duplicate messages.  */

int fill_cmd_asf_presence_ping (uint8_t message_tag, fiid_obj_t obj_cmd);

#ifdef __cplusplus
}
#endif

#endif /* RMCP_CMDS_H */
