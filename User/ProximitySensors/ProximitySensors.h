#ifndef PROXIMITY_SENSORS_H
#define PROXIMITY_SENSORS_H

#include "Sharp.h"
#include "VL53L0X_Initialize.h"

void ProximitySensors_Init(void);
void ProximitySensors_Read(uint8_t* proximitySensors);

#endif /* PROXIMITY_SENSORS_H */
