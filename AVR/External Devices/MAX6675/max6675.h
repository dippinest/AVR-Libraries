
#ifndef MAX6675_H_
#define MAX6675_H_

#include <stdint.h>

#include "max6675_configuration.h"

#ifdef MAX6675_USE_SOFTSPI
#include "softspi.h"
#else
#include "spi.h"
#endif

// ===============================================================================

float MAX6675_Get_Temperature_In_Celsius_Float();

uint16_t MAX6675_Get_Temperature_In_Celsius_Integer();

uint16_t MAX6675_Get_Temperature_In_Celsius_Fixpoint_2Bit();

#endif
