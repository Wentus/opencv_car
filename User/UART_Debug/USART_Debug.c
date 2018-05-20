#include "USART_Debug.h"

void Usart_Init()
{	
	  GPIO_InitTypeDef  gpio_USART;
	  GPIO_StructInit(&gpio_USART);  
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	  gpio_USART.GPIO_Pin = GPIO_Pin_9;
	  gpio_USART.GPIO_Mode = GPIO_Mode_AF_PP;
	  gpio_USART.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &gpio_USART);
	
	  gpio_USART.GPIO_Pin = GPIO_Pin_10 ;
	  gpio_USART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &gpio_USART);
	
	  USART_InitTypeDef husart1;
	  USART_StructInit(&husart1);
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
		husart1.USART_BaudRate = 115200;
	  husart1.USART_WordLength = USART_WordLength_8b ; 
	  husart1.USART_StopBits = USART_StopBits_1;
	  husart1.USART_Parity = USART_Parity_No;
	  husart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  husart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  
	  USART_Init(USART1,&husart1);
		USART_Cmd(USART1,ENABLE);	
}

void Usart_Transmit_uint8_t(uint8_t data){
	char buffer[50];
	int size = sprintf(buffer, "%i\n\r", data);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
}

void Usart_Transmit_uint16_t(uint16_t data){
	char buffer[50];
	int size = sprintf(buffer, "%i\n\r", data);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
}

void Usart_Transmit_uint32_t(uint32_t data){
	char buffer[50];
	int size = sprintf(buffer, "%u\n\r", data);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
}

void Usart_Transmit_uint64_t(uint64_t data){
	char buffer[50];
	int size = sprintf(buffer, "%llu\n\r", data);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
}

void Usart_Transmit_double(double data){
	char buffer[50];
	int size = sprintf(buffer, "%f\n\r", data);
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
}

void Usart_Transmit_string(char* buffer,uint8_t size){
	for(int i = 0; i < size-1; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART1,buffer[i]);
	}
	for(int j = 0; j <1000; j++);
	USART_SendData(USART1,'\n');
	for(int j = 0; j <1000; j++);
	USART_SendData(USART1,'\r');
}
