/*
 * motor_control.c
 *
 *  Created on: Mar 24, 2026
 *      Author: benja
 */
#include "balance_motor.h"
#include <math.h>

void Motor_Init(motor_control_t *motor_controller)
{
	HAL_TIM_PWM_Start(motor_controller->htim, motor_controller->channel);
	Set_Speed(motor_controller, 0.0f);
}

void Set_Speed(motor_control_t* motor_controller, float speed)
{
	if (speed >= 0)
	{
		//forward
		HAL_GPIO_WritePin(motor_controller->port_in1, motor_controller->pin_in1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor_controller->port_in2, motor_controller->pin_in2, GPIO_PIN_RESET);
	}
	else if (speed < 0)
	{
		//reverse
		HAL_GPIO_WritePin(motor_controller->port_in1, motor_controller->pin_in1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor_controller->port_in2, motor_controller->pin_in2, GPIO_PIN_SET);
	}
	else
	{
		//stop
		HAL_GPIO_WritePin(motor_controller->port_in1, motor_controller->pin_in1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor_controller->port_in2, motor_controller->pin_in2, GPIO_PIN_RESET);
	}

	float duty_cycle = fabsf(speed);
	if (duty_cycle > 1799.0f) duty_cycle = 1799.0f;

	__HAL_TIM_SET_COMPARE(motor_controller->htim, motor_controller->channel, duty_cycle);
}
