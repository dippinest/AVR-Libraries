

#include "lm75.h"



// ===============================================================================



#ifdef EEPROMI2C_USE_SOFTI2C


#include "softi2c.h"

#define _I2C_Start       SOFTI2C_Start
#define _I2C_Send_Byte   SOFTI2C_Send_Byte
#define _I2C_Restart     SOFTI2C_Restart
#define _I2C_Read_Byte   SOFTI2C_Read_Byte
#define _I2C_Stop        SOFTI2C_Stop

#else

#include "i2c.h"

#define _I2C_Start       I2C_Start
#define _I2C_Send_Byte   I2C_Send_Byte
#define _I2C_Restart     I2C_Restart
#define _I2C_Read_Byte   I2C_Read_Byte
#define _I2C_Stop        I2C_Stop



#endif



// ===============================================================================




static void _LM75_Set_Register_Pointer(LM75_t *lm75, uint8_t addr_reg)
{
	_I2C_Start();
	
	_I2C_Send_Byte(lm75->dev_addr << 1);
	_I2C_Send_Byte(addr_reg);
	
	_I2C_Stop();
}


static void _LM75_Write_UINT8_Configuration_Register(LM75_t *lm75)
{
	_I2C_Start();
	
	_I2C_Send_Byte((lm75->dev_addr << 1) | 0);
	_I2C_Send_Byte(_LM75_CONFUGURATION_REGISTER_ADDR);
	_I2C_Send_Byte(lm75->configuration_register);
	
	_I2C_Stop();
}


static void _LM75_Write_UINT16_Register(LM75_t *lm75, uint8_t addr_reg, uint16_t data_register)
{
	_I2C_Start();
	
	_I2C_Send_Byte((lm75->dev_addr << 1) | 0);
	_I2C_Send_Byte(addr_reg);
	_I2C_Send_Byte(data_register >> 8);
	_I2C_Send_Byte((uint8_t)data_register);
	
	_I2C_Stop();
}


static uint16_t _LM75_Read_UINT16_Register(LM75_t *lm75, uint8_t addr_reg)
{
	uint8_t high_byte = 0, low_byte = 0;
	
	_LM75_Set_Register_Pointer(lm75, addr_reg);
	
	_I2C_Start();
	
	_I2C_Send_Byte((lm75->dev_addr << 1) | 1);
	_I2C_Read_Byte(&high_byte, ACK);
	_I2C_Read_Byte(&low_byte, NACK);
	
	_I2C_Stop();
	
	
	return ((uint16_t)high_byte << 8) | low_byte;
}


// ===============================================================================



void LM75_Initialize_Object(LM75_t *lm75, uint8_t dev_addr, bool thermometer_is_enable)
{
	(*lm75).dev_addr = dev_addr;
	(*lm75).configuration_register = 0;
	
	
	if (thermometer_is_enable)
	{
		lm75->configuration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	else
	{
		lm75->configuration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	
	
	_LM75_Write_UINT8_Configuration_Register(lm75);
}



// ===============================================================================



void LM75_Set_Enable(LM75_t *lm75, bool thermometer_is_enable)
{
	if (thermometer_is_enable)
	{
		lm75->configuration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	else
	{
		lm75->configuration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(lm75);
}



void LM75_Set_OS_Mode(LM75_t *lm75, bool os_is_comparator_mode)
{
	if (os_is_comparator_mode)
	{
		lm75->configuration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_OS_COMP_INT_BIT_POS);
	}
	else
	{
		lm75->configuration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_OS_COMP_INT_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(lm75);
}



void LM75_Set_OS_Polarity(LM75_t *lm75, bool os_pol_is_low)
{
	if (os_pol_is_low)
	{
		lm75->configuration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_OS_POL_BIT_POS);
	}
	else
	{
		lm75->configuration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_OS_POL_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(lm75);
}



void LM75_Set_OS_Number_Of_Checks(LM75_t *lm75, uint8_t os_num_of_checks)
{
	lm75->configuration_register |= (os_num_of_checks << _LM75_CONFUGURATION_REGISTER_OS_F_QUE_BITS_POS);
	
	_LM75_Write_UINT8_Configuration_Register(lm75);
}



void LM75_Set_Integer_Upper_And_Lower_Limits_OS_Hysteresis_Temperature(LM75_t *lm75, int16_t low_limit_temp, int16_t high_limit_temp)
{
	if (low_limit_temp > high_limit_temp)
	{
		low_limit_temp  ^= high_limit_temp;
		high_limit_temp ^= low_limit_temp;
		low_limit_temp  ^= high_limit_temp;
	}
	
	lm75->thyst_value_register   = low_limit_temp;
	lm75->tos_value_register     = high_limit_temp;
	lm75->thyst_value_register <<= 8;
	lm75->tos_value_register   <<= 8;
	
	_LM75_Write_UINT16_Register(lm75, _LM75_THYST_VALUE_REGISTER_ADDR, lm75->thyst_value_register);
	_LM75_Write_UINT16_Register(lm75, _LM75_TOS_VALUE_REGISTER_ADDR,   lm75->tos_value_register);
}



// ===============================================================================



int16_t LM75_Get_Integer_Temperature(LM75_t *lm75)
{
	int16_t raw_temperature_data = _LM75_Read_UINT16_Register(lm75, _LM75_DATA_TEMP_REGISTER_ADDR);
	
	if (raw_temperature_data & 0x8000)
	{
		raw_temperature_data  *= -1;
		raw_temperature_data >>= 8;
		return raw_temperature_data * -1;
	}
	else
	{
		return (int16_t)(raw_temperature_data >> 8);
	}
}



float LM75_Get_Float_Temperature(LM75_t *lm75)
{
	int16_t raw_temperature_data = _LM75_Read_UINT16_Register(lm75, _LM75_DATA_TEMP_REGISTER_ADDR);
	
	return (float)(raw_temperature_data >> 5) * 0.125;
}



int32_t LM75_Get_FIXPoint_2_Fractional_Digits_Temperature(LM75_t *lm75)
{
	int8_t int_part, fract_part_3bit;
	int16_t raw_temperature_data = _LM75_Read_UINT16_Register(lm75, _LM75_DATA_TEMP_REGISTER_ADDR);
	
	int32_t pfixp_temp;
	
	if (raw_temperature_data & 0x8000)
	{
		raw_temperature_data  *= -1;
		raw_temperature_data >>= 6;
		fract_part_3bit = raw_temperature_data & 0b11;
		int_part = (int8_t)(raw_temperature_data >> 2);
		pfixp_temp = ((int32_t)int_part * 100) - ((int32_t)fract_part_3bit * 25);
	}
	else
	{
		raw_temperature_data >>= 6;
		fract_part_3bit = raw_temperature_data & 0b11;
		int_part = raw_temperature_data >> 2;
		pfixp_temp = (int_part * 100) + (fract_part_3bit * 25);
	}
	
	
	return pfixp_temp;
}



int32_t LM75_Get_FIXPoint_3_Fractional_Digits_Temperature(LM75_t *lm75)
{
	int8_t int_part, fract_part_3bit;
	int16_t raw_temperature_data = _LM75_Read_UINT16_Register(lm75, _LM75_DATA_TEMP_REGISTER_ADDR);
	
	int32_t pfixp_temp;
	
	if (raw_temperature_data & 0x8000)
	{
		raw_temperature_data  *= -1;
		raw_temperature_data >>= 5;
		fract_part_3bit = raw_temperature_data & 0b111;
		int_part = (int8_t)(raw_temperature_data >> 3);
		pfixp_temp = ((int32_t)int_part * 1000) - ((int32_t)fract_part_3bit * 125);
	}
	else
	{
		raw_temperature_data >>= 5;
		fract_part_3bit = raw_temperature_data & 0b111;
		int_part = raw_temperature_data >> 3;
		pfixp_temp = (int_part * 1000) + (fract_part_3bit * 125);
	}
	
	
	return pfixp_temp;
}






