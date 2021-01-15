#include "motor_ctrl.h"
#include "mpu6050.h"
#include "math.h"

void get_att(uint16_t Ts)
{
	int16_t imu_data[6];
	double	pitch, roll;
	
	mpu6050_read_6axis_data(&imu_data[0], &imu_data[1], &imu_data[2], &imu_data[3], &imu_data[4], &imu_data[5]);
	
	pitch = atan2(imu_data[3], -imu_data[5]) * RAD_TO_DEG;
	roll  = atan2(imu_data[4], -imu_data[5]) * RAD_TO_DEG;
}
