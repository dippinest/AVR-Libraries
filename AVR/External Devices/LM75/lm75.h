
#ifndef LM75_H_
#define LM75_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "lm75_configuration.h"

#ifdef HD44780_I2C_USE_SOFTI2C
#include "softi2c.h"
#else
#include "i2c.h"
#endif

// macros different I2C addresses for LM75
#define LM75_I2C_DEV_ADDR_A2F_A1F_A0F  0x48
#define LM75_I2C_DEV_ADDR_A2F_A1F_A0T  0x49
#define LM75_I2C_DEV_ADDR_A2F_A1T_A0F  0x4A
#define LM75_I2C_DEV_ADDR_A2F_A1T_A0T  0x4B
#define LM75_I2C_DEV_ADDR_A2T_A1F_A0F  0x4C
#define LM75_I2C_DEV_ADDR_A2T_A1F_A0T  0x4D
#define LM75_I2C_DEV_ADDR_A2T_A1T_A0F  0x4E
#define LM75_I2C_DEV_ADDR_A2T_A1T_A0T  0x4F

// OS out mode
#define LM75_OS_IS_COMPARATOR_MODE true
#define LM75_OS_IS_INTERRUPT_MODE  false

// OS polarity mode
#define LM75_OS_POL_IS_LOW         true
#define LM75_OS_POL_IS_HIGH        false

// LM75 mode
#define LM75_IS_ENABLE             true
#define LM75_IS_DISABLE            false

// the number of checks before starting the OS
#define LM75_OS_NUM_OF_CHECKS_IS_1 0b00
#define LM75_OS_NUM_OF_CHECKS_IS_2 0b01
#define LM75_OS_NUM_OF_CHECKS_IS_4 0b10
#define LM75_OS_NUM_OF_CHECKS_IS_6 0b11

// addresses of internal registers
#define _LM75_DATA_TEMP_REGISTER_ADDR      0x00
#define _LM75_CONFUGURATION_REGISTER_ADDR  0x01
#define _LM75_THYST_VALUE_REGISTER_ADDR    0x02
#define _LM75_TOS_VALUE_REGISTER_ADDR      0x03

// addresses of the tuning bits in the configuration register
#define _LM75_CONFUGURATION_REGISTER_SHUTDOWN_BIT_POS     0
#define _LM75_CONFUGURATION_REGISTER_OS_COMP_INT_BIT_POS  1
#define _LM75_CONFUGURATION_REGISTER_OS_POL_BIT_POS       2
#define _LM75_CONFUGURATION_REGISTER_OS_F_QUE_BITS_POS    4

// structure with data about the LM75 sensor
typedef struct
{
	uint8_t  dev_addr;
	uint8_t  confuguration_register;
	uint16_t tos_value_register;
	uint16_t thyst_value_register;
	
} LM75_t;

// ===============================================================================

LM75_t LM75_Get_Thermometer_Object(uint8_t dev_addr, bool thermometer_is_enable);

void LM75_Set_Target_Thermometer_Object(LM75_t *thermometer);

void LM75_Set_Enable(bool thermometer_is_enable);

void LM75_Set_OS_Mode(bool os_is_comparator_mode);

void LM75_Set_OS_Polarity(bool os_pol_is_low);

void LM75_Set_OS_Number_Of_Checks(uint8_t os_num_of_checks);

void LM75_Set_Integer_Upper_And_Lower_Limits_OS_Hysteresis_Temperature(int16_t low_limit_temp, int16_t high_limit_temp);

int16_t LM75_Get_Integer_Temperature();

float LM75_Get_Float_Temperature();

// the return value is a signed int32_t number with a pseudo-fixed point
// with 2 decimal places
int32_t LM75_Get_PFIXPoint_2digits_Temperature();

// the return value is a signed int32_t number with a pseudo-fixed point
// with 3 decimal places
int32_t LM75_Get_PFIXPoint_3digits_Temperature();

#endif
