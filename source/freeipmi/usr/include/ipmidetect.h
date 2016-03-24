/*****************************************************************************\
 *  $Id: ipmidetect.h,v 1.11 2010-02-08 22:02:31 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2012 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-228523
 *
 *  This file is part of Ipmidetect, tools and libraries for detecting
 *  IPMI nodes in a cluster. For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmidetect is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmidetect is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmidetect.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMIDETECT_H
#define IPMIDETECT_H

#include <stdio.h>

/*
 * Libipmidetect version
 *
 * MAJOR - Incremented when interfaces are changed or removed.
 *         Interfaces may be binary incompatible.  When incremented, MINOR
 *         and PATCH are zeroed.
 *
 * MINOR - Incremented when interfaces are added.  Interfaces are
 *         binary compatible with older minor versions.  When incremented,
 *         PATCH is zeroed.
 *
 * PATCH - Incremented when interfaces are not changed.  Typically
 *         incremented due to bug fixes or minor features.  Interfaces are
 *         forward and backward compatible to other PATCH versions.
 */

#define LIBIPMIDETECT_VERSION_MAJOR 1
#define LIBIPMIDETECT_VERSION_MINOR 0
#define LIBIPMIDETECT_VERSION_PATCH 0

/*
 * Ipmidetect Error Codes
 */

#define IPMIDETECT_ERR_SUCCESS               0
#define IPMIDETECT_ERR_HANDLE_NULL           1
#define IPMIDETECT_ERR_HANDLE_INVALID        2
#define IPMIDETECT_ERR_CONNECT               3
#define IPMIDETECT_ERR_CONNECT_TIMEOUT       4
#define IPMIDETECT_ERR_HOSTNAME_INVALID      5
#define IPMIDETECT_ERR_ISLOADED              6
#define IPMIDETECT_ERR_NOTLOADED             7
#define IPMIDETECT_ERR_OVERFLOW              8
#define IPMIDETECT_ERR_PARAMETERS            9
#define IPMIDETECT_ERR_NULLPTR              10
#define IPMIDETECT_ERR_OUT_OF_MEMORY        11
#define IPMIDETECT_ERR_NOTFOUND             12
#define IPMIDETECT_ERR_CONF_PARSE           13
#define IPMIDETECT_ERR_CONF_INPUT           14
#define IPMIDETECT_ERR_CONF_INTERNAL        15
#define IPMIDETECT_ERR_INTERNAL             16
#define IPMIDETECT_ERR_ERRNUMRANGE          17

typedef struct ipmidetect *ipmidetect_t;

/*
 * ipmidetect_handle_create
 *
 * Create an ipmidetect handle.
 *
 * Returns handle on success, NULL on error
 */
ipmidetect_t ipmidetect_handle_create (void);

/* ipmidetect_handle_destroy
 *
 * Destroy an ipmidetect handle.
 *
 * Returns 0 on success, -1 on error
 */
int ipmidetect_handle_destroy (ipmidetect_t handle);

/*
 * ipmidetect_load_data
 *
 * Loads data from the ipmidetectd daemon to determine which nodes
 * have been detected.
 *
 * If 'hostname' is NULL, 'port' is <= 0, or 'timeout_len' <=0, the
 * respective defaults will be used.
 *
 * Returns 0 on success, -1 on error
 */
int ipmidetect_load_data (ipmidetect_t handle,
                          const char *hostname,
                          int port,
                          int timeout_len);

/*
 * ipmidetect_errnum
 *
 * Return the most recent error number.
 *
 * Returns error number on success
 */
int ipmidetect_errnum (ipmidetect_t handle);

/*
 * ipmidetect_strerror
 *
 * Return a string message describing an error number.
 *
 * Returns pointer to message on success
 */
char *ipmidetect_strerror (int errnum);

/*
 * ipmidetect_errormsg
 *
 * Return a string message describing the most recent error.
 *
 * Returns pointer to message on success
 */
char *ipmidetect_errormsg (ipmidetect_t handle);

/*
 * ipmidetect_perror
 *
 * Output a message to standard error
 */
void ipmidetect_perror (ipmidetect_t handle, const char *msg);

/*
 * ipmidetect_get_detected_nodes_string
 *
 * Retrieve a ranged string of up nodes and store it in the buffer
 *
 * Returns 0 on success, -1 on error
 */
int ipmidetect_get_detected_nodes_string (ipmidetect_t handle,
                                          char *buf,
                                          int buflen);

/*
 * ipmidetect_get_undetected_nodes_string
 *
 * Retrieve a ranged string of undetected nodes and store it in the buffer
 *
 * Returns 0 on success, -1 on error
 */
int ipmidetect_get_undetected_nodes_string (ipmidetect_t handle,
                                            char *buf,
                                            int buflen);

/*
 * ipmidetect_is_node_detected
 *
 * Check if a node is detected
 *
 * Returns 1 if detected, 0 if undetected, -1 on error
 */
int ipmidetect_is_node_detected (ipmidetect_t handle, const char *node);

/*
 * ipmidetect_is_node_undetected
 *
 * Check if a node is undetected
 *
 * Returns 1 if undetected, 0 if detected, -1 on error
 */
int ipmidetect_is_node_undetected (ipmidetect_t handle, const char *node);

#endif /* IPMIDETECT_H */
