#ifndef __SYSTEM_CONFIG_H_
#define __SYSTEM_CONFIG_H_

#include <stdio.h>
#include <string.h>

#include "HardwareProfile.h"

#include "tcpip_config.h"

#include "HardwareProfile_PIC32MX_MRF24WB.h"


// Select which UART the STACK_USE_UART and STACK_USE_UART2TCP_BRIDGE
// options will use.  You can change these to U1BRG, U1MODE, etc. if you
// want to use the UART1 module instead of UART2.
#define UBRG                U1BRG
#define UMODE               U1MODE
#define USTA                U1STA
#define BusyUART()          BusyUART1()
#define CloseUART()         CloseUART1()
#define ConfigIntUART(a)    ConfigIntUART1(a)
#define DataRdyUART()       DataRdyUART1()
#define OpenUART(a,b,c)     OpenUART1(a,b,c)
#define ReadUART()          ReadUART1()
#define WriteUART(a)        WriteUART1(a)
#define getsUART(a,b,c)     getsUART1(a,b,c)
#define putsUART(a)         putsUART1(a)
#define getcUART()          getcUART1()
#define putcUART(a)         do { while (BusyUART()); WriteUART(a); while(BusyUART()); } while(0)
#define putrsUART(a)        putrsUART1(a)

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
