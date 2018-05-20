#include "PID.h"
#include "USART_Debug.h"

static double Servo_previousI;
static double Servo_previousError;

static double Engine_previousI;
static double Engine_previousError;

static double pid(double  now, double  need, double previousI, double previousError,
							double Kp, double Ki, double Kd)
{
	double P = Kp*(need - now);
	double I = Ki*(need - now) + previousI;
	double D = Kd*((need - now) - previousError);
	
	previousI = I;
	previousError = need - now;
	
	//Usart_Transmit_double(need - now);
	return P+I+D;
}

double ServoPID(double  now, double  need,double Kp, double Ki, double Kd)
{
	return pid(now, need, Servo_previousI, Servo_previousError,Kp,Ki,Kd);
}
double EnginePID(double  now, double  need,double Kp, double Ki, double Kd)
{
	return pid(now, need, Engine_previousI, Engine_previousError,Kp,Ki,Kd);
}
