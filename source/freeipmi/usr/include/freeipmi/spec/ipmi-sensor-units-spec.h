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

#ifndef IPMI_SENSOR_UNITS_SPEC_H
#define IPMI_SENSOR_UNITS_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPMI_SENSOR_UNIT_UNSPECIFIED             0
#define IPMI_SENSOR_UNIT_DEGREES_C               1
#define IPMI_SENSOR_UNIT_DEGREES_F               2
#define IPMI_SENSOR_UNIT_DEGREES_K               3
#define IPMI_SENSOR_UNIT_VOLTS                   4
#define IPMI_SENSOR_UNIT_AMPS                    5
#define IPMI_SENSOR_UNIT_WATTS                   6
#define IPMI_SENSOR_UNIT_JOULES                  7
#define IPMI_SENSOR_UNIT_COULOMBS                8
#define IPMI_SENSOR_UNIT_VA                      9
#define IPMI_SENSOR_UNIT_NITS                   10
#define IPMI_SENSOR_UNIT_LUMEN                  11
#define IPMI_SENSOR_UNIT_LUX                    12
#define IPMI_SENSOR_UNIT_CANDELA                13
#define IPMI_SENSOR_UNIT_KPA                    14
#define IPMI_SENSOR_UNIT_PSI                    15
#define IPMI_SENSOR_UNIT_NEWTON                 16
#define IPMI_SENSOR_UNIT_CFM                    17
#define IPMI_SENSOR_UNIT_RPM                    18
#define IPMI_SENSOR_UNIT_HZ                     19
#define IPMI_SENSOR_UNIT_MICROSECOND            20
#define IPMI_SENSOR_UNIT_MILLISECOND            21
#define IPMI_SENSOR_UNIT_SECOND                 22
#define IPMI_SENSOR_UNIT_MINUTE                 23
#define IPMI_SENSOR_UNIT_HOUR                   24
#define IPMI_SENSOR_UNIT_DAY                    25
#define IPMI_SENSOR_UNIT_WEEK                   26
#define IPMI_SENSOR_UNIT_MIL                    27
#define IPMI_SENSOR_UNIT_INCHES                 28
#define IPMI_SENSOR_UNIT_FEET                   29
#define IPMI_SENSOR_UNIT_CU_IN                  30
#define IPMI_SENSOR_UNIT_CU_FEET                31
#define IPMI_SENSOR_UNIT_MM                     32
#define IPMI_SENSOR_UNIT_CM                     33
#define IPMI_SENSOR_UNIT_M                      34
#define IPMI_SENSOR_UNIT_CU_CM                  35
#define IPMI_SENSOR_UNIT_CU_M                   36
#define IPMI_SENSOR_UNIT_LITERS                 37
#define IPMI_SENSOR_UNIT_FLUID_OUNCE            38
#define IPMI_SENSOR_UNIT_RADIANS                39
#define IPMI_SENSOR_UNIT_STERADIANS             40
#define IPMI_SENSOR_UNIT_REVOLUTIONS            41
#define IPMI_SENSOR_UNIT_CYCLES                 42
#define IPMI_SENSOR_UNIT_GRAVITIES              43
#define IPMI_SENSOR_UNIT_OUNCE                  44
#define IPMI_SENSOR_UNIT_POUND                  45
#define IPMI_SENSOR_UNIT_FT_LB                  46
#define IPMI_SENSOR_UNIT_OZ_IN                  47
#define IPMI_SENSOR_UNIT_GAUSS                  48
#define IPMI_SENSOR_UNIT_GILBERTS               49
#define IPMI_SENSOR_UNIT_HENRY                  50
#define IPMI_SENSOR_UNIT_MILLIHENRY             51
#define IPMI_SENSOR_UNIT_FARAD                  52
#define IPMI_SENSOR_UNIT_MICROFARAD             53
#define IPMI_SENSOR_UNIT_OHMS                   54
#define IPMI_SENSOR_UNIT_SIEMENS                55
#define IPMI_SENSOR_UNIT_MOLE                   56
#define IPMI_SENSOR_UNIT_BECQUEREL              57
#define IPMI_SENSOR_UNIT_PPM                    58
#define IPMI_SENSOR_UNIT_RESERVED               59
#define IPMI_SENSOR_UNIT_DECIBELS               60
#define IPMI_SENSOR_UNIT_DBA                    61
#define IPMI_SENSOR_UNIT_DBC                    62
#define IPMI_SENSOR_UNIT_GRAY                   63
#define IPMI_SENSOR_UNIT_SIEVERT                64
#define IPMI_SENSOR_UNIT_COLOR_TEMP_DEG_K       65
#define IPMI_SENSOR_UNIT_BIT                    66
#define IPMI_SENSOR_UNIT_KILOBIT                67
#define IPMI_SENSOR_UNIT_MEGABIT                68
#define IPMI_SENSOR_UNIT_GIGABIT                69
#define IPMI_SENSOR_UNIT_BYTE                   70
#define IPMI_SENSOR_UNIT_KILOBYTE               71
#define IPMI_SENSOR_UNIT_MEGABYTE               72
#define IPMI_SENSOR_UNIT_GIGABYTE               73
#define IPMI_SENSOR_UNIT_WORD                   74
#define IPMI_SENSOR_UNIT_DWORD                  75
#define IPMI_SENSOR_UNIT_QWORD                  76
#define IPMI_SENSOR_UNIT_LINE                   77
#define IPMI_SENSOR_UNIT_HIT                    78
#define IPMI_SENSOR_UNIT_MISS                   79
#define IPMI_SENSOR_UNIT_RETRY                  80
#define IPMI_SENSOR_UNIT_RESET                  81
#define IPMI_SENSOR_UNIT_OVERRUN_OVERFLOW       82
#define IPMI_SENSOR_UNIT_UNDERRUN               83
#define IPMI_SENSOR_UNIT_COLLISION              84
#define IPMI_SENSOR_UNIT_PACKETS                85
#define IPMI_SENSOR_UNIT_MESSAGES               86
#define IPMI_SENSOR_UNIT_CHARACTERS             87
#define IPMI_SENSOR_UNIT_ERROR                  88
#define IPMI_SENSOR_UNIT_CORRECTABLE_ERROR      89
#define IPMI_SENSOR_UNIT_UNCORRECTABLE_ERROR    90
#define IPMI_SENSOR_UNIT_FATAL_ERROR            91
#define IPMI_SENSOR_UNIT_GRAMS                  92

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SENSOR_UNIT_VALID(__sensor_unit)            \
  (((__sensor_unit + 1) >= (IPMI_SENSOR_UNIT_UNSPECIFIED + 1) \
    && (__sensor_unit) <= IPMI_SENSOR_UNIT_GRAMS) ? 1 : 0)

#define IPMI_SENSOR_RATE_UNIT_NONE               0
#define IPMI_SENSOR_RATE_UNIT_PER_US             1
#define IPMI_SENSOR_RATE_UNIT_PER_MS             2
#define IPMI_SENSOR_RATE_UNIT_PER_S              3
#define IPMI_SENSOR_RATE_UNIT_PER_MINUTE         4
#define IPMI_SENSOR_RATE_UNIT_PER_HOUR           5
#define IPMI_SENSOR_RATE_UNIT_PER_DAY            6

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_SENSOR_RATE_UNIT_VALID(__sensor_rate_unit)     \
  (((__sensor_rate_unit + 1) >= (IPMI_SENSOR_RATE_UNIT_NONE + 1) \
    && (__sensor_rate_unit) <= IPMI_SENSOR_RATE_UNIT_PER_DAY) ? 1 : 0)

extern const char *const ipmi_sensor_units[];
extern const char *const ipmi_sensor_units_abbreviated[];
extern const char *const ipmi_sensor_rate_units[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_SENSOR_UNITS_SPEC_H */
