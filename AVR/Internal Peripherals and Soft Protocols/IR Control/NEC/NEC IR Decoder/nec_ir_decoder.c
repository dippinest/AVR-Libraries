

#include "nec_ir_decoder.h"


static NEC_IR_Protocol_Data_t _nec_ir_data;

static uint16_t main_ir_counter     = 0;
static uint8_t  fsm_status          = NO_RECEPTION;
static uint8_t  samples_counter     = 0;
static uint8_t  bits_counter        = 0;

static void (*_reception_callback_function)()        = NULL;
static void (*_repeat_reception_callback_function)() = NULL;


// ===============================================================================


void NEC_IR_Decoder_Initialize(void (*reception_callback_function)(), void (*repeat_reception_callback_function)())
{
	NEC_IR_DECODER_EXINT_IN_GPIO_DDR &= ~(1 << NEC_IR_DECODER_EXINT_IN_GPIO_PIN);
	
	_reception_callback_function        = reception_callback_function;
	_repeat_reception_callback_function = repeat_reception_callback_function;
	
	NEC_IR_Decoder_FSM_Timer_Interrupt_Initialize();
	NEC_IR_Decoder_EXINT_Interrupt_Initialize();
	
	NEC_IR_Decoder_Reset();
}


// ===============================================================================


void NEC_IR_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)())
{
	_reception_callback_function = reception_callback_function;
}

void *NEC_IR_Decoder_Get_Reception_Callback_Function()
{
	return _reception_callback_function;
}

void NEC_IR_Decoder_Set_Repeat_Reception_Callback_Function(void (*repeat_reception_callback_function)())
{
	_repeat_reception_callback_function = repeat_reception_callback_function;
}

void *NEC_IR_Decoder_Get_Repeat_Reception_Callback_Function()
{
	return _repeat_reception_callback_function;
}


// ===============================================================================


NEC_IR_Protocol_Data_t NEC_IR_Decoder_Get_Data()
{
	return _nec_ir_data;
}


void NEC_IR_Decoder_Reset()
{
	_nec_ir_data.addr_1     = 0x00;
	_nec_ir_data.addr_2     = 0x00;
	_nec_ir_data.command_1  = 0x00;
	_nec_ir_data.command_2  = 0x00;

	fsm_status         = NO_RECEPTION;
	main_ir_counter    = 0;
	samples_counter    = 0;
	bits_counter       = 0;
}


bool NEC_IR_Check_Package_Integrity_For_Standart_Protocol(const NEC_IR_Protocol_Data_t *nec_ir_data)
{
	if ((_nec_ir_data.addr_1 ^ _nec_ir_data.addr_2) == 0xFF && (_nec_ir_data.command_1 ^ _nec_ir_data.command_2) == 0xFF)
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


bool _NEC_IR_Decoder_Get_Input_Level()
{
	if (NEC_IR_DECODER_EXINT_IN_GPIO_PINX & (1 << NEC_IR_DECODER_EXINT_IN_GPIO_PIN))
	{
		return _NEC_IR_DECODER_INPUT_LEVEL_HIGH;
	}
	
	return _NEC_IR_DECODER_INPUT_LEVEL_LOW;
}


void _NEC_IR_Decoder_Receive_Byte(uint8_t *b)
{
	++samples_counter;
	
	if (samples_counter == 2)
	{
		if (main_ir_counter >= (_NEC_IR_DECODER_BIT0_TIMEOUT - 1) && main_ir_counter <= (_NEC_IR_DECODER_BIT0_TIMEOUT + 1))
		{
			++bits_counter;
		}
		
		if (main_ir_counter >= (_NEC_IR_DECODER_BIT1_TIMEOUT - 1))
		{
			*b |= (1 << bits_counter);
			
			++bits_counter;
		}
		
		samples_counter = 0;
		
		main_ir_counter = 0;
	}
}


void NEC_IR_Decoder_FSM()
{
	switch(fsm_status)
	{
		case NO_RECEPTION:
		
		if (_NEC_IR_Decoder_Get_Input_Level() == _NEC_IR_DECODER_INPUT_LEVEL_LOW)
		{
			fsm_status = RECEPTION_START;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_START:
		
		if (main_ir_counter >= (_NEC_IR_DECODER_NUM_OF_START_SAMPLES - 1))
		{
			fsm_status = RECEPTION_POSTSTART;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_POSTSTART:
		
		if (main_ir_counter >= (_NEC_IR_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES - 1) && main_ir_counter <= (_NEC_IR_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES + 1))
		{
			fsm_status = RECEPTION_REPEAT_SAMPLE;
		}
		else
		{
			if (main_ir_counter >= (_NEC_IR_DECODER_NUM_OF_POSTSTART_SAMPLES - 1) && main_ir_counter <= (_NEC_IR_DECODER_NUM_OF_POSTSTART_SAMPLES + 1))
			{
				fsm_status = RECEPTION_ADDRESS_1;
			}
			else
			{
				fsm_status = NO_RECEPTION;
			}
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_REPEAT_SAMPLE:
		
		if (_repeat_reception_callback_function != NULL)
		{
			_repeat_reception_callback_function();
			
			fsm_status = NO_RECEPTION;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_ADDRESS_1:
		
		_NEC_IR_Decoder_Receive_Byte(&(_nec_ir_data.addr_1));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_ADDRESS_2;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_ADDRESS_2:
		
		_NEC_IR_Decoder_Receive_Byte(&(_nec_ir_data.addr_2));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_COMMAND_1;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_COMMAND_1:
		
		_NEC_IR_Decoder_Receive_Byte(&(_nec_ir_data.command_1));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_COMMAND_2;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_COMMAND_2:
		
		_NEC_IR_Decoder_Receive_Byte(&(_nec_ir_data.command_2));
		
		if (bits_counter >= 8)
		{
			if (_reception_callback_function != NULL)
			{
				_reception_callback_function();
			}
			
			fsm_status = NO_RECEPTION;
			
			bits_counter = 0;
		}
		
		break;


		default:

		NEC_IR_Decoder_Reset();
		
		break;
	}
}


// ===============================================================================


ISR(NEC_IR_DECODER_TIMER_VECTOR_INTERRUPT)
{
	++main_ir_counter;
	
	if (main_ir_counter >= _NEC_IR_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES)
	{
		NEC_IR_Decoder_Reset();
	}
}

ISR(NEC_IR_DECODER_EXINT_VECTOR_INTERRUPT)
{
	NEC_IR_Decoder_FSM();
}



