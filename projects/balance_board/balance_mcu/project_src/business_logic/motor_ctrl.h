#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include "sdk_include.h"

#define GYRO_X 0
#define GYRO_Y 1
#define GYRO_Z 2
#define ACC_X 3
#define ACC_Y 4
#define ACC_Z 5

void motor_ctrl_init(void);
void get_att(uint16_t Ws);
void speed_control(uint8_t axis);
void angle_control(uint8_t axis);

#endif
