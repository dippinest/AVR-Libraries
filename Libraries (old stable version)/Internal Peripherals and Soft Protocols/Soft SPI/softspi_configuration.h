
#ifndef SOFTSPI_CONFIGURATION_H_
#define SOFTSPI_CONFIGURATION_H_


// если вы хотите работать с несколькими программными SPI, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple software SPI, uncomment this define
// (otherwise comment it out)

#define SOFTSPI_USE_MULTIPLE_INTERFACE




#ifndef SOFTSPI_USE_MULTIPLE_INTERFACE

// определения GPIO для MISO вывода программного SPI
// -------------------------------------------------------------------------------
// GPIO definitions for MISO output of software SPI

#define SOFTSPI_MISO_DDR   DDRA
#define SOFTSPI_MISO_PINX  PINA
#define SOFTSPI_MISO_PIN   3


// определения GPIO для MOSI вывода программного SPI
// -------------------------------------------------------------------------------
// GPIO definitions for MOSI output of software SPI

#define SOFTSPI_MOSI_DDR   DDRA
#define SOFTSPI_MOSI_PORT  PORTA
#define SOFTSPI_MOSI_PIN   1


// определения GPIO для CLK вывода программного SPI
// -------------------------------------------------------------------------------
// GPIO definitions for CLK output of software SPI

#define SOFTSPI_CLK_DDR    DDRA
#define SOFTSPI_CLK_PORT   PORTA
#define SOFTSPI_CLK_PIN    0


// определение режима работы программного SPI
// -------------------------------------------------------------------------------
// determining the operating mode of the software SPI

#define SOFTSPI_MODE       SOFTSPI_MODE_0


// определение направления передачи данных (прямое или обратное) по программному SPI
// -------------------------------------------------------------------------------
// determining the direction of data transmission (direct or reverse) by software SPI

#define SOFTSPI_DATA_ORDER SOFTSPI_DATA_IS_ORDER_HIGHEST_BIT

#endif

#endif


