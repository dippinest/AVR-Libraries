

// ===============================================================================
//
// Библиотека для работы с датчиком давления и температуры BMP180
// по интерфейсу I2C. I2C можно использовать как аппаратный,
// так и программный - это можно настроить
// в файле конфигурации bmp180_i2c_configuration.h
//
// -------------------------------------------------------------------------------
//
// Library for working with the BMP180 pressure and temperature sensor
// via the I2C interface. I2C can be used both hardware and
// software - this can be configured in the
// configuration file bmp180_i2c_configuration.h
//
// ===============================================================================


#ifndef BMP180_I2C_H_
#define BMP180_I2C_H_

#include <stdint.h>
#include <stddef.h>

#include <math.h>

#include "bmp180_i2c_configuration.h"

// I2C address device
#define _BMP180_I2C_ADDRESS_DEVICE 0x77

// number of calibration registers
#define _BMP180_I2C_NUM_OF_16BIT_CALIBRATION_REGISTERS  11

// calibration register positions
#define _BMP180_I2C_AC1_CALIBRATION_REGISTER_POS 0
#define _BMP180_I2C_AC2_CALIBRATION_REGISTER_POS 1
#define _BMP180_I2C_AC3_CALIBRATION_REGISTER_POS 2
#define _BMP180_I2C_AC4_CALIBRATION_REGISTER_POS 3
#define _BMP180_I2C_AC5_CALIBRATION_REGISTER_POS 4
#define _BMP180_I2C_AC6_CALIBRATION_REGISTER_POS 5
#define _BMP180_I2C_B1_CALIBRATION_REGISTER_POS  6
#define _BMP180_I2C_B2_CALIBRATION_REGISTER_POS  7
#define _BMP180_I2C_MB_CALIBRATION_REGISTER_POS  8
#define _BMP180_I2C_MC_CALIBRATION_REGISTER_POS  9
#define _BMP180_I2C_MD_CALIBRATION_REGISTER_POS  10

// addresses of the first and last calibration registers
#define _BMP180_I2C_FIRST_CALIBRATION_REGISTER_ADDRESS  0xAA
#define _BMP180_I2C_LAST_CALIBRATION_REGISTER_ADDRESS   0xBF

// addresses of other registers
#define _BMP180_I2C_CHIP_ID_REGISTER_ADDRESS              0xD0
#define _BMP180_I2C_SOFT_RESET_REGISTER_ADDRESS           0xE0
#define _BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS  0xF4
#define _BMP180_I2C_OUT_MSB_REGISTER_ADDRESS              0xF6
#define _BMP180_I2C_OUT_LSB_REGISTER_ADDRESS              0xF7
#define _BMP180_I2C_OUT_XLSB_REGISTER_ADDRESS             0xF8

// code of the temperature measurement mode
#define _BMP180_I2C_TEMPERATURE_MEASUREMENT_MODE          0x2E

// position of the CSO bit
#define _BMP180_I2C_CSO_BIT_POS  5

// ===============================================================================

// pressure measurement accuracy modes
#define BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE0  0b00 // measurement accuracy 0.6 hPa, 4.5 ms max
#define BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE1  0b01 // measurement accuracy 0.5 hPa, 7.5 ms max
#define BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE2  0b10 // measurement accuracy 0.4 hPa, 13.5 ms max
#define BMP180_I2C_PRESSURE_OSS_ACCURACY_MODE3  0b11 // measurement accuracy 0.3 hPa, 25.5 ms max

// structure with BM180 calibration data
typedef struct
{
	int16_t AC1;
	int16_t AC2;
	int16_t AC3;
	int16_t B1;
	int16_t B2;
	int16_t MB;
	int16_t MC;
	int16_t MD;
	
	uint16_t AC4;
	uint16_t AC5;
	uint16_t AC6;
	
} BMP180_I2C_t;


// ===============================================================================


BMP180_I2C_t BMP180_I2C_Get_Device_Object();

void BMP180_I2C_Set_Target_Device_Object(BMP180_I2C_t *sensor);

BMP180_I2C_t *BMP180_I2C_Get_Target_Device_Object();


// ===============================================================================

uint8_t BMP180_I2C_Get_ID();

void BMP180_I2C_Soft_Reset();

// ===============================================================================

int16_t BMP180_I2C_Get_Temperature();

int32_t BMP180_I2C_Get_Pressure(uint8_t pressure_oss_accuracy_mode);

void BMP180_I2C_Get_Temperature_And_Pressure(int16_t *temperature, int32_t *pressure, uint8_t pressure_oss_accuracy_mode);

float BMP180_I2C_Convert_Pa_To_mmHg(int32_t pa);

float BMP180_I2C_Get_Altitude_From_Pressure(int32_t pa);


#endif



