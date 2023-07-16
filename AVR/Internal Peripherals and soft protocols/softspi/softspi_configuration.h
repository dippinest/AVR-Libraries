
#ifndef SOFTSPI_CONFIGURATION_H_
#define SOFTSPI_CONFIGURATION_H_

// macro for the possibility of implementing multiple soft-spi buses.
// if you only need one spi implementation, comment out this macro
#define SOFTSPI_USE_MULTIPLE_INTERFACE


#ifndef SOFTSPI_USE_MULTIPLE_INTERFACE

#define SOFTSPI_MISO_DDR   DDRA
#define SOFTSPI_MISO_PINX  PINA
#define SOFTSPI_MISO_PIN   3

#define SOFTSPI_MOSI_DDR   DDRA
#define SOFTSPI_MOSI_PORT  PORTA
#define SOFTSPI_MOSI_PIN   1

#define SOFTSPI_CLK_DDR    DDRA
#define SOFTSPI_CLK_PORT   PORTA
#define SOFTSPI_CLK_PIN    0

#define SOFTSPI_MODE       SOFTSPI_MODE_0
#define SOFTSPI_DATA_ORDER SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT

#endif

#endif