
#ifndef PID_H_
#define PID_H_

#include <stdint.h>
#include <stdio.h>

typedef struct
{
	float in_min_value;  // minimum value of the input parameter
	float in_max_value;  // maximum value of the input parameter
	float out_min_value; // minimum value of the output parameter
	float out_max_value; // maximum value of the output parameter
	float target_value;  // target value
	float last_error;    // last error value
	float integral;      // integral value
	float p;             // proportional coef
	float i;             // integral coef
	float d;             // differential coef
	float dt;            // delta t (time)
	
} PID_t;

// ===============================================================================

PID_t PID_Get_Controller_Object(float in_min_value, float in_max_value, float out_min_value, float out_max_value, float target_value, float p, float i, float d, float dt);

void PID_Set_Target_Controller_Object(PID_t *controller);

PID_t *PID_Get_Target_Controller_Object();

// ===============================================================================

float PID_Get(float current_value);

#endif