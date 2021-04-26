#include <stdlib.h>
#include "wifi.h"
#include "c_wifi.h"

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include <plib.h>
// Include all headers for any enabled TCPIP Stack functions
#include "tcpip.h"
#ifdef WIFI_STACK_USE_RTC
	#include "rtc.h"
#endif

#define WF_MODULE_NUMBER WF_MODULE_ETHERNETTASK

static unsigned short wOriginalAppConfigChecksum; // Checksum of the ROM defaults for AppConfig

static void InitAppConfig(void);
#if defined(WF_CS_TRIS)
void WF_Connect(void);
#if !defined(MRF24WG)
extern bool gRFModuleVer1209orLater;
#endif
#if defined(WF_CS_TRIS)
// Global variables
uint8_t ConnectionProfileID;
#endif
uint8 wifi_is_connected_value = 0;

void DisplayIPValue(IP_ADDR IPVal);

#if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED
tPassphraseReady g_WpsPassphrase;
#endif /* #if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED */
#endif

APP_CONFIG AppConfig;

static ROM uint8_t SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};

__attribute__(( weak )) void init_serial_wifi(void) {}
__attribute__(( weak )) void do_serial_wifi(void) {}
__attribute__(( weak )) void deinit_serial_wifi(void) {}

void init_wifi(void) {
	init_serial_wifi();
	// UART
	#if defined(STACK_USE_UART)
        
        #ifdef WIFI_STACK_USE_UART1
            UARTTX_TRIS = 0;
            UARTRX_TRIS = 1;
            UMODE = 0x8000; // Set UARTEN.  Note: this must be done before setting UTXEN

            USTA = 0x00001400; // RXEN set, TXEN set
            #define CLOSEST_UBRG_VALUE ((GetPeripheralClock() + 8ul * BAUD_RATE) / 16 / BAUD_RATE - 1)
            #define BAUD_ACTUAL (GetPeripheralClock() / 16 / (CLOSEST_UBRG_VALUE + 1))

            #define BAUD_ERROR ((BAUD_ACTUAL > BAUD_RATE) ? BAUD_ACTUAL-BAUD_RATE : BAUD_RATE-BAUD_ACTUAL)
            #define BAUD_ERROR_PRECENT ((BAUD_ERROR * 100 + BAUD_RATE / 2) / BAUD_RATE)
            #if (BAUD_ERROR_PRECENT > 3)
                #warning UART frequency error is worse than 3%
            #elif (BAUD_ERROR_PRECENT > 2)
                #warning UART frequency error is worse than 2%
            #endif

            UBRG = CLOSEST_UBRG_VALUE;
        #endif
	#endif

	#if defined(WF_CS_TRIS)
		WF_CS_IO = 1;
		WF_CS_TRIS = 0;
	#endif
	
	// Initialize the tick.
	TickInit();
#if defined(STACK_USE_MPFS2)
    MPFSInit();
#endif

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();
	
	// Initialize MAC, PHY and Stack.
	StackInit();
	
#if defined(WF_CS_TRIS)
#if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED
    g_WpsPassphrase.valid = false;
#endif /* #if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED */
    WF_Connect();
#endif

} 

void do_wifi(void) {
    static uint32_t dwLastIP = 0;

	do_serial_wifi();
    StackTask();

#if defined(WF_CS_TRIS)
#if !defined(MRF24WG)
    if (gRFModuleVer1209orLater)
#endif
        WiFiTask();
#endif

    // This tasks invokes each of the core stack application tasks
    StackApplications();

#if defined(STACK_USE_SMTP_CLIENT)
        SMTPDemo();
#endif
    
    // If the local IP address has changed (ex: due to DHCP lease change)
    // write the new IP address to the LCD display, UART, and Announce
    // service
    if (dwLastIP != AppConfig.MyIPAddr.Val) {
        dwLastIP = AppConfig.MyIPAddr.Val;

#if defined(STACK_USE_UART)
        putrsUART((ROM char *) "\r\nNew IP Address: ");
#endif

        DisplayIPValue(AppConfig.MyIPAddr);

#if defined(STACK_USE_UART)
        putrsUART((ROM char *) "\r\n");
#endif

#if defined(STACK_USE_ANNOUNCE)
        AnnounceIP();
#endif

    }
    
#if defined (MRF24WG)
#if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED
        if (g_WpsPassphrase.valid) {
            WF_ConvPassphraseToKey(g_WpsPassphrase.passphrase.keyLen, g_WpsPassphrase.passphrase.key,
                    g_WpsPassphrase.passphrase.ssidLen, g_WpsPassphrase.passphrase.ssid);
            WF_SetPSK(g_WpsPassphrase.passphrase.key);
            g_WpsPassphrase.valid = false;
        }
#endif /* #if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED */
#endif /* defined (MRF24WG) */

    if (AppConfig.hibernateFlag == 1) AppConfig.hibernateFlag = 0;

}

void deinit_wifi(void) {
	deinit_serial_wifi();

	WF_SPICON1 = 0;
	
	WF_SPI_IE_CLEAR = WF_SPI_INT_BITS;
	
	T1CON = 0;
	IEC0bits.T1IE = 0;	

	WF_CS_TRIS = 1;
	WF_SDI_TRIS = 1;
	WF_SCK_TRIS = 1;
	WF_SDO_TRIS = 1;
	WF_RESET_TRIS = 1;
	WF_INT_TRIS = 1;
	WF_HIBERNATE_TRIS = 1;
	
	WF_INT_IE_CLEAR = WF_INT_BIT;

	// UART
	#if defined(STACK_USE_UART)
        #ifdef WIFI_STACK_USE_UART1
            UARTTX_TRIS = 1;
            UARTRX_TRIS = 1;
            UMODE = 0x0000; // Set UARTEN.  Note: this must be done before setting UTXEN
        #endif
	#endif

	#if defined(WF_CS_TRIS)
		WF_CS_IO = 0;
		WF_CS_TRIS = 0;
	#endif
}

uint8 wifi_is_connected(void) {
    uint8 result = 0;
    result = wifi_is_connected_value;
    return result;
}

void isr_wifi_1ms(void) {
	extern void isr_wifi_tick_1ms(void);
	isr_wifi_tick_1ms();
}

void isr_eint_wifi(void) {
	extern void wifi_eint_handler(void);
	wifi_eint_handler();
}

static void InitAppConfig(void)
{
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    unsigned char vNeedToSaveDefaults = 0;
#endif

    while (1) {
        // Start out zeroing all AppConfig bytes to ensure all fields are
        // deterministic for checksum generation
        memset((void *) &AppConfig, 0x00, sizeof (AppConfig));

        AppConfig.Flags.bIsDHCPEnabled = true;
        AppConfig.Flags.bInConfigMode = true;
        memcpypgm2ram((void *) &AppConfig.MyMACAddr, (ROM void *) SerializedMACAddress, sizeof (AppConfig.MyMACAddr));

        AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2 << 8ul | MY_DEFAULT_IP_ADDR_BYTE3 << 16ul | MY_DEFAULT_IP_ADDR_BYTE4 << 24ul;
        AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
        AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2 << 8ul | MY_DEFAULT_MASK_BYTE3 << 16ul | MY_DEFAULT_MASK_BYTE4 << 24ul;
        AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
        AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2 << 8ul | MY_DEFAULT_GATE_BYTE3 << 16ul | MY_DEFAULT_GATE_BYTE4 << 24ul;
        AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2 << 8ul | MY_DEFAULT_PRIMARY_DNS_BYTE3 << 16ul | MY_DEFAULT_PRIMARY_DNS_BYTE4 << 24ul;
        AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2 << 8ul | MY_DEFAULT_SECONDARY_DNS_BYTE3 << 16ul | MY_DEFAULT_SECONDARY_DNS_BYTE4 << 24ul;

        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void *) MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);

#if defined(WF_CS_TRIS)
        // Load the default SSID Name
        WF_ASSERT(sizeof (MY_DEFAULT_SSID_NAME) - 1 <= sizeof (AppConfig.MySSID));
        memcpypgm2ram(AppConfig.MySSID, (ROM void *) MY_DEFAULT_SSID_NAME, sizeof (MY_DEFAULT_SSID_NAME));
        AppConfig.SsidLength = sizeof (MY_DEFAULT_SSID_NAME) - 1;

        AppConfig.SecurityMode = MY_DEFAULT_WIFI_SECURITY_MODE;

#if (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_OPEN)
        memset(AppConfig.SecurityKey, 0x00, sizeof (AppConfig.SecurityKey));
        AppConfig.SecurityKeyLength = 0;

#elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_40
        AppConfig.WepKeyIndex = 0; // This is the only WEP key index we currently support
        memcpypgm2ram(AppConfig.SecurityKey, (ROM void *) MY_DEFAULT_WEP_KEYS_40, sizeof (MY_DEFAULT_WEP_KEYS_40) - 1);
        AppConfig.SecurityKeyLength = sizeof (MY_DEFAULT_WEP_KEYS_40) - 1;

#elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_104
        AppConfig.WepKeyIndex = 0; // This is the only WEP key index we currently support
        memcpypgm2ram(AppConfig.SecurityKey, (ROM void *) MY_DEFAULT_WEP_KEYS_104, sizeof (MY_DEFAULT_WEP_KEYS_104) - 1);
        AppConfig.SecurityKeyLength = sizeof (MY_DEFAULT_WEP_KEYS_104) - 1;

#elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_KEY)
        memcpypgm2ram(AppConfig.SecurityKey, (ROM void *) MY_DEFAULT_PSK, sizeof (MY_DEFAULT_PSK) - 1);
        AppConfig.SecurityKeyLength = sizeof (MY_DEFAULT_PSK) - 1;

#elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
        memcpypgm2ram(AppConfig.SecurityKey, (ROM void *) MY_DEFAULT_PSK_PHRASE, sizeof (MY_DEFAULT_PSK_PHRASE) - 1);
        AppConfig.SecurityKeyLength = sizeof (MY_DEFAULT_PSK_PHRASE) - 1;

#elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPS_PUSH_BUTTON)
        memset(AppConfig.SecurityKey, 0x00, sizeof (AppConfig.SecurityKey));
        AppConfig.SecurityKeyLength = 0;

#elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPS_PIN)
        memcpypgm2ram(AppConfig.SecurityKey, (ROM void *) MY_DEFAULT_WPS_PIN, sizeof (MY_DEFAULT_WPS_PIN) - 1);
        AppConfig.SecurityKeyLength = sizeof (MY_DEFAULT_WPS_PIN) - 1;

#else
#error "No security defined"
#endif /* MY_DEFAULT_WIFI_SECURITY_MODE */

#endif

        // Compute the checksum of the AppConfig defaults as loaded from ROM
        wOriginalAppConfigChecksum = CalcIPChecksum((uint8_t *) & AppConfig, sizeof (AppConfig));

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        {
            NVM_VALIDATION_STRUCT NVMValidationStruct;

            // Check to see if we have a flag set indicating that we need to
            // save the ROM default AppConfig values.
            if (vNeedToSaveDefaults)
                SaveAppConfig(&AppConfig);

            // Read the NVMValidation record and AppConfig struct out of EEPROM/Flash
#if defined(EEPROM_CS_TRIS)
            {
                XEEReadArray(0x0000, (uint8_t *) & NVMValidationStruct, sizeof (NVMValidationStruct));
                XEEReadArray(sizeof (NVMValidationStruct), (uint8_t *) & AppConfig, sizeof (AppConfig));
            }
#elif defined(SPIFLASH_CS_TRIS)
            {
                SPIFlashReadArray(0x0000, (uint8_t *) & NVMValidationStruct, sizeof (NVMValidationStruct));
                SPIFlashReadArray(sizeof (NVMValidationStruct), (uint8_t *) & AppConfig, sizeof (AppConfig));
            }
#endif

            // Check EEPROM/Flash validity.  If it isn't valid, set a flag so
            // that we will save the ROM default values on the next loop
            // iteration.
            if ((NVMValidationStruct.wConfigurationLength != sizeof (AppConfig)) ||
                    (NVMValidationStruct.wOriginalChecksum != wOriginalAppConfigChecksum) ||
                    (NVMValidationStruct.wCurrentChecksum != CalcIPChecksum((uint8_t *) & AppConfig, sizeof (AppConfig)))) {
                // Check to ensure that the vNeedToSaveDefaults flag is zero,
                // indicating that this is the first iteration through the do
                // loop.  If we have already saved the defaults once and the
                // EEPROM/Flash still doesn't pass the validity check, then it
                // means we aren't successfully reading or writing to the
                // EEPROM/Flash.  This means you have a hardware error and/or
                // SPI configuration error.
                if (vNeedToSaveDefaults) {
                    WF_ASSERT(false);
                }

                // Set flag and restart loop to load ROM defaults and save them
                vNeedToSaveDefaults = 1;
                continue;
            }

            // If we get down here, it means the EEPROM/Flash has valid contents
            // and either matches the ROM defaults or previously matched and
            // was run-time reconfigured by the user.  In this case, we shall
            // use the contents loaded from EEPROM/Flash.
            break;
        }
#endif
        break;
    }
}


#if defined(WF_CS_TRIS)
/*****************************************************************************
 * FUNCTION: WF_Connect
 *
 * RETURNS:  None
 *
 * PARAMS:   None
 *
 *  NOTES:   Connects to an 802.11 network.  Customize this function as needed
 *           for your application.
 *****************************************************************************/
void WF_Connect(void)
{
    //uint8_t ConnectionState;
    uint8_t channelList[] = MY_DEFAULT_CHANNEL_LIST;

    /* create a Connection Profile */
    WF_CPCreate(&ConnectionProfileID);

    AppConfig.passPhraseToKeyFlag = 0;

    WF_SetRegionalDomain(MY_DEFAULT_DOMAIN);

    WF_CPSetSsid(ConnectionProfileID,
            AppConfig.MySSID,
            AppConfig.SsidLength);

    WF_CPSetNetworkType(ConnectionProfileID, MY_DEFAULT_NETWORK_TYPE);

    WF_CASetScanType(MY_DEFAULT_SCAN_TYPE);

    WF_CASetChannelList(channelList, sizeof (channelList));

    // The Retry Count parameter tells the WiFi Connection manager how many attempts to make when trying
    // to connect to an existing network.  In the Infrastructure case, the default is to retry forever so that
    // if the AP is turned off or out of range, the radio will continue to attempt a connection until the
    // AP is eventually back on or in range.  In the Adhoc case, the default is to retry 3 times since the
    // purpose of attempting to establish a network in the Adhoc case is only to verify that one does not
    // initially exist.  If the retry count was set to WF_RETRY_FOREVER in the AdHoc mode, an AdHoc network
    // would never be established.
    WF_CASetListRetryCount(MY_DEFAULT_LIST_RETRY_COUNT);

    WF_CASetEventNotificationAction(MY_DEFAULT_EVENT_NOTIFICATION_LIST);

    WF_CASetBeaconTimeout(MY_DEFAULT_BEACON_TIMEOUT);

#if !defined(MRF24WG)
    if (gRFModuleVer1209orLater) {
        // If WEP security is used, set WEP Key Type.  The default WEP Key Type is Shared Key.
        if (AppConfig.SecurityMode == WF_SECURITY_WEP_40 || AppConfig.SecurityMode == WF_SECURITY_WEP_104) {
            //WF_CPSetWepKeyType(ConnectionProfileID, MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE);
        }
    }
    // if earlier version than 1209, use WEP Open Key default in module.
#else
    {
        // If WEP security is used, set WEP Key Type.  The default WEP Key Type is Shared Key.
        if (AppConfig.SecurityMode == WF_SECURITY_WEP_40 || AppConfig.SecurityMode == WF_SECURITY_WEP_104) {
            WF_CPSetWepKeyType(ConnectionProfileID, MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE);
        }
    }
#endif

#if defined(MRF24WG)
    // Error check items specific to WPS Push Button mode
#if (MY_DEFAULT_WIFI_SECURITY_MODE==WF_SECURITY_WPS_PUSH_BUTTON)
#if !defined(WF_P2P)
    WF_ASSERT(strlen(AppConfig.MySSID) == 0); // SSID must be empty when using WPS
    WF_ASSERT(sizeof (channelList) == 11); // must scan all channels for WPS
#endif

#if (MY_DEFAULT_NETWORK_TYPE == WF_P2P)
    WF_ASSERT(strcmp((char *)AppConfig.MySSID, "DIRECT-") == 0);
    WF_ASSERT(sizeof (channelList) == 3);
    WF_ASSERT(channelList[0] == 1);
    WF_ASSERT(channelList[1] == 6);
    WF_ASSERT(channelList[2] == 11);
#endif
#endif
#endif /* MRF24WG */

#if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED
    if (AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE) {
        WF_ConvPassphraseToKey(AppConfig.SecurityKeyLength, AppConfig.SecurityKey,
                AppConfig.SsidLength, AppConfig.MySSID);
        AppConfig.SecurityMode--;
        AppConfig.SecurityKeyLength = 32;
        AppConfig.passPhraseToKeyFlag = 1;
    }
#if defined (MRF24WG)
    else if (AppConfig.SecurityMode == WF_SECURITY_WPS_PUSH_BUTTON
            || AppConfig.SecurityMode == WF_SECURITY_WPS_PIN) {
        WF_YieldPassphraseToHost();
    }
#endif /* defined (MRF24WG) */
#endif /* #if WF_HOST_DERIVE_KEY_FROM_PASSPHRASE == WF_ENABLED */

#if !defined(MRF24WG)
    Delay10us(10); /* required for MRF24WB */
#endif

    WF_CPSetSecurity(ConnectionProfileID,
            AppConfig.SecurityMode,
            AppConfig.WepKeyIndex, /* only used if WEP enabled, only 0 is supported currently */
            AppConfig.SecurityKey,
            AppConfig.SecurityKeyLength);

#if MY_DEFAULT_PS_POLL == WF_ENABLED
    WF_PsPollEnable(true);
#if !defined(MRF24WG)
    if (gRFModuleVer1209orLater)
        WFEnableDeferredPowerSave();
#endif /* !defined(MRF24WG) */
#else /* MY_DEFAULT_PS_POLL != WF_ENABLED */
    WF_PsPollDisable();
#endif /* MY_DEFAULT_PS_POLL == WF_ENABLED */

#if defined(STACK_USE_UART)
    WF_OutputConnectionInfo(&AppConfig);
#endif

#if WF_MODULE_CONNECTION_MANAGER == WF_DISABLED
    WF_DisableModuleConnectionManager();
#endif

#if defined(MRF24WG)
    WFEnableDebugPrint(ENABLE_WPS_PRINTS | ENABLE_P2P_PRINTS);
#endif

#if (WF_CHECK_LINK_STATUS == WF_ENABLED)
    WF_SetLinkDownThreshold(WF_LINK_LOST_THRESHOLD);
#endif

    WF_CMConnect(ConnectionProfileID);
}
#endif /* WF_CS_TRIS */


// Writes an IP address to the LCD display and the UART as available
void DisplayIPValue(IP_ADDR IPVal)
{
    //  printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    uint8_t IPDigit[4];
    uint8_t i;

    for (i = 0; i < sizeof (IP_ADDR); i++) {
        uitoa_my((uint16_t) IPVal.v[i], IPDigit);

#if defined(STACK_USE_UART)
        putsUART((char *) IPDigit);
#endif

    if (i == sizeof (IP_ADDR) - 1) {
        break;
    }

#if defined(STACK_USE_UART)
        putcUART('.');
#endif
    }
}
