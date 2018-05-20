#include "stm32f10x.h"
#include "Settings.h"
#include "USART_Debug.h"
#include "RPConnection.h"
#include "ProximitySensors.h"
#include "Engine.h"
#include "Servo.h"
#include "stdlib.h"

uint8_t proximitySensors[5];
//signed int speeed = 0;
uint8_t times = 0;
//uint8_t angle = 0;
//char bufferr[50];
//int sizee;
// sprintf(buffer, "%u\n\r", data);

void TIMTransmit_IRQ_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBase;
	
	TIM_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBase.TIM_Prescaler = 7200;
	TIM_TimeBase.TIM_Period = 100;
	TIM_TimeBase.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBase.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBase);
	
  TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef nvicStructure;
  nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);
	
}
//10ms
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)){
		ProximitySensors_Read(proximitySensors);
		if(times < 4){
			times++;
		}else{
			times = 0;
			SendToRaspberryPi(proximitySensors, 5);
			ChangeSpeed(getNeededSpeed());
		}
		if(GetAngle() != getNeededSpeed())
			ChangeAngle(getNeededSpeed());
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
uint8_t data[2];
int angle = 0;
int speed = 0;
int main(void)
{
	SetSysClockTo72();
  //Usart_Init();
	RPConnection_Init();
  //ProximitySensors_Init();
	SysTick_setting();
	//OptronInit();
	//EngineInit();
	//ServoInit();
	//TIMTransmit_IRQ_Init();
	data[0] = 1;
	data[1] = 2;
	while(1)
	{
			//for(int j = 0; j <2; j++);
		SendToRaspberryPi(data,2);
		delay_ms(10);
		angle = GetAngle();
		SendToRaspberryPi((uint8_t*)&angle,1);
		speed = GetSpeed();
		SendToRaspberryPi((uint8_t*)&speed,1);
		delay_ms(100);
		//SendToRaspberryPi("%i%i%i%i%i%i",254,proximitySensors[0],proximitySensors[1],proximitySensors[2],proximitySensors[3],proximitySensors[4]);
		//TIM_SetCompare3(TIM4,40);
		/*speeed = 300;
		sizee +=sprintf(bufferr, "%d : ", speeed);
		Usart_Transmit_string(bufferr, sizee);
		delay_ms(1500);
		Usart_Transmit_string("----------", sizeof("----------"));
		sizee = 0;*/
		
		/*speeed = 0;
		sizee +=sprintf(bufferr, "%d : ", speeed);
		Usart_Transmit_string(bufferr, sizee);
		delay_ms(120);
		Usart_Transmit_string("----------", sizeof("----------"));
		sizee = 0;*/
		
		/*speeed = -80;
		sizee +=sprintf(bufferr, "%d : ", speeed);
		Usart_Transmit_string(bufferr, sizee);
		delay_ms(1500);
		Usart_Transmit_string("----------", sizeof("----------"));
		sizee = 0;*/
		
	}	
}
