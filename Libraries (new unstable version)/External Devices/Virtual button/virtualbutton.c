

#include "virtualbutton.h"



void VirtualButton_Initialize_Object
(
	VirtualButton_t *vbutton,

	uint8_t *virtual_port,
	uint8_t  virtual_pin,

	bool     pull
)
{
	(*vbutton).virtual_port = virtual_port;
	(*vbutton).virtual_pin  = virtual_pin;

	(*vbutton).pull = pull;

	(*vbutton).press_counter      = 0;
	(*vbutton).long_press_counter = 0;
}



// ===============================================================================



bool VirtualButton_Is_Pressed(VirtualButton_t *vbutton)
{
	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			return true;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			return true;
		}
	}
	

	return false;
}


void VirtualButton_Hold_Polling(VirtualButton_t *vbutton, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}

	if (VirtualButton_Is_Pressed(vbutton))
	{
		callback_function();
	}
}


void VirtualButton_Hold_With_Timeout_Polling(VirtualButton_t *vbutton, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}


	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			++(vbutton->press_counter);

			if ((vbutton->press_counter > 0) && ((vbutton->press_counter % press_timeout) == 0))
			{
				callback_function();
			}
		}
		else
		{
			vbutton->press_counter = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			++(vbutton->press_counter);

			if ((vbutton->press_counter > 0) && ((vbutton->press_counter % press_timeout) == 0))
			{
				callback_function();
			}
		}
		else
		{
			vbutton->press_counter = 0;
		}
	}
}


void VirtualButton_Pressed_Polling(VirtualButton_t *vbutton, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}


	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->press_counter == 0)
			{
				vbutton->press_counter = 1;

				callback_function();
			}
		}
		else
		{
			vbutton->press_counter = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->press_counter == 0)
			{
				vbutton->press_counter = 1;

				callback_function();
			}
		}
		else
		{
			vbutton->press_counter = 0;
		}
	}
}


void VirtualButton_Pressed_And_Released_Polling(VirtualButton_t *vbutton, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->press_counter == 0)
			{
				vbutton->press_counter = 1;

				if (press_callback_function != NULL)
				{
					press_callback_function();
				}
			}
		}
		else
		{
			if (vbutton->press_counter)
			{
				if (release_callback_function != NULL)
				{
					release_callback_function();
				}
			}

			vbutton->press_counter = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->press_counter == 0)
			{
				vbutton->press_counter = 1;

				if (press_callback_function != NULL)
				{
					press_callback_function();
				}
			}
		}
		else
		{
			if (vbutton->press_counter)
			{
				if (release_callback_function != NULL)
				{
					release_callback_function();
				}
			}

			vbutton->press_counter = 0;
		}
	}
}


void VirtualButton_Long_Pressed_Polling(VirtualButton_t *vbutton, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}
	

	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->long_press_counter < press_timeout)
			{
				++(vbutton->long_press_counter);
			}
			else if (vbutton->long_press_counter == press_timeout)
			{
				callback_function();
				++(vbutton->long_press_counter);
			}
		}
		else
		{
			vbutton->long_press_counter = 0;
		}
	}
	else
	{
		{
			if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
			{
				if (vbutton->long_press_counter < press_timeout)
				{
					++(vbutton->long_press_counter);
				}
				else if (vbutton->long_press_counter == press_timeout)
				{
					callback_function();
					++(vbutton->long_press_counter);
				}
			}
			else
			{
				vbutton->long_press_counter = 0;
			}
		}
	}
}






