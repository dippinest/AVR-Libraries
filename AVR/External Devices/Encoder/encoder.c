
#include "encoder.h"


#ifndef ENCODER_USE_MULTIPLE_DEVICES

static void (*_left_turn_callback)()  = NULL;
static void (*_right_turn_callback)() = NULL;


void Encoder_Initialize()
{
	ENCODER_INPUT0_DDR &= ~(1 << ENCODER_INPUT0_PIN);
	ENCODER_INPUT1_DDR &= ~(1 << ENCODER_INPUT1_PIN);
}

void Encoder_Polling()
{
	static int8_t encoder_status = 1;
	
	if (encoder_status == 0)
	{
		if (_Bit_Is_Reset(ENCODER_INPUT0_PINX, ENCODER_INPUT0_PIN) ||
		_Bit_Is_Reset(ENCODER_INPUT1_PINX, ENCODER_INPUT1_PIN))
		{
			encoder_status = 1;

			if (_Bit_Is_Reset(ENCODER_INPUT0_PINX, ENCODER_INPUT0_PIN) &&
			_left_turn_callback != NULL)
			{
				_left_turn_callback();
			}
			
			if (_Bit_Is_Reset(ENCODER_INPUT1_PINX, ENCODER_INPUT1_PIN) &&
			_right_turn_callback != NULL)
			{
				_right_turn_callback();
			}
		}
	}

	if (_Bit_Is_Set(ENCODER_INPUT0_PINX, ENCODER_INPUT0_PIN) &&
	_Bit_Is_Set(ENCODER_INPUT1_PINX, ENCODER_INPUT1_PIN))
	{
		encoder_status = 0;
	}
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


Encoder_t Encoder_Get_Device_Object(

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
	
	encoder.status = 1;
	
	*(input0_ddr) &= ~(1 << input0_pin);
	*(input1_ddr) &= ~(1 << input1_pin);
	
	return encoder;
}

// ===============================================================================

void Encoder_Polling(Encoder_t *encoder)
{
	if (encoder->status == 0)
	{
		if (_Bit_Is_Reset_P(encoder->input0_pinx, encoder->input0_pin) ||
		_Bit_Is_Reset_P(encoder->input1_pinx, encoder->input1_pin))
		{
			encoder->status = 1;

			if (_Bit_Is_Reset_P(encoder->input0_pinx, encoder->input0_pin) &&
			encoder->_left_turn_callback != NULL)
			{
				encoder->_left_turn_callback();
			}
			
			if (_Bit_Is_Reset_P(encoder->input1_pinx, encoder->input1_pin) &&
			encoder->_right_turn_callback != NULL)
			{
				encoder->_right_turn_callback();
			}
		}
	}

	if (_Bit_Is_Set_P(encoder->input0_pinx, encoder->input0_pin) &&
	_Bit_Is_Set_P(encoder->input1_pinx, encoder->input1_pin))
	{
		encoder->status = 0;
	}
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


