
#define F_CPU 16000000UL
#include <util/delay.h>

#include "uart.h"
#include "spi.h"
#include "adc.h"
#include "filters.h"
#include "pid.h"
#include "max6675.h"

#define  OUTPUT_POWER OCR1A

void CS_ON()
{
	PORTD &= ~(1 << 7);
}

void CS_OFF()
{
	PORTD |= (1 << 7);
}

static PID_t pid;

int main(void)
{
	UART_Initialize(56000, true, false);
	
	// The load is controlled by a 10-bit PWM (T1 timer is used)
	DDRB   |=  (1 << 1);
	TCCR1A  = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
	TCCR1B  = (1 << CS11);
	
	DDRD   |= (1 << 7);
	SPI_Initialize(true, SPI_DEV_IS_MASTER, SPI_MODE_0, SPI_SPEED_FCPU_DIV_128);
	SPI_Set_CS_CallBack_Functions(CS_ON, CS_OFF);
	
	ADC_Initialize(5, ADC_PRESCALER_128, ADC_VREF_SOURCE_EXTERNAL_AVCC, true);
	
	#define PID_PERIOD 250 // dt = 250 ms
	
	// proportional coef = 4.55
	// integral coef     = 6.95
	// differential coef = 4.15
	// delta t (time)    = PID_PERIOD (250 ms)
	pid = PID_Get_Controller_Object(20, 60, 0, 1023, 20.0, 3.55, 6.45, 4.15, (1.0 / (float)PID_PERIOD));
	PID_Set_Target_Controller_Object(&pid);
	while (1)
	{
		// setting the target temperature value using a potentiometer (+20 ... +105 *C)
		pid.target_value = 20.0 + ADC_Get_Value_10bit() / 12;
		
		float real_temp = MAX6675_Get_Temperature_In_Celsius_Float();
		
		UART_Data_Transmit(&(pid.target_value), sizeof(float));
		UART_Data_Transmit(&real_temp, sizeof(float));
		
		OUTPUT_POWER = PID_Get(real_temp);
		
		// if temperature is higher than the set value, turn off the load
		// (PID calculations are performed to establish the integral value)
		if (real_temp > pid.target_value)
		{
			OUTPUT_POWER = 0;
		}
		
		_delay_ms(PID_PERIOD);
	}
}
