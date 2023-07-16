
#include "ds1307.h"

#ifdef DS1307_USE_SOFTI2C

void _DS1307_Set_Memory_Pointer(uint8_t addr_reg)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	
	SOFTI2C_Stop();
}

void _DS1307_Set_Byte(uint8_t addr_reg, uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}

uint8_t _DS1307_Get_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	_DS1307_Set_Memory_Pointer(addr_reg);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	return byte;
}

void DS1307_Set_Data_From_Struct(DS1307_Data_t *data)
{
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->seconds));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->minutes));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->hours));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->weekday));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->day_of_month));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->month));
	SOFTI2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->year));
	
	SOFTI2C_Stop();
}

void DS1307_Get_Data_To_Struct(DS1307_Data_t *data)
{
	uint8_t val;
	
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	SOFTI2C_Read_Byte(&val, ACK);
	val &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	data->seconds = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	data->minutes = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	data->hours = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	data->weekday = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	data->day_of_month = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	data->month = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, NACK);
	data->year = BCDCODE_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Stop();
}

void DS1307_Write_Data_To_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	for (uint8_t i = 0; i < data_size; i++)
	{
		SOFTI2C_Send_Byte(((uint8_t*)data)[i]);
	}
	
	SOFTI2C_Stop();
}

void *DS1307_Read_Data_From_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	for (uint8_t i = 0; i < data_size - 1; i++)
	{
		SOFTI2C_Read_Byte(&((uint8_t*)data)[i], ACK);
	}
	
	SOFTI2C_Read_Byte(&((uint8_t*)data)[data_size - 1], NACK);
	
	SOFTI2C_Stop();
	
	return data;
}

#else

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
	
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	return byte;
}

void DS1307_Set_Data_From_Struct(DS1307_Data_t *data)
{
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->seconds));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->minutes));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->hours));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->weekday));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->day_of_month));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->month));
	I2C_Send_Byte(BCDCODE_UInt8_To_UInt8BCD(data->year));
	
	I2C_Stop();
}

void DS1307_Get_Data_To_Struct(DS1307_Data_t *data)
{
	uint8_t val;
	
	_DS1307_Set_Memory_Pointer(_DS1307_ADDR_REGISTER_SECOND);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	I2C_Read_Byte(&val, ACK);
	val &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	data->seconds = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	data->minutes = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	data->hours = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	data->weekday = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	data->day_of_month = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	data->month = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, NACK);
	data->year = BCDCODE_UInt8BCD_To_UInt8(val);
	
	I2C_Stop();
}

void DS1307_Write_Data_To_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	I2C_Start();
	
	I2C_Send_Byte(_DS1307_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	for (uint8_t i = 0; i < data_size; i++)
	{
		I2C_Send_Byte(((uint8_t*)data)[i]);
	}
	
	I2C_Stop();
}

void *DS1307_Read_Data_From_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size)
{
	_DS1307_Set_Memory_Pointer(mem_addr + _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS1307_ADDRESS_DEVICE << 1) | 1);
	
	for (uint8_t i = 0; i < data_size - 1; i++)
	{
		I2C_Read_Byte(&((uint8_t*)data)[i], ACK);
	}
	
	I2C_Read_Byte(&((uint8_t*)data)[data_size - 1], NACK);
	
	I2C_Stop();
	
	return data;
}

#endif

void DS1307_Set_Seconds(uint8_t seconds)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_SECOND, BCDCODE_UInt8_To_UInt8BCD(seconds));
}

void DS1307_Set_Minutes(uint8_t minutes)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_MINUTES, BCDCODE_UInt8_To_UInt8BCD(minutes));
}

void DS1307_Set_Hours(uint8_t hours)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_HOURS, BCDCODE_UInt8_To_UInt8BCD(hours));
}

void DS1307_Set_Weekday(uint8_t weekday)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_WEEKDAY, BCDCODE_UInt8_To_UInt8BCD(weekday));
}

void DS1307_Set_Day_Of_Month(uint8_t day_of_month)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_DAY_OF_MONTH, BCDCODE_UInt8_To_UInt8BCD(day_of_month));
}

void DS1307_Set_Month(uint8_t month)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_MONTH, BCDCODE_UInt8_To_UInt8BCD(month));
}

void DS1307_Set_Year(uint8_t year)
{
	_DS1307_Set_Byte(_DS1307_ADDR_REGISTER_CURRENT_YEAR, BCDCODE_UInt8_To_UInt8BCD(year));
}

uint8_t DS1307_Get_Seconds()
{
	uint8_t seconds = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_SECOND);
	
	seconds &= ~(1 << _DS1307_WORK_PERMISSION_BIT_CH);
	
	seconds = BCDCODE_UInt8BCD_To_UInt8(seconds);
	
	return seconds;
}

uint8_t DS1307_Get_Minutes()
{
	uint8_t minutes = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_MINUTES);
	
	minutes = BCDCODE_UInt8BCD_To_UInt8(minutes);
	
	return minutes;
}

uint8_t DS1307_Get_Hours()
{
	uint8_t hours = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_HOURS);
	
	hours &= ~(1 << _DS1307_HOUR_MODE_BIT);
	hours =   BCDCODE_UInt8BCD_To_UInt8(hours);
	
	return hours;
}

uint8_t DS1307_Get_Weekday()
{
	uint8_t weekday = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_WEEKDAY);
	
	weekday = BCDCODE_UInt8BCD_To_UInt8(weekday);
	
	return weekday;
}

uint8_t DS1307_Get_Day_Of_Month()
{
	uint8_t day_of_month = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_DAY_OF_MONTH);
	
	day_of_month = BCDCODE_UInt8BCD_To_UInt8(day_of_month);
	
	return day_of_month;
}

uint8_t DS1307_Get_Month()
{
	uint8_t month = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_MONTH);
	
	month = BCDCODE_UInt8BCD_To_UInt8(month);
	
	return month;
}

uint8_t DS1307_Get_Year()
{
	uint8_t year = _DS1307_Get_Byte(_DS1307_ADDR_REGISTER_CURRENT_YEAR);
	
	year = BCDCODE_UInt8BCD_To_UInt8(year);
	
	return year;
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
