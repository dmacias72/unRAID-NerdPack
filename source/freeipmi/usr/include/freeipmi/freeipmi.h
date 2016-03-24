/*
 * Copyright (C) 2003-2012 FreeIPMI Core Team
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

#ifndef FREEIPMI_H
#define FREEIPMI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/api/ipmi-api.h>
#include <freeipmi/api/ipmi-chassis-cmds-api.h>
#include <freeipmi/api/ipmi-dcmi-cmds-api.h>
#include <freeipmi/api/ipmi-device-global-cmds-api.h>
#include <freeipmi/api/ipmi-event-cmds-api.h>
#include <freeipmi/api/ipmi-firmware-firewall-command-discovery-cmds-api.h>
#include <freeipmi/api/ipmi-fru-inventory-device-cmds-api.h>
#include <freeipmi/api/ipmi-lan-cmds-api.h>
#include <freeipmi/api/ipmi-messaging-support-cmds-api.h>
#include <freeipmi/api/ipmi-oem-intel-node-manager-cmds-api.h>
#include <freeipmi/api/ipmi-pef-and-alerting-cmds-api.h>
#include <freeipmi/api/ipmi-rmcpplus-support-and-payload-cmds-api.h>
#include <freeipmi/api/ipmi-sdr-repository-cmds-api.h>
#include <freeipmi/api/ipmi-sensor-cmds-api.h>
#include <freeipmi/api/ipmi-sel-cmds-api.h>
#include <freeipmi/api/ipmi-serial-modem-cmds-api.h>
#include <freeipmi/api/ipmi-sol-cmds-api.h>
#include <freeipmi/cmds/ipmi-bmc-watchdog-timer-cmds.h>
#include <freeipmi/cmds/ipmi-chassis-cmds.h>
#include <freeipmi/cmds/ipmi-dcmi-cmds.h>
#include <freeipmi/cmds/ipmi-dcmi-oem-cmds.h>
#include <freeipmi/cmds/ipmi-device-global-cmds.h>
#include <freeipmi/cmds/ipmi-event-cmds.h>
#include <freeipmi/cmds/ipmi-firmware-firewall-command-discovery-cmds.h>
#include <freeipmi/cmds/ipmi-fru-inventory-device-cmds.h>
#include <freeipmi/cmds/ipmi-lan-cmds.h>
#include <freeipmi/cmds/ipmi-messaging-support-cmds.h>
#include <freeipmi/cmds/ipmi-oem-intel-node-manager-cmds.h>
#include <freeipmi/cmds/ipmi-pef-and-alerting-cmds.h>
#include <freeipmi/cmds/ipmi-rmcpplus-support-and-payload-cmds.h>
#include <freeipmi/cmds/ipmi-sdr-repository-cmds.h>
#include <freeipmi/cmds/ipmi-sel-cmds.h>
#include <freeipmi/cmds/ipmi-sensor-cmds.h>
#include <freeipmi/cmds/ipmi-serial-modem-cmds.h>
#include <freeipmi/cmds/ipmi-sol-cmds.h>
#include <freeipmi/cmds/rmcp-cmds.h>
#include <freeipmi/debug/ipmi-debug.h>
#include <freeipmi/driver/ipmi-kcs-driver.h>
#include <freeipmi/driver/ipmi-ssif-driver.h>
#include <freeipmi/driver/ipmi-openipmi-driver.h>
#include <freeipmi/driver/ipmi-sunbmc-driver.h>
#include <freeipmi/fiid/fiid.h>
#include <freeipmi/fru/ipmi-fru.h>
#include <freeipmi/interface/ipmi-interface.h>
#include <freeipmi/interface/ipmi-ipmb-interface.h>
#include <freeipmi/interface/ipmi-kcs-interface.h>
#include <freeipmi/interface/ipmi-lan-interface.h>
#include <freeipmi/interface/ipmi-rmcpplus-interface.h>
#include <freeipmi/interface/rmcp-interface.h>
#include <freeipmi/interpret/ipmi-interpret.h>
#include <freeipmi/locate/ipmi-locate.h>
#include <freeipmi/payload/ipmi-sol-payload.h>
#include <freeipmi/record-format/ipmi-cipher-suite-record-format.h>
#include <freeipmi/record-format/ipmi-fru-dimmspd-record-format.h>
#include <freeipmi/record-format/ipmi-fru-information-record-format.h>
#include <freeipmi/record-format/ipmi-platform-event-trap-record-format.h>
#include <freeipmi/record-format/ipmi-sdr-record-format.h>
#include <freeipmi/record-format/ipmi-sel-record-format.h>
#include <freeipmi/record-format/oem/ipmi-fru-wistron-oem-record-format.h>
#include <freeipmi/record-format/oem/ipmi-sdr-oem-intel-node-manager-record-format.h>
#include <freeipmi/record-format/oem/ipmi-sdr-oem-intel-record-format.h>
#include <freeipmi/record-format/oem/ipmi-sel-oem-intel-record-format.h>
#include <freeipmi/record-format/oem/ipmi-sel-oem-linux-kernel-record-format.h>
#include <freeipmi/sdr/ipmi-sdr.h>
#include <freeipmi/sdr/oem/ipmi-sdr-oem-intel-node-manager.h>
#include <freeipmi/sel/ipmi-sel.h>
#include <freeipmi/sensor-read/ipmi-sensor-read.h>
#include <freeipmi/spec/ipmi-authentication-type-spec.h>
#include <freeipmi/spec/ipmi-channel-spec.h>
#include <freeipmi/spec/ipmi-cmd-spec.h>
#include <freeipmi/spec/ipmi-cmd-dcmi-spec.h>
#include <freeipmi/spec/ipmi-comp-code-spec.h>
#include <freeipmi/spec/ipmi-comp-code-dcmi-spec.h>
#include <freeipmi/spec/ipmi-device-types-spec.h>
#include <freeipmi/spec/ipmi-entity-ids-spec.h>
#include <freeipmi/spec/ipmi-event-reading-type-code-spec.h>
#include <freeipmi/spec/ipmi-fru-chassis-types-spec.h>
#include <freeipmi/spec/ipmi-fru-language-codes-spec.h>
#include <freeipmi/spec/ipmi-iana-enterprise-numbers-spec.h>
#include <freeipmi/spec/ipmi-ipmb-lun-spec.h>
#include <freeipmi/spec/ipmi-jedec-manufacturer-identification-code-spec.h>
#include <freeipmi/spec/ipmi-lan-configuration-parameters-spec.h>
#include <freeipmi/spec/ipmi-netfn-spec.h>
#include <freeipmi/spec/ipmi-pef-configuration-parameters-spec.h>
#include <freeipmi/spec/ipmi-privilege-level-spec.h>
#include <freeipmi/spec/ipmi-product-id-spec.h>
#include <freeipmi/spec/ipmi-rmcpplus-status-spec.h>
#include <freeipmi/spec/ipmi-sensor-and-event-code-tables-spec.h>
#include <freeipmi/spec/ipmi-sensor-types-spec.h>
#include <freeipmi/spec/ipmi-sensor-units-spec.h>
#include <freeipmi/spec/ipmi-serial-modem-configuration-parameters-spec.h>
#include <freeipmi/spec/ipmi-slave-address-spec.h>
#include <freeipmi/spec/ipmi-sol-configuration-parameters-spec.h>
#include <freeipmi/spec/ipmi-system-boot-option-parameters-spec.h>
#include <freeipmi/spec/ipmi-system-info-parameters-spec.h>
#include <freeipmi/spec/ipmi-system-software-id-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-ibm-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-sun-microsystems-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-cmd-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-comp-code-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-comp-code-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-comp-code-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-comp-code-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-comp-code-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-hp-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-event-reading-type-code-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-lan-configuration-parameters-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-lan-configuration-parameters-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-ibm-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-netfn-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-ibm-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-sun-microsystems-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-hp-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-and-event-code-tables-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-numbers-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-fujitsu-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-hp-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-intel-node-manager-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-supermicro-spec.h>
#include <freeipmi/spec/oem/ipmi-sensor-types-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-slave-address-oem-intel-spec.h>
#include <freeipmi/spec/oem/ipmi-slave-address-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-slave-address-oem-linux-kernel-spec.h>
#include <freeipmi/spec/oem/ipmi-slave-address-oem-quanta-spec.h>
#include <freeipmi/spec/oem/ipmi-slave-address-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-sol-configuration-parameters-oem-inventec-spec.h>
#include <freeipmi/spec/oem/ipmi-sol-configuration-parameters-oem-wistron-spec.h>
#include <freeipmi/spec/oem/ipmi-system-info-parameters-oem-dell-spec.h>
#include <freeipmi/spec/oem/ipmi-system-info-parameters-oem-wistron-spec.h>
#include <freeipmi/util/ipmi-channel-util.h>
#include <freeipmi/util/ipmi-cipher-suite-util.h>
#include <freeipmi/util/ipmi-device-types-util.h>
#include <freeipmi/util/ipmi-entity-ids-util.h>
#include <freeipmi/util/ipmi-error-util.h>
#include <freeipmi/util/ipmi-error-dcmi-util.h>
#include <freeipmi/util/ipmi-iana-enterprise-numbers-util.h>
#include <freeipmi/util/ipmi-ipmb-util.h>
#include <freeipmi/util/ipmi-jedec-manufacturer-identification-code-util.h>
#include <freeipmi/util/ipmi-lan-util.h>
#include <freeipmi/util/ipmi-outofband-util.h>
#include <freeipmi/util/ipmi-rmcpplus-util.h>
#include <freeipmi/util/ipmi-sensor-and-event-code-tables-util.h>
#include <freeipmi/util/ipmi-sensor-util.h>
#include <freeipmi/util/ipmi-timestamp-util.h>
#include <freeipmi/util/ipmi-util.h>
#include <freeipmi/util/ipmi-dcmi-util.h>
#include <freeipmi/util/rmcp-util.h>

#define FREEIPMI_PACKAGE_VERSION       1.5.1
#define FREEIPMI_PACKAGE_VERSION_MAJOR 1
#define FREEIPMI_PACKAGE_VERSION_MINOR 5
#define FREEIPMI_PACKAGE_VERSION_PATCH 1

/*
 * Libfreeipmi version
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

#define LIBFREEIPMI_VERSION_MAJOR 6
#define LIBFREEIPMI_VERSION_MINOR 0
#define LIBFREEIPMI_VERSION_PATCH 0

#ifdef __cplusplus
}
#endif

#endif /* FREEIPMI_H */

