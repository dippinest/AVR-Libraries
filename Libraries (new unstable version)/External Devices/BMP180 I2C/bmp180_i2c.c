

#include "bmp180_i2c.h"



// ===============================================================================

#ifdef BMP180_I2C_USE_SOFTI2C


#include "softi2c.h"

#define _I2C_Start       SOFTI2C_Start
#define _I2C_Send_Byte   SOFTI2C_Send_Byte
#define _I2C_Restart     SOFTI2C_Restart
#define _I2C_Read_Byte   SOFTI2C_Read_Byte
#define _I2C_Stop        SOFTI2C_Stop


#else


#include "i2c.h"

#define _I2C_Start       I2C_Start
#define _I2C_Send_Byte   I2C_Send_Byte
#define _I2C_Restart     I2C_Restart
#define _I2C_Read_Byte   I2C_Read_Byte
#define _I2C_Stop        I2C_Stop

#endif

// ===============================================================================




void _BMP180_I2C_Write_Byte(uint8_t addr_reg, uint8_t byte)
{
	_I2C_Start();
	
	_I2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	_I2C_Send_Byte(addr_reg);
	_I2C_Send_Byte(byte);
	
	_I2C_Stop();
}

uint8_t _BMP180_I2C_Read_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	_I2C_Start();
	_I2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	_I2C_Send_Byte(addr_reg);
	
	_I2C_Start();
	
	_I2C_Send_Byte((_BMP180_I2C_ADDRESS_DEVICE << 1) | 1);
	_I2C_Read_Byte(&byte, NACK);
	
	_I2C_Stop();
	
	return byte;
}



// ===============================================================================



void BMP180_I2C_Initialize_Object(BMP180_I2C_t *bmp180_i2c)
{
	(*bmp180_i2c).AC1  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAA)) << 8) | _BMP180_I2C_Read_Byte(0xAB);
	(*bmp180_i2c).AC2  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAC)) << 8) | _BMP180_I2C_Read_Byte(0xAD);
	(*bmp180_i2c).AC3  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAE)) << 8) | _BMP180_I2C_Read_Byte(0xAF);
	(*bmp180_i2c).AC4  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB0)) << 8) | _BMP180_I2C_Read_Byte(0xB1);
	(*bmp180_i2c).AC5  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB2)) << 8) | _BMP180_I2C_Read_Byte(0xB3);
	(*bmp180_i2c).AC6  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB4)) << 8) | _BMP180_I2C_Read_Byte(0xB5);
	(*bmp180_i2c).B1   = (((uint16_t)_BMP180_I2C_Read_Byte(0xB6)) << 8) | _BMP180_I2C_Read_Byte(0xB7);
	(*bmp180_i2c).B2   = (((uint16_t)_BMP180_I2C_Read_Byte(0xB8)) << 8) | _BMP180_I2C_Read_Byte(0xB9);
	(*bmp180_i2c).MB   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBA)) << 8) | _BMP180_I2C_Read_Byte(0xBB);
	(*bmp180_i2c).MC   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBC)) << 8) | _BMP180_I2C_Read_Byte(0xBD);
	(*bmp180_i2c).MD   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBE)) << 8) | _BMP180_I2C_Read_Byte(0xBF);
}



// ===============================================================================




uint8_t BMP180_I2C_Get_ID()
{
	return _BMP180_I2C_Read_Byte(_BMP180_I2C_CHIP_ID_REGISTER_ADDRESS);
}

void BMP180_I2C_Soft_Reset()
{
	return _BMP180_I2C_Write_Byte(_BMP180_I2C_SOFT_RESET_REGISTER_ADDRESS, 0xB6);
}



// ===============================================================================



int16_t BMP180_I2C_Get_Temperature(BMP180_I2C_t *bmp180_i2c)
{
	uint8_t msb, lsb;
	
	_BMP180_I2C_Write_Byte(
		_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS,
		_BMP180_I2C_TEMPERATURE_MEASUREMENT_MODE
	);
	
	
	while(_BMP180_I2C_Read_Byte(_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS) & (1 << _BMP180_I2C_CSO_BIT_POS));
	
	
	msb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_MSB_REGISTER_ADDRESS);
	lsb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_LSB_REGISTER_ADDRESS);
	
	int32_t UT = ((uint16_t)msb << 8) + lsb;
	
	
	int32_t X1 = ((UT - bmp180_i2c->AC6) * bmp180_i2c->AC5) / 32768;
	int32_t X2 = ((int32_t)bmp180_i2c->MC * 2048) / (X1 + bmp180_i2c->MD);
	int32_t B5 = X1 + X2;
	int16_t T  = (B5 + 8) / 160;
	
	return T;
}


int32_t BMP180_I2C_Get_Pressure(BMP180_I2C_t *bmp180_i2c, uint8_t pressure_oss_accuracy_mode)
{
	uint8_t msb, lsb, xlsb;
	
	_BMP180_I2C_Write_Byte(
		_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS,
		_BMP180_I2C_TEMPERATURE_MEASUREMENT_MODE
	);
	
	while(_BMP180_I2C_Read_Byte(_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS) & (1 << _BMP180_I2C_CSO_BIT_POS));
	
	msb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_MSB_REGISTER_ADDRESS);
	lsb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_LSB_REGISTER_ADDRESS);
	
	int32_t UT = ((uint16_t)msb << 8) + lsb;
	
	
	_BMP180_I2C_Write_Byte(
		_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS,
		(0x34 + (pressure_oss_accuracy_mode << 6))
	);
	
	while(_BMP180_I2C_Read_Byte(_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS) & (1 << _BMP180_I2C_CSO_BIT_POS));
	
	msb  = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_MSB_REGISTER_ADDRESS);
	lsb  = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_LSB_REGISTER_ADDRESS);
	xlsb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_XLSB_REGISTER_ADDRESS);
	
	int32_t UP = ((uint32_t)msb << 16) + ((uint16_t)lsb << 8) + xlsb;
	UP >>= (8 - pressure_oss_accuracy_mode);
	
	
	int32_t X1 = (((int32_t)UT - bmp180_i2c->AC6) * bmp180_i2c->AC5) / 32768;
	int32_t X2 = ((int32_t)bmp180_i2c->MC * 2048) / (X1 + bmp180_i2c->MD);
	int32_t B5 = X1 + X2;
	int32_t B6 = B5 - 4000;
	
	X1 = ((int32_t)bmp180_i2c->B2 * ((B6 * B6) / 4096)) / 2048;
	X2 = ((int32_t)bmp180_i2c->AC2 * B6) / 2048;
	
	int32_t X3 = X1 + X2;
	int32_t B3 = (( ((bmp180_i2c->AC1 * 4) + X3) << pressure_oss_accuracy_mode) + 2) / 4;
	
	X1 = ((int32_t)bmp180_i2c->AC3 * B6) / 8192;
	X2 = ((int32_t)bmp180_i2c->B1 * ((B6 * B6) / 4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;
	
	uint32_t B4 = ((int32_t)bmp180_i2c->AC4 * (uint32_t)(X3 + 32768)) / 32768;
	
	int32_t B7 = ((uint32_t)UP - B3) * (50000 >> pressure_oss_accuracy_mode);
	
	
	int32_t P;
	
	if (B7 < 0x80000000)
	{
		P = (B7 * 2) / B4;
	}
	else
	{
		P = (B7 / B4) * 2;
	}
	
	
	X1 = (P / 256) * (P / 256);
	X1 = (X1 * 3038) / 65536;
	X2 = (-7357 * P) / 65536;
	
	P = P + ( (X1 + X2 + 3791) / 16 );
	
	return P;
}


void BMP180_I2C_Get_Temperature_And_Pressure(BMP180_I2C_t *bmp180_i2c, int16_t *temperature, int32_t *pressure, uint8_t pressure_oss_accuracy_mode)
{
	uint8_t msb, lsb, xlsb;
	
	_BMP180_I2C_Write_Byte(
	_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS,
	_BMP180_I2C_TEMPERATURE_MEASUREMENT_MODE
	);
	
	while(_BMP180_I2C_Read_Byte(_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS) & (1 << _BMP180_I2C_CSO_BIT_POS));
	
	msb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_MSB_REGISTER_ADDRESS);
	lsb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_LSB_REGISTER_ADDRESS);
	
	int32_t UT = ((uint16_t)msb << 8) + lsb;
	
	
	int32_t X1 = ((UT - bmp180_i2c->AC6) * bmp180_i2c->AC5) / 32768;
	int32_t X2 = ((int32_t)bmp180_i2c->MC * 2048) / (X1 + bmp180_i2c->MD);
	int32_t B5 = X1 + X2;
	int16_t T  = (B5 + 8) / 160;
	
	*temperature = T;
	
	
	_BMP180_I2C_Write_Byte(
	_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS,
	(0x34 + (pressure_oss_accuracy_mode << 6))
	);
	
	while(_BMP180_I2C_Read_Byte(_BMP180_I2C_MEASUREMENT_CONTROL_REGISTER_ADDRESS) & (1 << _BMP180_I2C_CSO_BIT_POS));
	
	msb  = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_MSB_REGISTER_ADDRESS);
	lsb  = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_LSB_REGISTER_ADDRESS);
	xlsb = _BMP180_I2C_Read_Byte(_BMP180_I2C_OUT_XLSB_REGISTER_ADDRESS);
	
	int32_t UP = ((uint32_t)msb << 16) + ((uint16_t)lsb << 8) + xlsb;
	UP >>= (8 - pressure_oss_accuracy_mode);
	
	
	X1 = (((int32_t)UT - bmp180_i2c->AC6) * bmp180_i2c->AC5) / 32768;
	X2 = ((int32_t)bmp180_i2c->MC * 2048) / (X1 + bmp180_i2c->MD);
	B5 = X1 + X2;
	int32_t B6 = B5 - 4000;
	
	X1 = ((int32_t)bmp180_i2c->B2 * ((B6 * B6) / 4096)) / 2048;
	X2 = ((int32_t)bmp180_i2c->AC2 * B6) / 2048;
	
	int32_t X3 = X1 + X2;
	int32_t B3 = (( ((bmp180_i2c->AC1 * 4) + X3) << pressure_oss_accuracy_mode) + 2) / 4;
	
	X1 = ((int32_t)bmp180_i2c->AC3 * B6) / 8192;
	X2 = ((int32_t)bmp180_i2c->B1 * ((B6 * B6) / 4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;
	
	uint32_t B4 = ((int32_t)bmp180_i2c->AC4 * (uint32_t)(X3 + 32768)) / 32768;
	
	int32_t B7 = ((uint32_t)UP - B3) * (50000 >> pressure_oss_accuracy_mode);
	
	
	int32_t P;
	
	if (B7 < 0x80000000)
	{
		P = (B7 * 2) / B4;
	}
	else
	{
		P = (B7 / B4) * 2;
	}
	
	
	X1 = (P / 256) * (P / 256);
	X1 = (X1 * 3038) / 65536;
	X2 = (-7357 * P) / 65536;
	
	P = P + ( (X1 + X2 + 3791) / 16 );
	
	*pressure = P;
}




// ===============================================================================




float BMP180_I2C_Convert_Pa_To_mmHg(int32_t pa)
{
	float mmHg = pa * 0.00750062f;
	
	return mmHg;
}

float BMP180_I2C_Get_Altitude_From_Pressure(int32_t pa)
{
	const float sea_level_pressure = 101325;
	
	float altitude = 44330 * (1.0f - powf((pa / sea_level_pressure), 0.19029495718f));
	
	return altitude;
}





