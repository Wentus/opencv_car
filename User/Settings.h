#ifndef SETTINGS_H
#define SETTINGS_H

#include "stm32f10x.h"

void SetSysClockTo72(void);

void SysTick_setting(void);
void delay_ms(unsigned int msec);
void delay_s(unsigned int sec);

void inform_error(void);

#endif /* SETTINGS_H */
