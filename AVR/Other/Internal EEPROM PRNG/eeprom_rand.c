
#include "eeprom_rand.h"


// ===============================================================================

static uint16_t _init_eeprom_addr, _max_eeprom_addr;

// ===============================================================================


void EEPROM_RAND_Initialize(uint16_t init_eeprom_addr, uint16_t max_eeprom_addr)
{
	_init_eeprom_addr = init_eeprom_addr;
	_max_eeprom_addr = max_eeprom_addr;
}

uint8_t EEPROM_RAND_Get_8Bit_Value()
{
	_init_eeprom_addr = _init_eeprom_addr % _max_eeprom_addr;

	uint16_t eeprom_addr_ptr = _init_eeprom_addr;


	uint8_t a = EEPROM_Read_Byte(_init_eeprom_addr);

	eeprom_addr_ptr = (a ^ _init_eeprom_addr) % _max_eeprom_addr;


	uint8_t b = EEPROM_Read_Byte(eeprom_addr_ptr);

	uint8_t res = a + b;


	uint8_t eeprom_value_temp;

	if (a <= b)
	{
		eeprom_value_temp = EEPROM_Read_Byte((eeprom_addr_ptr + b) % _max_eeprom_addr);

		eeprom_value_temp += a;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}

		eeprom_addr_ptr = (a + _init_eeprom_addr) % _max_eeprom_addr;


		EEPROM_Write_Byte(eeprom_addr_ptr, eeprom_value_temp);


		eeprom_value_temp = EEPROM_Read_Byte(_init_eeprom_addr);

		eeprom_value_temp ^= res;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}
	}
	else
	{
		eeprom_value_temp = EEPROM_Read_Byte((eeprom_addr_ptr + a) % _max_eeprom_addr);

		eeprom_value_temp += res;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}

		eeprom_addr_ptr = (a ^ _init_eeprom_addr) % _max_eeprom_addr;


		EEPROM_Write_Byte(eeprom_addr_ptr, eeprom_value_temp);


		eeprom_value_temp = EEPROM_Read_Byte(_init_eeprom_addr);

		eeprom_value_temp ^= b;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}
	}

	EEPROM_Write_Byte(_init_eeprom_addr, eeprom_value_temp);

	++_init_eeprom_addr;

	return res;
}

uint16_t EEPROM_RAND_Get_16Bit_Value()
{
	uint16_t res = EEPROM_RAND_Get_8Bit_Value();

	res <<= 8;

	res |= EEPROM_RAND_Get_8Bit_Value();

	return res;
}

uint32_t EEPROM_RAND_Get_32Bit_Value()
{
	uint32_t res = EEPROM_RAND_Get_16Bit_Value();

	res <<= 8;

	res |= EEPROM_RAND_Get_16Bit_Value();

	return res;
}


