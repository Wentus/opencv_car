#ifndef VL53L0X_INITIALIZE_H
#define VL53L0X_INITIALIZE_H

#include "Settings.h"
#include "VL53L0X.h"

#define BITBAND_GPIO(bitband_addr, pin)	(*(volatile uint32_t *)(PERIPH_BB_BASE + ((intptr_t)bitband_addr - PERIPH_BASE)*32 + 4 * pin))

#define SYS_FREQ	72000000
#define Periph_enable_flag  0x01
#define I2C_CLOCK   50000

void VL53L0X_Initialize(void);

#endif /* VL53L0X_INITIALIZE_H */
