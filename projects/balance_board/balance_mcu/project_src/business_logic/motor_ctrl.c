#include "motor_ctrl.h"
#include "mpu6050.h"
#include "math.h"
#include "pid.h"
#include "motor.h"

float angle_x, angle_y;
float gyro_x, gyro_y;
float speed_x, speed_y;

pid_position_float_s pid_angle_x, pid_angle_y, pid_speed_x, pid_speed_y;
void motor_ctrl_init(void)
{
    pid_angle_x.out_max = 5;
    pid_angle_x.out_max = -5;
    pid_angle_y.out_max = 5;
    pid_angle_y.out_max = -5;
    
    pid_speed_x.out_max = 1000;
    pid_speed_x.out_max = -1000;
    pid_speed_y.out_max = 1000;
    pid_speed_y.out_max = -1000;
}


void get_att(uint16_t Ws)
{
	int16_t imu_data[6];
	float	pitch, roll;
	
	mpu6050_read_6axis_data(&imu_data[GYRO_X], &imu_data[GYRO_Y], &imu_data[GYRO_Z], &imu_data[ACC_X], &imu_data[ACC_Y], &imu_data[ACC_Z]);
	
    gyro_x = imu_data[GYRO_X] / 65.5f;
    gyro_y = imu_data[GYRO_Y] / 65.5f;
    
	roll = atan2(imu_data[ACC_X], -imu_data[ACC_Z]);
	pitch  = atan2(imu_data[ACC_Y], -imu_data[ACC_Z]);
    
    angle_x	= 0.7 * (angle_x + gyro_x * Ws) + 0.3 * pitch;
	angle_y	= 0.7 * (angle_y + gyro_y * Ws) + 0.3 * roll;
}


void speed_control(uint8_t axis)
{
    if(axis == 0)
    {
        pid_speed_x.current_err = speed_x;
    
        pid_speed_x.out = pid_speed_x.kp * pid_speed_x.current_err + pid_speed_x.kd * get_motor_encoder(MOTOR_NO_X);
        
        pid_speed_x.out = LIMIT_MAX_MIN(pid_speed_x.out, pid_speed_x.out_max, pid_speed_x.out_min);
        
        pid_angle_x.target = pid_speed_x.out;
    }
    else
    {
        pid_speed_y.current_err = speed_y;
    
        pid_speed_y.out = pid_speed_y.kp * pid_speed_y.current_err + pid_speed_y.kd * get_motor_encoder(MOTOR_NO_Y);
        
        pid_speed_y.out = LIMIT_MAX_MIN(pid_speed_y.out, pid_speed_y.out_max, pid_speed_y.out_min);
        
        pid_angle_y.target = pid_speed_y.out;
    }
}


void angle_control(uint8_t axis)
{
    if(axis == 0)
    {
        pid_angle_x.current_err = angle_x - pid_angle_x.target;
    
        pid_angle_x.out = pid_angle_x.kp * pid_angle_x.current_err + pid_angle_x.kd * gyro_x;
        
        pid_angle_x.out = LIMIT_MAX_MIN(pid_angle_x.out, pid_angle_x.out_max, pid_angle_x.out_min);
    }
    else
    {
        pid_angle_y.current_err = angle_y - pid_angle_y.target;
    
        pid_angle_y.out = pid_angle_y.kp * pid_angle_y.current_err + pid_angle_y.kd * gyro_y;
        
        pid_angle_y.out = LIMIT_MAX_MIN(pid_angle_y.out, pid_angle_y.out_max, pid_angle_y.out_min);
    }
}

