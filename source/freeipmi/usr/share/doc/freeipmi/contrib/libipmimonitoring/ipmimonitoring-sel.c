/*****************************************************************************\
 *  $Id: ipmimonitoring-sel.c,v 1.3 2010-07-22 21:49:00 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2015 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2006-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-222073
 *
 *  This file is part of Ipmimonitoring, an IPMI sensor monitoring
 *  library.  For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmimonitoring is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmimonitoring is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmimonitoring.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

/* This is an example of how to use the libipmimonitoring library to
 * read and monitor the SEL.
 *
 * At the top of this file, you'll find a number of variables for
 * configuration of IPMI communication and what SEL records you are
 * interested in monitoring.  Those variables are used in the
 * libipmimonitoring calls below.
 *
 * Hopefully this example will be sufficient to help anyone program
 * IPMI monitoring software for their environment.
 *
 * To compile, linking against the library should be sufficient for
 * most environments.  e.g.
 *
 * gcc -o ipmimonitoring-sel ipmimonitoring-sel.c -lipmimonitoring
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include <ipmi_monitoring.h>
#include <ipmi_monitoring_offsets.h>

/* Communication Configuration - Initialize accordingly */

/* Hostname, NULL for In-band communication, non-null for a hostname */
char *hostname = NULL; 

/* In-band Communication Configuration */
int driver_type = IPMI_MONITORING_DRIVER_TYPE_KCS; /* or -1 for default */
int disable_auto_probe = 0;     /* probe for in-band device */
unsigned int driver_address = 0; /* not used if probing */
unsigned int register_spacing = 0; /* not used if probing */
char *driver_device = NULL;     /* not used if probing */

/* Out-of-band Communication Configuration */
int protocol_version = IPMI_MONITORING_PROTOCOL_VERSION_1_5; /* or -1 for default */
char *username = "foousername";
char *password = "foopassword";
unsigned char *k_g = NULL;
unsigned int k_g_len = 0;
int privilege_level = IPMI_MONITORING_PRIVILEGE_LEVEL_USER; /* or -1 for default */
int authentication_type = IPMI_MONITORING_AUTHENTICATION_TYPE_MD5; /* or -1 for default */
int cipher_suite_id = 0;        /* or -1 for default */
int session_timeout = 0;        /* 0 for default */
int retransmission_timeout = 0; /* 0 for default */

/* Workarounds - specify workaround flags if necessary */
unsigned int workaround_flags = 0;

/* Initialize w/ record id numbers to only monitor specific record ids */
unsigned int record_ids[] = {0};
unsigned int record_ids_length = 0;

/* Initialize w/ sensor types to only monitor specific sensor types
 * see ipmi_monitoring.h sensor types list.
 */
unsigned int sensor_types[] = {0};
unsigned int sensor_types_length = 0;

/* Initialize w/ date range to only monitoring specific date range */
char *date_begin = NULL;        /* use MM/DD/YYYY format */
char *date_end = NULL;          /* use MM/DD/YYYY format */

/* Set to an appropriate alternate if desired */
char *sdr_cache_directory = "/tmp";
char *sel_config_file = NULL;

/* Set to 1 or 0 to enable these SEL flags
 * - See ipmi_monitoring.h for descriptions of these flags.
 */
int reread_sdr_cache = 0;
int interpret_oem_data = 0;
int assume_system_event_record = 0;
int entity_sensor_names = 0;

/* Initialization flags
 * 
 * Most commonly bitwise OR IPMI_MONITORING_FLAGS_DEBUG and/or
 * IPMI_MONITORING_FLAGS_DEBUG_IPMI_PACKETS for extra debugging
 * information.
 */
unsigned int ipmimonitoring_init_flags = 0;

static const char *
_get_sensor_type_string (int sensor_type)
{
  switch (sensor_type)
    {
    case IPMI_MONITORING_SENSOR_TYPE_RESERVED:
      return ("Reserved");
    case IPMI_MONITORING_SENSOR_TYPE_TEMPERATURE:
      return ("Temperature");
    case IPMI_MONITORING_SENSOR_TYPE_VOLTAGE:
      return ("Voltage");
    case IPMI_MONITORING_SENSOR_TYPE_CURRENT:
      return ("Current");
    case IPMI_MONITORING_SENSOR_TYPE_FAN:
      return ("Fan");
    case IPMI_MONITORING_SENSOR_TYPE_PHYSICAL_SECURITY:
      return ("Physical Security");
    case IPMI_MONITORING_SENSOR_TYPE_PLATFORM_SECURITY_VIOLATION_ATTEMPT:
      return ("Platform Security Violation Attempt");
    case IPMI_MONITORING_SENSOR_TYPE_PROCESSOR:
      return ("Processor");
    case IPMI_MONITORING_SENSOR_TYPE_POWER_SUPPLY:
      return ("Power Supply");
    case IPMI_MONITORING_SENSOR_TYPE_POWER_UNIT:
      return ("Power Unit");
    case IPMI_MONITORING_SENSOR_TYPE_COOLING_DEVICE:
      return ("Cooling Device");
    case IPMI_MONITORING_SENSOR_TYPE_OTHER_UNITS_BASED_SENSOR:
      return ("Other Units Based Sensor");
    case IPMI_MONITORING_SENSOR_TYPE_MEMORY:
      return ("Memory");
    case IPMI_MONITORING_SENSOR_TYPE_DRIVE_SLOT:
      return ("Drive Slot");
    case IPMI_MONITORING_SENSOR_TYPE_POST_MEMORY_RESIZE:
      return ("POST Memory Resize");
    case IPMI_MONITORING_SENSOR_TYPE_SYSTEM_FIRMWARE_PROGRESS:
      return ("System Firmware Progress");
    case IPMI_MONITORING_SENSOR_TYPE_EVENT_LOGGING_DISABLED:
      return ("Event Logging Disabled");
    case IPMI_MONITORING_SENSOR_TYPE_WATCHDOG1:
      return ("Watchdog 1");
    case IPMI_MONITORING_SENSOR_TYPE_SYSTEM_EVENT:
      return ("System Event");
    case IPMI_MONITORING_SENSOR_TYPE_CRITICAL_INTERRUPT:
      return ("Critical Interrupt");
    case IPMI_MONITORING_SENSOR_TYPE_BUTTON_SWITCH:
      return ("Button/Switch");
    case IPMI_MONITORING_SENSOR_TYPE_MODULE_BOARD:
      return ("Module/Board");
    case IPMI_MONITORING_SENSOR_TYPE_MICROCONTROLLER_COPROCESSOR:
      return ("Microcontroller/Coprocessor");
    case IPMI_MONITORING_SENSOR_TYPE_ADD_IN_CARD:
      return ("Add In Card");
    case IPMI_MONITORING_SENSOR_TYPE_CHASSIS:
      return ("Chassis");
    case IPMI_MONITORING_SENSOR_TYPE_CHIP_SET:
      return ("Chip Set");
    case IPMI_MONITORING_SENSOR_TYPE_OTHER_FRU:
      return ("Other Fru");
    case IPMI_MONITORING_SENSOR_TYPE_CABLE_INTERCONNECT:
      return ("Cable/Interconnect");
    case IPMI_MONITORING_SENSOR_TYPE_TERMINATOR:
      return ("Terminator");
    case IPMI_MONITORING_SENSOR_TYPE_SYSTEM_BOOT_INITIATED:
      return ("System Boot Initiated");
    case IPMI_MONITORING_SENSOR_TYPE_BOOT_ERROR:
      return ("Boot Error");
    case IPMI_MONITORING_SENSOR_TYPE_OS_BOOT:
      return ("OS Boot");
    case IPMI_MONITORING_SENSOR_TYPE_OS_CRITICAL_STOP:
      return ("OS Critical Stop");
    case IPMI_MONITORING_SENSOR_TYPE_SLOT_CONNECTOR:
      return ("Slot/Connector");
    case IPMI_MONITORING_SENSOR_TYPE_SYSTEM_ACPI_POWER_STATE:
      return ("System ACPI Power State");
    case IPMI_MONITORING_SENSOR_TYPE_WATCHDOG2:
      return ("Watchdog 2");
    case IPMI_MONITORING_SENSOR_TYPE_PLATFORM_ALERT:
      return ("Platform Alert");
    case IPMI_MONITORING_SENSOR_TYPE_ENTITY_PRESENCE:
      return ("Entity Presence");
    case IPMI_MONITORING_SENSOR_TYPE_MONITOR_ASIC_IC:
      return ("Monitor ASIC/IC");
    case IPMI_MONITORING_SENSOR_TYPE_LAN:
      return ("LAN");
    case IPMI_MONITORING_SENSOR_TYPE_MANAGEMENT_SUBSYSTEM_HEALTH:
      return ("Management Subsystem Health");
    case IPMI_MONITORING_SENSOR_TYPE_BATTERY:
      return ("Battery");
    case IPMI_MONITORING_SENSOR_TYPE_SESSION_AUDIT:
      return ("Session Audit");
    case IPMI_MONITORING_SENSOR_TYPE_VERSION_CHANGE:
      return ("Version Change");
    case IPMI_MONITORING_SENSOR_TYPE_FRU_STATE:
      return ("FRU State");
    }

  return ("Unrecognized");
}
 
static int
_ipmimonitoring (struct ipmi_monitoring_ipmi_config *ipmi_config)
{
  ipmi_monitoring_ctx_t ctx = NULL;
  unsigned int sel_flags = 0;
  unsigned int i;
  int sel_count;
  int errnum;
  int rv = -1;

  if (ipmi_monitoring_init (ipmimonitoring_init_flags, &errnum) < 0)
    {
      fprintf (stderr,
               "ipmi_monitoring_init: %s\n",
               ipmi_monitoring_ctx_strerror (errnum));
      goto cleanup;
    }

  if (!(ctx = ipmi_monitoring_ctx_create ()))
    {
      perror ("ipmi_monitoring_ctx_create:");
      goto cleanup;
    }

  if (sdr_cache_directory)
    {
      if (ipmi_monitoring_ctx_sdr_cache_directory (ctx,
                                                   sdr_cache_directory) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_ctx_sdr_cache_directory: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }

  /* Must call otherwise only default interpretations ever used */
  if (sel_config_file)
    {
      if (ipmi_monitoring_ctx_sel_config_file (ctx,
                                               sel_config_file) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_ctx_sel_config_file: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else
    {
      if (ipmi_monitoring_ctx_sel_config_file (ctx, NULL) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_ctx_sel_config_file: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  
  if (reread_sdr_cache)
    sel_flags |= IPMI_MONITORING_SEL_FLAGS_REREAD_SDR_CACHE;

  if (interpret_oem_data)
    sel_flags |= IPMI_MONITORING_SEL_FLAGS_INTERPRET_OEM_DATA;

  if (assume_system_event_record)
    sel_flags |= IPMI_MONITORING_SEL_FLAGS_ASSUME_SYSTEM_EVENT_RECORD;

  if (entity_sensor_names)
    sel_flags |= IPMI_MONITORING_SEL_FLAGS_ENTITY_SENSOR_NAMES;

  if (record_ids_length)
    {
      if ((sel_count = ipmi_monitoring_sel_by_record_id (ctx,
                                                         hostname,
                                                         ipmi_config,
                                                         sel_flags,
                                                         record_ids,
                                                         record_ids_length,
                                                         NULL,
                                                         NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_by_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else if (sensor_types_length)
    {
      if ((sel_count = ipmi_monitoring_sel_by_sensor_type (ctx,
                                                           hostname,
                                                           ipmi_config,
                                                           sel_flags,
                                                           sensor_types,
                                                           sensor_types_length,
                                                           NULL,
                                                           NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_by_sensor_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else if (date_begin
           || date_end)
    {
      if ((sel_count = ipmi_monitoring_sel_by_date_range (ctx,
                                                          hostname,
                                                          ipmi_config,
                                                          sel_flags,
                                                          date_begin,
                                                          date_end,
                                                          NULL,
                                                          NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_by_sensor_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else
    {
      if ((sel_count = ipmi_monitoring_sel_by_record_id (ctx,
                                                         hostname,
                                                         ipmi_config,
                                                         sel_flags,
                                                         NULL,
                                                         0,
                                                         NULL,
                                                         NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_by_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }

  printf ("%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
          "Record ID",
          "Record Type",
          "SEL State",
          "Timestamp",
          "Sensor Name",
          "Sensor Type",
          "Event Direction",
          "Event Type Code",
          "Event Data",
          "Event Offset",
          "Event Offset String");

  for (i = 0; i < sel_count; i++, ipmi_monitoring_sel_iterator_next (ctx))
    {
      int record_id, record_type, sel_state, sensor_type, sensor_number, event_direction,
        event_offset_type, event_offset, event_type_code, manufacturer_id;
      unsigned int timestamp, event_data1, event_data2, event_data3;
      int record_type_class;
      char *event_offset_string = NULL;
      const char *sensor_type_str;
      const char *event_direction_str;
      const char *sel_state_str;
      char *sensor_name = NULL;
      unsigned char oem_data[64];
      int oem_data_len;
      unsigned int j;

      if ((record_id = ipmi_monitoring_sel_read_record_id (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_read_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((record_type = ipmi_monitoring_sel_read_record_type (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_read_record_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((record_type_class = ipmi_monitoring_sel_read_record_type_class (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_read_record_type_class: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sel_state = ipmi_monitoring_sel_read_sel_state (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sel_read_sel_state: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if (sel_state == IPMI_MONITORING_STATE_NOMINAL)
        sel_state_str = "Nominal";
      else if (sel_state == IPMI_MONITORING_STATE_WARNING)
        sel_state_str = "Warning";
      else if (sel_state == IPMI_MONITORING_STATE_CRITICAL)
        sel_state_str = "Critical";
      else
        sel_state_str = "N/A";

      printf ("%u, %u, %s",
              record_id,
              record_type,
              sel_state_str);
      
      if (record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_SYSTEM_EVENT_RECORD
          || record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD)
        {
          
          if (ipmi_monitoring_sel_read_timestamp (ctx, &timestamp) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_timestamp: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }
          
          /* XXX: This should be converted to a nice date output using
           * your favorite timestamp -> string conversion functions.
           */
          printf (", %u", timestamp);
        }
      else
        printf (", N/A");

      if (record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_SYSTEM_EVENT_RECORD)
        {         
          /* If you are integrating ipmimonitoring SEL into a monitoring application,
           * you may wish to count the number of times a specific error occurred
           * and report that to the monitoring application.
           *
           * In this particular case, you'll probably want to check out
           * what sensor type each SEL event is reporting, the
           * event offset type, and the specific event offset that occurred.
           *
           * See ipmi_monitoring_offsets.h for a list of event offsets
           * and types.
           */

          if (!(sensor_name = ipmi_monitoring_sel_read_sensor_name (ctx)))
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_sensor_name: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if ((sensor_type = ipmi_monitoring_sel_read_sensor_type (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_sensor_type: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if ((sensor_number = ipmi_monitoring_sel_read_sensor_number (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_sensor_number: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if ((event_direction = ipmi_monitoring_sel_read_event_direction (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_direction: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if ((event_type_code = ipmi_monitoring_sel_read_event_type_code (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_type_code: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if (ipmi_monitoring_sel_read_event_data (ctx,
                                                   &event_data1,
                                                   &event_data2,
                                                   &event_data3) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_data: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }         

          if ((event_offset_type = ipmi_monitoring_sel_read_event_offset_type (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_offset_type: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }
          
          if ((event_offset = ipmi_monitoring_sel_read_event_offset (ctx)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_offset: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }
          
          if (!(event_offset_string = ipmi_monitoring_sel_read_event_offset_string (ctx)))
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_event_offset_string: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          if (!strlen (sensor_name))
            sensor_name = "N/A";
          
          sensor_type_str = _get_sensor_type_string (sensor_type);

          if (event_direction == IPMI_MONITORING_SEL_EVENT_DIRECTION_ASSERTION)
            event_direction_str = "Assertion";
          else
            event_direction_str = "Deassertion";

          printf (", %s, %s, %u, %s, %Xh, %Xh-%Xh-%Xh",
                  sensor_name,
                  sensor_type_str,
                  sensor_number,
                  event_direction_str,
                  event_type_code,
                  event_data1,
                  event_data2,
                  event_data3);
                  
          if (event_offset_type != IPMI_MONITORING_EVENT_OFFSET_TYPE_UNKNOWN)
            printf (", %Xh", event_offset);
          else
            printf (", N/A");
          
          if (event_offset_type != IPMI_MONITORING_EVENT_OFFSET_TYPE_UNKNOWN)
            printf (", %s", event_offset_string);
          else
            printf (", N/A");
        }
      else if (record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD
               || record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_NON_TIMESTAMPED_OEM_RECORD)
        {
          if (record_type_class == IPMI_MONITORING_SEL_RECORD_TYPE_CLASS_TIMESTAMPED_OEM_RECORD)
            {
              if ((manufacturer_id = ipmi_monitoring_sel_read_manufacturer_id (ctx)) < 0)
                {
                  fprintf (stderr,
                           "ipmi_monitoring_sel_read_manufacturer_id: %s\n",
                           ipmi_monitoring_ctx_errormsg (ctx));
                  goto cleanup;
                }
              
              printf (", Manufacturer ID = %Xh", manufacturer_id);
            }

          if ((oem_data_len = ipmi_monitoring_sel_read_oem_data (ctx, oem_data, 1024)) < 0)
            {
              fprintf (stderr,
                       "ipmi_monitoring_sel_read_oem_data: %s\n",
                       ipmi_monitoring_ctx_errormsg (ctx));
              goto cleanup;
            }

          printf (", OEM Data = ");

          for (j = 0; j < oem_data_len; j++)
            printf ("%02Xh ", oem_data[j]);
        }
      else
        printf (", N/A, N/A, N/A, N/A, N/A, N/A, N/A");
      
      printf ("\n");
    }

  rv = 0;
 cleanup:
  if (ctx)
    ipmi_monitoring_ctx_destroy (ctx);
  return (rv);
}

static void
_init_ipmi_config (struct ipmi_monitoring_ipmi_config *ipmi_config)
{
  assert (ipmi_config);

  ipmi_config->driver_type = driver_type;
  ipmi_config->disable_auto_probe = disable_auto_probe;
  ipmi_config->driver_address = driver_address;
  ipmi_config->register_spacing = register_spacing;
  ipmi_config->driver_device = driver_device;

  ipmi_config->protocol_version = protocol_version;
  ipmi_config->username = username;
  ipmi_config->password = password;
  ipmi_config->k_g = k_g;
  ipmi_config->k_g_len = k_g_len;
  ipmi_config->privilege_level = privilege_level;
  ipmi_config->authentication_type = authentication_type;
  ipmi_config->cipher_suite_id = cipher_suite_id;
  ipmi_config->session_timeout_len = session_timeout;
  ipmi_config->retransmission_timeout_len = retransmission_timeout;

  ipmi_config->workaround_flags = workaround_flags;
}

int
main (int argc, char **argv)
{
  struct ipmi_monitoring_ipmi_config ipmi_config;

  _init_ipmi_config (&ipmi_config);

  if (_ipmimonitoring (&ipmi_config) < 0)
    exit (1);

  exit (0);
}

