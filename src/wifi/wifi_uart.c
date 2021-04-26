/**
  Company:
    Microchip Technology Inc.

  File Name:
    uart.c

  Summary:
    

  Description:
    UART access routines for C18 and C30

 */

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) <2014> released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#define __UART_C_

#include "tcpip.h"
#include "c_wifi.h"

#if defined(STACK_USE_UART)

#ifdef WIFI_STACK_USE_USB
	#include "serial_usb.h"
#endif

#ifdef WIFI_STACK_USE_UART1
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
#endif

void putcUART(char ch) {
    putChar_usb(ch);
}

void putrsUART(const char *str) {
	while (*str != 0) {
		#ifdef WIFI_STACK_USE_USB
			putChar_usb(*str);
		#endif
		str++;
	}
}

void putsUART(const char* buffer) {
	while (*buffer != 0) {
		#ifdef WIFI_STACK_USE_USB
			putChar_usb(*buffer);
		#endif
		buffer++;
	}
}

#endif // STACK_USE_UART
