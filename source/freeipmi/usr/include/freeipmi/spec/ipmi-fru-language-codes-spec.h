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
/*****************************************************************************\
 *  Copyright (C) 2007-2015 Lawrence Livermore National Security, LLC.
 *  Copyright (C) 2007 The Regents of the University of California.
 *  Produced at Lawrence Livermore National Laboratory (cf, DISCLAIMER).
 *  Written by Albert Chu <chu11@llnl.gov>
 *  UCRL-CODE-232183
 *
 *  This file is part of Ipmi-fru, a tool used for retrieving
 *  motherboard field replaceable unit (FRU) information. For details,
 *  see http://www.llnl.gov/linux/.
 *
 *  Ipmi-fru is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  Ipmi-fru is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Ipmi-fru.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/

#ifndef IPMI_FRU_LANGUAGE_CODES_SPEC_H
#define IPMI_FRU_LANGUAGE_CODES_SPEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <freeipmi/fiid/fiid.h>

/*
 * achu:
 *
 * Not in IPMI spec.  In "Platform Management FRU Information Storage
 * Definition" document.
 */

#define IPMI_FRU_LANGUAGE_CODE_ENGLISH_LEGACY       0
#define IPMI_FRU_LANGUAGE_CODE_AFAR                 1
#define IPMI_FRU_LANGUAGE_CODE_ABKHAZIAN            2
#define IPMI_FRU_LANGUAGE_CODE_AFRIKAANS            3
#define IPMI_FRU_LANGUAGE_CODE_AMHARIC              4
#define IPMI_FRU_LANGUAGE_CODE_ARABIC               5
#define IPMI_FRU_LANGUAGE_CODE_ASSAMESE             6
#define IPMI_FRU_LANGUAGE_CODE_AYMARA               7
#define IPMI_FRU_LANGUAGE_CODE_AZERBAIJANI          8
#define IPMI_FRU_LANGUAGE_CODE_BASHKIR              9
#define IPMI_FRU_LANGUAGE_CODE_BYELORUSSIAN         10
#define IPMI_FRU_LANGUAGE_CODE_BULGARIAN            11
#define IPMI_FRU_LANGUAGE_CODE_BIHARI               12
#define IPMI_FRU_LANGUAGE_CODE_BISLAMA              13
#define IPMI_FRU_LANGUAGE_CODE_BENGALI_BANGLA       14
#define IPMI_FRU_LANGUAGE_CODE_TIBETAN              15
#define IPMI_FRU_LANGUAGE_CODE_BRETON               16
#define IPMI_FRU_LANGUAGE_CODE_CATALAN              17
#define IPMI_FRU_LANGUAGE_CODE_CORSICAN             18
#define IPMI_FRU_LANGUAGE_CODE_CZECH                19
#define IPMI_FRU_LANGUAGE_CODE_WELSH                20
#define IPMI_FRU_LANGUAGE_CODE_DANISH               21
#define IPMI_FRU_LANGUAGE_CODE_GERMAN               22
#define IPMI_FRU_LANGUAGE_CODE_BHUTANI              23
#define IPMI_FRU_LANGUAGE_CODE_GREEK                24
#define IPMI_FRU_LANGUAGE_CODE_ENGLISH              25
#define IPMI_FRU_LANGUAGE_CODE_ESPERANTO            26
#define IPMI_FRU_LANGUAGE_CODE_SPANISH              27
#define IPMI_FRU_LANGUAGE_CODE_ESTONIAN             28
#define IPMI_FRU_LANGUAGE_CODE_BASQUE               29
#define IPMI_FRU_LANGUAGE_CODE_PERSIAN              30
#define IPMI_FRU_LANGUAGE_CODE_FINNISH              31
#define IPMI_FRU_LANGUAGE_CODE_FIJI                 32
#define IPMI_FRU_LANGUAGE_CODE_FAEROESE             33
#define IPMI_FRU_LANGUAGE_CODE_FRENCH               34
#define IPMI_FRU_LANGUAGE_CODE_FRISIAN              35
#define IPMI_FRU_LANGUAGE_CODE_IRISH                36
#define IPMI_FRU_LANGUAGE_CODE_SCOTS_GAELIC         37
#define IPMI_FRU_LANGUAGE_CODE_GALICIAN             38
#define IPMI_FRU_LANGUAGE_CODE_GUARANI              39
#define IPMI_FRU_LANGUAGE_CODE_GUJARATI             40
#define IPMI_FRU_LANGUAGE_CODE_HAUSA                41
#define IPMI_FRU_LANGUAGE_CODE_HINDI                42
#define IPMI_FRU_LANGUAGE_CODE_CROATIAN             43
#define IPMI_FRU_LANGUAGE_CODE_HUNGARIAN            44
#define IPMI_FRU_LANGUAGE_CODE_ARMENIAN             45
#define IPMI_FRU_LANGUAGE_CODE_INTERLINGUA          46
#define IPMI_FRU_LANGUAGE_CODE_INTERLINGUE          47
#define IPMI_FRU_LANGUAGE_CODE_INUPIAK              48
#define IPMI_FRU_LANGUAGE_CODE_INDONESIAN           49
#define IPMI_FRU_LANGUAGE_CODE_ICELANDIC            50
#define IPMI_FRU_LANGUAGE_CODE_ITALIAN              51
#define IPMI_FRU_LANGUAGE_CODE_HEBREW               52
#define IPMI_FRU_LANGUAGE_CODE_JAPANESE             53
#define IPMI_FRU_LANGUAGE_CODE_YIDDISH              54
#define IPMI_FRU_LANGUAGE_CODE_JAVANESE             55
#define IPMI_FRU_LANGUAGE_CODE_GEORGIAN             56
#define IPMI_FRU_LANGUAGE_CODE_KAZAKH               57
#define IPMI_FRU_LANGUAGE_CODE_GREENLANDIC          58
#define IPMI_FRU_LANGUAGE_CODE_CAMBODIAN            59
#define IPMI_FRU_LANGUAGE_CODE_KANNADA              60
#define IPMI_FRU_LANGUAGE_CODE_KOREAN               61
#define IPMI_FRU_LANGUAGE_CODE_KASHMIRI             62
#define IPMI_FRU_LANGUAGE_CODE_KURDISH              63
#define IPMI_FRU_LANGUAGE_CODE_KIRGHIZ              64
#define IPMI_FRU_LANGUAGE_CODE_LATIN                65
#define IPMI_FRU_LANGUAGE_CODE_LINGALA              66
#define IPMI_FRU_LANGUAGE_CODE_LAOTHIAN             67
#define IPMI_FRU_LANGUAGE_CODE_LITHUANIAN           68
#define IPMI_FRU_LANGUAGE_CODE_LATVIAN_LETTISH      69
#define IPMI_FRU_LANGUAGE_CODE_MALAGASY             70
#define IPMI_FRU_LANGUAGE_CODE_MAORI                71
#define IPMI_FRU_LANGUAGE_CODE_MACEDONIAN           72
#define IPMI_FRU_LANGUAGE_CODE_MALAYALAM            73
#define IPMI_FRU_LANGUAGE_CODE_MONGOLIAN            74
#define IPMI_FRU_LANGUAGE_CODE_MOLDAVIAN            75
#define IPMI_FRU_LANGUAGE_CODE_MARATHI              76
#define IPMI_FRU_LANGUAGE_CODE_MALAY                77
#define IPMI_FRU_LANGUAGE_CODE_MALTESE              78
#define IPMI_FRU_LANGUAGE_CODE_BURMESE              79
#define IPMI_FRU_LANGUAGE_CODE_NAURU                80
#define IPMI_FRU_LANGUAGE_CODE_NEPALI               81
#define IPMI_FRU_LANGUAGE_CODE_DUTCH                82
#define IPMI_FRU_LANGUAGE_CODE_NORWEGIAN            83
#define IPMI_FRU_LANGUAGE_CODE_OCCITAN              84
#define IPMI_FRU_LANGUAGE_CODE_AFAN_OROMO           85
#define IPMI_FRU_LANGUAGE_CODE_ORIYA                86
#define IPMI_FRU_LANGUAGE_CODE_PUNJABI              87
#define IPMI_FRU_LANGUAGE_CODE_POLISH               88
#define IPMI_FRU_LANGUAGE_CODE_PASHTO_PUSHTO        89
#define IPMI_FRU_LANGUAGE_CODE_PORTUGUESE           90
#define IPMI_FRU_LANGUAGE_CODE_QUECHUA              91
#define IPMI_FRU_LANGUAGE_CODE_RHAETO_ROMANCE       92
#define IPMI_FRU_LANGUAGE_CODE_KIRUNDI              93
#define IPMI_FRU_LANGUAGE_CODE_ROMANIAN             94
#define IPMI_FRU_LANGUAGE_CODE_RUSSIAN              95
#define IPMI_FRU_LANGUAGE_CODE_KINYARWANDA          96
#define IPMI_FRU_LANGUAGE_CODE_SANSKRIT             97
#define IPMI_FRU_LANGUAGE_CODE_SINDHI               98
#define IPMI_FRU_LANGUAGE_CODE_SANGRO               99
#define IPMI_FRU_LANGUAGE_CODE_SERBO_CROATION       100
#define IPMI_FRU_LANGUAGE_CODE_SINGHALESE           101
#define IPMI_FRU_LANGUAGE_CODE_SLOVAK               102
#define IPMI_FRU_LANGUAGE_CODE_SLOVENIAN            103
#define IPMI_FRU_LANGUAGE_CODE_SAMOAN               104
#define IPMI_FRU_LANGUAGE_CODE_SHONA                105
#define IPMI_FRU_LANGUAGE_CODE_SOMALI               106
#define IPMI_FRU_LANGUAGE_CODE_ALBANIAN             107
#define IPMI_FRU_LANGUAGE_CODE_SERBIAN              108
#define IPMI_FRU_LANGUAGE_CODE_SISWATI              109
#define IPMI_FRU_LANGUAGE_CODE_SESOTHO              110
#define IPMI_FRU_LANGUAGE_CODE_SUDANESE             111
#define IPMI_FRU_LANGUAGE_CODE_SWEDISH              112
#define IPMI_FRU_LANGUAGE_CODE_SWAHILI              113
#define IPMI_FRU_LANGUAGE_CODE_TAMIL                114
#define IPMI_FRU_LANGUAGE_CODE_TELUGU               115
/* Spec has "Tegulu", likely a typo */
#define IPMI_FRU_LANGUAGE_CODE_TEGULU               IPMI_FRU_LANGUAGE_CODE_TELUGU
#define IPMI_FRU_LANGUAGE_CODE_TAJIK                116
#define IPMI_FRU_LANGUAGE_CODE_THAI                 117
#define IPMI_FRU_LANGUAGE_CODE_TIGRINYA             118
#define IPMI_FRU_LANGUAGE_CODE_TURKMEN              119
#define IPMI_FRU_LANGUAGE_CODE_TAGALOG              120
#define IPMI_FRU_LANGUAGE_CODE_SETSWANA             121
#define IPMI_FRU_LANGUAGE_CODE_TONGA                122
#define IPMI_FRU_LANGUAGE_CODE_TURKISH              123
#define IPMI_FRU_LANGUAGE_CODE_TSONGA               124
#define IPMI_FRU_LANGUAGE_CODE_TATAR                125
#define IPMI_FRU_LANGUAGE_CODE_TWI                  126
#define IPMI_FRU_LANGUAGE_CODE_UKRANIAN             127
#define IPMI_FRU_LANGUAGE_CODE_URDU                 128
#define IPMI_FRU_LANGUAGE_CODE_UZBEK                129
#define IPMI_FRU_LANGUAGE_CODE_VIETNAMESE           130
#define IPMI_FRU_LANGUAGE_CODE_VOLAPUK              131
#define IPMI_FRU_LANGUAGE_CODE_WOLOF                132
#define IPMI_FRU_LANGUAGE_CODE_XHOSA                133
#define IPMI_FRU_LANGUAGE_CODE_YORUBA               134
#define IPMI_FRU_LANGUAGE_CODE_CHINESE              135
#define IPMI_FRU_LANGUAGE_CODE_ZULU                 136

/* To avoid gcc warnings, add +1 in comparison */
#define IPMI_FRU_LANGUAGE_CODE_VALID(__language_code)          \
  (((__language_code + 1) >= (IPMI_FRU_LANGUAGE_CODE_ENGLISH_LEGACY + 1) \
    && (__language_code) <= IPMI_FRU_LANGUAGE_CODE_ZULU) ? 1 : 0)

extern const char *const ipmi_fru_language_codes[];

#ifdef __cplusplus
}
#endif

#endif /* IPMI_FRU_LANGUAGE_CODES_SPEC_H */
