#include "control.h"
#include "motor.h"
#include "uart_handler.h"
#include "math.h"

extern void Turn_Right(void);
extern void Turn_Left(void);
extern float Pitch,Roll,Yaw;
uint16_t Motor_X_Set,Motor_Y_Set;
uint16_t timer = 0;


float Position_KP=0.5,Position_KI=0,Position_KD=0;  			//X控制PID参数
float Position_Kp=-1.5,Position_Ki=-0.18,Position_Kd=0;  	//Y控制PID参数

void Control_Loop1(void)  		//基本要求1，摆幅固定，只在一个方向做简谐运动，固定Pitch，只找Roll          
{
	float omega = (2 * PI) / Period;					//单摆运动角频率
	float A = 5000;											//投影摆幅50cm
	float delta_x = A*sin(omega*timer);	//单位幅度变化
	float theta = asin(delta_x/Length);
	angle_dateprocess();
	
	Motor_X_Set = Position_PID_X (Roll, theta);				//位置PID，Roll角跟踪theta
	Motor_X_speed(Motor_X_Set);
	Motor_Y_Set = Position_PID_Y (Pitch, 0);					//位置PID，Pitch角固定为0
	Motor_Y_speed(Motor_Y_Set);
	timer += 5;													//响应单位时间5ms
}

int Position_PID_X (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //计算偏差
    Integral_bias += Bias;	                             //求出偏差的积分
    Pwm = Position_KP * Bias +                            //PID控制器比例项
          Position_KI * Integral_bias +                     //PID控制器积分项
          Position_KD * (Bias - Last_Bias);                 //PID控制器微分项
    Last_Bias = Bias;                                     //保存上一次偏差
    return Pwm;                                           //增量输出
}

int Position_PID_Y (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //计算偏差
    Integral_bias += Bias;	                             //求出偏差的积分
    Pwm = Position_Kp * Bias +                            //PID控制器比例项
          Position_Ki * Integral_bias +                     //PID控制器积分项
          Position_Kd * (Bias - Last_Bias);                 //PID控制器微分项
    Last_Bias = Bias;                                     //保存上一次偏差
    return Pwm;                                           //增量输出
}
