#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_

#include <stdio.h>
#include <string.h>

#include "HardwareProfile.h"

#include "tcpip_config.h"

#include "HardwareProfile_PIC32MX_MRF24WB.h"

//------------------------------------------------------------------------------
// End of /* Hardware I/O pin mappings */


// Compiler information
//------------------------------------------------------------------------------

// Include proper device header file
#include <p32xxxx.h>
#include <plib.h>

// Base RAM and ROM pointer types for given architecture
#define PTR_BASE        unsigned long
#define ROM_PTR_BASE    unsigned long

// Definitions that apply to all except Microchip MPLAB C Compiler for PIC18 MCUs (C18)
#define memcmppgm2ram(a,b,c)    memcmp(a,b,c)
#define strcmppgm2ram(a,b)      strcmp(a,b)
#define memcpypgm2ram(a,b,c)    memcpy(a,b,c)
#define strcpypgm2ram(a,b)      strcpy(a,b)
#define strncpypgm2ram(a,b,c)   strncpy(a,b,c)
#define strstrrampgm(a,b)       strstr(a,b)
#define strlenpgm(a)            strlen(a)
#define strchrpgm(a,b)          strchr(a,b)
#define strcatpgm2ram(a,b)      strcat(a,b)

// Definitions that apply to all 16-bit and 32-bit products
// (PIC24F, PIC24H, dsPIC30F, dsPIC33F, and PIC32)
#define ROM    const

// 32-bit specific defines (PIC32)
#define far
#define FAR
#define Reset()     SoftReset()
#define ClrWdt()    (WDTCONSET = _WDTCON_WDTCLR_MASK)

//------------------------------------------------------------------------------
// End of /* Compiler information */

#endif /* __SYSTEM_CONFIG_H_ */
