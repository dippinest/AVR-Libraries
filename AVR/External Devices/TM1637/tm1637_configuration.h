
#ifndef TM1637_CONFIGURATION_H_
#define TM1637_CONFIGURATION_H_


// если вы хотите работать с несколькими индикаторами TM1637, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple TM1637 indicators, uncomment this define
// (otherwise comment it out)

#define TM1637_USE_MULTIPLE_INTERFACE




#ifndef TM1637_USE_MULTIPLE_INTERFACE

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


#endif




