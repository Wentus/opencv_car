#ifndef PID_H
#define PID_H

#include "inttypes.h"

double ServoPID(double  now, double  need,double Kp, double Ki, double Kd);
double EnginePID(double  now, double  need,double Kp, double Ki, double Kd);

#endif /* PID_H */
