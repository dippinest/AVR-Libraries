
#include "samsung_ir_encoder.h"


static Samsung_IR_Protocol_Data_t _samsung_ir_data;

static uint8_t  main_ir_counter     = 0;
static uint8_t  fsm_status          = DISABLE;
static uint8_t  repeat_status       = NO_REPEAT;

static uint8_t  samples_counter     = 0;
static  int8_t  bits_counter        = 7;


// ===============================================================================


void Samsung_IR_Encoder_Initialize()
{
	SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PORT |= (1 << SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PIN);
	SAMSUNG_IR_ENCODER_IR_OUT_GPIO_DDR  |= (1 << SAMSUNG_IR_ENCODER_IR_OUT_GPIO_PIN);
	
	fsm_status            =  DISABLE;
	main_ir_counter       =  0;
	samples_counter       =  0;
	bits_counter          =  7;
	
	Samsung_IR_Encoder_FSM_Timer_Interrupt_Initialize();
	
	Samsung_IR_Encoder_Carrier_Frequency_Generator_Timer_Initialize();
}


// ===============================================================================


bool Samsung_IR_Encoder_Is_Active()
{
	if (fsm_status == DISABLE)
	{
		return false;
	}
	
	return true;
}

void Samsung_IR_Encoder_Stop_Transmittion()
{
	_Samsung_IR_Encoder_Set_IR_Out_Level_Low();
	
	fsm_status        =  DISABLE;
	repeat_status     =  NO_REPEAT;
	main_ir_counter   =  0;
	samples_counter   =  0;
	bits_counter      =  7;
}

void Samsung_IR_Encoder_Wait_Complete_And_Stop_Transmittion()
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	Samsung_IR_Encoder_Stop_Transmittion();
}

enum Samsung_IR_Encoder_Reception_Status Samsung_IR_Encoder_Get_FSM_Status()
{
	return fsm_status;
}


// ===============================================================================


void Samsung_IR_Encoder_Transmit_Standart_Packet(uint8_t addr, uint8_t command, bool is_repeating)
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	_samsung_ir_data.addr_1       =  addr;
	_samsung_ir_data.addr_2       =  addr;
	_samsung_ir_data.commmand_1   =  command;
	_samsung_ir_data.commmand_2   = ~command;
	
	main_ir_counter  = 0;
	bits_counter     = 7;
	
	
	if (is_repeating)
	{
		repeat_status = REPEAT_IS_ALLOWED;
	}
	else
	{
		repeat_status = NO_REPEAT;
	}
	
	
	fsm_status = TRANSMITTION_START;
}

void Samsung_IR_Encoder_Transmit_Custom_Packet(const Samsung_IR_Protocol_Data_t data, bool is_repeating)
{
	while ((fsm_status != DISABLE) && (fsm_status != TRANSMITTION_REPEATING_START));
	
	_samsung_ir_data.addr_1       = data.addr_1;
	_samsung_ir_data.addr_2       = data.addr_1;
	_samsung_ir_data.commmand_1   = data.commmand_1;
	_samsung_ir_data.commmand_2   = data.commmand_2;
	
	main_ir_counter  = 0;
	bits_counter     = 7;
	
	
	if (is_repeating)
	{
		repeat_status = REPEAT_IS_ALLOWED;
	}
	else
	{
		repeat_status = NO_REPEAT;
	}
	
	
	fsm_status = TRANSMITTION_START;
}


// ===============================================================================


void _Samsung_IR_Encoder_Send_Byte(uint8_t *b)
{
	++main_ir_counter;
	
	if (samples_counter == 0)
	{
		_Samsung_IR_Encoder_Set_IR_Out_Level_Low();
		
		samples_counter = 1;
		
		main_ir_counter = 0;
	}
	
	if (samples_counter == 1)
	{
		if ((*b & (1 << bits_counter)) && (main_ir_counter == _SAMSUNG_IR_ENCODER_BIT1_TIMEOUT))
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			main_ir_counter = 0;
			
			samples_counter = 0;
			
			--bits_counter;
		}
		
		if (!(*b & (1 << bits_counter)) && (main_ir_counter == _SAMSUNG_IR_ENCODER_BIT0_TIMEOUT))
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			main_ir_counter = 0;
			
			samples_counter = 0;
			
			--bits_counter;
		}
	}
}


void _Samsung_IR_Encoder_FSM()
{
	switch(fsm_status)
	{
		case TRANSMITTION_START:
		case TRANSMITTION_REPEATING_START:
		
		_Samsung_IR_Encoder_Set_IR_Out_Level_High();
		
		if (main_ir_counter > (_SAMSUNG_IR_ENCODER_NUM_OF_START_SAMPLES - 1))
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_Low();
			
			fsm_status = TRANSMITTION_POSTSTART;
			
			main_ir_counter = 0;
		}
		
		++main_ir_counter;
		
		break;
		
		
		case TRANSMITTION_POSTSTART:
		
		if (main_ir_counter > (_SAMSUNG_IR_ENCODER_NUM_OF_POSTSTART_SAMPLES - 1))
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_ADDRESS_1;
			
			main_ir_counter = 0;
		}
		
		++main_ir_counter;
		
		break;
		
		
		case TRANSMITTION_ADDRESS_1:
		
		_Samsung_IR_Encoder_Send_Byte(&(_samsung_ir_data.addr_1));
		
		if (bits_counter <= -1)
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_ADDRESS_2;
			
			bits_counter = 7;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_ADDRESS_2:
		
		_Samsung_IR_Encoder_Send_Byte(&(_samsung_ir_data.addr_2));
		
		if (bits_counter <= -1)
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_COMMAND_1;
			
			bits_counter = 7;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_COMMAND_1:
		
		_Samsung_IR_Encoder_Send_Byte(&(_samsung_ir_data.commmand_1));
		
		if (bits_counter <= -1)
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			fsm_status = TRANSMITTION_COMMAND_2;
			
			bits_counter = 7;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case TRANSMITTION_COMMAND_2:
		
		_Samsung_IR_Encoder_Send_Byte(&(_samsung_ir_data.commmand_2));
		
		if (bits_counter <= -1)
		{
			_Samsung_IR_Encoder_Set_IR_Out_Level_High();
			
			if (repeat_status == REPEAT_IS_ALLOWED)
			{
				fsm_status = REPEATING_IDLE_WAIT;
			}
			else
			{
				fsm_status = DISABLE;
			}
			
			bits_counter = 7;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		case REPEATING_IDLE_WAIT:
		
		_Samsung_IR_Encoder_Set_IR_Out_Level_Low();
		
		++main_ir_counter;
		
		if (main_ir_counter > _SAMSUNG_IR_ENCODER_MAX_NUM_OF_REPEAT_IDLE_PERIOD_SAMPLES)
		{
			fsm_status = TRANSMITTION_REPEATING_START;
			
			main_ir_counter = 0;
		}
		
		break;
		
		
		default:
		
		_Samsung_IR_Encoder_Set_IR_Out_Level_Low();
		
		fsm_status       = DISABLE;
		repeat_status    = NO_REPEAT;
		main_ir_counter  = 0;
		samples_counter  = 0;
		bits_counter     = 7;
		
		break;
	}
}




// ===============================================================================


ISR(SAMSUNG_IR_ENCODER_TIMER_VECTOR_INTERRUPT)
{
	_Samsung_IR_Encoder_FSM();
}


