#include "Engine.h"
#include "PID.h"
#include "USART_Debug.h"
#include "stdlib.h"

static uint8_t speedNow = 0;

void OptronInit()
{	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	
	GPIO_InitTypeDef gpioOptron;
	gpioOptron.GPIO_Pin = GPIO_Pin_14;
	gpioOptron.GPIO_Speed = GPIO_Speed_50MHz;
	gpioOptron.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &gpioOptron);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStruct;
  EXTI_StructInit(&EXTI_InitStruct);
  EXTI_InitStruct.EXTI_Line = EXTI_Line14;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitTypeDef NVIC_Struct;
	NVIC_Struct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Struct);

}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14)) {
		speedNow++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

void EngineInit()
{
	GPIO_InitTypeDef PWM_ports;
  TIM_TimeBaseInitTypeDef timer;
  TIM_OCInitTypeDef timerPWM;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  PWM_ports.GPIO_Mode = GPIO_Mode_AF_PP;
  PWM_ports.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  PWM_ports.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &PWM_ports);
	
	TIM_TimeBaseStructInit(&timer);
  timer.TIM_Prescaler = 1440-1;
  timer.TIM_Period = 100; 
  timer.TIM_ClockDivision =  TIM_CKD_DIV1;
  timer.TIM_CounterMode = TIM_CounterMode_Up;
	
  TIM_TimeBaseInit(TIM4, &timer);
 
  TIM_OCStructInit(&timerPWM);
  timerPWM.TIM_Pulse = 0;
  timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
  timerPWM.TIM_OutputState = TIM_OutputState_Enable;
  timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
  
	TIM_OC3Init(TIM4,&timerPWM);
	TIM_OC4Init(TIM4,&timerPWM);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

uint8_t GetSpeed()
{
	return speedNow;
}
/*static uint8_t speedToPWM(uint16_t Speed)
{
	Speed *=2;
	   if(Speed >= 25 && Speed < 100)
					return 36;
		 else if(Speed >= 100 && Speed <= 200)
					return 38;
		 else if(Speed >= 200 && Speed < 300)
					return 40;
		 else if(Speed >= 300 && Speed < 450)
					return 42;
		 else if(Speed >= 450 && Speed < 550)
					return 44;
		 else if(Speed >= 550 && Speed < 700)
					return 46;
		 else if(Speed >= 700 && Speed < 820)
					return 48;
		 else if(Speed >= 820 && Speed < 920)
					return 50;
		 else if(Speed >= 920 && Speed < 1020)
					return 52;
		 else if(Speed >= 1020 && Speed < 1100)
					return 54;
		 else if(Speed >= 1100 && Speed < 1150)
					return 56;
		 else if(Speed >= 1150 && Speed < 1200)
					return 58;
		 else if(Speed >= 1200 && Speed < 1300)
					return 52;
		 else return 34;
}*/

// sm/s
void ChangeSpeed(signed int speedNeed)
{
	static uint16_t  Speed = 0;
	if (speedNeed >= 0){
		Speed += EnginePID(speedNow/0.45, speedNeed, Engine_Kp, Engine_Ki, Engine_Kd);
		//size +=sprintf(buffer, "%f: ", Speed/0.45);
		//Usart_Transmit_string("SPEED", sizeof("SPEED"));
		if(Speed+30 < 0)
			Speed=0;
		else if(Speed+30 > 60)
			Speed = 30;
		
		TIM_SetCompare3(TIM4,(uint16_t)Speed+30);

		//Usart_Transmit_uint16_t((uint16_t)Speed);

	} else{
		Speed = EnginePID(speedNow/0.45, speedNeed, Engine_Kp, Engine_Ki, Engine_Kd);
		//size +=sprintf(buffer, "%f: ", Speed/0.45);
		//Usart_Transmit_string("SPEED", sizeof("SPEED"));
		if(Speed+30 < 0)
			Speed=0;
		else if(Speed+30 > 60)
			Speed = 30;
		
		TIM_SetCompare4(TIM4,(uint16_t)Speed+30);
		//Usart_Transmit_uint16_t((uint16_t)Speed+30);
		//Usart_Transmit_double(Speed/0.45);
	}
	speedNow = 0;
}
