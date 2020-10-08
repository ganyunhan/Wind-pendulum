#include "uart_handler.h"
#include "string.h"

struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;

void Uart_Get(void)
{
	static unsigned char ucRxCnt = 0, i = 0;
	extern char deviationx_rec[5],deviationx_rec[5];
	extern uint8_t	UART1RxBuffer[1];
	extern int recive_flag,scan_flag,servo_flag;
	extern char Uart_get[20];
	Uart_get[ucRxCnt++] = UART1RxBuffer[0];
	
	if(Uart_get[0] == 'W')										//头校验位W
	{
		
		if(Uart_get[ucRxCnt-1] == 'X')					//尾校验位X
		{
			recive_flag = 1;
				switch(Uart_get[1])
			{
				case 'A':														//帧头A:X方向正偏差，示例：WA4.26X   表示：左偏差4.26,即人脸在车右侧x=4.26处
					deviationx_rec[0] = '+';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'B':														//帧头B:X方向负偏差，示例：WB4.26X   表示：右偏差4.26,即人脸在车左侧x=-4.26处
					deviationx_rec[0] = '-';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'C':														//帧头C:Y方向正偏差，示例：WC4.26X   表示：下偏差4.26,即人脸在车上侧y=4.26处
					deviationx_rec[0] = '+';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'D':														//帧头D:Y方向负偏差，示例：WD4.26X   表示：上偏差4.26,即人脸在车下侧y=-4.26处
					deviationx_rec[0] = '-';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'S':														//帧头S:开启舵机扫描
					scan_flag = 1;break;
				
				case 'F':														//帧头F:停止舵机扫描，开始PID调整舵机
					scan_flag = 1;break;
			}
			Uart_DataProcess();
			ucRxCnt = 0;
		}
	}
	else ucRxCnt = 0;
}

void angle_rec(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//清空缓存区
	}
}

void angle_dateprocess(void)
{
	extern float Pitch,Roll,Yaw;
	
	Roll = (float)stcAngle.Angle[0]/32768*180;
	Pitch = (float)stcAngle.Angle[1]/32768*180;
	Yaw = (float)stcAngle.Angle[2]/32768*180;
}

void Get_Value(unsigned char* ucFlag)//获取VL53L0数据
{
	extern unsigned char ucRxData[100];
	char dis_rec[4];
	unsigned char *p;
	extern uint16_t Distance;
	int i=0;
	
		if(*ucFlag==1)
		{
			p=(unsigned char*)strstr((char*)ucRxData,"d:");
			
			while(*p!='m')
			{
				if(*p>='0'&&*p<='9')
				{
					
					dis_rec[i] = *p;
					i++;
				}
				p++;
			}
			Distance = atoi(dis_rec);
			i = 0;
			*ucFlag=0;
	 }
}

void Uart_DataProcess(void)
{
	extern float deviationx,deviationy;
	extern char deviationx_rec[5],deviationy_rec[5];
	deviationx = atof(deviationx_rec);
	deviationy = atof(deviationy_rec);
}
