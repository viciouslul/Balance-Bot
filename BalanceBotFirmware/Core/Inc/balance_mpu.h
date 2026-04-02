/*
 * balance_mpu.h
 *
 *  Created on: Mar 25, 2026
 *      Author: benja
 */

#ifndef INC_BALANCE_MPU_H_
#define INC_BALANCE_MPU_H_

#define MPU6050_ADDR 		0xD0
#define ACCEL_CONFIG_REG 	0x1C
#define GYRO_CONFIG_REG		0x1B
#define ACCEL_OFFSET -3.09f

#include "stm32f3xx_hal.h"

typedef struct
{
	int16_t accel_x_raw, accel_y_raw, accel_z_raw;
	int16_t gyro_x_raw, gyro_y_raw, gyro_z_raw;
    int16_t temp_raw;

    // Converted data
    float ax, ay, az;
    float gx, gy, gz;
    float temp;

	float angle;
    float angle_offset;
} MPU6050_t;

void MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_t *mpu);
void MPU6050_Calibrate(I2C_HandleTypeDef *hi2c, MPU6050_t *mpu);
#endif /* INC_BALANCE_MPU_H_ */
