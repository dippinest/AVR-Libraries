
#include "ds3231.h"


uint8_t _DS3231_UInt8_To_UInt8BCD(uint8_t num)
{
	return ((num / 10) << 4) | (num % 10);
}

uint8_t _DS3231_UInt8BCD_To_UInt8(uint8_t bcd_code)
{
	uint8_t num = (bcd_code >> 4) * 10;
	num += (bcd_code & 0x0F);
	return num;
}


#ifdef DS3231_USE_SOFTI2C


#include "softi2c.h"


void _DS3231_Set_Memory_Pointer(uint8_t addr_reg)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	
	SOFTI2C_Stop();
}

void _DS3231_Set_Byte(uint8_t addr_reg, uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}

uint8_t _DS3231_Get_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	_DS3231_Set_Memory_Pointer(addr_reg);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte((_DS3231_ADDRESS_DEVICE << 1) | 1);
	
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	return byte;
}

void DS3231_Set_Data_From_Struct(DS3231_Data_t *data)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(_DS3231_ADDR_REGISTER_SECOND);
	
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->seconds));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->minutes));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->hours));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->weekday));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->day_of_month));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->month));
	SOFTI2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->year));
	
	SOFTI2C_Stop();
}

void DS3231_Get_Data_To_Struct(DS3231_Data_t *data)
{
	uint8_t val;
	
	
	_DS3231_Set_Memory_Pointer(_DS3231_ADDR_REGISTER_SECOND);
	
	SOFTI2C_Start();
	
	
	SOFTI2C_Send_Byte((_DS3231_ADDRESS_DEVICE << 1) | 1);
	
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	
	data->seconds = _DS3231_UInt8BCD_To_UInt8(val);
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	data->minutes = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	val &= 0b00111111;
	
	data->hours = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	data->weekday = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	data->day_of_month = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Read_Byte(&val, ACK);
	
	val &= 0b00011111;
	
	data->month = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Read_Byte(&val, NACK);
	
	data->year = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	SOFTI2C_Stop();
}


#else

#include "i2c.h"


void _DS3231_Set_Memory_Pointer(uint8_t addr_reg)
{
	I2C_Start();
	
	I2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	
	I2C_Stop();
}

void _DS3231_Set_Byte(uint8_t addr_reg, uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}

uint8_t _DS3231_Get_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	_DS3231_Set_Memory_Pointer(addr_reg);
	
	I2C_Start();
	
	I2C_Send_Byte((_DS3231_ADDRESS_DEVICE << 1) | 1);
	
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	return byte;
}

void DS3231_Set_Data_From_Struct(DS3231_Data_t *data)
{
	I2C_Start();
	
	I2C_Send_Byte(_DS3231_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(_DS3231_ADDR_REGISTER_SECOND);
	
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->seconds));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->minutes));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->hours));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->weekday));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->day_of_month));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->month));
	I2C_Send_Byte(_DS3231_UInt8_To_UInt8BCD(data->year));
	
	I2C_Stop();
}

void DS3231_Get_Data_To_Struct(DS3231_Data_t *data)
{
	uint8_t val;
	
	
	_DS3231_Set_Memory_Pointer(_DS3231_ADDR_REGISTER_SECOND);
	
	I2C_Start();
	
	
	I2C_Send_Byte((_DS3231_ADDRESS_DEVICE << 1) | 1);
	
	
	I2C_Read_Byte(&val, ACK);
	
	
	data->seconds = _DS3231_UInt8BCD_To_UInt8(val);
	
	I2C_Read_Byte(&val, ACK);
	
	data->minutes = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Read_Byte(&val, ACK);
	
	val &= 0b00111111;
	
	data->hours = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Read_Byte(&val, ACK);
	
	data->weekday = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Read_Byte(&val, ACK);
	
	data->day_of_month = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Read_Byte(&val, ACK);
	
	val &= 0b00011111;
	
	data->month = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Read_Byte(&val, NACK);
	
	data->year = _DS3231_UInt8BCD_To_UInt8(val);
	
	
	
	I2C_Stop();
}


#endif




void DS3231_Set_Seconds(uint8_t seconds)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_SECOND, _DS3231_UInt8_To_UInt8BCD(seconds));
}


void DS3231_Set_Minutes(uint8_t minutes)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_MINUTES, _DS3231_UInt8_To_UInt8BCD(minutes));
}


void DS3231_Set_Hours(uint8_t hours)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_HOURS, _DS3231_UInt8_To_UInt8BCD(hours));
}


void DS3231_Set_Weekday(uint8_t weekday)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_WEEKDAY, _DS3231_UInt8_To_UInt8BCD(weekday));
}


void DS3231_Set_Day_Of_Month(uint8_t day_of_month)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_DAY_OF_MONTH, _DS3231_UInt8_To_UInt8BCD(day_of_month));
}


void DS3231_Set_Month(uint8_t month)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_MONTH, _DS3231_UInt8_To_UInt8BCD(month));
}


void DS3231_Set_Year(uint8_t year)
{
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_YEAR, _DS3231_UInt8_To_UInt8BCD(year));
}



// ===============================================================================



uint8_t DS3231_Get_Seconds()
{
	uint8_t seconds = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_SECOND);
	
	seconds = _DS3231_UInt8BCD_To_UInt8(seconds);
	
	return seconds;
}


uint8_t DS3231_Get_Minutes()
{
	uint8_t minutes = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_MINUTES);
	
	minutes = _DS3231_UInt8BCD_To_UInt8(minutes);
	
	return minutes;
}


uint8_t DS3231_Get_Hours()
{
	uint8_t hours = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_HOURS);
	
	hours &= 0b00111111;
	
	hours = _DS3231_UInt8BCD_To_UInt8(hours);
	
	return hours;
}


uint8_t DS3231_Get_Weekday()
{
	uint8_t weekday = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_WEEKDAY);
	
	weekday = _DS3231_UInt8BCD_To_UInt8(weekday);
	
	return weekday;
}


uint8_t DS3231_Get_Day_Of_Month()
{
	uint8_t day_of_month = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_DAY_OF_MONTH);
	
	day_of_month = _DS3231_UInt8BCD_To_UInt8(day_of_month);
	
	return day_of_month;
}


uint8_t DS3231_Get_Month()
{
	uint8_t month = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_MONTH);
	
	month &= 0b00011111;
	
	month = _DS3231_UInt8BCD_To_UInt8(month);
	
	return month;
}


uint8_t DS3231_Get_Year()
{
	uint8_t year = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_YEAR);
	
	year = _DS3231_UInt8BCD_To_UInt8(year);
	
	return year;
}



// ===============================================================================


void DS3231_Set_Aging_Offset(int8_t offset)
{
	_DS3231_Set_Byte(_DS3231_ADDR_AGING_OFFSET_REGISTER, (uint8_t)offset);
}

int8_t DS3231_Get_Aging_Offset()
{
	int8_t offset = (int8_t)_DS3231_Get_Byte(_DS3231_ADDR_AGING_OFFSET_REGISTER);

	return offset;
}

void DS3231_Start_Temperature_Compensation_Process()
{
	while(_DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER) & (1 << _DS3231_CONVERT_TEMPERATURE_BUSY_BIT));
	
	
	uint8_t control_reg_value = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_value |= (1 << _DS3231_CONVERT_TEMPERATURE_START_BIT);
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_value);
	
	
	while(_DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER) & (1 << _DS3231_CONVERT_TEMPERATURE_BUSY_BIT));
}


// ===============================================================================



int8_t DS3231_Get_Integer_Temperature()
{
	int8_t temperature_high_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_TEMPERATURE_HIGH_REGISTER);

	return temperature_high_reg_val;
}


float DS3231_Get_Float_Temperature()
{
	int8_t  temperature_high_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_TEMPERATURE_HIGH_REGISTER);
	uint8_t temperature_low_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_TEMPERATURE_LOW_REGISTER);

	float temperature;


	if (temperature_high_reg_val & 0b10000000)
	{
		temperature = (float)temperature_high_reg_val - ((temperature_low_reg_val >> 6) * 0.25);
	}
	else
	{
		temperature = (float)temperature_high_reg_val + ((temperature_low_reg_val >> 6) * 0.25);
	}


	return temperature;
}


int16_t DS3231_Get_FIXPoint_2_Fractional_Digits_Temperature()
{
	int8_t  temperature_high_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_TEMPERATURE_HIGH_REGISTER);
	uint8_t temperature_low_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_TEMPERATURE_LOW_REGISTER);

	int16_t temperature = temperature_high_reg_val;

	temperature *= 100;


	if (temperature_high_reg_val & 0b10000000)
	{
		temperature -= ((temperature_low_reg_val >> 6) * 25);
	}
	else
	{
		temperature += ((temperature_low_reg_val >> 6) * 25);
	}


	return temperature;
}



// ===============================================================================



void DS3231_Set_Clock_Enable(bool clock_is_enable)
{
	uint8_t control_reg_value = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_value |= (1 << _DS3231_ENABLE_OSCILLATOR_BIT);
	
	
	if (clock_is_enable)
	{
		control_reg_value &= ~(1 << _DS3231_ENABLE_OSCILLATOR_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_value);
}


void DS3231_Set_32768HZ_Output_Enable(uint8_t _32khz_output_is_enable)
{
	uint8_t control_and_status_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER);
	
	control_and_status_reg_val &= ~(1 << _DS3231_32768HZ_OUTPUT_ENABLE_BIT);
	
	
	if (_32khz_output_is_enable)
	{
		control_and_status_reg_val |=  (1 << _DS3231_32768HZ_OUTPUT_ENABLE_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER, control_and_status_reg_val);
}


void DS3231_Set_SQW_Enable(bool sqw_is_enable)
{
	DS3231_Alarm_1_Flag_Reset();
	DS3231_Alarm_2_Flag_Reset();
	
	
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_val &= ~(1 << _DS3231_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW);
	control_reg_val |=  (1 << _DS3231_INTERRUPT_CONTROL_BIT);
	
	
	if (sqw_is_enable)
	{
		control_reg_val |=  (1 << _DS3231_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW);
		control_reg_val &= ~(1 << _DS3231_INTERRUPT_CONTROL_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_val);
}


// Эта функция НЕ РАБОТАЕТ с чипами DS3231M, только с DS3231 !
//
// В DS3231M нет функции изменении частоты: она всегда равна 1 Гц!
//
// -------------------------------------------------------------------------------
//
// This function DOES NOT WORK with DS3231M chips, only with DS3231!
//
// The DS3231M does not have a frequency change function: it is always 1 Hz!
//
void DS3231_Set_SQW_Frequency(uint8_t sqw_frequency)
{
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_val &= 0b11100111;
	
	control_reg_val |= ((sqw_frequency & 0b11) << 3);
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_val);
}



// ===============================================================================



void DS3231_Set_Alarms_Interrupt_Enable(bool interrupt_is_enable)
{
	DS3231_Alarm_1_Flag_Reset();
	DS3231_Alarm_2_Flag_Reset();
	
	
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_val &= ~(1 << _DS3231_INTERRUPT_CONTROL_BIT);
	control_reg_val &= ~(1 << _DS3231_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW);
	
	
	if (interrupt_is_enable)
	{
		control_reg_val |= (1 << _DS3231_INTERRUPT_CONTROL_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_val);
}



void DS3231_Set_Alarm_1_Enable(bool alarm_1_is_enable)
{
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_val &= ~(1 << _DS3231_ALARM_1_INTERRUPT_ENABLE_BIT);
	
	
	if (alarm_1_is_enable)
	{
		control_reg_val |=  (1 << _DS3231_ALARM_1_INTERRUPT_ENABLE_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_val);
}


bool DS3231_Alarm_1_Is_Enable()
{
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	
	if (control_reg_val & (1 << _DS3231_ALARM_1_INTERRUPT_ENABLE_BIT))
	{
		return true;
	}
	
	return false;
}


bool DS3231_Alarm_1_Is_Triggered()
{
	uint8_t control_and_status_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER);
	
	
	if (control_and_status_reg_val & (1 << _DS3231_ALARM_1_FLAG_BIT))
	{
		return true;
	}
	
	return false;
}


void DS3231_Alarm_1_Flag_Reset()
{
	uint8_t control_and_status_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER);
	
	control_and_status_reg_val &= ~(1 << _DS3231_ALARM_1_FLAG_BIT);
	
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER, control_and_status_reg_val);
}


void DS3231_Set_Alarm_1_Seconds(uint8_t seconds)
{
	seconds = _DS3231_UInt8_To_UInt8BCD(seconds);
	
	uint8_t alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_SECOND);
	
	
	if (alarm_1_reg & (1 << _DS3231_A1_Mx_BIT))
	{
		seconds |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_SECOND, seconds);
}


void DS3231_Set_Alarm_1_Minutes(uint8_t minutes)
{
	minutes = _DS3231_UInt8_To_UInt8BCD(minutes);
	
	uint8_t alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_MINUTES);
	
	
	if (alarm_1_reg & (1 << _DS3231_A1_Mx_BIT))
	{
		minutes |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_MINUTES, minutes);
}


void DS3231_Set_Alarm_1_Hours(uint8_t hours)
{
	hours = _DS3231_UInt8_To_UInt8BCD(hours);
	
	uint8_t alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_HOURS);
	
	
	if (alarm_1_reg & (1 << _DS3231_A1_Mx_BIT))
	{
		hours |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_HOURS, hours);
}


void DS3231_Set_Alarm_1_Weekday(uint8_t weekday)
{
	weekday = _DS3231_UInt8_To_UInt8BCD(weekday);
	
	uint8_t alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY);
	
	
	if (alarm_1_reg & (1 << _DS3231_A1_Mx_BIT))
	{
		weekday |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	if (alarm_1_reg & (1 << _DS3231_A1_DY_BIT))
	{
		weekday |= (1 << _DS3231_A1_DY_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY, weekday);
}


void DS3231_Set_Alarm_1_Day_Of_Month(uint8_t day_of_month)
{
	DS3231_Set_Alarm_1_Weekday(day_of_month);
}



uint8_t DS3231_Get_Alarm_1_Seconds()
{
	uint8_t seconds = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_SECOND);
	
	
	if (seconds & (1 << _DS3231_A1_Mx_BIT))
	{
		seconds &= ~(1 << _DS3231_A1_Mx_BIT);
	}
	
	seconds = _DS3231_UInt8BCD_To_UInt8(seconds);
	
	return seconds;
}


uint8_t DS3231_Get_Alarm_1_Minutes()
{
	uint8_t minutes = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_MINUTES);
	
	
	if (minutes & (1 << _DS3231_A1_Mx_BIT))
	{
		minutes &= ~(1 << _DS3231_A1_Mx_BIT);
	}
	
	minutes = _DS3231_UInt8BCD_To_UInt8(minutes);
	
	return minutes;
}


uint8_t DS3231_Get_Alarm_1_Hours()
{
	uint8_t hours = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_HOURS);
	
	
	if (hours & (1 << _DS3231_A1_Mx_BIT))
	{
		hours &= ~(1 << _DS3231_A1_Mx_BIT);
	}
	
	hours &= ~(1 << _DS3231_HOUR_MODE_BIT);
	hours = _DS3231_UInt8BCD_To_UInt8(hours);
	
	return hours;
}


uint8_t DS3231_Get_Alarm_1_Weekday()
{
	uint8_t weekday = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY);
	
	
	if (weekday & (1 << _DS3231_A1_Mx_BIT))
	{
		weekday &= ~(1 << _DS3231_A1_Mx_BIT);
	}
	
	if (weekday & (1 << _DS3231_A1_DY_BIT))
	{
		weekday &= ~(1 << _DS3231_A1_DY_BIT);
	}
	
	weekday = _DS3231_UInt8BCD_To_UInt8(weekday);
	
	return weekday;
}


uint8_t DS3231_Get_Alarm_1_Day_Of_Month()
{
	uint8_t day_of_month = DS3231_Get_Weekday();
	
	return day_of_month;
}


void DS3231_Set_Alarm_1_Mode(uint8_t alarm_1_mode)
{
	uint8_t alarm_1_reg;
	
	
	
	// A1M1
	
	alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_SECOND);
	
	alarm_1_reg &= ~(1 << _DS3231_A1_Mx_BIT);
	
	if (alarm_1_mode & 0b1)
	{
		alarm_1_reg |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_SECOND, alarm_1_reg); alarm_1_mode >>= 1;
	
	
	
	// A1M2
	
	alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_MINUTES);
	
	alarm_1_reg &= ~(1 << _DS3231_A1_Mx_BIT);
	
	if (alarm_1_mode & 0b1)
	{
		alarm_1_reg |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_MINUTES, alarm_1_reg); alarm_1_mode >>= 1;
	
	
	
	// A1M3
	
	alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_HOURS);
	
	alarm_1_reg &= ~(1 << _DS3231_A1_Mx_BIT);
	
	if (alarm_1_mode & 0b1)
	{
		alarm_1_reg |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_HOURS, alarm_1_reg); alarm_1_mode >>= 1;
	
	
	
	// A1M4 and DY/~DT
	
	alarm_1_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY);
	
	alarm_1_reg &= ~(1 << _DS3231_A1_Mx_BIT);
	
	if (alarm_1_mode & 0b1)
	{
		alarm_1_reg |= (1 << _DS3231_A1_Mx_BIT);
	}
	
	alarm_1_mode >>= 1;
	
	
	alarm_1_reg &= ~(1 << _DS3231_A1_DY_BIT);
	
	if (alarm_1_mode & 0b1)
	{
		alarm_1_reg |= (1 << _DS3231_A1_DY_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY, alarm_1_reg);
}



// ===============================================================================



void DS3231_Set_Alarm_2_Enable(bool alarm_2_is_enable)
{
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	control_reg_val &= ~(1 << _DS3231_ALARM_2_INTERRUPT_ENABLE_BIT);
	
	
	if (alarm_2_is_enable)
	{
		control_reg_val |=  (1 << _DS3231_ALARM_2_INTERRUPT_ENABLE_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_REGISTER, control_reg_val);
}


bool DS3231_Alarm_2_Is_Enable()
{
	uint8_t control_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_REGISTER);
	
	
	if (control_reg_val & (1 << _DS3231_ALARM_2_INTERRUPT_ENABLE_BIT))
	{
		return true;
	}
	
	return false;
}


bool DS3231_Alarm_2_Is_Triggered()
{
	uint8_t control_and_status_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER);
	
	
	if (control_and_status_reg_val & (1 << _DS3231_ALARM_2_FLAG_BIT))
	{
		return true;
	}
	
	return false;
}


void DS3231_Alarm_2_Flag_Reset()
{
	uint8_t control_and_status_reg_val = _DS3231_Get_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER);
	
	control_and_status_reg_val &= ~(1 << _DS3231_ALARM_2_FLAG_BIT);
	
	
	_DS3231_Set_Byte(_DS3231_ADDR_CONTROL_AND_STATUS_REGISTER, control_and_status_reg_val);
}


void DS3231_Set_Alarm_2_Minutes(uint8_t minutes)
{
	minutes = _DS3231_UInt8_To_UInt8BCD(minutes);
	
	uint8_t alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_MINUTES);
	
	
	if (alarm_2_reg & (1 << _DS3231_A2_Mx_BIT))
	{
		minutes |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_MINUTES, minutes);
}


void DS3231_Set_Alarm_2_Hours(uint8_t hours)
{
	hours = _DS3231_UInt8_To_UInt8BCD(hours);
	
	uint8_t alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_HOURS);
	
	
	if (alarm_2_reg & (1 << _DS3231_A2_Mx_BIT))
	{
		hours |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_HOURS, hours);
}


void DS3231_Set_Alarm_2_Weekday(uint8_t weekday)
{
	weekday = _DS3231_UInt8_To_UInt8BCD(weekday);
	
	uint8_t alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY);
	
	
	if (alarm_2_reg & (1 << _DS3231_A2_Mx_BIT))
	{
		weekday |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	if (alarm_2_reg & (1 << _DS3231_A1_DY_BIT))
	{
		weekday |= (1 << _DS3231_A1_DY_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY, weekday);
}


void DS3231_Set_Alarm_2_Day_Of_Month(uint8_t day_of_month)
{
	DS3231_Set_Alarm_2_Weekday(day_of_month);
}



uint8_t DS3231_Get_Alarm_2_Minutes()
{
	uint8_t minutes = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_MINUTES);
	
	
	if (minutes & (1 << _DS3231_A2_Mx_BIT))
	{
		minutes &= ~(1 << _DS3231_A2_Mx_BIT);
	}
	
	minutes = _DS3231_UInt8BCD_To_UInt8(minutes);
	
	return minutes;
}


uint8_t DS3231_Get_Alarm_2_Hours()
{
	uint8_t hours = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_HOURS);
	
	
	if (hours & (1 << _DS3231_A2_Mx_BIT))
	{
		hours &= ~(1 << _DS3231_A2_Mx_BIT);
	}
	
	hours &= ~(1 << _DS3231_HOUR_MODE_BIT);
	hours =   _DS3231_UInt8BCD_To_UInt8(hours);
	
	return hours;
}


uint8_t DS3231_Get_Alarm_2_Weekday()
{
	uint8_t weekday = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY);
	
	
	if (weekday & (1 << _DS3231_A2_Mx_BIT))
	{
		weekday &= ~(1 << _DS3231_A2_Mx_BIT);
	}
	
	if (weekday & (1 << _DS3231_A1_DY_BIT))
	{
		weekday &= ~(1 << _DS3231_A1_DY_BIT);
	}
	
	weekday = _DS3231_UInt8BCD_To_UInt8(weekday);
	
	return weekday;
}


uint8_t DS3231_Get_Alarm_2_Day_Of_Month()
{
	uint8_t day_of_month = DS3231_Get_Weekday();
	
	return day_of_month;
}


void DS3231_Set_Alarm_2_Mode(uint8_t alarm_2_mode)
{
	uint8_t alarm_2_reg;
	
	
	
	// A2M2
	
	alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_MINUTES);
	
	alarm_2_reg &= ~(1 << _DS3231_A2_Mx_BIT);
	
	if (alarm_2_mode & 0b1)
	{
		alarm_2_reg |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_MINUTES, alarm_2_reg); alarm_2_mode >>= 1;
	
	
	
	// A2M3
	
	alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_HOURS);
	
	alarm_2_reg &= ~(1 << _DS3231_A2_Mx_BIT);
	
	if (alarm_2_mode & 0b1)
	{
		alarm_2_reg |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_HOURS, alarm_2_reg); alarm_2_mode >>= 1;
	
	
	
	// A2M4 and DY/~DT
	
	alarm_2_reg = _DS3231_Get_Byte(_DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY);
	
	alarm_2_reg &= ~(1 << _DS3231_A2_Mx_BIT);
	
	if (alarm_2_mode & 0b1)
	{
		alarm_2_reg |= (1 << _DS3231_A2_Mx_BIT);
	}
	
	alarm_2_mode >>= 1;
	
	
	alarm_2_reg &= ~(1 << _DS3231_A2_DY_BIT);
	
	if (alarm_2_mode & 0b1)
	{
		alarm_2_reg |= (1 << _DS3231_A2_DY_BIT);
	}
	
	_DS3231_Set_Byte(_DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY, alarm_2_reg);
}








