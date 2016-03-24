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

#ifndef IPMI_PRODUCT_ID_SPEC_H
#define IPMI_PRODUCT_ID_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************* 
 * Dell                                    *
 *******************************************/

/* achu: I believe 256 to be the poweredge "family" of products, but
 * I'm not sure.  At minimum, it covers the 2900, 2950, R610, and
 * R710.
 */
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE 256
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_2900 IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_2950 IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_R610 IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_R710 IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_R720 IPMI_DELL_PRODUCT_ID_POWEREDGE_BASE

/* achu: 0 doesn't seem right?  Did the manufacturer not burn the
 * right ID in?
 */
#define IPMI_DELL_PRODUCT_ID_POWEREDGE_C410X 0

/******************************************* 
 * Fujitsu                                 *
 *******************************************/

/*
 * Fujitsu Siemens Computers
 * Fujitsu Technology Solutions
 * iRMC S1 / iRMC S2
 */
#define IPMI_FUJITSU_PRODUCT_ID_MIN                 0x0200
#define IPMI_FUJITSU_PRODUCT_ID_MAX                 0x03FF

// iRMC-S1 based systems        
#define IPMI_FUJITSU_PRODUCT_ID_TX200S3             0x0200
#define IPMI_FUJITSU_PRODUCT_ID_TX300S3             0x0201
#define IPMI_FUJITSU_PRODUCT_ID_RX200S3             0x0202
#define IPMI_FUJITSU_PRODUCT_ID_RX300S3             0x0203
#define IPMI_FUJITSU_PRODUCT_ID_UNUSEDS3            0x0204
#define IPMI_FUJITSU_PRODUCT_ID_RX100S4             0x0205
#define IPMI_FUJITSU_PRODUCT_ID_TX150S5             0x0206
#define IPMI_FUJITSU_PRODUCT_ID_TX120S1             0x0207
#define IPMI_FUJITSU_PRODUCT_ID_BX630S2             0x0208
#define IPMI_FUJITSU_PRODUCT_ID_RX330S1             0x0209
#define IPMI_FUJITSU_PRODUCT_ID_E230RN1             0x0210
#define IPMI_FUJITSU_PRODUCT_ID_E230RSL             0x0211
#define IPMI_FUJITSU_PRODUCT_ID_RX330S1_SHA         0x0212
#define IPMI_FUJITSU_PRODUCT_ID_BX630S2_SHA         0x0213

#define IPMI_FUJITSU_PRODUCT_ID_IS_IRMC_S1(__product_id)           \
  (((__product_id) == IPMI_FUJITSU_PRODUCT_ID_TX200S3              \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_TX300S3           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_RX200S3           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_RX300S3           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_UNUSEDS3          \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_RX100S4           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_TX150S5           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_TX120S1           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_BX630S2           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_RX330S1           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_E230RN1           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_E230RSL           \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_RX330S1_SHA       \
    || (__product_id) == IPMI_FUJITSU_PRODUCT_ID_BX630S2_SHA) ? 1 : 0)

// iRMC-S2 based systems        
#define IPMI_FUJITSU_PRODUCT_ID_RX600S4             0x0218
#define IPMI_FUJITSU_PRODUCT_ID_TX200S4             0x0220
#define IPMI_FUJITSU_PRODUCT_ID_TX300S4             0x0221
#define IPMI_FUJITSU_PRODUCT_ID_RX200S4             0x0222
#define IPMI_FUJITSU_PRODUCT_ID_RX300S4             0x0223
#define IPMI_FUJITSU_PRODUCT_ID_UNUSEDS4            0x0224
#define IPMI_FUJITSU_PRODUCT_ID_RX100S5             0x0225
#define IPMI_FUJITSU_PRODUCT_ID_TX150S6             0x0226
#define IPMI_FUJITSU_PRODUCT_ID_TX120S2             0x0227

#define IPMI_FUJITSU_PRODUCT_ID_TX150S6_64K         0x0233
#define IPMI_FUJITSU_PRODUCT_ID_TX200S4_64K         0x0234
#define IPMI_FUJITSU_PRODUCT_ID_TX300S4_64K         0x0235

#define IPMI_FUJITSU_PRODUCT_ID_TX200S5             0x0240
#define IPMI_FUJITSU_PRODUCT_ID_TX300S5             0x0241
#define IPMI_FUJITSU_PRODUCT_ID_RX200S5             0x0242
#define IPMI_FUJITSU_PRODUCT_ID_RX300S5             0x0243
#define IPMI_FUJITSU_PRODUCT_ID_BX620S5             0x0244
#define IPMI_FUJITSU_PRODUCT_ID_RX100S6             0x0245
#define IPMI_FUJITSU_PRODUCT_ID_TX150S7             0x0246
#define IPMI_FUJITSU_PRODUCT_ID_BX960S1             0x0254
#define IPMI_FUJITSU_PRODUCT_ID_BX924S1             0x0255
#define IPMI_FUJITSU_PRODUCT_ID_BX920S1             0x0256
#define IPMI_FUJITSU_PRODUCT_ID_BX922S1             0x0257
#define IPMI_FUJITSU_PRODUCT_ID_RX600S5             0x0258

#define IPMI_FUJITSU_PRODUCT_ID_TX200S6             0x0260
#define IPMI_FUJITSU_PRODUCT_ID_TX300S6             0x0261
#define IPMI_FUJITSU_PRODUCT_ID_RX200S6             0x0262
#define IPMI_FUJITSU_PRODUCT_ID_RX300S6             0x0263

/******************************************* 
 * HP                                      *
 *******************************************/

#define IPMI_HP_PRODUCT_ID_PROLIANT_DL160_G8 8192

/*******************************************
 * Intel                                   *
 *******************************************/

#define IPMI_INTEL_PRODUCT_ID_SR870BN4 256
#define IPMI_INTEL_PRODUCT_ID_TIGER4   IPMI_INTEL_PRODUCT_ID_SR870BN4

#define IPMI_INTEL_PRODUCT_ID_S5500WB  62
#define IPMI_INTEL_PRODUCT_ID_SR1625   62

/* Quanta motherboard, but listed under a Intel manufacturer ID, why?? */
#define IPMI_INTEL_PRODUCT_ID_QUANTA_QSSC_S4R 64

#define IPMI_INTEL_PRODUCT_ID_S2600JF  77

#define IPMI_INTEL_PRODUCT_ID_S5000PAL 40

#define IPMI_INTEL_PRODUCT_ID_WINDMILL 2818

#define IPMI_INTEL_PRODUCT_ID_S2600KP  111
#define IPMI_INTEL_PRODUCT_ID_S2600WT2 112
#define IPMI_INTEL_PRODUCT_ID_S2600WTT 112

/* 
 * Intel derived
 */

#define IPMI_CALIFORNIA_DIGITAL_PRODUCT_ID_6440 IPMI_INTEL_PRODUCT_ID_SR870BN4

#define IPMI_PENGUIN_COMPUTING_PRODUCT_ID_RELION_700 IPMI_INTEL_PRODUCT_ID_S5500WB

#define IPMI_APPRO_PRODUCT_ID_512X IPMI_INTEL_PRODUCT_ID_S2600JF

#define IPMI_APPRO_PRODUCT_ID_QG812X_CN IPMI_INTEL_PRODUCT_ID_QUANTA_QSSC_S4R

#define IPMI_QUANTA_PRODUCT_ID_WINTERFELL IPMI_INTEL_PRODUCT_ID_WINDMILL

#define IPMI_WIWYNN_PRODUCT_ID_WINDMILL IPMI_INTEL_PRODUCT_ID_WINDMILL

/*******************************************
 * IBM                                     *
 *******************************************/

#define IPMI_IBM_PRODUCT_ID_X3455 20566
#define IPMI_IBM_PRODUCT_ID_X3755 14

/******************************************* 
 * Inventec                                *
 *******************************************/

#define IPMI_INVENTEC_PRODUCT_ID_5441 51
#define IPMI_INVENTEC_PRODUCT_ID_5442 52

/* 
 * Inventec derived
 */

#define IPMI_DELL_PRODUCT_ID_XANADU_II  IPMI_INVENTEC_PRODUCT_ID_5441
#define IPMI_DELL_PRODUCT_ID_XANADU_III IPMI_INVENTEC_PRODUCT_ID_5442

/******************************************* 
 * Quanta                                *
 *******************************************/
 
#define IPMI_QUANTA_PRODUCT_ID_S99Q 21401

/* 
 * Quanta derived
 */

#define IPMI_DELL_PRODUCT_ID_FS12_TY IPMI_QUANTA_PRODUCT_ID_S99Q

/******************************************* 
 * Sun Microsystems                        *
 *******************************************/

#define IPMI_SUN_MICROSYSTEMS_PRODUCT_ID_X4140 18177

/******************************************* 
 * Supermicro                              *
 *******************************************/

/* Seen in the wild w/ Peppercon IANA number 10437 */
/* achu: there is no product name pattern here, what gives Supermicro? */
#define IPMI_SUPERMICRO_PRODUCT_ID_FOUR_BASE       4
#define IPMI_SUPERMICRO_PRODUCT_ID_X7DBR_3         IPMI_SUPERMICRO_PRODUCT_ID_FOUR_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X7DB8           IPMI_SUPERMICRO_PRODUCT_ID_FOUR_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTN           IPMI_SUPERMICRO_PRODUCT_ID_FOUR_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X7SBI_LN4       IPMI_SUPERMICRO_PRODUCT_ID_FOUR_BASE

#define IPMI_SUPERMICRO_PRODUCT_ID_PEPPERCON_X7DBR_3    IPMI_SUPERMICRO_PRODUCT_ID_X7DBR_3
#define IPMI_SUPERMICRO_PRODUCT_ID_PEPPERCON_X7DB8      IPMI_SUPERMICRO_PRODUCT_ID_X7DB8
#define IPMI_SUPERMICRO_PRODUCT_ID_PEPPERCON_X8DTN      IPMI_SUPERMICRO_PRODUCT_ID_X8DTN
#define IPMI_SUPERMICRO_PRODUCT_ID_PEPPERCON_X7SBI_LN4  IPMI_SUPERMICRO_PRODUCT_ID_X7SBI_LN4

/* Seen in the wild w/ Supermicro workaround IANA number 47488 */
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DT_BASE       43707
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTH           IPMI_SUPERMICRO_PRODUCT_ID_X8DT_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTG           IPMI_SUPERMICRO_PRODUCT_ID_X8DT_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTU           IPMI_SUPERMICRO_PRODUCT_ID_X8DT_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DT3_LN4F      IPMI_SUPERMICRO_PRODUCT_ID_X8DT_BASE
/* achu: X8DTU-6+, why not same as above?  Not sure, possibly created
 * specifically for vendor or vendor changed for themselves.
 */
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTU_6PLUS     1549
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTL_BASE      6
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTL           IPMI_SUPERMICRO_PRODUCT_ID_X8DTL_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTL_3F        IPMI_SUPERMICRO_PRODUCT_ID_X8DTL_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8SIL_F         1541
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SC_BASE       1572
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SCL           IPMI_SUPERMICRO_PRODUCT_ID_X9SC_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SCM           IPMI_SUPERMICRO_PRODUCT_ID_X9SC_BASE
#define IPMI_SUPERMICRO_PRODUCT_ID_X8DTNPLUS_F     1551
#define IPMI_SUPERMICRO_PRODUCT_ID_X8SIE           1037
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SCA_F_O       1585
#define IPMI_SUPERMICRO_PRODUCT_ID_H8DGU_F         43025
#define IPMI_SUPERMICRO_PRODUCT_ID_H8DG6           48145
#define IPMI_SUPERMICRO_PRODUCT_ID_H8DGU           4520
#define IPMI_SUPERMICRO_PRODUCT_ID_X9DRI_LN4F_PLUS 1574

/* Seen in the wild w/ proper IANA number 10876 */
/* defined above: IPMI_SUPERMICRO_PRODUCT_ID_X9SCM */
#define IPMI_SUPERMICRO_PRODUCT_ID_X9DRI_F     1576
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SPU_F_O   1603
#define IPMI_SUPERMICRO_PRODUCT_ID_X9SCM_IIF   1600

/* Seen in the wild w/ Magnum Technologies IANA number 5593 */
#define IPMI_SUPERMICRO_PRODUCT_ID_MAGNUM_TECHNOLOGIES_X8DTL IPMI_SUPERMICRO_PRODUCT_ID_X8DTL

/******************************************* 
 * Wistron                                 *
 *******************************************/

/* achu: don't know original product name, so just using C6220. 
 * Will readjust as needed if learned later. 
 */
#define IPMI_WISTRON_PRODUCT_ID_C6220          131

/* 
 * Wistron derived
 */

#define IPMI_DELL_PRODUCT_ID_POWEREDGE_C6220   IPMI_WISTRON_PRODUCT_ID_C6220

#ifdef __cplusplus
}
#endif

#endif /* IPMI_PRODUCT_ID_SPEC_H */
