
#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef ACK
#define ACK true
#endif

#ifndef NACK
#define NACK false
#endif

#define I2C_STATUS_ERROR    true
#define I2C_STATUS_NOERROR  false

#define _I2C_GET_HEX_CODE_SPEED_TWPS00(I2C_FREQ_HZ) (((F_CPU / I2C_FREQ_HZ) - 16UL) / 2UL)

typedef bool I2C_STATUS;

void I2C_Initialize(uint32_t i2c_freq_hz_speed);

void I2C_Start();

void I2C_Stop();

void I2C_Restart();

void I2C_Send_Byte(uint8_t byte);

void I2C_Read_Byte(uint8_t *byte, bool ack);

I2C_STATUS I2C_Start_With_I2CStatus_Control();

I2C_STATUS I2C_Stop_With_I2CStatus_Control();

I2C_STATUS I2C_Restart_With_I2CStatus_Control();

I2C_STATUS I2C_Send_Byte_With_I2CStatus_Control(uint8_t byte);

I2C_STATUS I2C_Read_Byte_With_I2CStatus_Control(uint8_t *byte, bool ack);

bool I2C_Check_Device_By_Address(uint8_t dev_addr);

#endif