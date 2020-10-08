#include "VL53L1.h"

VL53L1_Dev_t                   dev;
int status=0;
volatile int IntCount;
#define isInterrupt 1 /* If isInterrupt = 1 then device working in interrupt mode, else device working in polling mode */
uint8_t byteData, sensorState=0;
uint16_t wordData;
uint8_t ToFSensor = 1; // 0=Left, 1=Center(default), 2=Right
uint16_t Distance;
uint16_t SignalRate;
uint16_t AmbientRate;
uint8_t RangeStatus;
uint8_t dataReady;
	

void vl53l1_init(void)
{
	
	XNUCLEO53L1A1_Init();
  dev.I2cHandle = &hi2c1;
  dev.I2cDevAddr = 0x52;

  ToFSensor = 1; // Select ToFSensor: 0=Left, 1=Center, 2=Right
  status = XNUCLEO53L1A1_ResetId(ToFSensor, 0); // Reset ToF sensor
  HAL_Delay(2);
  status = XNUCLEO53L1A1_ResetId(ToFSensor, 1); // Reset ToF sensor
  HAL_Delay(2);
 
/* Those basic I2C read functions can be used to check your own I2C functions */
  status = VL53L1_RdByte(&dev, 0x010F, &byteData);
//  printf("VL53L1X Model_ID: %X\n", byteData);
  status = VL53L1_RdByte(&dev, 0x0110, &byteData);
//  debug_log("VL53L1X Module_Type: %X\n", byteData);
  status = VL53L1_RdWord(&dev, 0x010F, &wordData);
//  debug_log("VL53L1X: %X\n", wordData);
  while(sensorState==0){
	status = VL53L1X_BootState(dev, &sensorState);
	HAL_Delay(2);
  }
//  debug_log("Chip booted\n");

  /* This function must to be called */
  status = VL53L1X_SensorInit(dev);

  /* Optional functions to set specific parameters here before start ranging */
//  debug_log("VL53L1X Ultra Lite Driver Example running ...\n");
  status = VL53L1X_StartRanging(dev);   /* This function has to be called to enable the ranging */
}

void vl53_readis(void)
{
	while (dataReady == 0)
		{
		  status = VL53L1X_CheckForDataReady(dev, &dataReady);
		  HAL_Delay(2);
	  }
	  dataReady = 0;
	  status = VL53L1X_GetRangeStatus(dev, &RangeStatus);
	  status = VL53L1X_GetDistance(dev, &Distance);
	  status = VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/
//	  debug_log("Now Distance is : %d mm\n", Distance);
}
