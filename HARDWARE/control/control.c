#include "control.h"
#include "motor.h"
#include "uart_handler.h"
#include "math.h"

extern void Turn_Right(void);
extern void Turn_Left(void);
extern float Pitch,Roll,Yaw;
uint16_t Motor_X_Set,Motor_Y_Set;
uint16_t timer = 0;


float Position_KP=0.5,Position_KI=0,Position_KD=0;  			//X����PID����
float Position_Kp=-1.5,Position_Ki=-0.18,Position_Kd=0;  	//Y����PID����

void Control_Loop1(void)  		//����Ҫ��1���ڷ��̶���ֻ��һ����������г�˶����̶�Pitch��ֻ��Roll          
{
	float omega = (2 * PI) / Period;					//�����˶���Ƶ��
	float A = 5000;											//ͶӰ�ڷ�50cm
	float delta_x = A*sin(omega*timer);	//��λ���ȱ仯
	float theta = asin(delta_x/Length);
	angle_dateprocess();
	
	Motor_X_Set = Position_PID_X (Roll, theta);				//λ��PID��Roll�Ǹ���theta
	Motor_X_speed(Motor_X_Set);
	Motor_Y_Set = Position_PID_Y (Pitch, 0);					//λ��PID��Pitch�ǹ̶�Ϊ0
	Motor_Y_speed(Motor_Y_Set);
	timer += 5;													//��Ӧ��λʱ��5ms
}

int Position_PID_X (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //����ƫ��
    Integral_bias += Bias;	                             //���ƫ��Ļ���
    Pwm = Position_KP * Bias +                            //PID������������
          Position_KI * Integral_bias +                     //PID������������
          Position_KD * (Bias - Last_Bias);                 //PID������΢����
    Last_Bias = Bias;                                     //������һ��ƫ��
    return Pwm;                                           //�������
}

int Position_PID_Y (float value, float Target)
{
    static float Bias, Pwm, Integral_bias, Last_Bias;
    Bias = value - Target;                                //����ƫ��
    Integral_bias += Bias;	                             //���ƫ��Ļ���
    Pwm = Position_Kp * Bias +                            //PID������������
          Position_Ki * Integral_bias +                     //PID������������
          Position_Kd * (Bias - Last_Bias);                 //PID������΢����
    Last_Bias = Bias;                                     //������һ��ƫ��
    return Pwm;                                           //�������
}
