/*
 * motor_control.h
 *
 *  Created on: Mar 24, 2026
 *      Author: benja
 */

#ifndef INC_BALANCE_MOTOR_H_
#define INC_BALANCE_MOTOR_H_
#include "stm32f3xx_hal.h"
#include <stdint.h>

#define MOTOR_MAX_PWM 1799

typedef struct
{
	float 					speed;
	TIM_HandleTypeDef 		*htim;
	uint32_t 				channel;
	GPIO_TypeDef			*port_in1;
	GPIO_TypeDef			*port_in2;
	uint32_t				pin_in1;
	uint32_t				pin_in2;
} motor_control_t;

void Motor_Init(motor_control_t *motor_controller);
void Set_Speed(motor_control_t* motor_controller, float speed);

#endif /* INC_BALANCE_MOTOR_H_ */
