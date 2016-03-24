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

#ifndef IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_SPEC_H
#define IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Dell Poweredge R610
 * Dell Poweredge R710
 */

/* achu: not official names, named based on use context */

/* achu: the strings are all over the place, "status" is the best name
 * I can think of
 */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_STATUS                    0x70

/* achu: names taken from code, are correct names? */
#define IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_OEM_DIAGNOSTIC_EVENT_DATA 0x7E

/*
 * Dell Poweredge R720
 */

#define IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_FAILURE                   0x8A

#ifdef __cplusplus
}
#endif

#endif /* IPMI_EVENT_READING_TYPE_CODE_OEM_DELL_SPEC_H */
