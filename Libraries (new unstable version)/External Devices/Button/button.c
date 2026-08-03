
#include "button.h"


void Button_Initialize_Object
(
	Button_t *button,

	uint8_t  *input_ddr,
	uint8_t  *input_pinx,
	uint8_t   input_pin
)
{
	(*button).input_ddr  = input_ddr;
	(*button).input_pinx = input_pinx;
	(*button).input_pin  = input_pin;
	
	
	(*button).counter_1 = 0;
	(*button).counter_2 = 0;
	
	
	*(input_ddr) &= ~(1 << input_pin);
}



// ===============================================================================



bool Button_PULLUP_Is_Pressed(Button_t *button)
{
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		return true;
	}
	
	return false;
}


void Button_PULLUP_Hold_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (Button_PULLUP_Is_Pressed(button))
	{
		callback_function();
	}
}


void Button_PULLUP_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		++(button->counter_1);
		
		if ((button->counter_1 % press_timeout) == 0)
		{
			callback_function();
		}
	}
	else
	{
		button->counter_1 = 0;
	}
}


void Button_PULLUP_Pressed_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_1 == 0)
		{
			button->counter_1 = 1;
			
			callback_function();
		}
	}
	else
	{
		button->counter_1 = 0;
	}
}


void Button_PULLUP_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_1 == 0)
		{
			button->counter_1 = 1;
			
			if (press_callback_function != NULL)
			{
				press_callback_function();
			}
		}
	}
	else
	{
		if (button->counter_1)
		{
			if (release_callback_function != NULL)
			{
				release_callback_function();
			}
		}
		
		button->counter_1 = 0;
	}
}


void Button_PULLUP_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_2 < press_timeout)
		{
			++(button->counter_2);
		}
		else if (button->counter_2 == press_timeout)
		{
			callback_function();
			
			++(button->counter_2);
		}
	}
	else
	{
		button->counter_2 = 0;
	}
}



// ===============================================================================



bool Button_PULLDOWN_Is_Pressed(Button_t *button)
{
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		return true;
	}
	
	return false;
}


void Button_PULLDOWN_Hold_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (Button_PULLDOWN_Is_Pressed(button))
	{
		callback_function();
	}
}


void Button_PULLDOWN_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		++(button->counter_1);
		
		if ((button->counter_1 % press_timeout) == 0)
		{
			callback_function();
		}
	}
	else
	{
		button->counter_1 = 0;
	}
}


void Button_PULLDOWN_Pressed_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_1 == 0)
		{
			button->counter_1 = 1;
			
			callback_function();
		}
	}
	else
	{
		button->counter_1 = 0;
	}
}


void Button_PULLDOWN_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_1 == 0)
		{
			button->counter_1 = 1;
			
			if (press_callback_function != NULL)
			{
				press_callback_function();
			}
		}
	}
	else
	{
		if (button->counter_1)
		{
			if (release_callback_function != NULL)
			{
				release_callback_function();
			}
		}
		
		button->counter_1 = 0;
	}
}


void Button_PULLDOWN_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		if (button->counter_2 < press_timeout)
		{
			++(button->counter_2);
		}
		else if (button->counter_2 == press_timeout)
		{
			callback_function();
			
			++(button->counter_2);
		}
	}
	else
	{
		button->counter_2 = 0;
	}
}



