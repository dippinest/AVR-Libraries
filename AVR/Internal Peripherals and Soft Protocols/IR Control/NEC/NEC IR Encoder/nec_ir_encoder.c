
#include "nec_ir_encoder.h"


static NEC_IR_Protocol_Data_t _nec_ir_data;

static uint8_t  main_ir_counter     = 0;
static uint8_t  fsm_status          = DISABLE;
static uint8_t  repeat_status       = NO_REPEAT;

static uint8_t  samples_counter     = 0;
static uint8_t  bits_counter        = 0;


// ===============================================================================


void NEC_IR_Encoder_Initialize()
{
	NEC_IR_ENCODER_IR_OUT_GPIO_PORT |= (1 << NEC_IR_ENCODER_IR_OUT_GPIO_PIN);
	NEC_IR_ENCODER_IR_OUT_GPIO_DDR  |= (1 << NEC_IR_ENCODER_IR_OUT_GPIO_PIN);
	
	fsm_status        =  DISABLE;
	repeat_status     =  NO_REPEAT;
	main_ir_counter   =  0;
	samples_counter   =  0;
	bits_counter      =  0;
	
	NEC_IR_Encoder_FSM_Timer_Interrupt_Initialize();
	
	NEC_IR_Encoder_Carrier_Frequency_Generator_Timer_Initialize();
}


// ===============================================================================


bool NEC_IR_Encoder_Is_Active()
{
	if (fsm_status == DISABLE)
	{
		return false;
	}
	
	return true;
}

void NEC_IR_Encoder_Set_Disable_Repetition_Transmittion_Packet()
{
	repeat_status = NO_REPEAT;
}

void NEC_IR_Encoder_Stop_Transmittion()
{
	_NEC_IR_Encoder_Set_IR_Out_Level_Low();
	
	repeat_status     =  NO_REPEAT;
	fsm_status        =  DISABLE;
	main_ir_counter   =  0;
	samples_counter   =  0;
	bits_counter      =  0;
}

void NEC_IR_Encoder_Wait_Complete_And_Stop_Transmittion()
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	NEC_IR_Encoder_Stop_Transmittion();
}

enum NEC_IR_Encoder_Reception_Status NEC_IR_Encoder_Get_FSM_Status()
{
	return fsm_status;
}


// ===============================================================================


void NEC_IR_Encoder_Transmit_Standart_Packet(uint8_t addr, uint8_t command, bool is_repeating)
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	_nec_ir_data.addr_1       =  addr;
	_nec_ir_data.addr_2       = ~addr;
	_nec_ir_data.commmand_1   =  command;
	_nec_ir_data.commmand_2   = ~command;
	
	main_ir_counter = 0;
	bits_counter    = 0;
	
	if (is_repeating)
	{
		repeat_status = IDLE_REPEAT;
	}
	else
	{
		repeat_status = NO_REPEAT;
	}
	
	fsm_status = TRANSMITTION_START;
}

void NEC_IR_Encoder_Transmit_Custom_Packet(const NEC_IR_Protocol_Data_t data, bool is_repeating)
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	_nec_ir_data.addr_1       = data.addr_1;
	_nec_ir_data.addr_2       = data.addr_1;
	_nec_ir_data.commmand_1   = data.commmand_1;
	_nec_ir_data.commmand_2   = data.commmand_2;
	
	main_ir_counter = 0;
	bits_counter    = 0;
	
	
	if (is_repeating)
	{
		repeat_status = IDLE_REPEAT;
	}
	else
	{
		repeat_status = NO_REPEAT;
	}
	
	
	fsm_status = TRANSMITTION_START;
}


// ===============================================================================


void _NEC_IR_Encoder_Send_Byte(uint8_t *b)
{
	++main_ir_counter;
	
	if (samples_counter == 0)
	{
		_NEC_IR_Encoder_Set_IR_Out_Level_Low();
		
		samples_counter = 1;
		
		main_ir_counter = 0;
	}
	
	if (samples_counter == 1)
	{
		if ((*b & (1 << bits_counter)) && (main_ir_counter == _NEC_IR_ENCODER_BIT1_TIMEOUT))
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			main_ir_counter = 0;
			
			samples_counter = 0;
			
			++bits_counter;
		}
		
		if (!(*b & (1 << bits_counter)) && (main_ir_counter == _NEC_IR_ENCODER_BIT0_TIMEOUT))
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			main_ir_counter = 0;
			
			samples_counter = 0;
			
			++bits_counter;
		}
	}
}


void _NEC_IR_Encoder_FSM()
{
	switch(fsm_status)
	{
		case TRANSMITTION_REPEAT_TIMEOUT:
		
		++main_ir_counter;
		
		_NEC_IR_Encoder_Set_IR_Out_Level_Low();
		
		if (main_ir_counter >= _NEC_IR_ENCODER_MAX_NUM_OF_IDLE_PERIOD_SAMPLES)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_REPEATING_START;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		
		case TRANSMITTION_START:
		case TRANSMITTION_REPEATING_START:
		
		++main_ir_counter;
		
		_NEC_IR_Encoder_Set_IR_Out_Level_High();
		
		if (main_ir_counter > _NEC_IR_ENCODER_NUM_OF_START_SAMPLES)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_Low();
			
			fsm_status = TRANSMITTION_POSTSTART;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_POSTSTART:
		
		++main_ir_counter;
		
		if ((repeat_status == RUN_REPEAT) && (main_ir_counter >= _NEC_IR_ENCODER_NUM_OF_POSTSTART_REPEAT_SAMPLES))
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_REPEAT_TIMEOUT;
			
			main_ir_counter = 0;
			
			break;
		}
		
		if ((repeat_status != RUN_REPEAT) && (main_ir_counter >= _NEC_IR_ENCODER_NUM_OF_POSTSTART_SAMPLES))
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_ADDRESS_1;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_ADDRESS_1:
		
		_NEC_IR_Encoder_Send_Byte(&(_nec_ir_data.addr_1));
		
		if (bits_counter >= 8)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_ADDRESS_2;
			
			bits_counter = 0;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_ADDRESS_2:
		
		_NEC_IR_Encoder_Send_Byte(&(_nec_ir_data.addr_2));
		
		if (bits_counter >= 8)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_COMMAND_1;
			
			bits_counter = 0;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_COMMAND_1:
		
		_NEC_IR_Encoder_Send_Byte(&(_nec_ir_data.commmand_1));
		
		if (bits_counter >= 8)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_COMMAND_2;
			
			bits_counter = 0;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_COMMAND_2:
		
		_NEC_IR_Encoder_Send_Byte(&(_nec_ir_data.commmand_2));
			
		if (bits_counter > 8)
		{
			_NEC_IR_Encoder_Set_IR_Out_Level_Low();
			
			if (repeat_status == NO_REPEAT)
			{
				fsm_status = DISABLE;
			}
			
			if (repeat_status == IDLE_REPEAT)
			{
				repeat_status = RUN_REPEAT;
				
				fsm_status    = TRANSMITTION_REPEAT_TIMEOUT;
			}
			
			main_ir_counter = 0;
			
			bits_counter = 0;
		}
		
		break;
		
		
		default:
		
		_NEC_IR_Encoder_Set_IR_Out_Level_Low();
		
		repeat_status    =  NO_REPEAT;
		fsm_status       =  DISABLE;
		main_ir_counter  =  0;
		samples_counter  =  0;
		bits_counter     =  0;
		
		break;
	}
}




// ===============================================================================


ISR(NEC_IR_ENCODER_TIMER_VECTOR_INTERRUPT)
{
	_NEC_IR_Encoder_FSM();
}


