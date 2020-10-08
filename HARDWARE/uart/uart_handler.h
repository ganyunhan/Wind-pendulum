#ifndef UART_HANDLER_H_
#define UART_HANDLER_H_

#include "main.h"
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"

struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};

void Uart_Get(void);
void Uart_DataProcess(void);
void Get_Value(unsigned char* ucFlag);//获取VL53L0数据
void angle_rec(unsigned char ucData);
void angle_dateprocess(void);

#endif
