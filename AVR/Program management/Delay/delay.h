
#ifndef DELAY_H_
#define DELAY_H_

#include <util/delay.h>
#include <stdint.h>
#include <stddef.h>

#include "delay_configuration.h"


#ifdef DELAY_USE_YIELD_MS

void Delay_Ms_Set_Yield_CallBack_Function(void (*delay_yield_ms)());

#endif

#ifdef DELAY_USE_YIELD_US

void Delay_Us_Set_Yield_CallBack_Function(void (*delay_yield_us)());

#endif



void Delay_Ms(uint16_t ms_delay);

void Delay_Us(uint16_t us_delay);


#endif
