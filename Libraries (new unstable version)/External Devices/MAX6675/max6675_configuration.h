

#ifndef MAX6675_CONFIGURATION_H_
#define MAX6675_CONFIGURATION_H_



// если вы хотите работать с устройством посредством программного SPI,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software SPI,
// uncomment this define (otherwise comment it out)

#define MAX6675_USE_SOFTSPI



// если вы хотите использовать колбэк-функции для изменения вывода
// CS (chip select) SPI устройства, раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to use callback functions to change the CS (chip select) output of the
// device's SPI, uncomment this define (otherwise comment it out)

#define MAX6675_USE_CS_CALLBACKS





#ifdef MAX6675_USE_SOFTSPI

#warning "COMPILER MESSAGE: Library "max6675.h" use software SPI!"

#else

#warning "COMPILER MESSAGE: Library "max6675.h" use hardware SPI!"

#endif



#ifdef MAX6675_USE_CS_CALLBACKS

#warning "COMPILER MESSAGE: Library "max6675.h" use SPI CS callbacks!"

#else

#warning "COMPILER MESSAGE: Library "max6675.h" do not use SPI CS callbacks!"

#endif





#endif





