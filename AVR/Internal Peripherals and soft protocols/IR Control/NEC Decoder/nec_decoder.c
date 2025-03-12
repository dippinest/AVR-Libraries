

#include "nec_decoder.h"


static NEC_Protocol_Data_t nec_data;

static uint16_t main_ir_nec_counter = 0;
static uint8_t  fsm_status          = NO_RECEPTION;
static uint8_t  samples_counter     = 0;
static uint8_t  bits_counter        = 0;

static void (*_reception_callback_function)()        = NULL;
static void (*_repeat_reception_callback_function)() = NULL;


// ===============================================================================


void NEC_Decoder_Initialize(void (*reception_callback_function)(), void (*repeat_reception_callback_function)())
{
	NEC_DECODER_EXINT_IN_GPIO_DDR &= ~(1 << NEC_DECODER_EXINT_IN_GPIO_PIN);
	
	_reception_callback_function        = reception_callback_function;
	_repeat_reception_callback_function = repeat_reception_callback_function;
	
	NEC_Decoder_Reset();
}

// ===============================================================================

void NEC_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)())
{
	_reception_callback_function = reception_callback_function;
}

void *NEC_Decoder_Get_Reception_Callback_Function()
{
	return _reception_callback_function;
}

void NEC_Decoder_Set_Repeat_Reception_Callback_Function(void (*repeat_reception_callback_function)())
{
	_repeat_reception_callback_function = repeat_reception_callback_function;
}

void *NEC_Decoder_Get_Repeat_Reception_Callback_Function()
{
	return _repeat_reception_callback_function;
}


// ===============================================================================


NEC_Protocol_Data_t NEC_Decoder_Get_Data()
{
	return nec_data;
}


void NEC_Decoder_Reset()
{
	nec_data.addr         = 0x00;
	nec_data.addr_inv     = 0x00;
	nec_data.commmand     = 0x00;
	nec_data.commmand_inv = 0x00;

	fsm_status            = NO_RECEPTION;
	main_ir_nec_counter   = 0;
	samples_counter       = 0;
	bits_counter          = 0;
}


bool _NEC_Decoder_Get_Input_Level()
{
	if (NEC_DECODER_EXINT_IN_GPIO_PINX & (1 << NEC_DECODER_EXINT_IN_GPIO_PIN))
	{
		return _NEC_DECODER_INPUT_LEVEL_HIGH;
	}
	
	return _NEC_DECODER_INPUT_LEVEL_LOW;
}


void _NEC_Decoder_Receive_Byte(uint8_t *b)
{
	++samples_counter;
	
	if (samples_counter == 2)
	{
		if (main_ir_nec_counter >= (_NEC_DECODER_BIT0_TIMEOUT - 1) && main_ir_nec_counter <= (_NEC_DECODER_BIT0_TIMEOUT + 1))
		{
			++bits_counter;
		}
		
		if (main_ir_nec_counter >= (_NEC_DECODER_BIT1_TIMEOUT - 1))
		{
			*b |= (1 << bits_counter);
			
			++bits_counter;
		}
		
		samples_counter = 0;
		
		main_ir_nec_counter = 0;
	}
}


void NEC_Decoder_FSM()
{
	switch(fsm_status)
	{
		case NO_RECEPTION:
		
		if (_NEC_Decoder_Get_Input_Level() == _NEC_DECODER_INPUT_LEVEL_LOW)
		{
			fsm_status = RECEPTION_START;
		}
		
		main_ir_nec_counter = 0;
		
		break;
		
		
		case RECEPTION_START:
		
		if (main_ir_nec_counter >= (_NEC_DECODER_NUM_OF_START_SAMPLES - 1))
		{
			fsm_status = RECEPTION_POSTSTART_TIMEOUT;
		}
		
		main_ir_nec_counter = 0;
		
		break;
		
		
		case RECEPTION_POSTSTART_TIMEOUT:
		
		if (main_ir_nec_counter >= (_NEC_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES - 1) && main_ir_nec_counter <= (_NEC_DECODER_NUM_OF_POSTSTART_REPEAT_SAMPLES + 1))
		{
			fsm_status = RECEPTION_REPEAT_SAMPLE;
		}
		else
		{
			if (main_ir_nec_counter >= (_NEC_DECODER_NUM_OF_POSTSTART_SAMPLES - 1) && main_ir_nec_counter <= (_NEC_DECODER_NUM_OF_POSTSTART_SAMPLES + 1))
			{
				fsm_status = RECEPTION_ADDRESS;
			}
			else
			{
				fsm_status = NO_RECEPTION;
			}
		}
		
		main_ir_nec_counter = 0;
		
		break;
		
		
		case RECEPTION_REPEAT_SAMPLE:
		
		if (_repeat_reception_callback_function != NULL)
		{
			if ((nec_data.addr ^ nec_data.addr_inv) == 0xFF && (nec_data.commmand ^ nec_data.commmand_inv) == 0xFF)
			{
				if (_repeat_reception_callback_function != NULL)
				{
					_repeat_reception_callback_function();
				}
			}
			
			fsm_status = NO_RECEPTION;
		}
		
		main_ir_nec_counter = 0;
		
		break;
		
		
		case RECEPTION_ADDRESS:
		
		_NEC_Decoder_Receive_Byte(&(nec_data.addr));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_INV_ADDRESS;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_INV_ADDRESS:
		
		_NEC_Decoder_Receive_Byte(&(nec_data.addr_inv));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_COMMAND;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_COMMAND:
		
		_NEC_Decoder_Receive_Byte(&(nec_data.commmand));
		
		if (bits_counter >= 8)
		{
			fsm_status = RECEPTION_INV_COMMAND;
			
			bits_counter = 0;
		}
		
		break;
		
		
		case RECEPTION_INV_COMMAND:
		
		_NEC_Decoder_Receive_Byte(&(nec_data.commmand_inv));
		
		if (bits_counter >= 8)
		{
			if ((nec_data.addr ^ nec_data.addr_inv) == 0xFF && (nec_data.commmand ^ nec_data.commmand_inv) == 0xFF)
			{
				if (_reception_callback_function != NULL)
				{
					_reception_callback_function();
				}
			}
			
			fsm_status = NO_RECEPTION;
			
			bits_counter = 0;
		}
		
		break;


		default:

		NEC_Decoder_Reset();
			
		break;
	}
}


// ===============================================================================


ISR(NEC_DECODER_TIMER_VECTOR_INTERRUPT)
{
	++main_ir_nec_counter;
	
	if (main_ir_nec_counter >= _NEC_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES)
	{
		NEC_Decoder_Reset();
	}
}

ISR(NEC_DECODER_EXINT_VECTOR_INTERRUPT)
{
	NEC_Decoder_FSM();
}

