
#ifndef ONEWIRE_CONFIGURATION_H_
#define ONEWIRE_CONFIGURATION_H_

#include <avr/io.h>


// если вы хотите работать с несколькими программными 1-Wire, раскомментируйте
// этот дефайн (иначе закомментируйте его)
// -------------------------------------------------------------------------------
// if you want to work with multiple software 1-Wire, uncomment this define
// (otherwise comment it out)

//#define ONEWIRE_USE_MULTIPLE_INTERFACE




#ifndef ONEWIRE_USE_MULTIPLE_INTERFACE

// определения GPIO для программного 1-Wire
// -------------------------------------------------------------------------------
// GPIO definitions for software 1-Wire

#define ONEWIRE_DDR   DDRA
#define ONEWIRE_PINX  PINA
#define ONEWIRE_PIN   1

#endif


#endif


