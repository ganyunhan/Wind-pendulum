#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"
#include "tim.h"

extern int speed_set;

void Motor_init(void);
void Motor_X_speed(int speed);
void Motor_Y_speed(int speed);
void Turn_Right(void);
void Turn_Left(void);
void Motor_Stop(void);
void Motor_Adjust(int speed , int adjust);
void Motor_set(int l_speed , int r_speed);

#endif
