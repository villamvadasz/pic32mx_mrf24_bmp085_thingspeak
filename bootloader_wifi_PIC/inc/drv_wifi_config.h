/*******************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    drv_wifi_config.h

  Summary:
    Module for Microchip TCP/IP Stack
    -Provides access to MRF24W WiFi controller
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard

  Description:
    MRF24W Driver Customization

 *******************************************************************************/

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

#ifndef __WF_CONFIG_H_
#define __WF_CONFIG_H_

#include <stdint.h>

/*******************************************************************************
 *                             DEFINES
 ********************************************************************************/

#define WF_TCPIP_DEMO

/****************************************************************************
 * MRF24WB0MA/B  (supports only 1/2 Mbps)
 *      Client in infrastructure network                     (ALL security)
 *      Adhoc network                                        (OPEN, WEP security)
 *
 * MRF24WG0MA/B
 *      Client in infrastructure network                     (ALL security)
 *      Adhoc network                                        (OPEN, WEP security)
 *      Group client (GC) in WFii direct (P2P) network
 *      SoftAP                                               (OPEN, WEP security)
 *      Supports WPS security connection
 *
 * Available documentation
 * DS52108A  Microchip MRF24W Getting started Guide for MRF24WB0MAB, MRF24WG0MA/B for MLA v5
 *****************************************************************************/


/*****************************************************************************/
/*****************************************************************************/
/*                             WIFI SECURITY COMPILE-TIME DEFAULTS           */
/*****************************************************************************/
/*****************************************************************************
 * Security modes available on WiFi network:
 *   WF_SECURITY_OPEN                      : No security
 *   WF_SECURITY_WEP_40                    : WEP Encryption using 40 bit keys
 *   WF_SECURITY_WEP_104                   : WEP Encryption using 104 bit keys
 *   WF_SECURITY_WPA_AUTO_WITH_KEY         : WPA-PSK or WPA2-PSK where 64 hex characters key is given to MRF24W for connecting
 *   WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE : WPA-PSK or WPA2-PSK where passphrase is given and converted by MRF24W to 64 hex characters key
 *   WF_SECURITY_WPS_PUSH_BUTTON           : WPS PBC method
 *   WF_SECURITY_WPS_PIN                   : WPS PIN method
 ******************************************************************************/

// Comments: CFG_WF_SOFT_AP is only available in EZ Config
#define CFG_WF_INFRASTRUCTURE 1
#define CFG_WF_ADHOC          2
#define CFG_WF_P2P            3

#define MY_DEFAULT_NETWORK_TYPE             CFG_WF_INFRASTRUCTURE /* CFG_WF_INFRASTRUCTURE, CFG_WF_ADHOC, CFG_WF_P2P */
#define MY_DEFAULT_DOMAIN                   WF_DOMAIN_ETSI
#define MY_DEFAULT_LIST_RETRY_COUNT         WF_RETRY_FOREVER /* Number of times to try to connect to the SSID when using Infrastructure network type */

#if MY_DEFAULT_NETWORK_TYPE == CFG_WF_ADHOC
#undef MY_DEFAULT_LIST_RETRY_COUNT
#define MY_DEFAULT_LIST_RETRY_COUNT         3
#endif

/*--------------------------------------------------------*/
/* if starting this demo in infrastructure or ad-hoc mode */
/*--------------------------------------------------------*/
#if MY_DEFAULT_NETWORK_TYPE == CFG_WF_INFRASTRUCTURE || MY_DEFAULT_NETWORK_TYPE == CFG_WF_ADHOC
#define MY_DEFAULT_WIFI_SECURITY_MODE       WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE
#define MY_DEFAULT_SCAN_TYPE                WF_ACTIVE_SCAN            /* WF_ACTIVE_SCAN or WF_PASSIVE_SCAN */
#define MY_DEFAULT_BEACON_TIMEOUT           (40)                      /* Number of beacon periods          */
#define MY_DEFAULT_SSID_NAME                "CHANGEME"        /* if WF_SECURITY_WPS_PUSH_BUTTON must be "" (empty string) */
#define MY_DEFAULT_PSK_PHRASE "CHANGEME"
//#define MY_DEFAULT_SSID_NAME                "CHANGEME"        /* if WF_SECURITY_WPS_PUSH_BUTTON must be "" (empty string) */
//#define MY_DEFAULT_PSK_PHRASE "CHANGEME"
#if defined(__XC8)
#define MY_DEFAULT_CHANNEL_LIST             {1,2,3,4,5,6,7,8,9,10,11} /* Default channel list for FCC */
#else
#define MY_DEFAULT_CHANNEL_LIST             {}                        /* Default channel list for FCC */
#endif
/* Select Infrastructure Power Save Mode */
#define MY_DEFAULT_PS_POLL                  WF_DISABLED               /* PS is not supported in Adhoc */
/*------------------------------------------------------*/
/* else if starting this demo in P2P(Wi-Fi Direct) mode */
/*------------------------------------------------------*/
#elif MY_DEFAULT_NETWORK_TYPE == CFG_WF_P2P
#if defined (MRF24WG)
/*
 * Wi-Fi Direct has been tested with Samsung Galaxy Tab 2 7.0 ( Android 4.0.3, Ice cream Sandwitch),
 * Galaxy-Nexus and Galaxy S III(Android 4.04). MRF24W supports only GC function.
 */
#define MY_DEFAULT_WIFI_SECURITY_MODE               WF_SECURITY_WPS_PUSH_BUTTON
#define MY_DEFAULT_SCAN_TYPE                        WF_ACTIVE_SCAN
#define MY_DEFAULT_SSID_NAME                        "DIRECT-" /* Fixed SSID. Do not change */
#define MY_DEFAULT_CHANNEL_LIST                     {1, 6, 11} /* Social channels. Do not change */
#define MY_DEFAULT_BEACON_TIMEOUT                   (40) /* Number of beacon periods */
#define MY_DEFAULT_PS_POLL                          WF_DISABLED
#else /* !defined (MRF24WG) */
#error "MRF24WB does not support Wi-Fi Direct (P2P)"
#endif /* defined (MRF24WG) */
#endif /* MY_DEFAULT_NETWORK_TYPE == CFG_WF_INFRASTRUCTURE */

#define WF_CHECK_LINK_STATUS   WF_ENABLED /* Gets the MRF to check the link status relying on Tx failures. */
#define WF_LINK_LOST_THRESHOLD 40 /* Consecutive Tx transmission failures to be considered the AP is gone away. */

/* 
 * MRF24W FW has a built-in connection manager, and it is enabled by default.
 * If you want to run your own connection manager in host side, you should
 * disable the FW connection manager to avoid possible conflict between the two.
 * Especially these two APIs can be affected if you do not disable it.
 * A) uint16_t WF_CMDisconnect(void)
 * B) uint16_t WF_Scan(uint8_t CpId)
 * These APIs will return failure when the conflict occurs.
 */
#define WF_MODULE_CONNECTION_MANAGER WF_ENABLED

#if defined(__XC32)
/* This is optional, which results faster key derivation */
#define WF_HOST_DERIVE_KEY_FROM_PASSPHRASE WF_ENABLED
#else
#define WF_HOST_DERIVE_KEY_FROM_PASSPHRASE WF_DISABLED
#endif

#if defined (MRF24WG)
/* only used when security is WF_SECURITY_WPS_PIN */
#define MY_DEFAULT_WPS_PIN "12390212" 
/* 
 * An example PIN.
 * The last digit is the checksum of first 7 digits.
 */
/* 
 * The MRF24W HW has 2 multicast filters. If your application requires more filters,
 * enable this to extend the filters to 16 maximum.
 */
#define WF_SOFTWARE_MULTICAST_FILTER WF_DISABLED                                                         
#endif /* !defined (MRF24WG) */

/*** Selecting Event Notification Type ***/
#define MY_DEFAULT_EVENT_NOTIFICATION_LIST  (WF_NOTIFY_CONNECTION_ATTEMPT_SUCCESSFUL  |         \
                                             WF_NOTIFY_CONNECTION_ATTEMPT_FAILED      |         \
                                             WF_NOTIFY_CONNECTION_TEMPORARILY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_PERMANENTLY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_REESTABLISHED)

#endif /* __WF_CONFIG_H_ */
