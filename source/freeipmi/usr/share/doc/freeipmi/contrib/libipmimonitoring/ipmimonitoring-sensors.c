/*****************************************************************************\
 *  $Id: ipmimonitoring-sensors.c,v 1.6 2010-07-22 21:49:00 chu11 Exp $
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
 * read and monitor sensors.
 *
 * At the top of this file, you'll find a number of variables for
 * configuration of IPMI communication and what sensors you are
 * interested in monitoring.  Those variables are used in the
 * libipmimonitoring calls below.
 *
 * Hopefully this example will be sufficient to help anyone program
 * IPMI monitoring software for their environment.
 *
 * To compile, linking against the library should be sufficient for
 * most environments.  e.g.
 *
 * gcc -o ipmimonitoring-sensors ipmimonitoring-sensors.c -lipmimonitoring
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include <ipmi_monitoring.h>
#include <ipmi_monitoring_bitmasks.h>

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

/* Set to an appropriate alternate if desired */
char *sdr_cache_directory = "/tmp";
char *sensor_config_file = NULL;

/* Set to 1 or 0 to enable these sensor reading flags
 * - See ipmi_monitoring.h for descriptions of these flags.
 */
int reread_sdr_cache = 0;
int ignore_non_interpretable_sensors = 1;
int bridge_sensors = 0;
int interpret_oem_data = 0;
int shared_sensors = 0;
int discrete_reading = 0;
int ignore_scanning_disabled = 0; 
int assume_bmc_owner = 0;
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
  unsigned int sensor_reading_flags = 0;
  unsigned int i;
  int sensor_count;
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
  if (sensor_config_file)
    {
      if (ipmi_monitoring_ctx_sensor_config_file (ctx,
                                                  sensor_config_file) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_ctx_sensor_config_file: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else
    {
      if (ipmi_monitoring_ctx_sensor_config_file (ctx, NULL) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_ctx_sensor_config_file: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    } 

  if (reread_sdr_cache)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_REREAD_SDR_CACHE;

  if (ignore_non_interpretable_sensors)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_IGNORE_NON_INTERPRETABLE_SENSORS;
  
  if (bridge_sensors)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_BRIDGE_SENSORS;

  if (interpret_oem_data)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_INTERPRET_OEM_DATA;

  if (shared_sensors)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_SHARED_SENSORS;

  if (discrete_reading)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_DISCRETE_READING;

  if (ignore_scanning_disabled)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_IGNORE_SCANNING_DISABLED;

  if (assume_bmc_owner)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_ASSUME_BMC_OWNER;

  if (entity_sensor_names)
    sensor_reading_flags |= IPMI_MONITORING_SENSOR_READING_FLAGS_ENTITY_SENSOR_NAMES;

  if (!record_ids_length && !sensor_types_length)
    {
      if ((sensor_count = ipmi_monitoring_sensor_readings_by_record_id (ctx,
                                                                        hostname,
                                                                        ipmi_config,
                                                                        sensor_reading_flags,
                                                                        NULL,
                                                                        0,
                                                                        NULL,
                                                                        NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_readings_by_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else if (record_ids_length)
    {
      if ((sensor_count = ipmi_monitoring_sensor_readings_by_record_id (ctx,
                                                                        hostname,
                                                                        ipmi_config,
                                                                        sensor_reading_flags,
                                                                        record_ids,
                                                                        record_ids_length,
                                                                        NULL,
                                                                        NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_readings_by_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }
  else
    {
      if ((sensor_count = ipmi_monitoring_sensor_readings_by_sensor_type (ctx,
                                                                          hostname,
                                                                          ipmi_config,
                                                                          sensor_reading_flags,
                                                                          sensor_types,
                                                                          sensor_types_length,
                                                                          NULL,
                                                                          NULL)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_readings_by_sensor_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }
    }

  printf ("%s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
          "Record ID",
          "Sensor Name",
          "Sensor Number",
          "Sensor Type",
          "Sensor State",
          "Sensor Reading",
          "Sensor Units",
          "Sensor Event/Reading Type Code",
          "Sensor Event Bitmask",
          "Sensor Event String");

  for (i = 0; i < sensor_count; i++, ipmi_monitoring_sensor_iterator_next (ctx))
    {
      int record_id, sensor_number, sensor_type, sensor_state, sensor_units,
        sensor_bitmask_type, sensor_bitmask, sensor_reading_type,
        event_reading_type_code;
      char **sensor_bitmask_strings = NULL;
      const char *sensor_type_str;
      const char *sensor_state_str;
      char *sensor_name = NULL;
      void *sensor_reading;

      if ((record_id = ipmi_monitoring_sensor_read_record_id (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_record_id: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_number = ipmi_monitoring_sensor_read_sensor_number (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_number: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_type = ipmi_monitoring_sensor_read_sensor_type (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if (!(sensor_name = ipmi_monitoring_sensor_read_sensor_name (ctx)))
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_name: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_state = ipmi_monitoring_sensor_read_sensor_state (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_state: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_units = ipmi_monitoring_sensor_read_sensor_units (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_units: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_bitmask_type = ipmi_monitoring_sensor_read_sensor_bitmask_type (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_bitmask_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_bitmask = ipmi_monitoring_sensor_read_sensor_bitmask (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_bitmask: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if (!(sensor_bitmask_strings = ipmi_monitoring_sensor_read_sensor_bitmask_strings (ctx)))
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_bitmask_strings: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if ((sensor_reading_type = ipmi_monitoring_sensor_read_sensor_reading_type (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_sensor_reading_type: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      sensor_reading = ipmi_monitoring_sensor_read_sensor_reading (ctx);

      if ((event_reading_type_code = ipmi_monitoring_sensor_read_event_reading_type_code (ctx)) < 0)
        {
          fprintf (stderr,
                   "ipmi_monitoring_sensor_read_event_reading_type_code: %s\n",
                   ipmi_monitoring_ctx_errormsg (ctx));
          goto cleanup;
        }

      if (!strlen (sensor_name))
        sensor_name = "N/A";

      sensor_type_str = _get_sensor_type_string (sensor_type);

      printf ("%u, %s, %u, %s",
              record_id,
              sensor_name,
              sensor_number,
              sensor_type_str);

      if (sensor_state == IPMI_MONITORING_STATE_NOMINAL)
        sensor_state_str = "Nominal";
      else if (sensor_state == IPMI_MONITORING_STATE_WARNING)
        sensor_state_str = "Warning";
      else if (sensor_state == IPMI_MONITORING_STATE_CRITICAL)
        sensor_state_str = "Critical";
      else
        sensor_state_str = "N/A";

      printf (", %s", sensor_state_str);

      if (sensor_reading)
        {
          const char *sensor_units_str;

          if (sensor_reading_type == IPMI_MONITORING_SENSOR_READING_TYPE_UNSIGNED_INTEGER8_BOOL)
            printf (", %s",
                    (*((uint8_t *)sensor_reading) ? "true" : "false"));
          else if (sensor_reading_type == IPMI_MONITORING_SENSOR_READING_TYPE_UNSIGNED_INTEGER32)
            printf (", %u",
                    *((uint32_t *)sensor_reading));
          else if (sensor_reading_type == IPMI_MONITORING_SENSOR_READING_TYPE_DOUBLE)
            printf (", %.2f",
                    *((double *)sensor_reading));
          else
            printf (", N/A");

          if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_CELSIUS)
            sensor_units_str = "C";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_FAHRENHEIT)
            sensor_units_str = "F";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_VOLTS)
            sensor_units_str = "V";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_AMPS)
            sensor_units_str = "A";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_RPM)
            sensor_units_str = "RPM";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_WATTS)
            sensor_units_str = "W";
          else if (sensor_units == IPMI_MONITORING_SENSOR_UNITS_PERCENT)
            sensor_units_str = "%";
          else
            sensor_units_str = "N/A";

          printf (", %s", sensor_units_str);
        }
      else
        printf (", N/A, N/A");
  
      printf (", %Xh", event_reading_type_code);
 
      /* It is possible you may want to monitor specific event
       * conditions that may occur.  If that is the case, you may want
       * to check out what specific bitmask type and bitmask events
       * occurred.  See ipmi_monitoring_bitmasks.h for a list of
       * bitmasks and types.
       */

      if (sensor_bitmask_type != IPMI_MONITORING_SENSOR_BITMASK_TYPE_UNKNOWN)
        printf (", %Xh", sensor_bitmask);
      else
        printf (", N/A");
  
      if (sensor_bitmask_type != IPMI_MONITORING_SENSOR_BITMASK_TYPE_UNKNOWN)
        {     
          unsigned int i = 0;
          
          printf (",");
          
          while (sensor_bitmask_strings[i])
            {
              printf (" ");
              
              printf ("'%s'",
                      sensor_bitmask_strings[i]);
              
              i++;
            }
        }
      else
        printf (", N/A");

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

