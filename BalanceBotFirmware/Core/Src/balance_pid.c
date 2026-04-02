/*
 * balance_pid.c
 *
 *  Created on: Mar 23, 2026
 *      Author: benja
 */
#include "balance_pid.h"

void PID_Init(pid_control_t *pid_controller)
{
	pid_controller->integral_sum 	= 0.0f;
	pid_controller->prev_error 		= 0.0f;
}

float PIDController_Task(pid_control_t *pid_controller, float set_point, float measurement)
{
	float error = set_point - measurement;

	//P: Error = Setpoint - measurement: Kp * error
	float proportional = pid_controller->Kp * error;

	//I: Add current Error to integral_sum: I = Ki * integral_sum
	pid_controller->integral_sum += error;
	if (pid_controller->integral_sum >= pid_controller->out_max) pid_controller->integral_sum = pid_controller->out_max;
	if (pid_controller->integral_sum <= pid_controller->out_min) pid_controller->integral_sum = pid_controller->out_min;
	float integral = pid_controller->Ki * pid_controller->integral_sum;

	//D: Delta error = Error - prev_error: D = Kd * delta_error
	float delta_error = error - pid_controller->prev_error;
	float derivative = pid_controller->Kd * delta_error;

	pid_controller->prev_error = error;

	float output = (proportional + integral + derivative);
	if (output >= pid_controller->out_max) return pid_controller->out_max;
	if (output <= pid_controller->out_min) return pid_controller->out_min;

	return output;
}
