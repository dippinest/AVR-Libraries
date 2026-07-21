
#include "encoder.h"


// ===============================================================================
// Глобальная LUT (Общая для всех энкодеров)
// ===============================================================================
static const uint8_t _encoder_lut_table[16] =
{
	0, 1, 2, 0, 2, 0, 0, 1, 1, 0, 0, 2, 0, 2, 1, 0
};




#ifndef ENCODER_USE_MULTIPLE_DEVICES


#ifndef _Bit_Is_Set
#define _Bit_Is_Set(port, bit)    ((port & (1 << bit)))
#endif

#ifndef _Bit_Is_Reset
#define _Bit_Is_Reset(port, bit) !((port & (1 << bit)))
#endif



static uint8_t _last_state = 0;

static void (*_left_turn_callback)()  = NULL;
static void (*_right_turn_callback)() = NULL;



void Encoder_Initialize()
{
	ENCODER_INPUT0_DDR &= ~(1 << ENCODER_INPUT0_PIN);
	ENCODER_INPUT1_DDR &= ~(1 << ENCODER_INPUT1_PIN);
}

void Encoder_Polling(void)
{
	uint8_t current_state = 0;
	
	
	if (ENCODER_INPUT0_PINX & (1 << ENCODER_INPUT0_PIN))
	{
		current_state |= (1 << 0);
	}
	
	if (ENCODER_INPUT1_PINX & (1 << ENCODER_INPUT1_PIN))
	{
		current_state |= (1 << 1);
	}
	

	if (current_state == _last_state)
	{
		return;
	}
	


	uint8_t direction = _encoder_lut_table[ ((_last_state << 2) | current_state) ];



	if (direction == 1)
	{
		if (_left_turn_callback)
		{
			_left_turn_callback();
		}
	}
	else if (direction == 2)
	{
		if (_right_turn_callback)
		{
			_right_turn_callback();
		}
	}



	_last_state = current_state;
}

// ===============================================================================

void Encoder_Set_Left_Turn_CallBack_Function(void (*callback_function)())
{
	_left_turn_callback  = callback_function;
}

void Encoder_Set_Right_Turn_CallBack_Function(void (*callback_function)())
{
	_right_turn_callback = callback_function;
}

void *Encoder_Get_Left_Turn_CallBack_Function()
{
	return _left_turn_callback;
}

void *Encoder_Get_Right_Turn_CallBack_Function()
{
	return _right_turn_callback;
}


#else // ===============================================================================


#ifndef _Bit_Is_Set_P
#define _Bit_Is_Set_P(port, bit)    ((*port) & (1 << bit))
#endif

#ifndef _Bit_Is_Reset_P
#define _Bit_Is_Reset_P(port, bit) !((*port) & (1 << bit))
#endif


Encoder_t Encoder_Create_Object(

	uint8_t *input0_ddr,
	uint8_t *input0_pinx,
	uint8_t  input0_pin,

	uint8_t *input1_ddr,
	uint8_t *input1_pinx,
	uint8_t  input1_pin,

	void (*_left_turn_callback)(),
	void (*_right_turn_callback)()
)
{
	Encoder_t encoder;
	
	encoder.input0_ddr   = input0_ddr;
	encoder.input0_pinx  = input0_pinx;
	encoder.input0_pin   = input0_pin;
	
	encoder.input1_ddr   = input1_ddr;
	encoder.input1_pinx  = input1_pinx;
	encoder.input1_pin   = input1_pin;
	
	
	encoder._left_turn_callback  = _left_turn_callback;
	encoder._right_turn_callback = _right_turn_callback;
	
	
	*(input0_ddr) &= ~(1 << input0_pin);
	*(input1_ddr) &= ~(1 << input1_pin);
	
	
	
	encoder.last_state = 0;
	
	if (*(encoder.input0_pinx) & (1 << encoder.input0_pin))
	{
		encoder.last_state |= (1 << 0);
	}
	
	if (*(encoder.input1_pinx) & (1 << encoder.input1_pin))
	{
		encoder.last_state |= (1 << 1);
	}
	
	
	return encoder;
}


// ===============================================================================


void Encoder_Polling(Encoder_t *encoder)
{
	uint8_t current_state = 0;
	
	
	if (*(encoder->input0_pinx) & (1 << encoder->input0_pin))
	{
		current_state |= (1 << 0);
	}
	
	if (*(encoder->input1_pinx) & (1 << encoder->input1_pin))
	{
		current_state |= (1 << 1);
	}
	


	if (current_state == (encoder->last_state))
	{
		return;
	}
	


	uint8_t direction = _encoder_lut_table[(encoder->last_state << 2) | current_state];


	if (direction == 1)
	{
		if (encoder->_left_turn_callback)
		{
			encoder->_left_turn_callback();
		}
		else if (direction == 2)
		{
			if (encoder->_right_turn_callback)
			{
				encoder->_right_turn_callback();
			}
		}
	}


	encoder->last_state = current_state;
}


// ===============================================================================


void Encoder_Set_Left_Turn_CallBack_Function(Encoder_t *encoder, void (*callback_function)())
{
	encoder->_left_turn_callback = callback_function;
}

void Encoder_Set_Right_Turn_CallBack_Function(Encoder_t *encoder, void (*callback_function)())
{
	encoder->_right_turn_callback = callback_function;
}

void *Encoder_Get_Left_Turn_CallBack_Function(Encoder_t *encoder)
{
	return encoder->_left_turn_callback;
}

void *Encoder_Get_Right_Turn_CallBack_Function(Encoder_t *encoder)
{
	return encoder->_right_turn_callback;
}


// ===============================================================================



#endif



