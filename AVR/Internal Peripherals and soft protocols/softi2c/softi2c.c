
#include "softi2c.h"
#include "softi2c_configuration.h"


#ifndef SOFTI2C_USE_MULTIPLE_INTERFACE

void SOFTI2C_Initialize()
{
	SOTFI2C_SDA_PIN_PORT &= ~(1 << SOTFI2C_SDA_PIN);
	SOTFI2C_SCL_PIN_PORT &= ~(1 << SOTFI2C_SCL_PIN);
	
	SOTFI2C_SDA_SET_HIGH;
	SOTFI2C_SCL_SET_HIGH;
	
}

void SOFTI2C_Start()
{
	SOTFI2C_SCL_SET_HIGH;
	SOFTI2C_DELAY;
	
	SOTFI2C_SDA_SET_LOW;
}

void SOFTI2C_Stop()
{
	SOTFI2C_SDA_SET_LOW;
	SOFTI2C_DELAY;
	
	SOTFI2C_SCL_SET_HIGH;
	SOFTI2C_DELAY;
	
	SOTFI2C_SDA_SET_HIGH;
}

void SOFTI2C_Restart()
{
	SOFTI2C_Start();
}

uint8_t SOFTI2C_Send_Byte(uint8_t data)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		SOTFI2C_SCL_SET_LOW;
		SOFTI2C_DELAY;
		
		if (data & 0x80)
		{
			SOTFI2C_SDA_SET_HIGH;
		}
		else
		{
			SOTFI2C_SDA_SET_LOW;
		}
		
		SOFTI2C_DELAY;
		
		SOTFI2C_SCL_SET_HIGH;
		SOFTI2C_DELAY;
		
		while (!(SOTFI2C_SCL_PIN_PINX & (1 << SOTFI2C_SCL_PIN)));
		
		data <<= 1;
	}
	
	SOTFI2C_SCL_SET_LOW;
	SOFTI2C_DELAY;
	
	SOTFI2C_SDA_SET_HIGH;
	SOFTI2C_DELAY;
	
	SOTFI2C_SCL_SET_HIGH;
	SOFTI2C_DELAY;
	
	uint8_t ack = !(SOTFI2C_SDA_PIN_PINX & (1 << SOTFI2C_SDA_PIN));
	
	SOTFI2C_SCL_SET_LOW;
	SOFTI2C_DELAY;
	
	return ack;
}

void SOFTI2C_Read_Byte(uint8_t *data, bool ack)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		SOTFI2C_SCL_SET_HIGH;
		SOFTI2C_DELAY;
		
		if (SOTFI2C_SDA_PIN_PINX & (1 << SOTFI2C_SDA_PIN))
		{
			*data |= (0x80 >> i);
		}
		
		SOTFI2C_SCL_SET_LOW;
		SOFTI2C_DELAY;
	}
	
	if (ack)
	{
		SOTFI2C_SDA_SET_LOW;
	}
	else
	{
		SOTFI2C_SDA_SET_HIGH;
	}
	
	SOTFI2C_SCL_SET_HIGH;
	SOFTI2C_DELAY;
	
	SOTFI2C_SCL_SET_LOW;
	SOFTI2C_DELAY;
	
	SOTFI2C_SDA_SET_HIGH;
}


#else

static SOFTI2C_t *target_softi2c_interface_object = NULL;

SOFTI2C_t SOFTI2C_Get_Interface_Object(

	uint8_t *scl_ddr,
	uint8_t *scl_pinx,
	uint8_t *scl_port,
	uint8_t  scl_pin,

	uint8_t *sda_ddr,
	uint8_t *sda_pinx,
	uint8_t *sda_port,
	uint8_t  sda_pin,

	uint8_t  clock_delay
)
{
	SOFTI2C_t softi2c_interface;
	
	softi2c_interface.softi2c_scl_ddr     = scl_ddr;
	softi2c_interface.softi2c_scl_pinx    = scl_pinx;
	softi2c_interface.softi2c_scl_port    = scl_port;
	softi2c_interface.softi2c_scl_pin     = scl_pin;
	
	softi2c_interface.softi2c_sda_ddr     = sda_ddr;
	softi2c_interface.softi2c_sda_pinx    = sda_pinx;
	softi2c_interface.softi2c_sda_port    = sda_port;
	softi2c_interface.softi2c_sda_pin     = sda_pin;
	
	softi2c_interface.softi2c_clock_delay = clock_delay;
	
	return softi2c_interface;
}

SOFTI2C_t *SOFTI2C_Get_Target_Interface_Object()
{
	return target_softi2c_interface_object;
}

// ===============================================================================

static void _SOTFI2C_CLOCK_DELAY()
{
	_delay_loop_2(target_softi2c_interface_object->softi2c_clock_delay);
}

static void _SOTFI2C_SDA_SET_LOW()
{
	*(target_softi2c_interface_object->softi2c_sda_ddr) |=  (1 << target_softi2c_interface_object->softi2c_sda_pin);
}

static void _SOTFI2C_SDA_SET_HIGH()
{
	*(target_softi2c_interface_object->softi2c_sda_ddr) &= ~(1 << target_softi2c_interface_object->softi2c_sda_pin);
}

static void _SOTFI2C_SCL_SET_LOW()
{
	*(target_softi2c_interface_object->softi2c_scl_ddr) |=  (1 << target_softi2c_interface_object->softi2c_scl_pin);
}

static void _SOTFI2C_SCL_SET_HIGH()
{
	*(target_softi2c_interface_object->softi2c_scl_ddr) &= ~(1 << target_softi2c_interface_object->softi2c_scl_pin);
}

// ===============================================================================

void SOFTI2C_Set_Target_Interface_Object(SOFTI2C_t *softi2c_interface)
{
	target_softi2c_interface_object = softi2c_interface;
}

void SOFTI2C_Start()
{
	_SOTFI2C_SCL_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
	
	_SOTFI2C_SDA_SET_LOW();
	_SOTFI2C_CLOCK_DELAY();
}

void SOFTI2C_Stop()
{
	_SOTFI2C_SDA_SET_LOW();
	_SOTFI2C_CLOCK_DELAY();
	_SOTFI2C_SCL_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
	_SOTFI2C_SDA_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
}

void SOFTI2C_Restart()
{
	SOFTI2C_Start();
}

uint8_t SOFTI2C_Send_Byte(uint8_t data)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOTFI2C_SCL_SET_LOW();
		_SOTFI2C_CLOCK_DELAY();
		
		if (data & 0x80)
		{
			_SOTFI2C_SDA_SET_HIGH();
		}
		else
		{
			_SOTFI2C_SDA_SET_LOW();
		}
		
		_SOTFI2C_CLOCK_DELAY();
		_SOTFI2C_SCL_SET_HIGH();
		_SOTFI2C_CLOCK_DELAY();
		
		while (!(*(target_softi2c_interface_object->softi2c_scl_pinx) & (1 << target_softi2c_interface_object->softi2c_scl_pin)));
		
		data <<= 1;
	}
	
	_SOTFI2C_SCL_SET_LOW();
	_SOTFI2C_CLOCK_DELAY();
	
	_SOTFI2C_SDA_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
	
	_SOTFI2C_SCL_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
	
	uint8_t ack = !(*(target_softi2c_interface_object->softi2c_sda_pinx) & (1 << target_softi2c_interface_object->softi2c_sda_pin));
	
	_SOTFI2C_SCL_SET_LOW();
	_SOTFI2C_CLOCK_DELAY();
	
	return ack;
}

void SOFTI2C_Read_Byte(uint8_t *data, bool ack)
{
	for (int8_t i = 0; i < 8; ++i)
	{
		_SOTFI2C_SCL_SET_HIGH();
		_SOTFI2C_CLOCK_DELAY();
		
		if (*(target_softi2c_interface_object->softi2c_sda_pinx) & (1 << target_softi2c_interface_object->softi2c_sda_pin))
		{
			*data |= (0x80 >> i);
		}
		
		_SOTFI2C_SCL_SET_LOW();
		_SOTFI2C_CLOCK_DELAY();
	}
	
	if (ack)
	{
		_SOTFI2C_SDA_SET_LOW();
	}
	else
	{
		_SOTFI2C_SDA_SET_HIGH();
	}
	
	_SOTFI2C_SCL_SET_HIGH();
	_SOTFI2C_CLOCK_DELAY();
	
	_SOTFI2C_SCL_SET_LOW();
	_SOTFI2C_CLOCK_DELAY();
	
	_SOTFI2C_SDA_SET_HIGH();
}

#endif
