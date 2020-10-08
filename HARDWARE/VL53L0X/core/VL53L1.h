#ifndef _VL53L1_H
#define _VL53L1_H

#include "VL53L1X_API.h"
#include "VL53l1X_calibration.h"
#include "X-NUCLEO-53L1A1.h"
#include "i2c.h"

void vl53l1_init(void);
void vl53_readis(void);

#endif
