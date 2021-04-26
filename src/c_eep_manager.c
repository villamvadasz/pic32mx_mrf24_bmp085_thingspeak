#include "eep_manager.h"
#include "c_eep_manager.h"

#include <stdio.h>
#include "app.h"

uint8 testVariable = 0;
const uint8 defaultVariable = 0x12;
uint16 test2Variable = 0;
const uint16 default2Variable = 0x1234;

EepManager_ItemTable eepManager_ItemTable[EepManager_Items_LastItem] = {
	{EepManager_Items_Variable1, sizeof(testVariable),	&testVariable,	(void *)&defaultVariable,	EEP_USE_CRC, EEP_HAVE_BACKUP},
	{EepManager_Items_Variable2, sizeof(test2Variable), &test2Variable, (void *)&default2Variable,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable3, 2, 					NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable4, 2, 					NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable5, 2, 					NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable6, 2,						NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable7, 2, 					NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable8, 2,					 	NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},
	{EepManager_Items_Variable9, 2, 					NULL, NULL,	EEP_USE_CRC, EEP_NO_BACKUP},	
};
