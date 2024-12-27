
#include "eeprom_rand.h"


// ===============================================================================


uint8_t EEPROM_RAND_Get_8Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr)
{
	uint8_t eeprom_addr_ptr;


	eeprom_addr_ptr = init_eeprom_addr % max_eeprom_addr;


	uint8_t a = eeprom_read_byte(&init_eeprom_addr);


	eeprom_addr_ptr = a ^ init_eeprom_addr;

	eeprom_addr_ptr = eeprom_addr_ptr % max_eeprom_addr;


	uint8_t b = eeprom_read_byte(&eeprom_addr_ptr);


	uint8_t res = a + b;

	uint8_t eeprom_value_temp;

	if (a <= b)
	{
		eeprom_value_temp = eeprom_read_byte(&eeprom_addr_ptr);


		eeprom_value_temp += a;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}

		eeprom_addr_ptr = a ^ init_eeprom_addr;

		eeprom_addr_ptr = eeprom_addr_ptr % max_eeprom_addr;


		eeprom_write_byte(&eeprom_addr_ptr, eeprom_value_temp);


		eeprom_value_temp = eeprom_read_byte(&init_eeprom_addr);

		eeprom_value_temp += res;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}


		eeprom_write_byte(&init_eeprom_addr, eeprom_value_temp);
	}
	else
	{
		eeprom_value_temp = eeprom_read_byte(&eeprom_addr_ptr);


		eeprom_value_temp += res;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}

		eeprom_addr_ptr = a ^ init_eeprom_addr;

		eeprom_addr_ptr = eeprom_addr_ptr % max_eeprom_addr;

		eeprom_write_byte(&eeprom_addr_ptr, eeprom_value_temp);


		eeprom_value_temp = eeprom_read_byte(&init_eeprom_addr);

		eeprom_value_temp += b;

		if (eeprom_value_temp == 0)
		{
			eeprom_value_temp = 1;
		}

		eeprom_write_byte(&init_eeprom_addr, eeprom_value_temp);
	}

	return res;
}

uint16_t EEPROM_RAND_Get_16Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr)
{
	uint16_t res = EEPROM_RAND_Get_8Bit_Value(init_eeprom_addr, max_eeprom_addr);

	res <<= 8;

	res |= EEPROM_RAND_Get_8Bit_Value(init_eeprom_addr, max_eeprom_addr);

	return res;
}

uint32_t EEPROM_RAND_Get_32Bit_Value(uint8_t init_eeprom_addr, uint8_t max_eeprom_addr)
{
	uint32_t res = EEPROM_RAND_Get_16Bit_Value(init_eeprom_addr, max_eeprom_addr);

	res <<= 8;

	res |= EEPROM_RAND_Get_16Bit_Value(init_eeprom_addr, max_eeprom_addr);

	return res;
}


