#ifndef __HARDWARE_PROFILE_PIC32MX_MRF24WB_H__
#define __HARDWARE_PROFILE_PIC32MX_MRF24WB_H__

	#define UARTTX_TRIS         (TRISDbits.TRISD3)
	#define UARTTX_IO           (PORTDbits.RD3)
	#define UARTRX_TRIS         (TRISDbits.TRISD2)
	#define UARTRX_IO           (PORTDbits.RD2)

	// MRF24W in SPI1 slot
	#define WF_CS_TRIS          (TRISFbits.TRISF0)
	#define WF_CS_IO            (LATFbits.LATF0)
	#define WF_SDI_TRIS         (TRISGbits.TRISG7)
	#define WF_SCK_TRIS         (TRISGbits.TRISG6)
	#define WF_SDO_TRIS         (TRISGbits.TRISG8)
	#define WF_RESET_TRIS       (TRISDbits.TRISD9)
	#define WF_RESET_IO         (LATDbits.LATD9)
	#define WF_INT_TRIS         (TRISDbits.TRISD10) // INT3
	#define WF_INT_IO           (PORTDbits.RD10)
	#define WF_HIBERNATE_TRIS   (TRISFbits.TRISF0)
	#define WF_HIBERNATE_IO     (PORTFbits.RF0)
	#define WF_INT_EDGE         (INTCONbits.INT3EP)
	#define WF_INT_IE           (IEC0bits.INT3IE)
	#define WF_INT_IF           (IFS0bits.INT3IF)
	#define WF_INT_IE_CLEAR     IEC0CLR
	#define WF_INT_IF_CLEAR     IFS0CLR
	#define WF_INT_IE_SET       IEC0SET
	#define WF_INT_IF_SET       IFS0SET
	#define WF_INT_BIT          0x00008000
	#define WF_INT_IPCSET       IPC3SET
	#define WF_INT_IPCCLR       IPC3CLR
	#define WF_INT_IPC_MASK     0xFF000000
	#define WF_INT_IPC_VALUE    0x0C000000
	
	#define WF_SSPBUF           (SPI2BUF)
	#define WF_SPISTAT          (SPI2STAT)
	#define WF_SPISTATbits      (SPI2STATbits)
	#define WF_SPICON1          (SPI2CON)
	#define WF_SPICON1bits      (SPI2CONbits)
	#define WF_SPI_IE_CLEAR     IEC1CLR
	#define WF_SPI_IF_CLEAR     IFS1CLR
	#define WF_SPI_INT_BITS     0x000000E0
	#define WF_SPI_BRG          (SPI2BRG)
	#define WF_MAX_SPI_FREQ     (10000000ul)    // Hz

#endif
