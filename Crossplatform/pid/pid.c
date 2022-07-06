
#include "pid.h"

static PID_t *target_pid = NULL;

// ===============================================================================

PID_t PID_Get_Controller_Object(float in_min_value, float in_max_value, float out_min_value, float out_max_value, float target_value, float p, float i, float d, float dt)
{
	PID_t pid;
	
	pid.in_min_value  = in_min_value;
	pid.in_max_value  = in_max_value;
	pid.out_min_value = out_min_value;
	pid.out_max_value = out_max_value;
	
	pid.target_value  = target_value;
	
	pid.last_error    = 0.0;
	pid.integral      = 0.0;
	
	pid.p  = p;
	pid.i  = i;
	pid.d  = d;
	pid.dt = dt;
	
	return pid;
}

void PID_Set_Target_Controller_Object(PID_t *controller)
{
	target_pid = controller;
}

PID_t *PID_Get_Target_Controller_Object()
{
	return target_pid;
}

// ===============================================================================

float PID_Get(float current_value)
{
	float PID = 0.0; // PID = (p * error) + (i * integral * dt) + (d * (E - last_error) / dt)
	
	float error = target_pid->target_value - current_value;
	
	// proportional
	PID = target_pid->p * error;
	
	// integral
	target_pid->integral += error;
	target_pid->integral /= 2;
	
	if (target_pid->integral > target_pid->in_max_value)
	{
		target_pid->integral = target_pid->in_max_value;
	}
	
	if (target_pid->integral < target_pid->in_min_value)
	{
		target_pid->integral = target_pid->in_min_value;
	}
	
	PID += target_pid->i * (target_pid->integral * target_pid->dt);
	
	// differential
	PID += ((error - target_pid->last_error) * target_pid->d) / target_pid->dt;
	
	if (PID > target_pid->out_max_value)
	{
		PID = target_pid->out_max_value;
	}
	
	if (PID < target_pid->out_min_value)
	{
		PID = target_pid->out_min_value;
	}
	
	target_pid->last_error = error;
	
	return PID;
}
