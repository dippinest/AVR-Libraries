
#include "softspi.h"

// chip select ON for SPI1
inline void CS_ON_1()
{
	PORTA &= ~(1 << 3);
}

// chip select OFF for SPI1
inline void CS_OFF_1()
{
	PORTA |=  (1 << 3);
}


// chip select ON for SPI2
inline void CS_ON_2()
{
	PORTD &= ~(1 << 7);
}

// chip select OFF for SPI2
inline void CS_OFF_2()
{
	PORTD |=  (1 << 7);
}

uint8_t spi1_transmitted_data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}; // data to be sent via SPI1
uint8_t spi2_transmitted_data[] = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7}; // data to be sent via SPI2

int main(void)
{
	// SPI1
	//
	// MISO - PORTA 0
	// MOSI - PORTA 1
	// CLK  - PORTA 2
	//
	// SPI mode - MODE0
	// Data order is highest bit
	SOFTSPI_t spi_1 = SOFTSPI_Create_Object(T(DDRA), T(PINA), 0, T(DDRA), T(PORTA), 1, T(DDRA), T(PORTA), 2, SOFTSPI_MODE_0, SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT);
	
	// SPI1
	//
	// MISO - PORTD 4
	// MOSI - PORTD 5
	// CLK  - PORTD 6
	//
	// SPI mode - MODE0
	// Data order is highest bit
	SOFTSPI_t spi_2 = SOFTSPI_Create_Object(T(DDRD), T(PIND), 4, T(DDRD), T(PORTD), 5, T(DDRD), T(PORTD), 6, SOFTSPI_MODE_0, SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT);
	
	DDRA |= (1 << 3);
	DDRD |= (1 << 7);
	
	
	// setting SPI1
	SOFTSPI_Set_Target_Object(&spi_1);
	
	CS_ON_1();
	
	SOFTSPI_Send_Data(spi1_transmitted_data, 8); // send data
	
	CS_OFF_1();
	
	
	// setting SPI2
	SOFTSPI_Set_Target_Object(&spi_2);
	
	CS_ON_2();
	
	SOFTSPI_Send_Data(spi2_transmitted_data, 8); // send data
	
	CS_OFF_2();
	
	while (1)
	{
	}
}


