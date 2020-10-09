#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include "stdio.h"
#include "motor.h"

#define PI			3.14
#define Length	750			//�ڳ�750mm
#define Gra			9800		//�������ٶ�
#define Period				1730		//����1730����

extern int speed_set;

int Position_PID_X (float value, float Target);
int Position_PID_Y (float value, float Target);
void Track(void);
void Control_Loop1(void);

#endif
