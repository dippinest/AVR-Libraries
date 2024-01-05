
#ifndef TM1637_CONFIGURATION_H_
#define TM1637_CONFIGURATION_H_



// определения GPIO для CLK TM1637
// -------------------------------------------------------------------------------
// GPIO definitions for CLK TM1637

#define TM1637_CLK_DDR	 DDRC
#define TM1637_CLK_PORT  PORTC
#define TM1637_CLK_PIN   0


// определения GPIO для DIO TM1637
// -------------------------------------------------------------------------------
// GPIO definitions for DIO TM1637

#define TM1637_DIO_DDR	 DDRC
#define TM1637_DIO_PINX  PINC
#define TM1637_DIO_PORT  PORTC
#define TM1637_DIO_PIN   1


#endif


