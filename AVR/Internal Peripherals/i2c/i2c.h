// =============================================================================================================
//  Header              : i2c.h                                                                                -
//  Created             : 20.02.2022                                                                           -
//  Author              : Denis Chicherov (dippinest)                                                          -
//  Description         : Declaring functions to work with the TWI Interface Module (I2C)                      -
// =============================================================================================================

#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>
#include <stdbool.h>
#include <stdint.h>

#define I2C_STATUS_ERROR    true
#define I2C_STATUS_NOERROR  false

#define _I2C_GET_HEX_CODE_SPEED_TWPS00(I2C_FREQ_HZ) (((F_CPU / I2C_FREQ_HZ) - 16UL) / 2UL)

typedef bool I2C_STATUS;

void I2C_Initialize(uint32_t i2c_freq_hz_speed);

I2C_STATUS I2C_Start();

I2C_STATUS I2C_Stop();

I2C_STATUS I2C_Restart();

I2C_STATUS I2C_Send_Byte(uint8_t byte);

I2C_STATUS I2C_Read_Byte_With_Confirmation(uint8_t *byte);

I2C_STATUS I2C_Read_Byte_Without_Confirmation(uint8_t *byte);

void I2C_Start_Without_I2CStatus_Control();

void I2C_Stop_Without_I2CStatus_Control();

void I2C_Restart_Without_I2CStatus_Control();

void I2C_Send_Byte_Without_I2CStatus_Control(uint8_t byte);

uint8_t I2C_Read_Byte_With_Confirmation_Without_I2CStatus_Control();

uint8_t I2C_Read_Byte_Without_Confirmation_Without_I2CStatus_Control();

bool I2C_Check_Device_By_Address(uint8_t dev_addr);

#endif