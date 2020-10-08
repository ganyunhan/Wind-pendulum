#include "linefinder.h"

uint16_t K1,K2,K3,K4;

void ScanLine_ReadPins(void)
{
	if(HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin) == GPIO_PIN_RESET)	K1 = 1; else K1 = 0;		//K1为最左侧光电对管
	if(HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin) == GPIO_PIN_RESET)	K2 = 1; else K2 = 0;
	if(HAL_GPIO_ReadPin(K3_GPIO_Port, K3_Pin) == GPIO_PIN_RESET)	K3 = 1; else K3 = 0;
	if(HAL_GPIO_ReadPin(K4_GPIO_Port, K4_Pin) == GPIO_PIN_RESET)	K4 = 1; else K4 = 0;
//	printf("K1 = %d	K2 = %d	K3 = %d	K4 = %d",K1,K2,K3,K4);
}

uint16_t ScanLine(void)
{
	uint16_t scanResult;
	uint16_t key = 0;

	ScanLine_ReadPins();
	switch (K1)
  {
  	case 1:key += 0x08;break;
  	case 0:key += 0x00;break;
  }
	switch (K2)
  {
  	case 1:key += 0x04;break;
  	case 0:key += 0x00;break;
  }
	switch (K3)
  {
  	case 1:key += 0x02;break;
  	case 0:key += 0x00;break;
  }
	switch (K4)
  {
  	case 1:key += 0x01;break;
  	case 0:key += 0x00;break;
  }
	
	switch (key)
  {
  	case 0x06: scanResult = 1;break;
  	case 0x0E: scanResult = 2;break;
		case 0x07: scanResult = 3;break;
		case 0x0C: scanResult = 4;break;
		case 0x08: scanResult = 5;break;
		case 0x04: scanResult = 5;break;
		case 0x03: scanResult = 6;break;
		case 0x02: scanResult = 7;break;
		case 0x01: scanResult = 7;break;
		case 0x00: scanResult = 8;break;
		case 0x0F: scanResult = 1;break;
  }
	return 	scanResult;					 
}
