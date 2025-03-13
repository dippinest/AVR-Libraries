
#include "nec_encoder.h"


static NEC_Protocol_Data_t nec;

static uint8_t  main_ir_nec_counter = 0;
static uint8_t  fsm_status          = DISABLE;
static uint8_t  repeat_status       = NO_REPEAT;

static uint8_t  samples_counter     = 0;
static uint8_t  bits_counter        = 0;


// ===============================================================================

void NEC_Encoder_Initialize()
{
	NEC_ENCODER_IR_OUT_GPIO_DDR |= (1 << NEC_ENCODER_IR_OUT_GPIO_PIN);
	
	fsm_status            =  DISABLE;
	repeat_status         =  NO_REPEAT;
	main_ir_nec_counter   =  0;
	samples_counter       =  0;
	bits_counter          =  0;
}


// ===============================================================================

bool NEC_Encoder_Is_Active()
{
	if (fsm_status == DISABLE)
	{
		return false;
	}
	
	return true;
}

void NEC_Encoder_Set_Disable_Repetition_Transmittion_Packet()
{
	repeat_status = NO_REPEAT;
}

void NEC_Encoder_Stop_Transmittion()
{
	_NEC_Encoder_Set_IR_Out_Level_Low();
	
	repeat_status         =  NO_REPEAT;
	fsm_status            =  DISABLE;
	main_ir_nec_counter   =  0;
	samples_counter       =  0;
	bits_counter          =  0;
}

void NEC_Encoder_Wait_Complete_And_Stop_Transmittion()
{
	if (repeat_status != NO_REPEAT)
	{
		while (fsm_status != TRANSMITTION_START);
	}
	else
	{
		while (fsm_status != DISABLE);
	}
	
	_NEC_Encoder_Set_IR_Out_Level_Low();
	
	repeat_status         =  NO_REPEAT;
	fsm_status            =  DISABLE;
	main_ir_nec_counter   =  0;
	samples_counter       =  0;
	bits_counter          =  0;
}

enum NEC_Encoder_Reception_Status NEC_Encoder_Get_FSM_Status()
{
	return fsm_status;
}


// ===============================================================================


void NEC_Encoder_Transmit_Packet(uint8_t address, uint8_t command, bool is_repeating)
{
	nec.addr         =  address;
	nec.addr_inv     = ~address;
	nec.commmand     =  command;
	nec.commmand_inv = ~command;
	
	main_ir_nec_counter = 0;
	bits_counter        = 0;
	
	fsm_status   = TRANSMITTION_START;
	
	if (is_repeating)
	{
		repeat_status = IDLE_REPEAT;
	}
	else
	{
		repeat_status = NO_REPEAT;
	}
}


// ===============================================================================


void _NEC_Encoder_Send_Byte(uint8_t *b)
{
	++main_ir_nec_counter;
	
	if (samples_counter == 0)
	{
		_NEC_Encoder_Set_IR_Out_Level_Low();
		
		samples_counter = 1;
		
		main_ir_nec_counter = 0;
	}
	
	if (samples_counter == 1)
	{
		if ((*b & (1 << bits_counter)) && (main_ir_nec_counter == _NEC_ENCODER_BIT1_TIMEOUT))
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			main_ir_nec_counter = 0;
			
			samples_counter = 0;
			
			++bits_counter;
		}
		
		if (!(*b & (1 << bits_counter)) && (main_ir_nec_counter == _NEC_ENCODER_BIT0_TIMEOUT))
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			main_ir_nec_counter = 0;
			
			samples_counter = 0;
			
			++bits_counter;
		}
	}
}


void _NEC_Encoder_FSM()
{
	switch(fsm_status)
	{
		case TRANSMITTION_REPEAT_TIMEOUT:
		
		++main_ir_nec_counter;
		
		_NEC_Encoder_Set_IR_Out_Level_Low();
		
		if (main_ir_nec_counter >= _NEC_ENCODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_START;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		
		case TRANSMITTION_START:
		
		++main_ir_nec_counter;
		
		_NEC_Encoder_Set_IR_Out_Level_High();
		
		if (main_ir_nec_counter > _NEC_ENCODER_NUM_OF_START_SAMPLES)
		{
			_NEC_Encoder_Set_IR_Out_Level_Low();
			
			fsm_status = TRANSMITTION_POSTSTART;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_POSTSTART:
		
		++main_ir_nec_counter;
		
		if (repeat_status == RUN_REPEAT && main_ir_nec_counter >= _NEC_ENCODER_NUM_OF_POSTSTART_REPEAT_SAMPLES)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_REPEAT_TIMEOUT;
			
			main_ir_nec_counter = 0;
		}
		
		if (repeat_status != RUN_REPEAT && main_ir_nec_counter >= _NEC_ENCODER_NUM_OF_POSTSTART_SAMPLES)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_ADDRESS;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_ADDRESS:
		
		_NEC_Encoder_Send_Byte(&(nec.addr));
		
		if (bits_counter >= 8)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_INV_ADDRESS;
			
			bits_counter = 0;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_INV_ADDRESS:
		
		_NEC_Encoder_Send_Byte(&(nec.addr_inv));
		
		if (bits_counter >= 8)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_COMMAND;
			
			bits_counter = 0;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_COMMAND:
		
		_NEC_Encoder_Send_Byte(&(nec.commmand));
		
		if (bits_counter >= 8)
		{
			_NEC_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_INV_COMMAND;
			
			bits_counter = 0;
			
			main_ir_nec_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_INV_COMMAND:
		
		if (bits_counter < 8)
		{
			_NEC_Encoder_Send_Byte(&(nec.commmand_inv));
		}
		else
		{
			_NEC_Encoder_Set_IR_Out_Level_Low();
			
			if (repeat_status == NO_REPEAT)
			{
				fsm_status = DISABLE;
			}
			else
			{
				repeat_status = RUN_REPEAT;
				
				fsm_status    = TRANSMITTION_REPEAT_TIMEOUT;
			}
			
			main_ir_nec_counter = 0;
			
			bits_counter = 0;
		}
		
		break;
		
		
		default:
		
		_NEC_Encoder_Set_IR_Out_Level_Low();
		
		repeat_status        =  RUN_REPEAT;
		fsm_status           =  DISABLE;
		main_ir_nec_counter  =  0;
		samples_counter      =  0;
		bits_counter         =  0;
		
		break;
	}
}




// ===============================================================================


ISR(NEC_ENCODER_TIMER_VECTOR_INTERRUPT)
{
	_NEC_Encoder_FSM();
}


