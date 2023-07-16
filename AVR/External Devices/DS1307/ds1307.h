
#ifndef DS1307_H_
#define DS1307_H_

#include <util/delay.h>
#include <stdbool.h>
#include "bcdcode.h"

#include "ds1307_configuration.h"

#ifdef DS1307_USE_SOFTI2C
#include "softi2c.h"
#else
#include "i2c.h"
#endif

// I2C address device
#define _DS1307_ADDRESS_DEVICE 0x68

// addresses of internal DS1307 registers (time data is stored in them)
#define _DS1307_ADDR_REGISTER_SECOND                0x00
#define _DS1307_ADDR_REGISTER_MINUTES               0x01
#define _DS1307_ADDR_REGISTER_HOURS                 0x02
#define _DS1307_ADDR_REGISTER_CURRENT_WEEKDAY       0x03
#define _DS1307_ADDR_REGISTER_CURRENT_DAY_OF_MONTH  0x04
#define _DS1307_ADDR_REGISTER_CURRENT_MONTH         0x05
#define _DS1307_ADDR_REGISTER_CURRENT_YEAR          0x06
#define _DS1307_ADDR_CONTROL_REGISTER               0x07
#define _DS1307_ADDR_VERTEX_OF_USER_RAM_REGISTER    0x08

#define _DS1307_HOUR_MODE_BIT                           6
#define _DS1307_IS_HOUR_AM_BIT                          5
#define _DS1307_WORK_PERMISSION_BIT_CH                  7
#define _DS1307_SQUARE_WAVE_OUTPUT_PERMISSION_BIT_SQW   4

#define DS1307_SQWE_FREQUENCY_1_HZ                      0x0
#define DS1307_SQWE_FREQUENCY_4096_HZ                   0x1
#define DS1307_SQWE_FREQUENCY_8192_HZ                   0x2
#define DS1307_SQWE_FREQUENCY_32768_HZ                  0x3


enum DS1307_Enum_Days
{
	MONDAY = 1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};

enum DS1307_Enum_Month
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
	
} DS1307_Data_t;

void DS1307_Set_Seconds(uint8_t seconds);

void DS1307_Set_Minutes(uint8_t minutes);

void DS1307_Set_Hours(uint8_t hours);

void DS1307_Set_Weekday(uint8_t weekday);

void DS1307_Set_Day_Of_Month(uint8_t day_of_month);

void DS1307_Set_Month(uint8_t month);

void DS1307_Set_Year(uint8_t year);

void DS1307_Set_Data_From_Struct(DS1307_Data_t *data);

uint8_t DS1307_Get_Seconds();

uint8_t DS1307_Get_Minutes();

uint8_t DS1307_Get_Hours();

uint8_t DS1307_Get_Weekday();

uint8_t DS1307_Get_Day_Of_Month();

uint8_t DS1307_Get_Month();

uint8_t DS1307_Get_Year();

void DS1307_Get_Data_To_Struct(DS1307_Data_t *data);

void DS1307_Set_Enable(bool clock_is_enable);

void DS1307_Set_Clock_Enable(bool clock_is_enable);

void DS1307_Set_SQW_Enable(bool sqw_is_enable);


// these functions are used to write data to the user RAM area
// (56 bytes are available). Memory addresses range - from 0x00 to 0x37

void DS1307_Set_SQW_Frequency(uint8_t sqw_frequency);

void DS1307_Write_Byte_To_User_RAM(uint8_t mem_addr, uint8_t byte);

uint8_t DS1307_Read_Byte_From_User_RAM(uint8_t mem_addr);

void DS1307_Write_Data_To_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size);

void *DS1307_Read_Data_From_User_RAM(uint8_t mem_addr, void *data, uint8_t data_size);

#endif
