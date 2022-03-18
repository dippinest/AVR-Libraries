#define F_CPU 16000000UL

#include "i2c.h"
#include "hd44780_i2c.h"

// (I calculated the coefficients for the NTC thermistor MF52 NTC-MF52AT 100 kOhm)
#define A_COEF       0.0006660824105f
#define B_COEF       0.0002239282041f
#define C_COEF       0.0000000719951882f
#define SERIAL_R     120900
#define U_GEN        5.0f
#define U_REF        5.0f
#define ADC_MAX_VAL  1023 // max value 10-bit ADC

#include "ntc_thermometer.h"

inline void ADC_Initialize()
{
	ADCSRA |= (1 << ADEN)  | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX  |= (0 << REFS1) | (1 << REFS0) | (0 << MUX3)  | (0 << MUX2) | (1 << MUX1) | (0 << MUX0);
}

uint16_t ADC_Get_Value()
{
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

int main(void)
{
	I2C_Initialize(100000);
	ADC_Initialize();
	
	HD44780_I2C display = HD44780_I2C_Get_Display_Object(HD44780_I2C_PCF8574_DEV_ADDR_A2T_A1T_A0T, true);
	
	HD44780_I2C_Set_Target_Display_Object(&display);
	
	HD44780_I2C_Set_Cursor_Pos(0, 0); HD44780_I2C_Print_String("NTC THERMOMETER");
	
	while (1)
	{
		float temperature_K = NTC_Thermometer_Get_Temperature_To_Kelvin(ADC_Get_Value());
		
		// convert Kelvin 2 Celsius
		float temperature_C = temperature_K - 273.15f;
		
		// convert Celsius 2 Fahrenheit
		float temperature_F = (temperature_C * 1.8f) + 32.0f;
		
		HD44780_I2C_Clear_String_By_Pos(1, 0, 19); HD44780_I2C_Set_Cursor_Pos(1, 0); HD44780_I2C_Print_StringFmt("Temp = %.1f *K", temperature_K);
		HD44780_I2C_Clear_String_By_Pos(2, 0, 19); HD44780_I2C_Set_Cursor_Pos(2, 0); HD44780_I2C_Print_StringFmt("Temp = %.1f *C", temperature_C);
		HD44780_I2C_Clear_String_By_Pos(3, 0, 19); HD44780_I2C_Set_Cursor_Pos(3, 0); HD44780_I2C_Print_StringFmt("Temp = %.1f *F", temperature_F);
		
		_delay_ms(500);
	}
}