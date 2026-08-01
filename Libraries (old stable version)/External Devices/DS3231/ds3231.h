

// ===============================================================================
//
// Библиотека для работы с I2C часами реального времени DS3231/DS3231M.
// I2C можно использовать как аппаратный, так и программный - это можно настроить
// в файле конфигурации ds3231_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the DS3231/DS3231M real-time I2C clock.
// I2C can be used both hardware and software - this can be configured
// in the ds3231_configuration.h configuration file.
//
// ===============================================================================


#ifndef DS3231_H_
#define DS3231_H_


#include <stdint.h>
#include <stdbool.h>

#include "ds3231_configuration.h"



// I2C address device
#define _DS3231_ADDRESS_DEVICE 0x68


// addresses of internal DS3231 registers (time data is stored in them)
#define _DS3231_ADDR_REGISTER_SECOND                0x00
#define _DS3231_ADDR_REGISTER_MINUTES               0x01
#define _DS3231_ADDR_REGISTER_HOURS                 0x02
#define _DS3231_ADDR_REGISTER_WEEKDAY               0x03
#define _DS3231_ADDR_REGISTER_DAY_OF_MONTH          0x04
#define _DS3231_ADDR_REGISTER_MONTH                 0x05
#define _DS3231_ADDR_REGISTER_YEAR                  0x06
#define _DS3231_ADDR_REGISTER_ALARM_1_SECOND        0x07
#define _DS3231_ADDR_REGISTER_ALARM_1_MINUTES       0x08
#define _DS3231_ADDR_REGISTER_ALARM_1_HOURS         0x09
#define _DS3231_ADDR_REGISTER_ALARM_1_WEEKDAY       0x0A
#define _DS3231_ADDR_REGISTER_ALARM_2_MINUTES       0x0B
#define _DS3231_ADDR_REGISTER_ALARM_2_HOURS         0x0C
#define _DS3231_ADDR_REGISTER_ALARM_2_WEEKDAY       0x0D
#define _DS3231_ADDR_CONTROL_REGISTER               0x0E
#define _DS3231_ADDR_CONTROL_AND_STATUS_REGISTER    0x0F
#define _DS3231_ADDR_AGING_OFFSET_REGISTER          0x10
#define _DS3231_ADDR_TEMPERATURE_HIGH_REGISTER      0x11
#define _DS3231_ADDR_TEMPERATURE_LOW_REGISTER       0x12



#define _DS3231_A1_Mx_BIT   7
#define _DS3231_A1_DY_BIT   6
#define _DS3231_A2_Mx_BIT   7
#define _DS3231_A2_DY_BIT   6

#define _DS3231_HOUR_MODE_BIT                             6
#define _DS3231_IS_HOUR_AM_BIT                            5
#define _DS3231_ENABLE_OSCILLATOR_BIT                     7
#define _DS3231_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW     6
#define _DS3231_INTERRUPT_CONTROL_BIT                     2
#define _DS3231_ALARM_2_INTERRUPT_ENABLE_BIT              1
#define _DS3231_ALARM_1_INTERRUPT_ENABLE_BIT              0
#define _DS3231_32768HZ_OUTPUT_ENABLE_BIT                 3
#define _DS3231_CONVERT_TEMPERATURE_START_BIT             3
#define _DS3231_CONVERT_TEMPERATURE_BUSY_BIT              2
#define _DS3231_ALARM_2_FLAG_BIT                          1
#define _DS3231_ALARM_1_FLAG_BIT                          0


// alarm 1 operation mode
#define DS3231_ALARM_1_MODE_EVERY_SECOND                             0b01111
#define DS3231_ALARM_1_MODE_SECONDS_MATCH                            0b01110
#define DS3231_ALARM_1_MODE_MINUTES_AND_SECONDS_MATCH                0b01100
#define DS3231_ALARM_1_MODE_HOURS_MINUTES_AND_SECONDS_MATCH          0b01000
#define DS3231_ALARM_1_MODE_DATE_HOURS_MINUTES_AND_SECONDS_MATCH     0b00000
#define DS3231_ALARM_1_MODE_WEEKDAY_HOURS_MINUTES_AND_SECONDS_MATCH  0b10000


// alarm 2 operation mode
#define DS3231_ALARM_2_MODE_EVERY_MINUTE                             0b0111
#define DS3231_ALARM_2_MODE_MINUTES_MATCH                            0b0110
#define DS3231_ALARM_2_MODE_HOURS_AND_MINUTES_MATCH                  0b0100
#define DS3231_ALARM_2_MODE_DATE_HOURS_AND_MINUTES_MATCH             0b0000
#define DS3231_ALARM_2_MODE_WEEKDAY_HOURS_AND_MINUTES_MATCH          0b1000



// operating modes of the SQW generator
#define DS3231_SQW_FREQUENCY_1_HZ     0b00
#define DS3231_SQW_FREQUENCY_1024_HZ  0b01
#define DS3231_SQW_FREQUENCY_4096_HZ  0b10
#define DS3231_SQW_FREQUENCY_8192_HZ  0b11




enum DS3231_Enum_Days
{
	MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};



enum DS3231_Enum_Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};


// structure for storing time data
typedef struct
{
	uint8_t seconds;       // seconds
	uint8_t minutes;       // minutes
	uint8_t hours;         // hours
	uint8_t weekday;       // day of weekday
	uint8_t day_of_month;  // day of month
	uint8_t month;         // month
	uint8_t year;          // year (add the current two-digit year to the 2000th)
	
} DS3231_Data_t;



// ===============================================================================



void DS3231_Set_Data_From_Struct(DS3231_Data_t *data);

void DS3231_Get_Data_To_Struct(DS3231_Data_t *data);



// ===============================================================================



void DS3231_Set_Seconds(uint8_t seconds);

void DS3231_Set_Minutes(uint8_t minutes);

void DS3231_Set_Hours(uint8_t hours);

void DS3231_Set_Weekday(uint8_t weekday);

void DS3231_Set_Day_Of_Month(uint8_t day_of_month);

void DS3231_Set_Month(uint8_t month);

void DS3231_Set_Year(uint8_t year);



// ===============================================================================



uint8_t DS3231_Get_Seconds();

uint8_t DS3231_Get_Minutes();

uint8_t DS3231_Get_Hours();

uint8_t DS3231_Get_Weekday();

uint8_t DS3231_Get_Day_Of_Month();

uint8_t DS3231_Get_Month();

uint8_t DS3231_Get_Year();



// ===============================================================================


void DS3231_Set_Aging_Offset(int8_t offset);

int8_t DS3231_Get_Aging_Offset();

void DS3231_Start_Temperature_Compensation_Process();


// ===============================================================================



int8_t DS3231_Get_Integer_Temperature();

float DS3231_Get_Float_Temperature();

int16_t DS3231_Get_FIXPoint_2_Fractional_Digits_Temperature();



// ===============================================================================



void DS3231_Set_Clock_Enable(bool clock_is_enable);

void DS3231_Set_32768HZ_Output_Enable(uint8_t _32khz_output_is_enable);

void DS3231_Set_SQW_Enable(bool sqw_is_enable);


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
void DS3231_Set_SQW_Frequency(uint8_t sqw_frequency);



// ===============================================================================



void DS3231_Set_Alarms_Interrupt_Enable(bool interrupt_is_enable);


void DS3231_Set_Alarm_1_Enable(bool alarm_1_is_enable);

bool DS3231_Alarm_1_Is_Enable();

bool DS3231_Alarm_1_Is_Triggered();

void DS3231_Alarm_1_Flag_Reset();

void DS3231_Set_Alarm_1_Seconds(uint8_t seconds);

void DS3231_Set_Alarm_1_Minutes(uint8_t minutes);

void DS3231_Set_Alarm_1_Hours(uint8_t hours);

void DS3231_Set_Alarm_1_Weekday(uint8_t weekday);

void DS3231_Set_Alarm_1_Day_Of_Month(uint8_t day_of_month);


uint8_t DS3231_Get_Alarm_1_Seconds();

uint8_t DS3231_Get_Alarm_1_Minutes();

uint8_t DS3231_Get_Alarm_1_Hours();

uint8_t DS3231_Get_Alarm_1_Weekday();

uint8_t DS3231_Get_Alarm_1_Day_Of_Month();

void DS3231_Set_Alarm_1_Mode(uint8_t alarm_1_mode);



// ===============================================================================



void DS3231_Set_Alarm_2_Enable(bool alarm_2_is_enable);

bool DS3231_Alarm_2_Is_Enable();

bool DS3231_Alarm_2_Is_Triggered();

void DS3231_Alarm_2_Flag_Reset();

void DS3231_Set_Alarm_2_Minutes(uint8_t minutes);

void DS3231_Set_Alarm_2_Hours(uint8_t hours);

void DS3231_Set_Alarm_2_Weekday(uint8_t weekday);

void DS3231_Set_Alarm_2_Day_Of_Month(uint8_t day_of_month);


uint8_t DS3231_Get_Alarm_2_Minutes();

uint8_t DS3231_Get_Alarm_2_Hours();

uint8_t DS3231_Get_Alarm_2_Weekday();

uint8_t DS3231_Get_Alarm_2_Day_Of_Month();

void DS3231_Set_Alarm_2_Mode(uint8_t alarm_2_mode);


#endif




