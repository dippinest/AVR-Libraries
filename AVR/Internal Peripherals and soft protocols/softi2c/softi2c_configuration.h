
#ifndef SOFTI2C_CONFIGURATION_H_
#define SOFTI2C_CONFIGURATION_H_


// если вы хотите работать с несколькими программными I2C, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple software I2C, uncomment this define
// (otherwise comment it out)

#define SOFTI2C_USE_MULTIPLE_INTERFACE




#ifndef SOFTI2C_USE_MULTIPLE_INTERFACE

// определения GPIO для SCL вывода программного I2C
// -------------------------------------------------------------------------------
// GPIO definitions for SCL output of software I2C

#define SOTFI2C_SCL_PIN_DDR	  DDRA
#define SOTFI2C_SCL_PIN_PINX  PINA
#define SOTFI2C_SCL_PIN_PORT  PORTA
#define SOTFI2C_SCL_PIN       1


// определения GPIO для SDA вывода программного I2C
// -------------------------------------------------------------------------------
// GPIO definitions for SDA output of software I2C

#define SOTFI2C_SDA_PIN_DDR	  DDRD
#define SOTFI2C_SDA_PIN_PINX  PIND
#define SOTFI2C_SDA_PIN_PORT  PORTD
#define SOTFI2C_SDA_PIN       6


// задержка между тактами SCL программного I2C
// -------------------------------------------------------------------------------
// delay between clock cycles of SCL software I2C

#define SOTFI2C_CLOCK_DELAY 50

#endif


#endif
