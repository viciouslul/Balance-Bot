/*
 * balance_pid.h
 *
 *  Created on: Mar 23, 2026
 *      Author: benja
 */
#ifndef INC_BALANCE_PID_H_
#define INC_BALANCE_PID_H_

#include <stdint.h>

typedef struct
{
	float Kp;
	float Ki;
	float Kd;

	float prev_error;
	float integral_sum;

	float out_max;
	float out_min;
} pid_control_t;

void PID_Init(pid_control_t *pid_controller);
float PIDController_Task(pid_control_t *pid_controller, float set_point, float measurement);

#endif /* INC_BALANCE_PID_H_ */
