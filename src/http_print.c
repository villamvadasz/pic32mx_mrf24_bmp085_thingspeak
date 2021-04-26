#include "k_stdtype.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "system_config.h"

#include "app.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "tcpip.h"

void HTTPPrint_reboot(void)
{
    // This is not so much a print function, but causes the board to reboot
    // when the configuration is changed.  If called via an AJAX call, this
    // will gracefully reset the board and bring it back online immediately
    Reset();
}

void HTTPPrint_MyVariableTemperature(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_Temperature);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariablePressure(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_Pressure);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariableHumidity(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_Humiditiy);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariableCO2(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_CO2);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariableLiPoVoltage(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_LiPo_Voltage);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariableLiPoPercentage(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%.2f", (double)app_LiPo_Percentage);
    TCPPutString(sktHTTP, app_str);
}

void HTTPPrint_MyVariableBootloaderTrigger(void) {
	unsigned char app_str[32];
	sprintf((char *)app_str, "%d", app_BootloaderTrigger);
    TCPPutString(sktHTTP, app_str);
}

#endif