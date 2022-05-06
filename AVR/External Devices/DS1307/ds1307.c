// ======================================================================================================
//  Header              : ds1307.c                                                                      -
//  Created             : 06.05.2022                                                                    -
//  Author              : Denis Chicherov (dippinest)                                                   -
//  Description         : Defining defining functions and macros for working with the RTC DS1307 chip   -
// ======================================================================================================

#include "ds1307.h"

void _DS1307_Set_Memory_Pointer(uint8_t addr_reg)
{
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	
	I2C_Stop();
}

void _DS1307_Set_Byte(uint8_t addr_reg, uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}

uint8_t _DS1307_Get_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	_DS1307_Set_Memory_Pointer(addr_reg);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	I2C_Read_Byte_Without_Confirmation(&byte);
	
	I2C_Stop();
	
	_delay_ms(5);
	
	return byte;
}

void DS1307_Set_Seconds(uint8_t seconds)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_SECOND, BCDCODE_Convert_UINT8_To_UINT8_BCD(seconds));
}

void DS1307_Set_Minutes(uint8_t minutes)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_MINUTES, BCDCODE_Convert_UINT8_To_UINT8_BCD(minutes));
}

void DS1307_Set_Hours(uint8_t hours)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_HOURS, BCDCODE_Convert_UINT8_To_UINT8_BCD(hours));
}

void DS1307_Set_Weekday(uint8_t weekday)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_WEEKDAY, BCDCODE_Convert_UINT8_To_UINT8_BCD(weekday));
}

void DS1307_Set_Day_Of_Month(uint8_t day_of_month)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_DAY_OF_MONTH, BCDCODE_Convert_UINT8_To_UINT8_BCD(day_of_month));
}

void DS1307_Set_Month(uint8_t month)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_MONTH, BCDCODE_Convert_UINT8_To_UINT8_BCD(month));
}

void DS1307_Set_Year(uint8_t year)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_YEAR, BCDCODE_Convert_UINT8_To_UINT8_BCD(year));
}

void DS1307_Set_Data_From_Struct(DS1307_Data_t *data)
{
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->seconds));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->minutes));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->hours));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->weekday));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->day_of_month));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->month));
	I2C_Send_Byte(BCDCODE_Convert_UINT8_To_UINT8_BCD(data->year));
	
	I2C_Stop();
}

uint8_t DS1307_Get_Seconds()
{
	uint8_t seconds = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	seconds &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	
	seconds = BCDCODE_Convert_UINT8_BCD_To_UINT8(seconds);
	
	return seconds;
}

uint8_t DS1307_Get_Minutes()
{
	uint8_t minutes = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_MINUTES);
	
	minutes = BCDCODE_Convert_UINT8_BCD_To_UINT8(minutes);
	
	return minutes;
}

uint8_t DS1307_Get_Hours()
{
	uint8_t hours = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_HOURS);
	
	hours &= ~(1 << _DS1307_HOUR_MODE_BIT);
	hours =   BCDCODE_Convert_UINT8_BCD_To_UINT8(hours);
	
	return hours;
}

uint8_t DS1307_Get_Weekday()
{
	uint8_t weekday = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_WEEKDAY);
	
	weekday = BCDCODE_Convert_UINT8_BCD_To_UINT8(weekday);
	
	return weekday;
}

uint8_t DS1307_Get_Day_Of_Month()
{
	uint8_t day_of_month = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_DAY_OF_MONTH);
	
	day_of_month = BCDCODE_Convert_UINT8_BCD_To_UINT8(day_of_month);
	
	return day_of_month;
}

uint8_t DS1307_Get_Month()
{
	uint8_t month = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_MONTH);
	
	month = BCDCODE_Convert_UINT8_BCD_To_UINT8(month);
	
	return month;
}

uint8_t DS1307_Get_Year()
{
	uint8_t year = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_YEAR);
	
	year = BCDCODE_Convert_UINT8_BCD_To_UINT8(year);
	
	return year;
}

void DS1307_Get_Data_To_Struct(DS1307_Data_t *data)
{
	uint8_t val;
	
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	I2C_Read_Byte_With_Confirmation(&val);
	val &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	data->seconds = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_With_Confirmation(&val);
	data->minutes = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_With_Confirmation(&val);
	data->hours = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_With_Confirmation(&val);
	data->weekday = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_With_Confirmation(&val);
	data->day_of_month = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_With_Confirmation(&val);
	data->month = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Read_Byte_Without_Confirmation(&val);
	data->year = BCDCODE_Convert_UINT8_BCD_To_UINT8(val);
	
	I2C_Stop();
}

void DS1307_Set_Enable(bool clock_is_enable)
{
	uint8_t current_second_val = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	current_second_val |= (1 << _DS1307_WORK_PERMISSION_BIT_CH);
	
	if (clock_is_enable)
	{
		current_second_val &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	}
	
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_SECOND, current_second_val);
}

void DS1307_Set_Clock_Enable(bool clock_is_enable)
{
	uint8_t current_second_val = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	current_second_val |= (1 << _DS1307_WORK_PERMISSION_BIT_CH);
	
	if (clock_is_enable)
	{
		current_second_val &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	}
	
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_SECOND, current_second_val);
}

void DS1307_Set_SQW_Enable(bool sqw_is_enable)
{
	uint8_t current_control_reg_val = _DS1307_Get_Byte(_DS1307_ADDR_CONTROL_REGISTER);
	
	current_control_reg_val &= ~(1 << _DS1307_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW);
	
	if (sqw_is_enable)
	{
		current_control_reg_val |= (1 << _DS1307_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW);
	}
	
	_DS1307_Set_Byte(_DS1307_ADDR_CONTROL_REGISTER, current_control_reg_val);
}

void DS1307_Set_SQW_Frequency(uint8_t sqw_frequency)
{
	uint8_t current_control_reg_val = _DS1307_Get_Byte(_DS1307_ADDR_CONTROL_REGISTER);
	
	current_control_reg_val &= 0b11111100;
	current_control_reg_val |= (sqw_frequency & 0b00000011);
	
	_DS1307_Set_Byte(_DS1307_ADDR_CONTROL_REGISTER, current_control_reg_val);
}

void DS1307_Write_Byte_To_User_RAM(uint8_t mem_addr, uint8_t byte)
{
	_DS1307_Set_Byte((mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER), byte);
}

uint8_t DS1307_Read_Byte_From_User_RAM(uint8_t mem_addr)
{
	return _DS1307_Get_Byte((mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER));
}

void DS1307_Write_Page_To_User_RAM(uint8_t mem_addr, void *page, uint8_t page_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	for (uint8_t i = 0; i < page_size; i++)
	{
		I2C_Send_Byte(((uint8_t*)page)[i]);
	}
	
	I2C_Stop();
}

void *DS1307_Read_Page_From_User_RAM(uint8_t mem_addr, void *page, uint8_t page_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	for (uint8_t i = 0; i < page_size - 1; i++)
	{
		I2C_Read_Byte_With_Confirmation(&((uint8_t*)page)[i]);
	}
	
	I2C_Read_Byte_Without_Confirmation(&((uint8_t*)page)[page_size - 1]);
	
	I2C_Stop();
	
	return page;
}