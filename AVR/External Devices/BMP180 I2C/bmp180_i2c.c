
#include "bmp180_i2c.h"

static BMP180_I2C_t *target_sensor = NULL;


// ===============================================================================


#ifdef BMP180_I2C_USE_SOFTI2C

#include "softi2c.h"

void _BMP180_I2C_Write_Byte(uint8_t addr_reg, uint8_t byte)
{
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	SOFTI2C_Send_Byte(byte);
	
	SOFTI2C_Stop();
}

uint8_t _BMP180_I2C_Read_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	SOFTI2C_Start();
	SOFTI2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	SOFTI2C_Send_Byte(addr_reg);
	
	SOFTI2C_Start();
	
	SOFTI2C_Send_Byte((_BMP180_I2C_ADDRESS_DEVICE << 1) | 1);
	SOFTI2C_Read_Byte(&byte, NACK);
	
	SOFTI2C_Stop();
	
	return byte;
}


#else // ===============================================================================


#include "i2c.h"

void _BMP180_I2C_Write_Byte(uint8_t addr_reg, uint8_t byte)
{
	I2C_Start();
	
	I2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	I2C_Send_Byte(byte);
	
	I2C_Stop();
}

uint8_t _BMP180_I2C_Read_Byte(uint8_t addr_reg)
{
	uint8_t byte;
	
	I2C_Start();
	I2C_Send_Byte(_BMP180_I2C_ADDRESS_DEVICE << 1);
	I2C_Send_Byte(addr_reg);
	
	I2C_Start();
	
	I2C_Send_Byte((_BMP180_I2C_ADDRESS_DEVICE << 1) | 1);
	I2C_Read_Byte(&byte, NACK);
	
	I2C_Stop();
	
	return byte;
}


#endif // ===============================================================================


BMP180_I2C_t BMP180_I2C_Get_Object()
{
	BMP180_I2C_t sensor;
	
	sensor.AC1  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAA)) << 8) | _BMP180_I2C_Read_Byte(0xAB);
	sensor.AC2  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAC)) << 8) | _BMP180_I2C_Read_Byte(0xAD);
	sensor.AC3  = (((uint16_t)_BMP180_I2C_Read_Byte(0xAE)) << 8) | _BMP180_I2C_Read_Byte(0xAF);
	sensor.AC4  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB0)) << 8) | _BMP180_I2C_Read_Byte(0xB1);
	sensor.AC5  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB2)) << 8) | _BMP180_I2C_Read_Byte(0xB3);
	sensor.AC6  = (((uint16_t)_BMP180_I2C_Read_Byte(0xB4)) << 8) | _BMP180_I2C_Read_Byte(0xB5);
	sensor.B1   = (((uint16_t)_BMP180_I2C_Read_Byte(0xB6)) << 8) | _BMP180_I2C_Read_Byte(0xB7);
	sensor.B2   = (((uint16_t)_BMP180_I2C_Read_Byte(0xB8)) << 8) | _BMP180_I2C_Read_Byte(0xB9);
	sensor.MB   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBA)) << 8) | _BMP180_I2C_Read_Byte(0xBB);
	sensor.MC   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBC)) << 8) | _BMP180_I2C_Read_Byte(0xBD);
	sensor.MD   = (((uint16_t)_BMP180_I2C_Read_Byte(0xBE)) << 8) | _BMP180_I2C_Read_Byte(0xBF);
	
	return sensor;
}

void BMP180_I2C_Set_Target_Object(BMP180_I2C_t *sensor)
{
	target_sensor = sensor;
}

BMP180_I2C_t *BMP180_I2C_Get_Target_Object()
{
	return target_sensor;
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


int16_t BMP180_I2C_Get_Temperature()
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
	
	
	int32_t X1 = ((UT - target_sensor->AC6) * target_sensor->AC5) / 32768;
	int32_t X2 = ((int32_t)target_sensor->MC * 2048) / (X1 + target_sensor->MD);
	int32_t B5 = X1 + X2;
	int16_t T  = (B5 + 8) / 160;
	
	return T;
}

int32_t BMP180_I2C_Get_Pressure(uint8_t pressure_oss_accuracy_mode)
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
	
	
	int32_t X1 = (((int32_t)UT - target_sensor->AC6) * target_sensor->AC5) / 32768;
	int32_t X2 = ((int32_t)target_sensor->MC * 2048) / (X1 + target_sensor->MD);
	int32_t B5 = X1 + X2;
	int32_t B6 = B5 - 4000;
	
	X1 = ((int32_t)target_sensor->B2 * ((B6 * B6) / 4096)) / 2048;
	X2 = ((int32_t)target_sensor->AC2 * B6) / 2048;
	
	int32_t X3 = X1 + X2;
	int32_t B3 = (( ((target_sensor->AC1 * 4) + X3) << pressure_oss_accuracy_mode) + 2) / 4;
	
	X1 = ((int32_t)target_sensor->AC3 * B6) / 8192;
	X2 = ((int32_t)target_sensor->B1 * ((B6 * B6) / 4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;
	
	uint32_t B4 = ((int32_t)target_sensor->AC4 * (uint32_t)(X3 + 32768)) / 32768;
	
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

void BMP180_I2C_Get_Temperature_And_Pressure(int16_t *temperature, int32_t *pressure, uint8_t pressure_oss_accuracy_mode)
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
	
	
	int32_t X1 = ((UT - target_sensor->AC6) * target_sensor->AC5) / 32768;
	int32_t X2 = ((int32_t)target_sensor->MC * 2048) / (X1 + target_sensor->MD);
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
	
	
	X1 = (((int32_t)UT - target_sensor->AC6) * target_sensor->AC5) / 32768;
	X2 = ((int32_t)target_sensor->MC * 2048) / (X1 + target_sensor->MD);
	B5 = X1 + X2;
	int32_t B6 = B5 - 4000;
	
	X1 = ((int32_t)target_sensor->B2 * ((B6 * B6) / 4096)) / 2048;
	X2 = ((int32_t)target_sensor->AC2 * B6) / 2048;
	
	int32_t X3 = X1 + X2;
	int32_t B3 = (( ((target_sensor->AC1 * 4) + X3) << pressure_oss_accuracy_mode) + 2) / 4;
	
	X1 = ((int32_t)target_sensor->AC3 * B6) / 8192;
	X2 = ((int32_t)target_sensor->B1 * ((B6 * B6) / 4096)) / 65536;
	X3 = ((X1 + X2) + 2) / 4;
	
	uint32_t B4 = ((int32_t)target_sensor->AC4 * (uint32_t)(X3 + 32768)) / 32768;
	
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


