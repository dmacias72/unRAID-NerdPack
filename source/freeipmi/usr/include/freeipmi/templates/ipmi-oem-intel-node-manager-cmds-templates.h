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

#ifndef IPMI_OEM_INTEL_NODE_MANAGER_CMDS_TEMPLATES_H
#define IPMI_OEM_INTEL_NODE_MANAGER_CMDS_TEMPLATES_H

#ifdef __cplusplus
extern "C" {
#endif

/* This header file is for documentation only */

#if 0

Please see fiid.h for details concerning the fiid interface.

The following list the configurable fields of individual packet/record
templates in FreeIPMI.  Each field is listed as a list of the
following.

{ bits, "field name", field flag, field flag, ... }

bits - indicates the number of bits in the field

field name - indicates the name of the field, used for getting/setting
             fields in the fiid API.

field flags - flags indicating qualities of the field.  The following
              qualities may exist for each field.

    REQUIRED - field is required for the packet/record
    OPTIONAL - field is optional for the packet/record

    LENGTH-FIXED - field length is fixed at the number of bits listed

    LENGTH-VARIABLE - field length is variable for the number of bits
                      listed

    MAKES-PACKET-SUFFICIENT - indicates field or fields are
                              "sufficient" to make a packet/record valid
                              and not malformed, but not necessarily a
                              complete packet/record.

/*
 * Intel Node Manager
 *
 * For Intel Chips, not just Intel Motherboards.  Confirmed for:
 *
 * Intel S5500WB/Penguin Computing Relion 700
 * Intel S2600JF/Appro 512X
 * Intel S2600KP
 * Intel S2600WT2
 * Intel S2600WTT
 * Inventec 5441/Dell Xanadu II
 * Inventec 5442/Dell Xanadu III
 * Quanta S99Q/Dell FS12-TY
 * Quanta QSSC-S4R/Appro GB812X-CN
 */

Enable Disable Node Manager Policy Control Request
--------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "policy_enable_disable", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Enable Disable Node Manager Policy Control Response
---------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_enable_disable_node_manager_policy_control_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }   

Set Node Manager Policy Request
-------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_enabled", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }
    { 4,  "policy_trigger_type", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_configuration_action", REQUIRED, LENGTH-FIXED }
    { 2,  "aggressive_cpu_power_correction", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_storage_option", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.send_alert", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.shutdown_system", REQUIRED, LENGTH-FIXED }
    { 5,  "policy_exception_actions.reserved", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_power_domain", REQUIRED, LENGTH-FIXED }
    { 16, "policy_target_limit", REQUIRED, LENGTH-FIXED }
    { 32, "correction_time_limit", REQUIRED, LENGTH-FIXED }
    { 16, "policy_trigger_limit", REQUIRED, LENGTH-FIXED }
    { 16, "statistics_reporting_period", REQUIRED, LENGTH-FIXED }

Set Node Manager Policy Request - Boot Time Policy
--------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_boot_time_policy_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_enabled", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }
    { 4,  "policy_trigger_type", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_configuration_action", REQUIRED, LENGTH-FIXED }
    { 2,  "aggressive_cpu_power_correction", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_storage_option", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.send_alert", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.shutdown_system", REQUIRED, LENGTH-FIXED }
    { 5,  "policy_exception_actions.reserved", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_power_domain", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_target_limit.platform_booting_mode", REQUIRED, LENGTH-FIXED }
    { 7,  "policy_target_limit.cores_disabled", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_target_limit.reserved", REQUIRED, LENGTH-FIXED } 
    { 16, "policy_target_limit", REQUIRED, LENGTH-FIXED }
    { 32, "correction_time_limit", REQUIRED, LENGTH-FIXED }
    { 16, "policy_trigger_limit", REQUIRED, LENGTH-FIXED }
    { 16, "statistics_reporting_period", REQUIRED, LENGTH-FIXED }

Set Node Manager Policy Response
--------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Policy Request
-------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Policy Response
--------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_enabled", REQUIRED, LENGTH-FIXED }
    { 1,  "per_domain_node_manager_policy_control_enabled", REQUIRED, LENGTH-FIXED }
    { 1,  "global_node_manager_policy_control_enabled", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_created_and_managed_by_other_management", REQUIRED, LENGTH-FIXED }
    { 4,  "policy_trigger_type", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_type", REQUIRED, LENGTH-FIXED }
    { 2,  "aggressive_cpu_power_correction", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_storage_option", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.send_alert", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_exception_actions.shutdown_system", REQUIRED, LENGTH-FIXED }
    { 5,  "policy_exception_actions.reserved", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_power_domain",  REQUIRED, LENGTH-FIXED }
    { 16, "policy_target_limit", REQUIRED, LENGTH-FIXED }
    { 32, "correction_time_limit", REQUIRED, LENGTH-FIXED }
    { 16, "policy_trigger_limit", REQUIRED, LENGTH-FIXED }
    { 16, "statistics_reporting_period", REQUIRED, LENGTH-FIXED }

Set Node Manager Alert Thresholds Request
-----------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }
    { 8,  "number_of_alert_thresholds", REQUIRED, LENGTH-FIXED }
    { 16, "alert_threshold1", OPTIONAL, LENGTH-FIXED }
    { 16, "alert_threshold2", OPTIONAL, LENGTH-FIXED }
    { 16, "alert_threshold3", OPTIONAL, LENGTH-FIXED }

Set Node Manager Alert Thresholds Response
------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_alert_thresholds_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Alert Thresholds Request
-----------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Alert Thresholds Response
------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_alert_thresholds_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "number_of_alert_thresholds", REQUIRED, LENGTH-FIXED }
    { 16, "alert_threshold1", OPTIONAL, LENGTH-FIXED }
    { 16, "alert_threshold2", OPTIONAL, LENGTH-FIXED }
    { 16, "alert_threshold3", OPTIONAL, LENGTH-FIXED }

Set Node Manager Policy Suspend Periods Request
-----------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }
    { 8,  "number_of_policy_suspend_periods", REQUIRED, LENGTH-FIXED }
    { 8,  "policy1.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy1.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy2.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy2.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy3.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy3.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy4.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy4.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy5.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy5.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }

Set Node Manager Policy Suspend Periods Response
------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_policy_suspend_periods_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Policy Suspend Periods Request
-----------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Policy Suspend Periods Response
------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_policy_suspend_periods_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "number_of_policy_suspend_periods", REQUIRED, LENGTH-FIXED }
    { 8,  "policy1.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy1.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy1.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy2.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy2.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy2.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy3.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy3.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy3.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy4.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy4.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy4.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy5.suspend_start_time", OPTIONAL, LENGTH-FIXED }
    { 8,  "policy5.suspend_stop_time", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.monday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.tuesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.wednesday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.thursday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.friday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.saturday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.sunday", OPTIONAL, LENGTH-FIXED }
    { 1,  "policy5.suspend_period_recurrence.reserved", OPTIONAL, LENGTH-FIXED }

Reset Node Manager Statistics Request
-------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_reset_node_manager_statistics_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "mode", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Reset Node Manager Statistics Response
--------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_reset_node_manager_statistics_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Statistics Request
-----------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_statistics_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "mode", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Statistics Response
------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_statistics_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 16, "current", REQUIRED, LENGTH-FIXED }
    { 16, "minimum", REQUIRED, LENGTH-FIXED }
    { 16, "maximum", REQUIRED, LENGTH-FIXED }
    { 16, "average", REQUIRED, LENGTH-FIXED }
    { 32, "timestamp", REQUIRED, LENGTH-FIXED }
    { 32, "statistics_reporting_period", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_global_administrative_state", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_operational_state", REQUIRED, LENGTH-FIXED }
    { 1,  "measurements_state", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_activation_state", REQUIRED, LENGTH-FIXED }

Get Node Manager Capabilities Request
-------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_capabilities_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 4,  "policy_trigger_type", REQUIRED, LENGTH-FIXED }
    { 3,  "policy_type", REQUIRED, LENGTH-FIXED }
    { 1,  "policy_power_domain", REQUIRED, LENGTH-FIXED }

Get Node Manager Capabilities Response
--------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_capabilities_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "max_concurrent_settings", REQUIRED, LENGTH-FIXED }
    { 16, "max_power_thermal_time_after_reset", REQUIRED, LENGTH-FIXED }
    { 16, "min_power_thermal_time_after_reset", REQUIRED, LENGTH-FIXED }
    { 32, "min_correction_time", REQUIRED, LENGTH-FIXED }
    { 32, "max_correction_time", REQUIRED, LENGTH-FIXED }
    { 16, "min_statistics_reporting_period", REQUIRED, LENGTH-FIXED }
    { 16, "max_statistics_reporting_period", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_limiting_scope.domain_id", REQUIRED, LENGTH-FIXED }
    { 3,  "domain_limiting_scope.reserved", REQUIRED, LENGTH-FIXED }
    { 1,  "domain_limiting_scope.limiting_based_on", REQUIRED, LENGTH-FIXED }

Get Node Manager Version Request
--------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_version_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Version Response
---------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_version_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "node_manager_version", REQUIRED, LENGTH-FIXED }
    { 8,  "ipmi_interface_version", REQUIRED, LENGTH-FIXED }
    { 8,  "patch_version", REQUIRED, LENGTH-FIXED }
    { 8,  "major_firmware_revision", REQUIRED, LENGTH-FIXED }
    { 8,  "minor_firmware_revision", REQUIRED, LENGTH-FIXED }

Set Node Manager Power Draw Range Request
-----------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_power_draw_range_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }
    { 16, "minimum_power_draw", REQUIRED, LENGTH-FIXED }
    { 16, "maximum_power_draw", REQUIRED, LENGTH-FIXED }

Set Node Manager Power Draw Range Response
------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_power_draw_range_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Set Node Manager Alert Destination Request
------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "channel_number", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 1,  "alert_receiver_deactivation", REQUIRED, LENGTH-FIXED }
    { 8,  "destination_information", REQUIRED, LENGTH-FIXED }
    { 7,  "alert_string_selector", REQUIRED, LENGTH-FIXED }
    { 1,  "send_alert_string", REQUIRED, LENGTH-FIXED }

Set Node Manager Alert Destination (IPMB) Request
-------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_ipmb_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "channel_number", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 1,  "alert_receiver_deactivation", REQUIRED, LENGTH-FIXED }
    { 1,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 7,  "slave_address", REQUIRED, LENGTH-FIXED }
    { 7,  "alert_string_selector", REQUIRED, LENGTH-FIXED }
    { 1,  "send_alert_string", REQUIRED, LENGTH-FIXED }

Set Node Manager Alert Destination (LAN) Request
------------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_lan_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "channel_number", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 1,  "alert_receiver_deactivation", REQUIRED, LENGTH-FIXED }
    { 4,  "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 7,  "alert_string_selector", REQUIRED, LENGTH-FIXED }
    { 1,  "send_alert_string", REQUIRED, LENGTH-FIXED }

Set Node Manager Alert Destination Response
-------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_node_manager_alert_destination_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Alert Destination Request
------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_alert_destination_rq

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }

Get Node Manager Alert Destination Response
-------------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_node_manager_alert_destination_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "channel_number", REQUIRED, LENGTH-FIXED }
    { 3,  "reserved1", REQUIRED, LENGTH-FIXED }
    { 1,  "alert_receiver_deactivation", REQUIRED, LENGTH-FIXED }
    { 4,  "destination_selector", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved2", REQUIRED, LENGTH-FIXED }
    { 7,  "alert_string_selector", REQUIRED, LENGTH-FIXED }
    { 1,  "send_alert_string", REQUIRED, LENGTH-FIXED }

Get Turbo Synchronization Ratio Request
---------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio_rq

    { 8,  "cmd",REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id",REQUIRED, LENGTH-FIXED }
    { 8,  "cpu_socket_number",REQUIRED, LENGTH-FIXED }
    { 8,  "active_cores_configuration",REQUIRED, LENGTH-FIXED }
    { 8,  "turbo_ratio_limit",REQUIRED, LENGTH-FIXED }

Get Turbo Synchronization Ratio Response
----------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_set_turbo_synchronization_ratio_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id",REQUIRED, LENGTH-FIXED }

Get Turbo Synchronization Ratio Request
---------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio_rq

    { 8,  "cmd",REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id",REQUIRED, LENGTH-FIXED }
    { 8,  "cpu_socket_number",REQUIRED, LENGTH-FIXED }
    { 8,  "active_cores_configuration",REQUIRED, LENGTH-FIXED }

Get Turbo Synchronization Ratio Response
----------------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_turbo_synchronization_ratio_rs

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id",REQUIRED, LENGTH-FIXED }
    { 8,  "current_turbo_ratio_limit",REQUIRED, LENGTH-FIXED }
    { 8,  "default_turbo_ratio_limit",REQUIRED, LENGTH-FIXED }
    { 8,  "maximum_turbo_ratio_limit",REQUIRED, LENGTH-FIXED }
    { 8,  "minimum_turbo_ratio_limit",REQUIRED, LENGTH-FIXED }

Get Limiting Policy ID Request
------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_limiting_policy_id_rq =

    { 8,  "cmd", REQUIRED, LENGTH-FIXED }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 4,  "domain_id", REQUIRED, LENGTH-FIXED }
    { 4,  "reserved", REQUIRED, LENGTH-FIXED }

Get Limiting Policy ID Response
-------------------------------

FIID Template: tmpl_cmd_oem_intel_node_manager_get_limiting_policy_id_rs =

    { 8,  "cmd", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 8,  "comp_code", REQUIRED, LENGTH-FIXED, MAKES-PACKET-SUFFICIENT }
    { 24, "manufacturer_id", REQUIRED, LENGTH-FIXED }
    { 8,  "policy_id", REQUIRED, LENGTH-FIXED }


#endif  /* 0 */

#ifdef __cplusplus
}
#endif

#endif /* IPMI_OEM_CMDS_TEMPLATES_H */
