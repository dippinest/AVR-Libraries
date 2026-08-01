

#include "samsung_ir_decoder.h"
#include "uart.h"


static Samsung_IR_Protocol_Data_t _samsung_ir_data;

static uint16_t main_ir_counter    = 0;
static uint8_t  fsm_status         = IDLE;
static uint8_t  samples_counter    = 0;
static  int8_t  bits_counter       = 7;

static bool    is_repeat = false;


static void (*_reception_callback_function)() = NULL;


// ===============================================================================


void Samsung_IR_Decoder_Initialize(void (*reception_callback_function)())
{
	SAMSUNG_IR_DECODER_EXINT_IN_GPIO_DDR &= ~(1 << SAMSUNG_IR_DECODER_EXINT_IN_GPIO_PIN);
	
	_reception_callback_function = reception_callback_function;
	
	Samsung_IR_Decoder_FSM_Timer_Interrupt_Initialize();
	Samsung_IR_Decoder_EXINT_Interrupt_Initialize();
	
	Samsung_IR_Decoder_Reset();
}


// ===============================================================================


void Samsung_IR_Decoder_Set_Reception_Callback_Function(void (*reception_callback_function)())
{
	_reception_callback_function = reception_callback_function;
}

void *Samsung_IR_Decoder_Get_Reception_Callback_Function()
{
	return _reception_callback_function;
}


// ===============================================================================


Samsung_IR_Protocol_Data_t Samsung_IR_Decoder_Get_Data()
{
	return _samsung_ir_data;
}


void Samsung_IR_Decoder_Reset()
{
	_samsung_ir_data.addr_1       = 0x00;
	_samsung_ir_data.addr_2       = 0x00;
	_samsung_ir_data.commmand_1   = 0x00;
	_samsung_ir_data.commmand_2   = 0x00;
	

	fsm_status       = IDLE;
	main_ir_counter  = 0;
	samples_counter  = 0;
	bits_counter     = 7;
}


bool Samsung_IR_Decoder_Received_Package_Is_Repeated()
{
	return is_repeat;
}

bool Samsung_IR_Check_Package_Integrity_For_Standart_Protocol(const Samsung_IR_Protocol_Data_t *_samsung_ir_data)
{
	if ((_samsung_ir_data->addr_1 == _samsung_ir_data->addr_2) && (_samsung_ir_data->commmand_1 ^ _samsung_ir_data->commmand_2) == 0xFF)
	{
		return true;
	}
	
	return false;
}


// ===============================================================================


bool _Samsung_IR_Decoder_Get_Input_Level()
{
	if (SAMSUNG_IR_DECODER_EXINT_IN_GPIO_PINX & (1 << SAMSUNG_IR_DECODER_EXINT_IN_GPIO_PIN))
	{
		return _SAMSUNG_IR_DECODER_INPUT_LEVEL_HIGH;
	}
	
	return _SAMSUNG_IR_DECODER_INPUT_LEVEL_LOW;
}


void _Samsung_IR_Decoder_Receive_Byte(uint8_t *b)
{
	++samples_counter;
	
	if (samples_counter == 2)
	{
		if (main_ir_counter >= (_SAMSUNG_IR_DECODER_BIT0_TIMEOUT - 1) && main_ir_counter <= (_SAMSUNG_IR_DECODER_BIT0_TIMEOUT + 1))
		{
			--bits_counter;
		}
		
		if (main_ir_counter >= (_SAMSUNG_IR_DECODER_BIT1_TIMEOUT - 1) && main_ir_counter <= (_SAMSUNG_IR_DECODER_BIT1_TIMEOUT + 1))
		{
			*b |= (1 << bits_counter);
			
			--bits_counter;
		}
		
		samples_counter = 0;
		
		main_ir_counter = 0;
	}
}


void Samsung_IR_Decoder_FSM()
{
	switch(fsm_status)
	{
		case IDLE:
		
		if (_Samsung_IR_Decoder_Get_Input_Level() == _SAMSUNG_IR_DECODER_INPUT_LEVEL_LOW)
		{
			fsm_status = RECEPTION_START;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_START:
		
		if (main_ir_counter >= (_SAMSUNG_IR_DECODER_NUM_OF_START_SAMPLES - 1))
		{
			fsm_status = RECEPTION_POSTSTART;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_POSTSTART:
		
		if (main_ir_counter >= (_SAMSUNG_IR_DECODER_NUM_OF_START_SAMPLES - 1) && main_ir_counter <= (_SAMSUNG_IR_DECODER_NUM_OF_POSTSTART_SAMPLES + 1))
		{
			fsm_status = RECEPTION_ADDRESS_1;
		}
		else
		{
			fsm_status = IDLE;
			
			is_repeat = false;
		}
		
		main_ir_counter = 0;
		
		break;
		
		
		case RECEPTION_ADDRESS_1:
		
		_Samsung_IR_Decoder_Receive_Byte(&(_samsung_ir_data.addr_1));
		
		if (bits_counter <= -1)
		{
			fsm_status = RECEPTION_ADDRESS_2;
			
			bits_counter = 7;
		}
		
		break;
		
		
		case RECEPTION_ADDRESS_2:
		
		_Samsung_IR_Decoder_Receive_Byte(&(_samsung_ir_data.addr_2));
		
		if (bits_counter <= -1)
		{
			fsm_status = RECEPTION_COMMAND_1;
			
			bits_counter = 7;
		}
		
		break;
		
		
		case RECEPTION_COMMAND_1:
		
		_Samsung_IR_Decoder_Receive_Byte(&(_samsung_ir_data.commmand_1));
		
		if (bits_counter <= -1)
		{
			fsm_status = RECEPTION_COMMAND_2;
			
			bits_counter = 7;
		}
		
		break;
		
		
		case RECEPTION_COMMAND_2:
		
		_Samsung_IR_Decoder_Receive_Byte(&(_samsung_ir_data.commmand_2));
		
		if (bits_counter <= -1)
		{
			if (_reception_callback_function != NULL)
			{
				_reception_callback_function();
			}
			
			is_repeat = true;
			
			Samsung_IR_Decoder_Reset();
		}
		
		break;


		default:

		Samsung_IR_Decoder_Reset();
		
		is_repeat = false;
		
		break;
	}
}


// ===============================================================================


ISR(SAMSUNG_IR_DECODER_TIMER_VECTOR_INTERRUPT)
{
	++main_ir_counter;
	
	if (main_ir_counter >= (_SAMSUNG_IR_DECODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES + 5))
	{
		Samsung_IR_Decoder_Reset();
		
		is_repeat = false;
	}
}

ISR(SAMSUNG_IR_DECODER_EXINT_VECTOR_INTERRUPT)
{
	Samsung_IR_Decoder_FSM();
}

