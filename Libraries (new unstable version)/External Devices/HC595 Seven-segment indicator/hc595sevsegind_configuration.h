

#ifndef HC595SEVSEGIND_CONFIGURATION_H_
#define HC595SEVSEGIND_CONFIGURATION_H_



// если вы хотите работать с устройством посредством программного SPI,
// раскомментируйте этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with the device via software SPI,
// uncomment this define (otherwise comment it out)
//
#define HC595SEVSEGIND_USE_SOFTSPI





#ifdef HC595SEVSEGIND_USE_SOFTSPI

#warning "COMPILER MESSAGE: Library "hc595sevsegind.h" use software SPI!"

#else

#warning "COMPILER MESSAGE: Library "hc595sevsegind.h" use hardware SPI!"

#endif



#endif





