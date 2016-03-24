/*****************************************************************************\
 *  $Id: ipmiconsole.h,v 1.89 2010-08-03 00:10:59 chu11 Exp $
 *****************************************************************************
 *  Copyright (C) 2007-2012 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2006-2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-221226
 *
 *  This file is part of Ipmiconsole, a set of IPMI 2.0 SOL libraries
 *  and utilities.  For details, see http://www.llnl.gov/linux/.
 *
 *  Ipmiconsole is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmiconsole is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmiconsole.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMICONSOLE_H
#define IPMICONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <freeipmi/freeipmi.h>

/*
 * Libipmiconsole version
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

#define LIBIPMICONSOLE_VERSION_MAJOR 1
#define LIBIPMICONSOLE_VERSION_MINOR 2
#define LIBIPMICONSOLE_VERSION_PATCH 2

/*
 * IPMI Console Error Codes
 */
#define IPMICONSOLE_ERR_SUCCESS                               0
#define IPMICONSOLE_ERR_CTX_NULL                              1
#define IPMICONSOLE_ERR_CTX_INVALID                           2
#define IPMICONSOLE_ERR_ALREADY_SETUP                         3
#define IPMICONSOLE_ERR_NOT_SETUP                             4
#define IPMICONSOLE_ERR_CTX_NOT_SUBMITTED                     5
#define IPMICONSOLE_ERR_CTX_IS_SUBMITTED                      6
#define IPMICONSOLE_ERR_PARAMETERS                            7
#define IPMICONSOLE_ERR_HOSTNAME_INVALID                      8
#define IPMICONSOLE_ERR_IPMI_2_0_UNAVAILABLE                  9
#define IPMICONSOLE_ERR_CIPHER_SUITE_ID_UNAVAILABLE          10
#define IPMICONSOLE_ERR_USERNAME_INVALID                     11
#define IPMICONSOLE_ERR_PASSWORD_INVALID                     12
#define IPMICONSOLE_ERR_K_G_INVALID                          13
#define IPMICONSOLE_ERR_PRIVILEGE_LEVEL_INSUFFICIENT         14
#define IPMICONSOLE_ERR_PRIVILEGE_LEVEL_CANNOT_BE_OBTAINED   15
#define IPMICONSOLE_ERR_SOL_UNAVAILABLE                      16
#define IPMICONSOLE_ERR_SOL_INUSE                            17
#define IPMICONSOLE_ERR_SOL_STOLEN                           18
#define IPMICONSOLE_ERR_SOL_REQUIRES_ENCRYPTION              19
#define IPMICONSOLE_ERR_SOL_REQUIRES_NO_ENCRYPTION           20
#define IPMICONSOLE_ERR_BMC_BUSY                             21
#define IPMICONSOLE_ERR_BMC_ERROR                            22
#define IPMICONSOLE_ERR_BMC_IMPLEMENTATION                   23
#define IPMICONSOLE_ERR_CONNECTION_TIMEOUT                   24
#define IPMICONSOLE_ERR_SESSION_TIMEOUT                      25
#define IPMICONSOLE_ERR_EXCESS_RETRANSMISSIONS_SENT          26
#define IPMICONSOLE_ERR_EXCESS_ERRORS_RECEIVED               27
#define IPMICONSOLE_ERR_OUT_OF_MEMORY                        28
#define IPMICONSOLE_ERR_TOO_MANY_OPEN_FILES                  29
#define IPMICONSOLE_ERR_SYSTEM_ERROR                         30
#define IPMICONSOLE_ERR_INTERNAL_ERROR                       31
#define IPMICONSOLE_ERR_ERRNUMRANGE                          32

/*
 * Debug Flags
 *
 * Utilized with ipmiconsole_engine_init() or with struct
 * ipmiconsole_engine_config below for debugging.
 *
 * When used with ipmiconsole_engine_init(), enables debugging in
 * libipmiconsole global activities, such as the libipmiconsole engine
 * threads.
 *
 * When used with struct ipmiconsole_engine_config and a context,
 * enables debugging specific to an IPMI connection with a specific
 * host.
 *
 * STDOUT       - Output debugging to stdout
 * STDERR       - Output debugging to stderr
 * SYSLOG       - Output debugging to the Syslog
 * FILE         - Output debugging to files in current working directory
 * IPMI_PACKETS - Dump IPMI Packets too
 * DEFAULT      - Informs library to use default, may it be standard
 *                or configured via libipmiconsole.conf.
 */
#define IPMICONSOLE_DEBUG_STDOUT           0x00000001
#define IPMICONSOLE_DEBUG_STDERR           0x00000002
#define IPMICONSOLE_DEBUG_SYSLOG           0x00000004
#define IPMICONSOLE_DEBUG_FILE             0x00000008
#define IPMICONSOLE_DEBUG_IPMI_PACKETS     0x00000010
#define IPMICONSOLE_DEBUG_DEFAULT          0xFFFFFFFF

/*
 * IPMI Privilege Constants
 *
 * Utilized with struct ipmiconsole_ipmi_config below to specify a
 * privilege level to authenticate with.
 */
#define IPMICONSOLE_PRIVILEGE_USER                0
#define IPMICONSOLE_PRIVILEGE_OPERATOR            1
#define IPMICONSOLE_PRIVILEGE_ADMIN               2

/*
 * Workaround Flags
 *
 * Utilized with struct ipmiconsole_ipmi_config below to specify
 * workarounds for specific motherboard manufacturers.
 *
 * AUTHENTICATION_CAPABILITIES
 *
 * This workaround flag will skip early checks for username
 * capabilities, authentication capabilities, and K_g support and
 * allow IPMI authentication to succeed.  It works around multiple
 * issues in which the remote system does not properly report username
 * capabilities, authentication capabilities, or K_g status.
 *
 * INTEL_2_0_SESSION
 *
 * This workaround flag will work around several Intel IPMI 2.0
 * authentication issues.  The issues covered include padding of
 * usernames, automatic acceptance of a RAKP 4 response integrity
 * check when using the integrity algorithm MD5-128, and password
 * truncation if the authentication algorithm is HMAC-MD5-128.
 *
 * SUPERMICRO_2_0_SESSION
 *
 * This workaround option will work around several Supermicro IPMI 2.0
 * authentication issues on motherboards w/ Peppercon IPMI firmware.
 * The issues covered include handling invalid length authentication
 * codes.
 *
 * SUN_2_0_SESSION
 *
 * This workaround flag will work work around several Sun IPMI 2.0
 * authentication issues.  The issues covered include invalid lengthed
 * hash keys, improperly hashed keys, and invalid cipher suite
 * records.  This workaround automatically includes the
 * OPEN_SESSION_PRIVILEGE workaround.  
 *
 * OPEN_SESSION_PRIVILEGE
 * 
 * This workaround flag will slightly alter FreeIPMI's IPMI 2.0
 * connection protocol to workaround an invalid hashing algorithm used
 * by the remote system.  The privilege level sent during the Open
 * Session stage of an IPMI 2.0 connection is used for hashing keys
 * instead of the privilege level sent during the RAKP1 connection
 * stage.  This workaround is automatically triggered with the
 * SUN_2_0_SESSION workaround.
 *
 * NON_EMPTY_INTEGRITY_CHECK_VALUE
 *
 * This workaround option will work around an invalid integrity check
 * value during an IPMI 2.0 session establishment when using Cipher
 * Suite ID 0.  The integrity check value should be 0 length, however
 * the remote motherboard responds with a non-empty field.
 *
 * NO_CHECKSUM_CHECK
 *
 * This workaround option will work around motheboards that calculate
 * checksums incorrectly in IPMI command responses, but the packet is
 * otherwise valid.  Users are cautioned on the use of this option, as
 * it removes some validation of packet integrity.  However, it is
 * unlikely to be an issue in most situations.
 *
 * SERIAL_ALERTS_DEFERRED
 *
 * This workaround option will set serial alerts to be deferred
 * instead of have them be failures.  This works around motherboards
 * that perform IPMI over serial along with IPMI serial over LAN.
 *
 * INCREMENT_SOL_PACKET_SEQUENCE
 *
 * This workaround option will increment the SOL payload packet
 * sequence number under dire circumstances.  Normally SOL should
 * never do this, however some motherboards have shown to get "stuck"
 * due to an internal bug on the motherboard.  This workaround can
 * help in getting the BMC un-stuck.
 *
 * IGNORE_SOL_PAYLOAD_SIZE
 *
 * This workaround flag will not check for valid SOL payload sizes and
 * assume a proper set.  It works around remote systems that report
 * invalid IPMI 2.0 SOL payload sizes.
 *
 * IGNORE_SOL_PORT
 *
 * This workaround flag will ignore alternate SOL ports specified
 * during the protocol.  It works around remote systems that report
 * invalid alternate SOL ports.
 *
 * SKIP_SOL_ACTIVATION_STATUS
 *
 * This workaround flag will not check the current activation status
 * of SOL during the protocol setup.  It works around remote systems
 * that do not properly support this command.
 *
 * SKIP_CHANNEL_PAYLOAD_SUPPORT
 *
 * This workaround flag will skip the portion of the protocol that
 * checks if SOL is supported on the current channel.  It works around
 * remote systems that do not properly support this command.
 *
 * DEFAULT
 *
 * Informs library to use default, may it be the standard default or
 * a default configured via libipmiconsole.conf.
 *
 * Note: The non-logical bitmask order below is set for future
 * expansion and matching w/ libfreeipmi.
 */
#define IPMICONSOLE_WORKAROUND_AUTHENTICATION_CAPABILITIES     0x00000001
#define IPMICONSOLE_WORKAROUND_INTEL_2_0_SESSION               0x00000002
#define IPMICONSOLE_WORKAROUND_SUPERMICRO_2_0_SESSION          0x00000004
#define IPMICONSOLE_WORKAROUND_SUN_2_0_SESSION                 0x00000008
#define IPMICONSOLE_WORKAROUND_OPEN_SESSION_PRIVILEGE          0x00000010
#define IPMICONSOLE_WORKAROUND_NON_EMPTY_INTEGRITY_CHECK_VALUE 0x00000020
#define IPMICONSOLE_WORKAROUND_NO_CHECKSUM_CHECK               0x00000040
#define IPMICONSOLE_WORKAROUND_SERIAL_ALERTS_DEFERRED          0x00000080
#define IPMICONSOLE_WORKAROUND_INCREMENT_SOL_PACKET_SEQUENCE   0x00000100
#define IPMICONSOLE_WORKAROUND_IGNORE_SOL_PAYLOAD_SIZE         0x01000000
#define IPMICONSOLE_WORKAROUND_IGNORE_SOL_PORT                 0x02000000
#define IPMICONSOLE_WORKAROUND_SKIP_SOL_ACTIVATION_STATUS      0x04000000
#define IPMICONSOLE_WORKAROUND_SKIP_CHANNEL_PAYLOAD_SUPPORT    0x08000000
#define IPMICONSOLE_WORKAROUND_DEFAULT                         0xFFFFFFFF

/*
 * Engine Flags
 *
 * Utilized with struct ipmiconsole_engine_config below to alter
 * libipmiconsole engine behavior. 
 *
 * CLOSE_FD
 *
 * By default, the ipmiconsole engine will not close the file
 * descriptor (returned by ipmiconsole_ctx_fd()) when an error occurs
 * within the ipmiconsole engine (such as a session timeout).  A user
 * will subsequently see an EOF on a read() or an EPIPE on a write()
 * to know an error occurred.
 *
 * This flag will inform the engine to close the file descriptor on
 * error.  This will change the behavior of how the user should
 * program with the file descriptor.  For example, calls to read() and
 * write() would likely return with EBADF errors instead of EOF or
 * EPIPE errors respectively.  Calls to select() may return with EBADF
 * errors and calls to poll() could result in POLLNVAL returned
 * events.
 *
 * OUTPUT_ON_SOL_ESTABLISHED
 *
 * When submitting a context to the engine non-blocking, another way
 * to determine if the SOL session has been established is if data has
 * output from the remote console and is available for you to read.
 * Under most circumstances, this isn't a controllable situation.
 *
 * This flag will inform the engine to output a single NUL character
 * ('\0') to the console once a SOL session has been established.  If
 * the CLOSE_FD flag isn't used above, this would allow the user to
 * expect an EOF vs. 1 byte of data on a read() to determine if the
 * SOL session has failed or succeeded.  The user may choose to output
 * the NUL anyways (it should do no harm) or simply throw out the
 * first byte ever read from remote console.
 *
 * LOCK_MEMORY
 *
 * Inform libipmiconsole to lock memory to prevent sensitive
 * information (such as usernames and passwords) to be non-swappable.
 *
 * SERIAL_KEEPALIVE
 *
 * On some motherboards, it's been observed that IPMI connections
 * between the IPMI client and remote BMC/server can stay alive while
 * the remote server's internal connection between the BMC and serial
 * chip can be lost.  This has been observed under several situations, 
 * such as when the remote system is rebooted or a IPMI SOL session is
 * stolen.   
 *
 * The affect is that this loss of the serial connection will not be
 * noticed by the IPMI client until serial data is transfered from the
 * client to the BMC and a timeout (or similar error) eventually occurs.
 * The IPMI client must then reconnect to restablish the session.
 *
 * This is a severe problem for IPMI clients that predominantly log
 * serial data or display serial output without user interactivity.
 * From the IPMI client perspective, there is simply no output from
 * the serial port and no error has actually occurred.
 * 
 * This option will inform the libipmiconsole engine to send serial
 * keepalive packets in addition to the IPMI keepalive packets that
 * normally keep a connection alive.  The serial keepalive packets are
 * standard SOL payload packets, but contain a single NUL character in
 * them.  The single NUL character is to ensure that the underlying
 * serial receiver is alive and functioning.  Retransmission and
 * timeouts are handled identically to normal IPMI packets in the code
 * (e.g. as if somebody typed a character).  The serial keepalive
 * packets are dispatched if a SOL packet response has not been
 * received within the length of time of a session timeout.
 *
 * This option is highly recommended for IPMI clients that do not have
 * high user interactivity, as this may discover broken connections
 * far more quickly.  However, caution should be maintained, as the
 * NUL character byte may affect the remote system depending on what
 * input it may or may not be expecting.
 * 
 * SERIAL_KEEPALIVE_EMPTY
 *
 * This option is identical to SERIAL_KEEPALIVE, except that the
 * serial keepalive packets are empty and without character data.  On
 * some motherboards, this may be sufficient to deal with the "serial
 * keepalive" issue and character data need not be sent with each
 * packet.  On some systems though, a SOL packet without character
 * data may not be ACKed, and therefore the keepalive fails.
 *
 * DEFAULT
 *
 * Informs library to use default, may it be the standard default or
 * a default configured via libipmiconsole.conf.
 */
#define IPMICONSOLE_ENGINE_CLOSE_FD                  0x00000001
#define IPMICONSOLE_ENGINE_OUTPUT_ON_SOL_ESTABLISHED 0x00000002
#define IPMICONSOLE_ENGINE_LOCK_MEMORY               0x00000004
#define IPMICONSOLE_ENGINE_SERIAL_KEEPALIVE          0x00000008
#define IPMICONSOLE_ENGINE_SERIAL_KEEPALIVE_EMPTY    0x00000010
#define IPMICONSOLE_ENGINE_DEFAULT                   0xFFFFFFFF

/*
 * Behavior Flags
 *
 * Utilized with struct ipmiconsole_protocol_config below to atler
 * SOL connection behavior.
 *
 * ERROR_ON_SOL_INUSE
 *
 * Under most circumstances, if SOL is detected as being in use,
 * libipmiconsole will attempt to deactivate the earlier SOL session
 * and activate the SOL session under the current one.  This default
 * behavior exists for several reasons, most notably that earlier SOL
 * sessions may have not been able to be deactivated properly.  This
 * security flag changes the default behavior to return an error if
 * SOL is already detected as being in use.  If it is detected as in
 * use, the errnum returned from ipmiconsole_ctx_errnum() would be
 * IPMICONSOLE_ERR_SOL_INUSE.
 *
 * DEACTIVATE_ONLY
 *
 * Only attempt to deactivate the SOL session.  If an SOL session is
 * not active, do nothing.
 *
 * DEACTIVATE_ALL_INSTANCES
 *
 * When a SOL session is deactivated via the DEACTIVATE_ONLY flag,
 * only the currently configured SOL payload instance will be
 * deactivated, not any other instance.  This flag will inform
 * libipmiconsole to deactivate all presently activated instances.
 * This may be useful in a few circumstances where a user might want
 * to deactivate all current sessions.
 * 
 * DEFAULT
 *
 * Informs library to use default, may it be the standard default or
 * a default configured via libipmiconsole.conf.
 */
#define IPMICONSOLE_BEHAVIOR_ERROR_ON_SOL_INUSE       0x00000001
#define IPMICONSOLE_BEHAVIOR_DEACTIVATE_ONLY          0x00000002
#define IPMICONSOLE_BEHAVIOR_DEACTIVATE_ALL_INSTANCES 0x00000004
#define IPMICONSOLE_BEHAVIOR_DEFAULT                  0xFFFFFFFF

/*
 * Context Status
 *
 * Returned by ipmiconsole_ctx_status() below.
 *
 * ERROR
 *
 * An error has occurred retrieving the status.
 *
 * NOT_SUBMITTED
 *
 * The context has not been submitted to the engine.
 *
 * SUBMITTED
 *
 * The context has been submitted to the engine.  SOL has not been
 * established and an error has not yet occurred.
 *
 * SOL_ERROR
 *
 * The context has received an error during SOL establishment.
 *
 * SOL_ESTABLISHED
 *
 * The context has established a SOL session.
 *
 */
enum ipmiconsole_ctx_status
{
  IPMICONSOLE_CTX_STATUS_ERROR = -1,
  IPMICONSOLE_CTX_STATUS_NOT_SUBMITTED = 0,
  IPMICONSOLE_CTX_STATUS_SUBMITTED = 1,
  IPMICONSOLE_CTX_STATUS_SOL_ERROR = 2,
  IPMICONSOLE_CTX_STATUS_SOL_ESTABLISHED = 3,
};
typedef enum ipmiconsole_ctx_status ipmiconsole_ctx_status_t;

/*
 * ipmiconsole_ipmi_config
 *
 * IPMI configuration for a connection to a remote IPMI machine.
 * Defaults can be modified using the libipmiconsole.conf file.
 *
 * username
 *
 *   BMC username. Pass NULL ptr for default username.  Standard
 *   default is the null (e.g. empty) username.  Maximum length of 16
 *   bytes.
 *
 * password
 *
 *   BMC password. Pass NULL ptr for default password.  Standard
 *   default is the null (e.g. empty) password.  Maximum length of 20
 *   bytes.
 *
 * k_g
 *
 *   BMC Key for 2-key authentication.  Pass NULL ptr to use the
 *   default.  Standard default is the null (e.g. empty) k_g,
 *   which will use the password as the BMC key.  The k_g key need not
 *   be an ascii string.
 *
 * k_g_len
 *
 *   Length of k_g.  Necessary b/c k_g may contain null values in its
 *   key.  Maximum length of 20 bytes.
 *
 * privilege_level
 *
 *   privilege level to authenticate with.
 *
 *   Supported privilege levels:
 *
 *   IPMICONSOLE_PRIVILEGE_USER
 *   IPMICONSOLE_PRIVILEGE_OPERATOR
 *   IPMICONSOLE_PRIVILEGE_ADMIN
 *
 *   Pass < 0 for default.  Standard default is
 *   IPMICONSOLE_PRIVILEGE_ADMIN.
 *
 * cipher_suite_id
 *
 *   Cipher suite identifier to determine authentication, integrity,
 *   and confidentiality algorithms to use.
 *
 *   Supported Cipher Suite IDs
 *   (Key: A - Authentication Algorithm
 *         I - Integrity Algorithm
 *         C - Confidentiality Algorithm)
 *
 *   0 - A = None; I = None; C = None
 *   1 - A = HMAC-SHA1; I = None; C = None
 *   2 - A = HMAC-SHA1; I = HMAC-SHA1-96; C = None
 *   3 - A = HMAC-SHA1; I = HMAC-SHA1-96; C = AES-CBC-128
 *   6 - A = HMAC-MD5; I = None; C = None
 *   7 - A = HMAC-MD5; I = HMAC-MD5-128; C = None
 *   8 - A = HMAC-MD5; I = HMAC-MD5-128; C = AES-CBC-128
 *   11 - A = HMAC-MD5; I = MD5-128; C = None
 *   12 - A = HMAC-MD5; I = MD5-128; C = AES-CBC-128
 *   15 - A = HMAC-SHA256; I = None; C = None
 *   16 - A = HMAC-SHA256; I = HMAC-SHA256-128; C = None
 *   17 - A = HMAC-SHA256; I = HMAC-SHA256-128; C = AES-CBC-128
 *
 *   Pass < 0 for default.  Standard default is 3.
 *
 * workaround_flags
 *
 *   Bitwise OR of flags indicating IPMI implementation changes.  Some
 *   BMCs which are non-compliant and may require a workaround flag
 *   for correct operation. Pass IPMICONSOLE_WORKAROUND_DEFAULT for
 *   default.  Standard default is 0, no modifications to the IPMI
 *   protocol.
 */
struct ipmiconsole_ipmi_config
{
  char *username;
  char *password;
  unsigned char *k_g;
  unsigned int k_g_len;
  int privilege_level;
  int cipher_suite_id;
  unsigned int workaround_flags;
};

/*
 * ipmiconsole_protocol_config
 *
 * Configuration information for the IPMI protocol management.
 * Defaults can be modified using the libipmiconsole.conf file.
 *
 * session_timeout_len
 *
 *   Specifies the session timeout length in milliseconds.  Pass <= 0
 *   for default.  Standard default is 60000 (60 seconds).
 *
 * retransmission_timeout_len
 *
 *   Specifies the packet retransmission timeout length in
 *   milliseconds.  Pass <= 0 for default.  Standard default is
 *   500 (0.5 seconds).
 *
 * retransmission_backoff_count
 *
 *   Specifies the packet retransmission count until retransmission
 *   timeout lengths will be backed off.  Pass <= 0 for default.
 *   Standard default is 2.
 *
 * keepalive_timeout_len
 *
 *   Specifies the session timeout length in milliseconds until a
 *   keepalive packet is sent.  Pass <= 0 for default.  Standard
 *   default is 20000 (20 seconds).
 *
 * retransmission_keepalive_timeout_len
 *
 *   Specifies the keepalive packet retransmission timeout length in
 *   milliseconds.  Pass <= 0 for default.  Standard default is
 *   5000 (5 seconds).
 *
 * acceptable_packet_errors_count
 *
 *   Specifies the maximum number of consecutive packet errors that
 *   can be received from a remote BMC before an error is returned and
 *   the session ended.  Pass <= 0 for default.  Standard
 *   default is 16.
 *
 *   Note: This has been added to the behavior of the IPMI engine due
 *   to issues where remote BMCs can become "un-synced" with sequence
 *   numbers due to a network kernel boot.  It is possible a stream of
 *   packets can be sent to the remote client with session sequence
 *   numbers that are excessively outside of the acceptable window
 *   range.
 *
 * maximum_retransmission_count
 *
 *   Specifies the maximum number of retransmissions that can be sent
 *   for any IPMI packet before an error is returned and the session
 *   ended.  Pass <= 0 for default.  Standard default is 16.
 *
 *   Note: This has been added to the behavior of the IPMI engine due
 *   to issues where remote BMCs can become "un-synced" with sequence
 *   numbers due to a network kernel boot.  It is possible for some
 *   packets (in particular 'ping' packets to keep an IPMI session
 *   alive) to be accepted by the remote BMC, but not SOL packets.
 *
 */
struct ipmiconsole_protocol_config
{
  int session_timeout_len;
  int retransmission_timeout_len;
  int retransmission_backoff_count;
  int keepalive_timeout_len;
  int retransmission_keepalive_timeout_len;
  int acceptable_packet_errors_count;
  int maximum_retransmission_count;
};

/*
 * ipmiconsole_engine_config
 *
 * Configuration information for how the engine should interact with
 * the user or API.  Defaults can be modified using the
 * libipmiconsole.conf file.
 *
 * engine_flags
 *
 *   Bitwise OR of flags indicating how the ipmiconsole engine should
 *   behave for a particular context.  Pass IPMICONSOLE_ENGINE_DEFAULT
 *   for default.  Standard default is 0.
 *
 * behavior_flags
 *
 *   Bitwise OR of flags indicating any protocol behavior that should
 *   be changed from the default.  Pass IPMICONSOLE_BEHAVIOR_DEFAULT
 *   for default.  Standard default is 0.
 *
 * debug_flags
 *
 *   Bitwise OR of flags indicating how debug output should (or should
 *   not) be output. Pass IPMICONSOLE_DEBUG_DEFAULT for default.
 *   Standard default is 0.
 *
 */
struct ipmiconsole_engine_config
{
  unsigned int engine_flags;
  unsigned int behavior_flags;
  unsigned int debug_flags;
};

/*
 * Context Config Option
 *
 * Used for setting or getting advanced configuration options.  See
 * ipmiconsole_ctx_set_config_option() and
 * ipmiconsole_ctx_get_config_option().
 *
 * SOL_PAYLOAD_INSTANCE
 *
 * The SOL payload instance number to be used.  Defaults to 1 and has
 * range of 1 to 15.  Most systems only support a single instance,
 * however a few allow users to access multiple.  They could be used
 * to allow multiple users to see the same serial session, or allow
 * users to access different serial sessions behind a device.  It is
 * not commonly available or necessary when communicating via SOL to a
 * single server.  The SOL payload instance number is specified and
 * retrieved via a pointer to an unsigned int.
 *
 */
enum ipmiconsole_ctx_config_option
{
  IPMICONSOLE_CTX_CONFIG_OPTION_SOL_PAYLOAD_INSTANCE = 0,
};
typedef enum ipmiconsole_ctx_config_option ipmiconsole_ctx_config_option_t;

#define IPMICONSOLE_THREAD_COUNT_MAX       32

typedef struct ipmiconsole_ctx *ipmiconsole_ctx_t;

/*
 * Ipmiconsole_callback
 *
 * Function prototype for a callback function.
 * ipmiconsole_engine_submit() below.
 */
typedef void (*Ipmiconsole_callback)(void *);

/*
 * ipmiconsole_engine_init
 *
 * Initialize the ipmiconsole engine.  Engine threads will be created
 * which will manage SOL sessions for the user.  This function must be
 * called before ipmi console contexts can be submitted into the
 * engine.  This call will also parse and load alternate defaults from
 * the libipmiconsole.conf defaults file.
 *
 * Parameters:
 *
 * thread_count
 *
 *   Number of threads the engine will support.  Pass 0 for default of 4.
 *
 * debug_flags
 *
 *   Bitwise OR of flags indicating how debug output should (or should
 *   not) be output. Pass 0 for default of no debugging.
 *
 * Returns 0 on success, -1 on error.  On error errno will be set to
 * indicate error.  Possible errnos are ENOMEM if memory cannot be
 * allocated.
 */
int ipmiconsole_engine_init (unsigned int thread_count,
                             unsigned int debug_flags);

/*
 * ipmiconsole_engine_submit
 *
 * Submit a context to the ipmiconsole engine non-blocking.  This
 * function can return prior to a SOL session being established.  A
 * return value of 0 indicates the context was submitted properly.  A
 * return value of -1 indicates an error occurred during the
 * submission.  On an error, ipmiconsole_ctx_errnum() can be used to
 * determine the type of error that occured.
 *
 * After a context has been submitted, the user may determine if a SOL
 * session has been established several ways:
 *
 * A) Poll on the context status, retrieved via
 * ipmiconsole_ctx_status().  On an error, ipmiconsole_ctx_errnum()
 * can be used to determine the specific IPMI related error that
 * occurred.
 *
 * B) Poll on the context file descriptor, retrieved via
 * ipmiconsole_ctx_fd().  A SOL establishment error will result in an
 * EOF being returned on the file descriptor.  A proper SOL
 * establishment can be determined via a readable character on the
 * file descriptor.  The use of the OUTPUT_ON_SOL_ESTABLISHED Engine
 * flag above can aid in this.  The CLOSE_FD Engine flag can be set to
 * slightly alter this behavior, please see above. On an error,
 * ipmiconsole_ctx_errnum() can be used to determine the specific IPMI
 * related error that occurred.
 *
 * C) Specify a callback function.  The callback function specified as
 * a parameter below will be called directly after a SOL session has
 * been established or a session establishment error has occurred
 * (e.g. SOL not supported, authentication error, etc.).  Within those
 * callback functions, ipmiconsole_ctx_status() can be used to
 * determine which has occurred.  This callback will be called by the
 * engine thread, therefore users may need to protect their
 * application's shared data.
 *
 * Due to the non-blocking semantics of this function, it is possible
 * that multiple errors could occur simultaneously and the errnum
 * retrieved via ipmiconsole_ctx_errnum() may not be the one that
 * caused the SOL session to fail.  However, this will not occur given
 * proper usage of the API.  For example, if the user called
 * ipmiconsole_engine_submit() twice with the same context, an SOL
 * error in the engine background could race with the setting of the
 * errnum IPMICONSOLE_ERR_CTX_IS_SUBMITTED in the second call.
 *
 * Parameters:
 *
 * callback
 *
 *   If specified, a callback function will be called from the engine
 *   when a SOL session has been established or a SOL establishment
 *   error has occurred.  Will only be called under a non-blocking
 *   engine submission via ipmiconsole_engine_submit().  Will be
 *   called once and only once during an individual engine submission.
 *   For example, if a SOL session is established then a later session
 *   timeout occurs, the later session timeout will not generate a
 *   function call to the callback.  Pass NULL for no callback.
 *
 *   The callback function can be called simultaneously from different
 *   engine threads.  It is the user's responsibility to protect
 *   against any race conditions in their callback function.
 *
 * callback_arg
 *
 *   Specify an arbitrary argument to be passed to the callback
 *   routine.  If the callback will be required to process the context
 *   status, the context should be included in this argument.
 *
 * Returns 0 on success, -1 on error.  ipmiconsole_ctx_errnum() can be
 * called to determine the cause of the error.
 */
int ipmiconsole_engine_submit (ipmiconsole_ctx_t c,
                               Ipmiconsole_callback callback,
                               void *callback_arg);

/*
 * ipmiconsole_engine_submit_block
 *
 * Submit a context to the ipmiconsole engine and block until a SOL
 * session is established or an error/timeout occurs.  A return value
 * of 0 indicates the SOL session was established and a -1 indicates
 * an error occurred.  On an error, ipmiconsole_ctx_errnum() can be
 * used to determine the type of error that occured.
 *
 * Returns 0 on success, -1 on error.  ipmiconsole_ctx_errnum() can be
 * called to determine the cause of the error.
 */
int ipmiconsole_engine_submit_block (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_engine_teardown
 *
 * Teardown the ipmiconsole engine.  This function will destroy
 * all threads and contexts managed by the engine.
 *
 * Parameters:
 *
 * cleanup_sol_sessions
 *
 *   If set to non zero, SOL sessions will be torn down cleanly.
 *   ipmiconsole_engine_teardown() will block until all active ipmi
 *   sessions have been closed cleanly or timed out.
 */
void ipmiconsole_engine_teardown (int cleanup_sol_sessions);

/*
 * ipmiconsole_ctx_create
 *
 * Create an ipmiconsole context.  The context can then be submitted
 * into the ipmiconsole engine (via ipmiconsole_engine_submit() or
 * ipmiconsole_engine_submit_block()) to establish a SOL session.  The
 * context cannot be submitted to the ipmiconsole engine more than
 * once.  After it has been submitted to the ipmiconsole engine, it
 * cannot be reused.
 *
 * Parameters:
 *
 * hostname
 *
 *   Host or IP address you wish to connect to.
 *
 * ipmi_config
 *
 *   IPMI configuration.  See ipmiconsole_ipmi_config definition
 *   above.
 *
 * protocol_config
 *
 *   IPMI protocol configuration.  See ipmiconsole_protocol_config
 *   definition above.
 *
 * engine_config
 *
 *   Ipmiconsole engine configuration.  See ipmiconsole_engine_config
 *   definition above.
 *
 * Returns ctx on success, NULL on error.  On error errno will be set to
 * indicate error.  Possible errnos are EINVAL on invalid input,
 * ENOMEM if memory cannot be allocated, EMFILE if process file
 * descriptors limits have been reached, and EAGAIN if
 * ipmiconsole_engine_init() has not yet been called.
 */
ipmiconsole_ctx_t ipmiconsole_ctx_create (const char *hostname,
                                          struct ipmiconsole_ipmi_config *ipmi_config,
                                          struct ipmiconsole_protocol_config *protocol_config,
                                          struct ipmiconsole_engine_config *engine_config);

/*
 * ipmiconsole_ctx_set_config
 *
 * Set the value of an advanced configuration value.  This
 * configuration value must be set prior to a context being submitted
 * to the ipmiconsole engine (via ipmiconsole_engine_submit() or
 * ipmiconsole_engine_submit_block()).  After it has been submitted to
 * the ipmiconsole engine, it cannot be changed.
 *
 * See enum ipmiconsole_ctx_config_option above for config options and
 * pointer types expected by this function.
 *
 * Returns 0 on success, -1 on error.  ipmiconsole_ctx_errnum() can be
 * called to determine the cause of the error.
 */
int ipmiconsole_ctx_set_config (ipmiconsole_ctx_t c,
				ipmiconsole_ctx_config_option_t config_option,
                                void *config_option_value);
/*
 * ipmiconsole_ctx_get_config
 *
 * Get the value of an advanced configuration value.
 *
 * See enum ipmiconsole_ctx_config_option above for config options and
 * pointer types expected by this function.
 *
 * Returns 0 on success, -1 on error.  ipmiconsole_ctx_errnum() can be
 * called to determine the cause of the error.
 */
int ipmiconsole_ctx_get_config (ipmiconsole_ctx_t c,
				ipmiconsole_ctx_config_option_t config_option,
                                void *config_option_value);

/*
 * ipmiconsole_ctx_errnum
 *
 * Returns the errnum of the most recently recorded error for the
 * context that has not yet been read by the user.
 */
int ipmiconsole_ctx_errnum (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_ctx_strerror
 *
 * Returns a pointer to statically allocated string describing the
 * error code in errnum.
 */
char *ipmiconsole_ctx_strerror (int errnum);

/*
 * ipmiconsole_ctx_errormsg
 *
 * Returns a pointer to statically allocated string describing the
 * most recent error for the context.
 */
char *ipmiconsole_ctx_errormsg (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_ctx_status
 *
 * Returns the current context status.  Primarily used to determine if
 * a context submission (submitted non-blocking via
 * ipmiconsole_engine_submit()) has been established or not.  Returns
 * IPMICONSOLE_CTX_STATUS_ERROR (-1) on error.
 */
ipmiconsole_ctx_status_t ipmiconsole_ctx_status (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_ctx_fd
 *
 * Returns a file descriptor for console reading and writing after it
 * has been submitted to the engine.  Returns -1 on error.
 * ipmiconsole_ctx_errnum() can be called to determine the cause of
 * the error.
 *
 * If the user closes the file descriptor while the serial over lan
 * session is established, the session will be torn down in the
 * engine.
 *
 * If an error occurs on the engine side (for example a session
 * timeout) the other end of the file descriptor pair (from which this
 * fd is a part of) will be closed.  The error can be determined via
 * ipmiconsole_ctx_errnum().  The user of this file descriptor will
 * typically see this affect via an EOF on a read() or an EPIPE on a
 * write().  For alternate file descriptor behavior, see ENGINE flags
 * above.
 */
int ipmiconsole_ctx_fd (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_ctx_generate_break
 *
 * Generate a break on an active serial over LAN session.
 *
 * Returns 0 on success, -1 on error.  ipmiconsole_ctx_errnum() can be
 * called to determine the cause of the error.
 */
int ipmiconsole_ctx_generate_break (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_ctx_destroy
 *
 * Destroy a context.  Will close file descriptor retrieved from
 * ipmiconsole_ctx_fd().
 */
void ipmiconsole_ctx_destroy (ipmiconsole_ctx_t c);

/*
 * ipmiconsole_username_is_valid
 *
 * Convenience function to determine if a username is valid. Note that
 * a NULL pointer, which would result in libipmiconsole using a
 * default value, is considered an invalid input here.
 *
 * Returns 1 if username is valid, 0 if it is not.
 */
int ipmiconsole_username_is_valid (const char *username);

/*
 * ipmiconsole_password_is_valid
 *
 * Convenience function to determine if a password is valid.  Note
 * that a NULL pointer, which would result in libipmiconsole using a
 * default value, is considered an invalid input here.
 *
 * Returns 1 if password is valid, 0 if it is not.
 */
int ipmiconsole_password_is_valid (const char *password);

/*
 * ipmiconsole_k_g_is_valid
 *
 * Convenience function to determine if a k_g is valid.  Note that a
 * NULL pointer, which would result in libipmiconsole using a default
 * value, is considered an invalid input here.
 *
 * Returns 1 if k_g is valid, 0 if it is not.
 */
int ipmiconsole_k_g_is_valid (const unsigned char *k_g, unsigned int k_g_len);

/*
 * ipmiconsole_privilege_level_is_valid
 *
 * Convenience function to determine if a privilege level is valid.
 * Note that a negative value, which would result in libipmiconsole
 * using a default value, is considered an invalid input here.
 *
 * Returns 1 if privilege level is valid, 0 if it is not.
 */
int ipmiconsole_privilege_level_is_valid (int privilege_level);

/*
 * ipmiconsole_cipher_suite_id_is_valid
 *
 * Convenience function to determine if a cipher suite id is valid.
 * Note that a negative value, which would result in libipmiconsole
 * using a default value, is considered an invalid input here.
 *
 * Returns 1 if cipher suite id is valid, 0 if it is not.
 */
int ipmiconsole_cipher_suite_id_is_valid (int cipher_suite_id);

/*
 * ipmiconsole_workaround_flags_is_valid
 *
 * Convenience function to determine if workaround flags are valid.
 * Note that a bitmask value of IPMICONSOLE_WORKAROUND_DEFAULT, which
 * would result in libipmiconsole using a default value, is considered
 * an invalid input here.
 *
 * Returns 1 if workaround flags are valid, 0 if they are not.
 */
int ipmiconsole_workaround_flags_is_valid (unsigned int workaround_flags);

#ifdef __cplusplus
}
#endif

#endif /* IPMICONSOLE_H */
