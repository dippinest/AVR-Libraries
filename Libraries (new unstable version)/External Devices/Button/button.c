
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
	
	
	(*button).status = 0;
	
	
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
		++(button->status);
		
		if ((button->status % press_timeout) == 0)
		{
			callback_function();
		}
	}
	else
	{
		button->status = 0;
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
		if (button->status == 0)
		{
			button->status = 1;
			
			callback_function();
		}
	}
	else
	{
		button->status = 0;
	}
}


void Button_PULLUP_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
	{
		if (button->status == 0)
		{
			button->status = 1;
			
			if (press_callback_function != NULL)
			{
				press_callback_function();
			}
		}
	}
	else
	{
		if (button->status)
		{
			if (release_callback_function != NULL)
			{
				release_callback_function();
			}
		}
		
		button->status = 0;
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
		if (button->status < press_timeout)
		{
			++(button->status);
		}
		else if (button->status == press_timeout)
		{
			callback_function();
			
			++(button->status);
		}
	}
	else
	{
		button->status = 0;
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
		++(button->status);
		
		if ((button->status % press_timeout) == 0)
		{
			callback_function();
		}
	}
	else
	{
		button->status = 0;
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
		if (button->status == 0)
		{
			button->status = 1;
			
			callback_function();
		}
	}
	else
	{
		button->status = 0;
	}
}


void Button_PULLDOWN_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
	{
		if (button->status == 0)
		{
			button->status = 1;
			
			if (press_callback_function != NULL)
			{
				press_callback_function();
			}
		}
	}
	else
	{
		if (button->status)
		{
			if (release_callback_function != NULL)
			{
				release_callback_function();
			}
		}
		
		button->status = 0;
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
		if (button->status < press_timeout)
		{
			++(button->status);
		}
		else if (button->status == press_timeout)
		{
			callback_function();
			
			++(button->status);
		}
	}
	else
	{
		button->status = 0;
	}
}



