#ifndef SERVO_H
#define SERVO_H

#include "stm32f10x.h"

#define Servo_Kp 1
#define Servo_Ki 0.5
#define Servo_Kd 0.1

void ServoInit(void);

signed int GetAngle(void);
void ChangeAngle(signed int angle);

#endif /* SERVO_H */
