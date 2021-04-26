/*****************************************************************************
  AUTO-GENERATED CODE:  Microchip MPFS Generator version: 2.2.2

  Microchip TCP/IP Stack Application Demo

  Company:
    Microchip Technology Inc.

  File Name:
    mpfs_img2.c

  Summary:
    NOT FOR HAND MODIFICATION.
    This file is automatically generated by the MPFS Generator Utility.
    ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR.
    Generated Mo Apr 26 2021 09:05:02 

  Description:
    Defines an MPFS2 image to be stored in program memory.
 *****************************************************************************/

// DOM-IGNORE-BEGIN
/*****************************************************************************
Software License Agreement
Copyright(c) 2014 Microchip Technology Inc. All rights reserved.
Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital
signal controller that is integrated into your product or third party
product (pursuant to the sublicense terms in the accompanying license
agreement).

You should refer to the license agreement accompanying this Software
for additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
OR OTHER SIMILAR COSTS.
 *****************************************************************************/
// DOM-IGNORE-END

#define __MPFS_IMG2_C_

#include "system_config.h"

#if !defined(MPFS_USE_EEPROM) && !defined(MPFS_USE_SPI_FLASH)
#include "tcpip.h"

#if defined(STACK_USE_MPFS2)

/**************************************
 * MPFS2 Image Data
 **************************************/
#define DATACHUNK000000 \
	0x4d,0x50,0x46,0x53,0x02,0x01,0x02,0x00,0x0a,0xa3,0xff,0xff,0x38,0x00,0x00,0x00, /* MPFS........8... */ \
	0x43,0x00,0x00,0x00,0x96,0x02,0x00,0x00,0xdc,0x65,0x86,0x60,0x00,0x00,0x00,0x00, /* C........e.`.... */ \
	0x02,0x00,0x42,0x00,0x00,0x00,0xd9,0x02,0x00,0x00,0x38,0x00,0x00,0x00,0xdc,0x65, /* ..B.......8....e */ \
	0x86,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x69,0x6e,0x64,0x65,0x78,0x2e,0x68,0x74, /* .`......index.ht */ \
	0x6d,0x00,0x00,0x3c,0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,0x09,0x3c,0x62,0x6f,0x64, /* m..<html>...<bod */ \
	0x79,0x3e,0x0d,0x0a,0x09,0x09,0x3c,0x68,0x31,0x3e,0x4d,0x79,0x20,0x46,0x69,0x72, /* y>....<h1>My Fir */ \
	0x73,0x74,0x20,0x48,0x65,0x61,0x64,0x69,0x6e,0x67,0x3c,0x2f,0x68,0x31,0x3e,0x0d, /* st Heading</h1>. */ \
	0x0a,0x09,0x09,0x3c,0x70,0x3e,0x4d,0x79,0x20,0x66,0x69,0x72,0x73,0x74,0x20,0x70, /* ...<p>My first p */ \
	0x61,0x72,0x61,0x67,0x72,0x61,0x70,0x68,0x2e,0x3c,0x2f,0x70,0x3e,0x0d,0x0a,0x09, /* aragraph.</p>... */ \
	0x09,0x54,0x65,0x6d,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x65,0x3a,0x20,0x7e,0x4d, /* .Temperature: ~M */ \
	0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65,0x54,0x65,0x6d,0x70,0x65,0x72,0x61, /* yVariableTempera */ \
	0x74,0x75,0x72,0x65,0x7e,0x20,0x43,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09,0x50, /* ture~ C<br>....P */ \
	0x72,0x65,0x73,0x73,0x75,0x72,0x65,0x3a,0x20,0x7e,0x4d,0x79,0x56,0x61,0x72,0x69, /* ressure: ~MyVari */ \
	0x61,0x62,0x6c,0x65,0x50,0x72,0x65,0x73,0x73,0x75,0x72,0x65,0x7e,0x20,0x68,0x50, /* ablePressure~ hP */ \
	0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09,0x48,0x75,0x6d,0x69,0x64,0x69,0x74,0x79, /* <br>....Humidity */ \
	0x3a,0x20,0x7e,0x4d,0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65,0x48,0x75,0x6d, /* : ~MyVariableHum */ \
	0x69,0x64,0x69,0x74,0x79,0x7e,0x20,0x25,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09, /* idity~ %<br>.... */ \
	0x43,0x4f,0x32,0x3a,0x20,0x7e,0x4d,0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65, /* CO2: ~MyVariable */ \
	0x43,0x4f,0x32,0x7e,0x20,0x70,0x70,0x6d,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09, /* CO2~ ppm<br>.... */ \
	0x4c,0x69,0x50,0x6f,0x20,0x56,0x6f,0x6c,0x74,0x61,0x67,0x65,0x3a,0x20,0x7e,0x4d, /* LiPo Voltage: ~M */ \
	0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65,0x4c,0x69,0x50,0x6f,0x56,0x6f,0x6c, /* yVariableLiPoVol */ \
	0x74,0x61,0x67,0x65,0x7e,0x20,0x56,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09,0x4c, /* tage~ V<br>....L */ \
	0x69,0x50,0x6f,0x20,0x50,0x65,0x72,0x63,0x65,0x6e,0x74,0x61,0x67,0x65,0x3a,0x20, /* iPo Percentage:  */ \
	0x7e,0x4d,0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65,0x4c,0x69,0x50,0x6f,0x50, /* ~MyVariableLiPoP */ \
	0x65,0x72,0x63,0x65,0x6e,0x74,0x61,0x67,0x65,0x7e,0x20,0x25,0x3c,0x62,0x72,0x3e, /* ercentage~ %<br> */ \
	0x0d,0x0a,0x09,0x09,0x42,0x6f,0x6f,0x74,0x6c,0x6f,0x61,0x64,0x65,0x72,0x20,0x54, /* ....Bootloader T */ \
	0x72,0x69,0x67,0x67,0x65,0x72,0x20,0x43,0x6f,0x75,0x6e,0x74,0x65,0x72,0x3a,0x20, /* rigger Counter:  */ \
	0x7e,0x4d,0x79,0x56,0x61,0x72,0x69,0x61,0x62,0x6c,0x65,0x42,0x6f,0x6f,0x74,0x6c, /* ~MyVariableBootl */ \
	0x6f,0x61,0x64,0x65,0x72,0x54,0x72,0x69,0x67,0x67,0x65,0x72,0x7e,0x3c,0x62,0x72, /* oaderTrigger~<br */ \
	0x3e,0x0d,0x0a,0x09,0x09,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x09,0x09,0x3c,0x66,0x6f, /* >....<br>....<fo */ \
	0x72,0x6d,0x20,0x6d,0x65,0x74,0x68,0x6f,0x64,0x3d,0x22,0x67,0x65,0x74,0x22,0x20, /* rm method="get"  */ \
	0x61,0x63,0x74,0x69,0x6f,0x6e,0x3d,0x22,0x69,0x6e,0x64,0x65,0x78,0x2e,0x68,0x74, /* action="index.ht */ \
	0x6d,0x22,0x3e,0x0d,0x0a,0x09,0x09,0x09,0x3c,0x6c,0x61,0x62,0x65,0x6c,0x20,0x66, /* m">.....<label f */ \
	0x6f,0x72,0x3d,0x22,0x66,0x6e,0x61,0x6d,0x65,0x22,0x3e,0x42,0x6f,0x6f,0x74,0x6c, /* or="fname">Bootl */ \
	0x6f,0x61,0x64,0x65,0x72,0x20,0x74,0x72,0x69,0x67,0x67,0x65,0x72,0x20,0x69,0x73, /* oader trigger is */ \
	0x20,0x42,0x4f,0x4f,0x54,0x4c,0x4f,0x41,0x44,0x45,0x52,0x3a,0x3c,0x2f,0x6c,0x61, /*  BOOTLOADER:</la */ \
	0x62,0x65,0x6c,0x3e,0x0d,0x0a,0x09,0x09,0x09,0x3c,0x69,0x6e,0x70,0x75,0x74,0x20, /* bel>.....<input  */ \
	0x74,0x79,0x70,0x65,0x3d,0x22,0x74,0x65,0x78,0x74,0x22,0x20,0x69,0x64,0x3d,0x22, /* type="text" id=" */ \
	0x66,0x6e,0x61,0x6d,0x65,0x22,0x20,0x6e,0x61,0x6d,0x65,0x3d,0x22,0x66,0x6e,0x61, /* fname" name="fna */ \
	0x6d,0x65,0x22,0x3e,0x0d,0x0a,0x09,0x09,0x09,0x3c,0x69,0x6e,0x70,0x75,0x74,0x20, /* me">.....<input  */ \
	0x74,0x79,0x70,0x65,0x3d,0x22,0x73,0x75,0x62,0x6d,0x69,0x74,0x22,0x20,0x76,0x61, /* type="submit" va */ \
	0x6c,0x75,0x65,0x3d,0x22,0x42,0x6f,0x6f,0x74,0x6c,0x6f,0x61,0x64,0x65,0x72,0x22, /* lue="Bootloader" */ \
	0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x6d,0x61,0x72,0x67,0x69,0x6e,0x2d,0x74, /*  style="margin-t */ \
	0x6f,0x70,0x3a,0x35,0x70,0x78,0x3b,0x22,0x3e,0x0d,0x0a,0x09,0x09,0x3c,0x2f,0x66, /* op:5px;">....</f */ \
	0x6f,0x72,0x6d,0x3e,0x0d,0x0a,0x09,0x3c,0x2f,0x62,0x6f,0x64,0x79,0x3e,0x0d,0x0a, /* orm>...</body>.. */ \
	0x3c,0x2f,0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,0x5b,0x00,0x00,0x00,0x00,0x00,0x00, /* </html>..[...... */ \
	0x00,0x86,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xaf,0x00,0x00,0x00,0x02,0x00,0x00, /* ................ */ \
	0x00,0xd2,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0xfb,0x00,0x00,0x00,0x04,0x00,0x00, /* ................ */ \
	0x00,0x2d,0x01,0x00,0x00,0x05,0x00,0x00,0x00,0x6d,0x01,0x00,0x00,0x06,0x00,0x00, /* .-.......m...... */ \
	0x00                                                                             /* .                */

/**************************************
 * MPFS2 C linkable symbols
 **************************************/
// For old C18 compiler, these are split into seperate arrays because it speeds up compilation a lot.  
// For other compilers, the entire data array must be defined as a single variable to 
// ensure that the linker does not reorder the data chunks in Flash when compiler 
// optimizations are turned on.
// Now we are using the new XC8 compiler, and we simply keep this tradition here.
#if defined(__XC8)
	ROM uint8_t MPFS_Start[] = {DATACHUNK000000};
#else
	ROM uint8_t MPFS_Start[] = {DATACHUNK000000};
#endif

/**************************************************************
 * End of MPFS
 **************************************************************/

#endif // #if defined(STACK_USE_MPFS2)

#endif // #if !defined(MPFS_USE_EEPROM) && !defined(MPFS_USE_SPI_FLASH)