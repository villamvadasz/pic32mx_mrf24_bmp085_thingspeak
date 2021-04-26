/*********************************************************************
 *
 *                  PIC32 Boot Loader
 *
 *********************************************************************
 * FileName:        Bootloader.c
 * Dependencies:
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id:  $
 * $Name: $
 *
 **********************************************************************/
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "Bootloader.h"
#include "Framework.h"
#include <stdlib.h>
#include <plib.h>

#define BOOTLOADER_TRIGGER 0xDEAD1234

typedef struct _ExceptionLog {
	unsigned int _excep_code;
	unsigned int _excep_addr;
	unsigned int magicWord;
} ExceptionLog;

#pragma GCC diagnostic error "-w"
volatile unsigned int bootloader_request_A __attribute__ ((persistent, address(0xA0000F00)));
volatile unsigned int bootloader_request_B __attribute__ ((persistent, address(0xA0000F10)));
volatile unsigned int bootloader_was_reset_called __attribute__ ((persistent, address(0xA0000F20)));
volatile ExceptionLog exceptionLog[16] __attribute__ ((persistent, address(0xA0000200)));
#pragma GCC diagnostic pop

#ifndef BOOTLOADER_IS_AN_UPDATER_APPLICATION
	#ifdef __32MX440F256H__
		#ifdef XTAL_8MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_10MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = OFF			// Not possible to generate USB clock from 10MHz
			#pragma config FPLLMUL  = MUL_16
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz. Not possible
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_20MHZ
			#pragma config POSCMOD  = HS
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config UPLLIDIV = DIV_5			// USB PLL Input Divider. PLL input need 4MHz
			#pragma config FPLLIDIV = DIV_5			// PLL Input Divider. PLL input need 4MHz...5MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#if (PB_DIV == 2)
			#pragma config FPBDIV   = DIV_2
		#endif	
		#if (PB_DIV == 4)
			#pragma config FPBDIV   = DIV_4
		#endif	
		#ifdef INT_OSC_8MHZ
			#ifndef XTAL_8MHZ
				#error Internal 8MHz need 8MHz configuration (XTAL_8MHZ)
			#endif
			#pragma config FNOSC = FRCPLL
		#else 
			#pragma config FNOSC = PRIPLL
		#endif
		#pragma config FWDTEN   = OFF				// Watchdog Timer
		#pragma config WDTPS	= PS1				// Watchdog Timer Postscale
		#pragma config FCKSM	= CSECMD			// Clock Switching & Fail Safe Clock Monitor
		#pragma config OSCIOFNC = OFF				// CLKO Enable
		#pragma config IESO	    = OFF				// Internal/External Switch-over
		#pragma config FSOSCEN  = OFF				// Secondary Oscillator Enable (KLO was off)
		#pragma config CP	    = OFF				// Code Protect
		#pragma config BWP	    = OFF				// Boot Flash Write Protect
		#pragma config PWP	    = OFF				// Program Flash Write Protect
	#endif
	#ifdef __32MX470F512H__
		// DEVCFG3
		// USERID = No Setting
		#pragma config FSRSSEL = PRIORITY_7			// Peripheral Module Disable Configuration (Allow only one reconfiguration)
		#pragma config PMDL1WAY = OFF				// Peripheral Module Disable Configuration (Allow only one reconfiguration)
		#pragma config IOL1WAY = OFF				// Peripheral Pin Select Configuration (Allow multiple reconfigurations)
		#pragma config FUSBIDIO = ON				// USB USBID Selection (Controlled by the USB Module)
		#pragma config FVBUSONIO = ON

		// DEVCFG2
		#ifdef XTAL_8MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_10MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = OFF			// Not possible to generate USB clock from 10MHz
			#pragma config FPLLMUL  = MUL_16
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz. Not possible
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_20MHZ
			#pragma config POSCMOD  = HS
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config UPLLIDIV = DIV_5			// USB PLL Input Divider. PLL input need 4MHz
			#pragma config FPLLIDIV = DIV_5			// PLL Input Divider. PLL input need 4MHz...5MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#if (PB_DIV == 2)
			#pragma config FPBDIV   = DIV_2
		#endif	
		#if (PB_DIV == 4)
			#pragma config FPBDIV   = DIV_4
		#endif	
		#ifdef INT_OSC_8MHZ
			#ifndef XTAL_8MHZ
				#error Internal 8MHz need 8MHz configuration (XTAL_8MHZ)
			#endif
			#pragma config FNOSC = FRCPLL
		#else 
			#pragma config FNOSC = PRIPLL
		#endif

		// DEVCFG1
		#pragma config FSOSCEN  = OFF				// Secondary Oscillator Enable (Disable SOSC)
		#pragma config IESO     = OFF				// Internal/External Switch Over (Enabled)
		#pragma config OSCIOFNC = OFF				// CLKO Output Signal Active on the OSCO Pin (Disabled)
		#pragma config FCKSM    = CSECMD			// Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
		#pragma config WDTPS    = PS1048576			// Watchdog Timer Postscaler (1:1048576)
		#pragma config WINDIS   = OFF
		#pragma config FWDTEN   = OFF
		#pragma config FWDTWINSZ = WINSZ_25

		// DEVCFG0
		#pragma config DEBUG = OFF
		#pragma config JTAGEN = OFF
		#pragma config ICESEL = ICS_PGx2
		#pragma config PWP = OFF
		#pragma config BWP = OFF
		#pragma config CP = OFF
	#endif
	#ifdef __32MX460F512L__
		#ifdef XTAL_8MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_10MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = OFF			// Not possible to generate USB clock from 10MHz
			#pragma config FPLLMUL  = MUL_16
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz. Not possible
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_20MHZ
			#pragma config POSCMOD  = HS
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config UPLLIDIV = DIV_5			// USB PLL Input Divider. PLL input need 4MHz
			#pragma config FPLLIDIV = DIV_5			// PLL Input Divider. PLL input need 4MHz...5MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#if (PB_DIV == 2)
			#pragma config FPBDIV   = DIV_2
		#endif	
		#if (PB_DIV == 4)
			#pragma config FPBDIV   = DIV_4
		#endif	
		#ifdef INT_OSC_8MHZ
			#ifndef XTAL_8MHZ
				#error Internal 8MHz need 8MHz configuration (XTAL_8MHZ)
			#endif
			#pragma config FNOSC = FRCPLL
		#else 
			#pragma config FNOSC = PRIPLL
		#endif
		#pragma config FWDTEN   = OFF				// Watchdog Timer
		#pragma config WDTPS	= PS1				// Watchdog Timer Postscale
		#pragma config FCKSM	= CSECMD			// Clock Switching & Fail Safe Clock Monitor
		#pragma config OSCIOFNC = OFF				// CLKO Enable
		#pragma config IESO	    = OFF				// Internal/External Switch-over
		#pragma config FSOSCEN  = OFF				// Secondary Oscillator Enable (KLO was off)
		#pragma config CP	    = OFF				// Code Protect
		#pragma config BWP	    = OFF				// Boot Flash Write Protect
		#pragma config PWP	    = OFF				// Program Flash Write Protect
	#endif
	#ifdef __32MX470F512L__
		// DEVCFG3
		// USERID = No Setting
		#pragma config FSRSSEL = PRIORITY_7			// Peripheral Module Disable Configuration (Allow only one reconfiguration)
		#pragma config PMDL1WAY = OFF				// Peripheral Module Disable Configuration (Allow only one reconfiguration)
		#pragma config IOL1WAY = OFF				// Peripheral Pin Select Configuration (Allow multiple reconfigurations)
		#pragma config FUSBIDIO = ON				// USB USBID Selection (Controlled by the USB Module)
		#pragma config FVBUSONIO = ON

		// DEVCFG2
		#ifdef XTAL_8MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_10MHZ
			#pragma config POSCMOD  = XT
			#pragma config UPLLEN   = OFF			// Not possible to generate USB clock from 10MHz
			#pragma config FPLLMUL  = MUL_16
			#pragma config FPLLIDIV = DIV_2			// PLL Input Divider. PLL input need 4MHz...5MHz
			#pragma config UPLLIDIV = DIV_2			// USB PLL Input Divider. PLL input need 4MHz. Not possible
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#ifdef XTAL_20MHZ
			#pragma config POSCMOD  = HS
			#pragma config UPLLEN   = ON
			#pragma config FPLLMUL  = MUL_20
			#pragma config UPLLIDIV = DIV_5			// USB PLL Input Divider. PLL input need 4MHz
			#pragma config FPLLIDIV = DIV_5			// PLL Input Divider. PLL input need 4MHz...5MHz
			#ifdef SYS_FREQ_10MHZ
				#pragma config FPLLODIV = DIV_8
			#endif
			#ifdef SYS_FREQ_20MHZ
				#pragma config FPLLODIV = DIV_4
			#endif
			#ifdef SYS_FREQ_40MHZ
				#pragma config FPLLODIV = DIV_2
			#endif
			#ifdef SYS_FREQ_80MHZ
				#pragma config FPLLODIV = DIV_1
			#endif
		#endif
		#if (PB_DIV == 2)
			#pragma config FPBDIV   = DIV_2
		#endif	
		#if (PB_DIV == 4)
			#pragma config FPBDIV   = DIV_4
		#endif	
		#ifdef INT_OSC_8MHZ
			#ifndef XTAL_8MHZ
				#error Internal 8MHz need 8MHz configuration (XTAL_8MHZ)
			#endif
			#pragma config FNOSC = FRCPLL
		#else 
			#pragma config FNOSC = PRIPLL
		#endif

		// DEVCFG1
		#pragma config FSOSCEN  = OFF				// Secondary Oscillator Enable (Disable SOSC)
		#pragma config IESO     = OFF					// Internal/External Switch Over (Enabled)
		#pragma config OSCIOFNC = OFF				// CLKO Output Signal Active on the OSCO Pin (Disabled)
		#pragma config FCKSM    = CSECMD				// Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
		#pragma config WDTPS    = PS1048576			// Watchdog Timer Postscaler (1:1048576)
		#pragma config WINDIS   = OFF
		#pragma config FWDTEN   = OFF
		#pragma config FWDTWINSZ = WINSZ_25

		// DEVCFG0
		#pragma config DEBUG = OFF
		#pragma config JTAGEN = OFF
		#pragma config ICESEL = ICS_PGx2
		#pragma config PWP = OFF
		#pragma config BWP = OFF
		#pragma config CP = OFF
	#endif
#endif

#define SWITCH_PRESSED 0



#ifdef __cplusplus
extern "C" {
#endif
BOOL CheckTrigger(void);
void JumpToApp(void);
BOOL ValidAppPresent(void);
#ifdef __cplusplus
}
#endif
/********************************************************************
* Function: 	main()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Main entry function. If there is a trigger or 
*				if there is no valid application, the device 
*				stays in firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
INT main(void)
{
	UINT pbClk;

	// Setup configuration
	pbClk = SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
	
	//InitLED();
	
	// Enter firmware upgrade mode if there is a trigger or if the application is not valid
	if(CheckTrigger() || !ValidAppPresent())
	{
		// Initialize the transport layer - UART/USB/Ethernet
		TRANS_LAYER_Init(pbClk);
		
		while(!FRAMEWORK_ExitFirmwareUpgradeMode()) // Be in loop till framework recieves "run application" command from PC
		{
			// Enter firmware upgrade mode.
			// Be in loop, looking for commands from PC
			TRANS_LAYER_Task(); // Run Transport layer tasks
			FRAMEWORK_FrameWorkTask(); // Run frame work related tasks (Handling Rx frame, process frame and so on)
			// Blink LED (Indicates the user that bootloader is running).
		}
		// Close trasnport layer.
		TRANS_LAYER_Close();
	}

	// No trigger + valid application = run application.
	JumpToApp();
	
	return 0;
}			


/********************************************************************
* Function: 	CheckTrigger()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If triggered
				FALSE: No trigger
*
* Side Effects:	None.
*
* Overview: 	Checks if there is a trigger to enter 
				firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
BOOL  CheckTrigger(void)
{
	BOOL result = FALSE;
	#ifdef BOOTLOADER_SWITCH_TRIGGER
		UINT SwitchStatus;
		SwitchStatus = ReadSwitchStatus();
		if(SwitchStatus == SWITCH_PRESSED)
		{
			// Switch is pressed
			result = TRUE;
		}
	#endif
	if ((bootloader_request_A == BOOTLOADER_TRIGGER) && (bootloader_request_B == ~BOOTLOADER_TRIGGER)) {
		result = TRUE;
	}
	#ifdef BOOTLOADER_DELAYED_AUTOAPPLICATION
		//Force trigger always
		result = TRUE;
	#endif
	return result;
}	


/********************************************************************
* Function: 	JumpToApp()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Jumps to application.
*
*			
* Note:		 	None.
********************************************************************/
void JumpToApp(void)
{	
	void (*fptr)(void);
	//Set the request explicit to be able to detect when application is not running properly and does unwanted resets
	bootloader_request_A = BOOTLOADER_TRIGGER;
	bootloader_request_B = ~BOOTLOADER_TRIGGER;
	fptr = (void (*)(void))USER_APP_RESET_ADDRESS;
	#ifdef BOOTLOADER_IS_AN_UPDATER_APPLICATION
		SoftReset();
	#else
		fptr();
	#endif
}	


/********************************************************************
* Function: 	ValidAppPresent()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If application is valid.
*
* Side Effects:	None.
*
* Overview: 	Logic: Check application vector has 
				some value other than "0xFFFFFFFF"
*
*			
* Note:		 	None.
********************************************************************/
BOOL ValidAppPresent(void)
{
	DWORD *AppPtr;
	AppPtr = (DWORD *)USER_APP_RESET_ADDRESS;
	if(*AppPtr == 0xFFFFFFFF)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}			


/*********************End of File************************************/


