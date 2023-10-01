
#ifndef MAX7219_CONFIGURATION_H_
#define MAX7219_CONFIGURATION_H_


// если вы хотите работать с устройством посредством программного SPI,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software SPI,
// uncomment this define (otherwise comment it out)

//#define MAX7219_USE_SOFTSPI


// если вы хотите использовать колбэк-функции для изменения вывода
// CS (chip select) SPI устройства, раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to use callback functions to change the CS (chip select) output of the
// device's SPI, uncomment this define (otherwise comment it out)

#define MAX7219_USE_CS_CALLBACKS

#endif


