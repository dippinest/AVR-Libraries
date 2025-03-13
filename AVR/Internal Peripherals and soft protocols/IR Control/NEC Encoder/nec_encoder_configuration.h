

#ifndef NEC_ENCODER_CONFIGURATION_H_
#define NEC_ENCODER_CONFIGURATION_H_


#include <avr/io.h>



// ����������� ������ �� �������
// -------------------------------------------------------------------------------
// determination of the IR signal output

#define NEC_ENCODER_IR_OUT_GPIO_DDR    DDRB
#define NEC_ENCODER_IR_OUT_GPIO_PIN    3




// ��������������� ������� ���������� �������
// -------------------------------------------------------------------------------
// redefining the timer interrupt vector

#define NEC_ENCODER_TIMER_VECTOR_INTERRUPT TIMER0_COMPA_vect




// inline-������� ��������� ���������� ������� �� ����������.
// ���������� ���������� ������ 560 ���. �� ������ �������� ���������,
// ������ �� ��������� ������ ����������, ��������� ��� ������� � ������������������� ����������!
// -------------------------------------------------------------------------------
// inline function for setting timer interruptions by coincidence.
// An interrupt is called every 560 microseconds. You can change the settings,
// but do not change the interruption period, as this will cause the library to malfunction!

inline void NEC_Encoder_FSM_Timer_Interrupt_Initialize()
{
	TIMSK  = (1 << OCIE0A);
	
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS01) | (1 << CS00);
	
	TCNT0 = 0x97;
	OCR0A = 0x68;
}




// inline-������� ��������� �������
// ������ ������� ����������� ������ �� ������������ ������ OCRx �� �����������������
// ��������� � �������� 78 ���. ����� �������, ������ ������ �������� �� ���������
// ������� �� ������� � �������� 38 ���.
// �� ������ �������� ���������, ������ �� ��������� ������ �������,
// ��������� ��� ������� � ������������������� ����������!
// -------------------------------------------------------------------------------
// inline function timer setting
// This function adjusts the timer to switch the OCRx output to the opposite state
// with a frequency of 78 kHz. Thus, this timer is responsible for generating
// an IR carrier signal with a frequency of 38 kHz. You can change the settings,
// but do not change the timer period, as this will cause the library to malfunction!

inline void NEC_Encoder_Carrier_Frequency_Generator_Timer_Initialize()
{
	TCCR1A = (1 << COM1A0);
	
	TCNT1 = 0xFF62;
	OCR1A = 0x009D;
	
	TCCR1B = (1 << CS10) | (1 << WGM12);
}




// inline-������� ���������� ���������� ������ �� �������
// -------------------------------------------------------------------------------
// inline function for the status of the IR signal output control

inline void _NEC_Encoder_Set_IR_Out_Level_High()
{
	TCCR1A = (1 << COM1A0);
}

inline void _NEC_Encoder_Set_IR_Out_Level_Low()
{
	TCCR1A = (1 << COM1A1);
}




#endif





