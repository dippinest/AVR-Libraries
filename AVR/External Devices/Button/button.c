
#include "button.h"


#ifndef _Bit_Is_Set_P
#define _Bit_Is_Set_P(port, bit)    ((*port) & (1 << bit))
#endif

#ifndef _Bit_Is_Reset_P
#define _Bit_Is_Reset_P(port, bit) !((*port) & (1 << bit))
#endif


Button_t Button_Get_Object(

	uint8_t *input_ddr,
	uint8_t *input_pinx,
	uint8_t  input_pin,

	bool     pull
)
{
	Button_t button;
	
	button.input_ddr  = input_ddr;
	button.input_pinx = input_pinx;
	button.input_pin  = input_pin;
	
	button.pull   = pull;
	
	button.status = 0;
	
	*(input_ddr) &= ~(1 << input_pin);
	
	return button;
}

// ===============================================================================


bool Button_Is_Pressed(Button_t *button)
{
	if (button->pull == BUTTON_INPUT_PULLUP)
	{
		if (_Bit_Is_Reset_P(button->input_pinx, button->input_pin))
		{
			return true;
		}
	}
	else
	{
		if (_Bit_Is_Set_P(button->input_pinx, button->input_pin))
		{
			return true;
		}
	}
	
	return false;
}


void Button_Hold_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (Button_Is_Pressed(button))
	{
		callback_function();
	}
}


void Button_Hold_With_Timeout_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (button->pull == BUTTON_INPUT_PULLUP)
	{
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
	else
	{
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
}


void Button_Pressed_Polling(Button_t *button, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (button->pull == BUTTON_INPUT_PULLUP)
	{
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
	else
	{
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
}


void Button_Pressed_And_Released_Polling(Button_t *button, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (button->pull == BUTTON_INPUT_PULLUP)
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
	else
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
}


void Button_Long_Pressed_Polling(Button_t *button, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	
	if (button->pull == BUTTON_INPUT_PULLUP)
	{
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
	else
	{
		{
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
	}
}


