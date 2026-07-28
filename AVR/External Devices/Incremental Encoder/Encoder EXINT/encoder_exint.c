
#include "encoder_exint.h"


#ifndef ENCODER_EXINT_USE_MULTIPLE_DEVICES


#ifndef _Bit_Is_Set
#define _Bit_Is_Set(port, bit)    ((port & (1 << bit)))
#endif


static void (*_left_turn_callback)()  = NULL;
static void (*_right_turn_callback)() = NULL;




void Encoder_EXINT_Initialize()
{
	ENCODER_EXINT_INPUT0_DDR_EXINT &= ~(1 << ENCODER_EXINT_INPUT0_PIN_EXINT);
	ENCODER_EXINT_INPUT1_DDR       &= ~(1 << ENCODER_EXINT_INPUT1_PIN);
}


void Encoder_EXINT_Processing(void)
{
	if ((_left_turn_callback == NULL) || (_right_turn_callback == NULL))
	{
		return;
	}
	
	
	
	uint8_t encoder_inputs_state = 0;
	
	
	if (_Bit_Is_Set(ENCODER_EXINT_INPUT0_PINX_EXINT, ENCODER_EXINT_INPUT0_PIN_EXINT))
	{
		encoder_inputs_state |= (1 << 1);
	}
	
	if (_Bit_Is_Set(ENCODER_EXINT_INPUT1_PINX, ENCODER_EXINT_INPUT1_PIN))
	{
		encoder_inputs_state |= (1 << 0);
	}
	
	
	
	switch(encoder_inputs_state)
	{
		case 0b00: _right_turn_callback(); break;
		
		case 0b01: _left_turn_callback();  break;
		
		case 0b10: _left_turn_callback();  break;
		
		case 0b11: _right_turn_callback(); break;
		
		default: break;
	}
}



// ===============================================================================



void Encoder_EXINT_Set_Left_Turn_CallBack_Function(void (*callback_function)())
{
	_left_turn_callback  = callback_function;
}

void Encoder_EXINT_Set_Right_Turn_CallBack_Function(void (*callback_function)())
{
	_right_turn_callback = callback_function;
}

void *Encoder_EXINT_Get_Left_Turn_CallBack_Function()
{
	return _left_turn_callback;
}

void *Encoder_EXINT_Get_Right_Turn_CallBack_Function()
{
	return _right_turn_callback;
}



#else // ===============================================================================



#ifndef _Bit_Is_Set
#define _Bit_Is_Set(port, bit)    ((port) & (1 << bit))
#endif

#ifndef _Bit_Is_Reset
#define _Bit_Is_Reset(port, bit) !((port) & (1 << bit))
#endif


Encoder_EXINT_t Encoder_EXINT_Create_Object(

	uint8_t *input0_ddr_exint,
	uint8_t *input0_pinx_exint,
	uint8_t  input0_pin_exint,

	uint8_t *input1_ddr,
	uint8_t *input1_pinx,
	uint8_t  input1_pin,

	void (*_left_turn_callback)(),
	void (*_right_turn_callback)()
)
{
	Encoder_EXINT_t encoder;
	
	encoder.input0_ddr_exint   = input0_ddr_exint;
	encoder.input0_pinx_exint  = input0_pinx_exint;
	encoder.input0_pin_exint   = input0_pin_exint;
	
	encoder.input1_ddr   = input1_ddr;
	encoder.input1_pinx  = input1_pinx;
	encoder.input1_pin   = input1_pin;
	
	
	encoder._left_turn_callback  = _left_turn_callback;
	encoder._right_turn_callback = _right_turn_callback;
	
	
	*(input0_ddr_exint) &= ~(1 << input0_pin_exint);
	*(input1_ddr)       &= ~(1 << input1_pin);
	
	
	return encoder;
}



// ===============================================================================



void Encoder_EXINT_Processing(Encoder_EXINT_t *encoder)
{
	if (( (encoder->_left_turn_callback) == NULL) || ( (encoder->_right_turn_callback) == NULL))
	{
		return;
	}
	
	
	
	uint8_t encoder_inputs_state = 0;
	
	
	if (_Bit_Is_Set(*(encoder->input0_pinx_exint), (encoder->input0_pin_exint)))
	{
		encoder_inputs_state |= (1 << 1);
	}
	
	if (_Bit_Is_Set(*(encoder->input1_pinx), (encoder->input1_pin)))
	{
		encoder_inputs_state |= (1 << 0);
	}
	
	
	
	switch(encoder_inputs_state)
	{
		case 0b00: (encoder->_right_turn_callback)(); break;
		
		case 0b01: (encoder->_left_turn_callback)();  break;
		
		case 0b10: (encoder->_left_turn_callback)();  break;
		
		case 0b11: (encoder->_right_turn_callback)(); break;
		
		default: break;
	}
}



// ===============================================================================



void Encoder_EXINT_Set_Left_Turn_CallBack_Function(Encoder_EXINT_t *encoder, void (*callback_function)())
{
	encoder->_left_turn_callback = callback_function;
}

void Encoder_EXINT_Set_Right_Turn_CallBack_Function(Encoder_EXINT_t *encoder, void (*callback_function)())
{
	encoder->_right_turn_callback = callback_function;
}

void *Encoder_EXINT_Get_Left_Turn_CallBack_Function(Encoder_EXINT_t *encoder)
{
	return encoder->_left_turn_callback;
}

void *Encoder_EXINT_Get_Right_Turn_CallBack_Function(Encoder_EXINT_t *encoder)
{
	return encoder->_right_turn_callback;
}



// ===============================================================================




#endif


