
#ifndef SPI_CONFIGURATION_H_
#define SPI_CONFIGURATION_H_

#include <avr/io.h>

#define SPI_MOSI_DDR   DDRB
#define SPI_MISO_PORT  PORTB
#define SPI_MOSI_PIN   3

#define SPI_MISO_DDR   DDRB
#define SPI_MISO_PINX  PINB
#define SPI_MISO_PIN   4

#define SPI_SCK_DDR    DDRB
#define SPI_SCK_PORTB  PORTB
#define SPI_SCK_PIN    5

#define SPI_SS_DDR     DDRB
#define SPI_SS_PIN     2

#define SPI_USE_CS_FUNCTION_CALLBACK

#endif