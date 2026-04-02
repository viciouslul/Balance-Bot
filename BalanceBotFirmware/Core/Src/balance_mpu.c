/*
 * balance_mpu.c
 *
 *  Created on: Mar 25, 2026
 *      Author: benja
 */
#include "balance_mpu.h"
#include <math.h>

void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
	uint8_t check;
	uint8_t data;

	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, 0x75, 1, &check, 1, 1000);
	if (check == 0x68)
	{
		//wake up!
		data = 0;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x6B, 1, &data, 1, 1000);

		//set sample rate to 1KHz.
		data = 0x07;
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x19, 1, &data, 1, 1000);

		data = 0x00;  // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> <strong>±</strong> 2g
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		data = 0x00;  // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> <strong>±</strong> 250 ̐/s
		HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);
	}
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_t *mpu)
{
	uint8_t Rec_Data[14] = {0};

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, 0x3B, 1, Rec_Data, 14, 1000);

    // RAW values
    mpu->accel_x_raw = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    mpu->accel_y_raw = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    mpu->accel_z_raw = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    mpu->temp_raw    = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);

    mpu->gyro_x_raw  = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    mpu->gyro_y_raw  = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    mpu->gyro_z_raw  = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

    // Accelerometer
    mpu->ax = mpu->accel_x_raw / 16384.0f;
    mpu->ay = mpu->accel_y_raw / 16384.0f;
    mpu->az = mpu->accel_z_raw / 16384.0f;

    // Gyroscope
    mpu->gx = mpu->gyro_x_raw / 131.0f;
    mpu->gy = mpu->gyro_y_raw / 131.0f;
    mpu->gz = mpu->gyro_z_raw / 131.0f;

    // Temperature
    mpu->temp = (mpu->temp_raw / 340.0f) + 36.53f;

    //tilt around x
    float raw_angle = atan2f(mpu->ay, mpu->az) * 57.2958f;
    float accel_angle = raw_angle - ACCEL_OFFSET;
    //tilt around y
    //float accel_angle = atan2f(mpu->ax, mpu->az) * 57.2958f;

    mpu->angle = 0.98f * (mpu->angle + (mpu->gx * 0.005f)) + 0.02f * accel_angle;
}
