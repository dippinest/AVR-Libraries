
#include "anacomp.h"

#ifdef ANACOMP_USE_CALLBACK

static void (*_reception_callback)() = NULL;

void ANACOMP_Set_CallBack_Function(void (*callback_function)())
{
	_reception_callback = callback_function;
}

void *ANACOMP_Get_CallBack_Function()
{
	return _reception_callback;
}

ISR(ANA_COMP_vect)
{
	_reception_callback();
}

#endif
