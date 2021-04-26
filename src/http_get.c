#include "k_stdtype.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "system_config.h"

#include "app.h"
#include "bootloader_interface.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "tcpip.h"

/*****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPExecuteGet(void)

  Internal:
    See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
    uint8_t *ptr;
    uint8_t filename[20];

    // Load the file name
    // Make sure uint8_t filename[] above is large enough for your longest name
    MPFSGetFilename(curHTTP.file, filename, 20);

    if (!memcmppgm2ram(filename, "index.htm", 9)) {
        ptr = HTTPGetROMArg(curHTTP.data, (ROM uint8_t *) "fname");
        if (ptr) {
			if (
				(ptr[0] == 'B') && 
				(ptr[1] == 'O') && 
				(ptr[2] == 'O') && 
				(ptr[3] == 'T') && 
				(ptr[4] == 'L') && 
				(ptr[5] == 'O') && 
				(ptr[6] == 'A') && 
				(ptr[7] == 'D') && 
				(ptr[8] == 'E') && 
				(ptr[9] == 'R')
			) {
				app_BootloaderTrigger++;
				bootloader_reset();
			}
		}
		
	}
    // If it's the LED updater file
    else if (!memcmppgm2ram(filename, "cookies.htm", 11)) {
        // This is very simple.  The names and values we want are already in
        // the data array.  We just set the hasArgs value to indicate how many
        // name/value pairs we want stored as cookies.
        // To add the second cookie, just increment this value.
        // remember to also add a dynamic variable callback to control the printout.
        curHTTP.hasArgs = 0x01;
    }

    return HTTP_IO_DONE;
}

#endif