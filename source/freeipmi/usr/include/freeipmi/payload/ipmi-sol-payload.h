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

#ifndef IPMI_SOL_PAYLOAD_H
#define IPMI_SOL_PAYLOAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/fiid/fiid.h>

#define IPMI_SOL_PACKET_SEQUENCE_NUMBER_MAX    0xF

#define IPMI_SOL_FLUSH_OUTBOUND        0x1
#define IPMI_SOL_DO_NOT_FLUSH_OUTBOUND 0x0

#define IPMI_SOL_FLUSH_OUTBOUND_VALID(__val) \
  (((__val) == IPMI_SOL_FLUSH_OUTBOUND       \
    || (__val) == IPMI_SOL_DO_NOT_FLUSH_OUTBOUND) ? 1 : 0)

#define IPMI_SOL_FLUSH_INBOUND        0x1
#define IPMI_SOL_DO_NOT_FLUSH_INBOUND 0x0

#define IPMI_SOL_FLUSH_INBOUND_VALID(__val) \
  (((__val) == IPMI_SOL_FLUSH_INBOUND       \
    || (__val) == IPMI_SOL_DO_NOT_FLUSH_INBOUND) ? 1 : 0)

#define IPMI_SOL_ASSERT_DCD_DSR       0x0
#define IPMI_SOL_DEASSERT_DCD_DSR     0x1

#define IPMI_SOL_ASSERT_DCD_DSR_VALID(__val) \
  (((__val) == IPMI_SOL_ASSERT_DCD_DSR       \
    || (__val) == IPMI_SOL_DEASSERT_DCD_DSR) ? 1 : 0)

#define IPMI_SOL_ASSERT_CTS       0x0
#define IPMI_SOL_DEASSERT_CTS     0x1

#define IPMI_SOL_ASSERT_CTS_VALID(__val) \
  (((__val) == IPMI_SOL_ASSERT_CTS       \
    || (__val) == IPMI_SOL_DEASSERT_CTS) ? 1 : 0)

#define IPMI_SOL_GENERATE_BREAK        0x1
#define IPMI_SOL_DO_NOT_GENERATE_BREAK 0x0

#define IPMI_SOL_GENERATE_BREAK_VALID(__val) \
  (((__val) == IPMI_SOL_GENERATE_BREAK       \
    || (__val) == IPMI_SOL_DO_NOT_GENERATE_BREAK) ? 1 : 0)

#define IPMI_SOL_ASSERT_RI       0x0
#define IPMI_SOL_DEASSERT_RI     0x1

#define IPMI_SOL_ASSERT_RI_VALID(__val) \
  (((__val) == IPMI_SOL_ASSERT_RI       \
    || (__val) == IPMI_SOL_DEASSERT_RI) ? 1 : 0)

#define IPMI_SOL_ACK                0x0
#define IPMI_SOL_NACK               0x1

#define IPMI_SOL_ACK_VALID(__val) \
  (((__val) == IPMI_SOL_ACK       \
    || (__val) == IPMI_SOL_NACK) ? 1 : 0)

#define IPMI_SOL_NACK_VALID(__val) \
  (((__val) == IPMI_SOL_ACK        \
    || (__val) == IPMI_SOL_NACK) ? 1 : 0)

#define IPMI_SOL_BREAK_CONDITION_DETECTED 0x1
#define IPMI_SOL_NO_BREAK_DETECTED        0x0

#define IPMI_SOL_TRANSMIT_OVERRUN_CHARACTERS_DROPPED     0x1
#define IPMI_SOL_TRANSMIT_OVERRUN_NO_CHARACTERS_DROPPED  0x0

#define IPMI_SOL_SOL_DEACTIVATING 0x1
#define IPMI_SOL_SOL_ACTIVE       0x0

#define IPMI_SOL_CHARACTER_TRANSFER_UNAVAILABLE 0x1
#define IPMI_SOL_CHARACTER_TRANSFER_AVAILABLE   0x0

/* 
 * fill* functions return 0 on success, -1 on error.
 *
 * obj_sol_payload must be for the fill function's respective fiid
 * template request.
 *
 * see freeipmi/templates/ for template definitions 
 */

extern fiid_template_t tmpl_sol_payload_data;
extern fiid_template_t tmpl_sol_payload_data_remote_console_to_bmc;
extern fiid_template_t tmpl_sol_payload_data_bmc_to_remote_console;
  
int fill_sol_payload_data (uint8_t packet_sequence_number,
                           uint8_t packet_ack_nack_sequence_number,
                           uint8_t accepted_character_count,
                           uint8_t operation_status,
                           const void *character_data,
                           unsigned int character_data_len,
                           fiid_obj_t obj_sol_payload);

int fill_sol_payload_data_remote_console_to_bmc (uint8_t packet_sequence_number,
                                                 uint8_t packet_ack_nack_sequence_number,
                                                 uint8_t accepted_character_count,
                                                 uint8_t flush_outbound,
                                                 uint8_t flush_inbound,
                                                 uint8_t drop_dcd_dsr,
                                                 uint8_t cts_pause,
                                                 uint8_t generate_break,
                                                 uint8_t ring_wor,
                                                 uint8_t nack,
                                                 const void *character_data,
                                                 unsigned int character_data_len,
                                                 fiid_obj_t obj_sol_payload);

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SOL_PAYLOAD_H */
