
#include "virtualbutton.h"


#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


VirtualButton_t VirtualButton_Create_Object(

	uint8_t* virtual_port,
	uint8_t  virtual_pin,

	bool     pull
)
{
	VirtualButton_t vbutton;

	vbutton.virtual_port = virtual_port;
	vbutton.virtual_pin  = virtual_pin;

	vbutton.pull = pull;

	vbutton.status = 0;

	return vbutton;
}

// ===============================================================================


bool VirtualButton_Is_Pressed(VirtualButton_t* vbutton)
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


void VirtualButton_Hold_Polling(VirtualButton_t* vbutton, void (*callback_function)())
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


void VirtualButton_Hold_With_Timeout_Polling(VirtualButton_t* vbutton, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}

	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			++(vbutton->status);

			if ((vbutton->status % press_timeout) == 0)
			{
				callback_function();
			}
		}
		else
		{
			vbutton->status = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			++(vbutton->status);

			if ((vbutton->status % press_timeout) == 0)
			{
				callback_function();
			}
		}
		else
		{
			vbutton->status = 0;
		}
	}
}


void VirtualButton_Pressed_Polling(VirtualButton_t* vbutton, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}

	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->status == 0)
			{
				vbutton->status = 1;

				callback_function();
			}
		}
		else
		{
			vbutton->status = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->status == 0)
			{
				vbutton->status = 1;

				callback_function();
			}
		}
		else
		{
			vbutton->status = 0;
		}
	}
}


void VirtualButton_Pressed_And_Released_Polling(VirtualButton_t* vbutton, void (*press_callback_function)(), void (*release_callback_function)())
{
	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->status == 0)
			{
				vbutton->status = 1;

				if (press_callback_function != NULL)
				{
					press_callback_function();
				}
			}
		}
		else
		{
			if (vbutton->status)
			{
				if (release_callback_function != NULL)
				{
					release_callback_function();
				}
			}

			vbutton->status = 0;
		}
	}
	else
	{
		if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->status == 0)
			{
				vbutton->status = 1;

				if (press_callback_function != NULL)
				{
					press_callback_function();
				}
			}
		}
		else
		{
			if (vbutton->status)
			{
				if (release_callback_function != NULL)
				{
					release_callback_function();
				}
			}

			vbutton->status = 0;
		}
	}
}


void VirtualButton_Long_Pressed_Polling(VirtualButton_t* vbutton, uint16_t press_timeout, void (*callback_function)())
{
	if (callback_function == NULL)
	{
		return;
	}

	if (vbutton->pull == VIRTUALBUTTON_INPUT_LOGICAL_LEVEL_HIGH)
	{
		if (_Bit_Is_Reset(*(vbutton->virtual_port), vbutton->virtual_pin))
		{
			if (vbutton->status < press_timeout)
			{
				++(vbutton->status);
			}
			else if (vbutton->status == press_timeout)
			{
				callback_function();
				++(vbutton->status);
			}
		}
		else
		{
			vbutton->status = 0;
		}
	}
	else
	{
		{
			if (_Bit_Is_Set(*(vbutton->virtual_port), vbutton->virtual_pin))
			{
				if (vbutton->status < press_timeout)
				{
					++(vbutton->status);
				}
				else if (vbutton->status == press_timeout)
				{
					callback_function();
					++(vbutton->status);
				}
			}
			else
			{
				vbutton->status = 0;
			}
		}
	}
}





