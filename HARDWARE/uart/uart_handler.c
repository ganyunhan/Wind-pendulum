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
	
	if(Uart_get[0] == 'W')										//ͷУ��λW
	{
		
		if(Uart_get[ucRxCnt-1] == 'X')					//βУ��λX
		{
			recive_flag = 1;
				switch(Uart_get[1])
			{
				case 'A':														//֡ͷA:X������ƫ�ʾ����WA4.26X   ��ʾ����ƫ��4.26,�������ڳ��Ҳ�x=4.26��
					deviationx_rec[0] = '+';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'B':														//֡ͷB:X����ƫ�ʾ����WB4.26X   ��ʾ����ƫ��4.26,�������ڳ����x=-4.26��
					deviationx_rec[0] = '-';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'C':														//֡ͷC:Y������ƫ�ʾ����WC4.26X   ��ʾ����ƫ��4.26,�������ڳ��ϲ�y=4.26��
					deviationx_rec[0] = '+';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'D':														//֡ͷD:Y����ƫ�ʾ����WD4.26X   ��ʾ����ƫ��4.26,�������ڳ��²�y=-4.26��
					deviationx_rec[0] = '-';
					for(i = 2; i < ucRxCnt-1; i++)
				{
						deviationx_rec[i-1] = Uart_get[i];
				}break;
				
				case 'S':														//֡ͷS:�������ɨ��
					scan_flag = 1;break;
				
				case 'F':														//֡ͷF:ֹͣ���ɨ�裬��ʼPID�������
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
	
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		switch(ucRxBuffer[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
			//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//��ջ�����
	}
}

void angle_dateprocess(void)
{
	extern float Pitch,Roll,Yaw;
	
	Roll = (float)stcAngle.Angle[0]/32768*180;
	Pitch = (float)stcAngle.Angle[1]/32768*180;
	Yaw = (float)stcAngle.Angle[2]/32768*180;
}

void Get_Value(unsigned char* ucFlag)//��ȡVL53L0����
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
