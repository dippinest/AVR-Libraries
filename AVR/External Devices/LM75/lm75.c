// ======================================================================================================
//  Header              : lm75.c                                                                        -
//  Created             : 27.03.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Defining of function for working with I2C temperature sensor LM75/LM75A       -
//                                                                                                      -
//                        ATN: all measurements are carried out in degrees Celsius                      -
// ======================================================================================================

#include "lm75.h"

static LM75_t *target_thermometer = NULL;

static void _LM75_Set_Register_Pointer(uint8_t addr_reg)
{
	I2C_Start();
	I2C_Send_Byte(target_thermometer->dev_addr << 1);
	I2C_Send_Byte(addr_reg);
	I2C_Stop();
}

static void _LM75_Write_UINT8_Configuration_Register(uint8_t configuration_data_register)
{
	I2C_Start();
	I2C_Send_Byte((target_thermometer->dev_addr << 1) | 0);
	I2C_Send_Byte(_LM75_CONFUGURATION_REGISTER_ADDR);
	I2C_Send_Byte(configuration_data_register);
	I2C_Stop();
}

static void _LM75_Write_UINT16_Register(uint8_t addr_reg, uint16_t data_register)
{
	I2C_Start();
	I2C_Send_Byte((target_thermometer->dev_addr << 1) | 0);
	I2C_Send_Byte(addr_reg);
	I2C_Send_Byte(data_register >> 8);
	I2C_Send_Byte((uint8_t)data_register);
	I2C_Stop();
}

static uint16_t _LM75_Read_UINT16_Register(uint8_t addr_reg)
{
	uint8_t high_byte = 0, low_byte = 0;
	
	_LM75_Set_Register_Pointer(addr_reg);
	
	I2C_Start();
	I2C_Send_Byte((target_thermometer->dev_addr << 1) | 1);
	I2C_Read_Byte_With_Confirmation(&high_byte);
	I2C_Read_Byte_Without_Confirmation(&low_byte);
	I2C_Stop();
	
	return ((uint16_t)high_byte << 8) | low_byte;
}

LM75_t LM75_Get_Thermometer_Object(uint8_t dev_addr, bool thermometer_is_enable)
{
	LM75_t thermometer;
	
	thermometer.dev_addr = dev_addr;
	thermometer.confuguration_register = 0;
	
	target_thermometer = &thermometer;
	
	if (thermometer_is_enable)
	{
		target_thermometer->confuguration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	else
	{
		target_thermometer->confuguration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(target_thermometer->confuguration_register);
	
	return thermometer;
}

void LM75_Set_Target_Thermometer_Object(LM75_t *thermometer)
{
	target_thermometer = thermometer;
}

void LM75_Set_Enable(bool thermometer_is_enable)
{
	if (thermometer_is_enable)
	{
		target_thermometer->confuguration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	else
	{
		target_thermometer->confuguration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(target_thermometer->confuguration_register);
}

void LM75_Set_OS_Mode(bool os_is_comparator_mode)
{
	if (os_is_comparator_mode)
	{
		target_thermometer->confuguration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_OS_COMP_INT_BIT_POS);
	}
	else
	{
		target_thermometer->confuguration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_OS_COMP_INT_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(target_thermometer->confuguration_register);
}

void LM75_Set_OS_Polarity(bool os_pol_is_low)
{
	if (os_pol_is_low)
	{
		target_thermometer->confuguration_register &= ~(1 << _LM75_CONFUGURATION_REGISTER_OS_POL_BIT_POS);
	}
	else
	{
		target_thermometer->confuguration_register |=  (1 << _LM75_CONFUGURATION_REGISTER_OS_POL_BIT_POS);
	}
	
	_LM75_Write_UINT8_Configuration_Register(target_thermometer->confuguration_register);
}

void LM75_Set_OS_Number_Of_Checks(uint8_t os_num_of_checks)
{
	target_thermometer->confuguration_register |= (os_num_of_checks << _LM75_CONFUGURATION_REGISTER_OS_F_QUE_BITS_POS);
	
	_LM75_Write_UINT8_Configuration_Register(target_thermometer->confuguration_register);
}

void LM75_Set_Integer_Upper_And_Lower_Limits_OS_Hysteresis_Temperature(int16_t low_limit_temp, int16_t high_limit_temp)
{
	if (low_limit_temp > high_limit_temp)
	{
		low_limit_temp  ^= high_limit_temp;
		high_limit_temp ^= low_limit_temp;
		low_limit_temp  ^= high_limit_temp;
	}
	
	target_thermometer->thyst_value_register   = low_limit_temp;
	target_thermometer->tos_value_register     = high_limit_temp;
	target_thermometer->thyst_value_register <<= 8;
	target_thermometer->tos_value_register   <<= 8;
	
	_LM75_Write_UINT16_Register(_LM75_THYST_VALUE_REGISTER_ADDR, target_thermometer->thyst_value_register);
	_LM75_Write_UINT16_Register(_LM75_TOS_VALUE_REGISTER_ADDR,   target_thermometer->tos_value_register);
}

int16_t LM75_Get_Integer_Temperature()
{
	int16_t raw_temperature_data = (_LM75_Read_UINT16_Register(_LM75_DATA_TEMP_REGISTER_ADDR));
	
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

float LM75_Get_Float_Temperature()
{
	int16_t raw_temperature_data = (_LM75_Read_UINT16_Register(_LM75_DATA_TEMP_REGISTER_ADDR));
	
	return (float)(raw_temperature_data >> 5) * 0.125;
}

Fixpoint_3bit_t LM75_Get_Fixpoint_3Bit_Temperature()
{
	Fixpoint_3bit_t temp;
	
	int16_t raw_temperature_data = (_LM75_Read_UINT16_Register(_LM75_DATA_TEMP_REGISTER_ADDR));
	
	temp.fract_part_3bit = (uint8_t)(raw_temperature_data & 0b111);
	
	if (raw_temperature_data & 0x8000)
	{
		raw_temperature_data  *= -1;
		raw_temperature_data >>= 8;
		temp.int_part = raw_temperature_data * -1;
	}
	else
	{
		temp.int_part = (int16_t)(raw_temperature_data >> 8);
		temp.fract_part_3bit = 0;
	}
	
	return temp;
}