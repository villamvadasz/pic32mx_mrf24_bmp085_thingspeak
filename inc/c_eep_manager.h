#ifndef _C_EEP_MANAGER_H_
#define _C_EEP_MANAGER_H_

	#define EEPROM_START_ADDR	0x0000
	#define EEPROM_SIZE			0x0800

	//Use 0xFF to disable version check
	//#define EEPROM_VERSION 0xFF

	#define EEPROM_VERSION 0x09
	//#define EEPROM_INVALIDATE_OLD

	typedef enum _EepManager_Item {
		EepManager_Items_Variable1 = 0,
		EepManager_Items_Variable2,
		EepManager_Items_Variable3,
		EepManager_Items_Variable4,
		EepManager_Items_Variable5,
		EepManager_Items_Variable6,
		EepManager_Items_Variable7,
		EepManager_Items_Variable8,
		EepManager_Items_Variable9,
		EepManager_Items_LastItem,
	} EepManager_Item;

#endif
