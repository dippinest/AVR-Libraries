
#include "softi2c.h"

int main(void)
{
	uint8_t i2c_receiver;
	
	// I2C1
	//
	// SCL - PORTD 5
	// SDA - PORTD 6
	//
	// soft I2C delay = 10
	SOFTI2C_t i2c_1 = SOFTI2C_Get_Object(T(DDRD), T(PIND), T(PORTD), 5, T(DDRD), T(PIND), T(PORTD), 6, 10);
	
	// I2C2
	//
	// SCL - PORTA 0
	// SDA - PORTA 1
	//
	// soft I2C delay = 10
	SOFTI2C_t i2c_2 = SOFTI2C_Get_Object(T(DDRA), T(PINA), T(PORTA), 0, T(DDRA), T(PINA), T(PORTA), 1, 10);
	
	// setting I2C1
	SOFTI2C_Set_Target_Object(&i2c_1);
	
	
	// ========================= TEST I2C1 =========================
	
	SOFTI2C_Start(); // start
	
	SOFTI2C_Send_Byte(0b10110010); // send address + write bit (0)
	SOFTI2C_Send_Byte(0x23);       // send byte
	
	SOFTI2C_Restart(); // restart
	
	SOFTI2C_Send_Byte(0b10110011); // send address + read bit (1)
	
	SOFTI2C_Read_Byte(&i2c_receiver, ACK);  // read byte with confirmation
	SOFTI2C_Read_Byte(&i2c_receiver, ACK);  // read byte with confirmation
	SOFTI2C_Read_Byte(&i2c_receiver, NACK); // read byte without confirmation
	
	SOFTI2C_Stop(); // stop
	
	

	// setting I2C2
	SOFTI2C_Set_Target_Object(&i2c_2);
	
	
	// ========================= TEST I2C2 =========================
	
	SOFTI2C_Start(); // start
	
	SOFTI2C_Send_Byte(0b11011100); // send address + write bit (0)
	SOFTI2C_Send_Byte(0xCA);       // send byte
	
	SOFTI2C_Restart(); // restart
	
	SOFTI2C_Send_Byte(0b11011101); // send address + read bit (1)
	
	SOFTI2C_Read_Byte(&i2c_receiver, ACK);  // read byte with confirmation
	SOFTI2C_Read_Byte(&i2c_receiver, ACK);  // read byte with confirmation
	SOFTI2C_Read_Byte(&i2c_receiver, NACK); // read byte without confirmation
	
	SOFTI2C_Stop(); // stop

	while (1)
	{
	}
}

