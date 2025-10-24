
#ifndef SPI_CONFIGURATION_H_
#define SPI_CONFIGURATION_H_

#include <avr/io.h>


// определения GPIO для MOSI вывода SPI
// -------------------------------------------------------------------------------
// GPIO definitions for MOSI output of SPI

#define SPI_MOSI_DDR   DDRB
#define SPI_MOSI_PORT  PORTB
#define SPI_MOSI_PIN   3


// определения GPIO для MISO вывода SPI
// -------------------------------------------------------------------------------
// GPIO definitions for MISO output of SPI

#define SPI_MISO_DDR   DDRB
#define SPI_MISO_PORT  PORTB
#define SPI_MISO_PIN   4


// определения GPIO для SCK вывода SPI
// -------------------------------------------------------------------------------
// GPIO definitions for SCK output of SPI

#define SPI_SCK_DDR    DDRB
#define SPI_SCK_PORT   PORTB
#define SPI_SCK_PIN    5


// определения GPIO для SS вывода SPI
// -------------------------------------------------------------------------------
// GPIO definitions for SS output of SPI

#define SPI_SS_DDR     DDRB
#define SPI_SS_PIN     2

#endif


