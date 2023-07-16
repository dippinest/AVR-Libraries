
#ifndef SOFTI2C_CONFIGURATION_H_
#define SOFTI2C_CONFIGURATION_H_

#include <util/delay.h>


// macro for the possibility of implementing multiple soft-i2c buses.
// if you only need one i2c implementation, comment out this macro
#define SOFTI2C_USE_MULTIPLE_INTERFACE


#ifndef SOFTI2C_USE_MULTIPLE_INTERFACE

#define SOTFI2C_SCL_PIN_DDR	  DDRA
#define SOTFI2C_SCL_PIN_PINX  PINA
#define SOTFI2C_SCL_PIN_PORT  PORTA
#define SOTFI2C_SCL_PIN       1

#define SOTFI2C_SDA_PIN_DDR	  DDRD
#define SOTFI2C_SDA_PIN_PINX  PIND
#define SOTFI2C_SDA_PIN_PORT  PORTD
#define SOTFI2C_SDA_PIN       6

#define SOTFI2C_CLOCK_DELAY 50

#endif


#endif
