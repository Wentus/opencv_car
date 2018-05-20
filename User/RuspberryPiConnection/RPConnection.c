#include "RPConnection.h"
//#include "USART_Debug.h"

static uint8_t angle = 0;
static uint8_t speed = 0;

void RPConnection_Init()
{	
	  GPIO_InitTypeDef  gpio_USART;
	  GPIO_StructInit(&gpio_USART);  
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	  gpio_USART.GPIO_Pin = GPIO_Pin_2;
	  gpio_USART.GPIO_Mode = GPIO_Mode_AF_PP;
	  gpio_USART.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &gpio_USART);
	
	  gpio_USART.GPIO_Pin = GPIO_Pin_3;
	  gpio_USART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &gpio_USART);
	
	  USART_InitTypeDef husart2;
	  USART_StructInit(&husart2);
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
		husart2.USART_BaudRate = 9600;
	  husart2.USART_WordLength = USART_WordLength_8b ; 
	  husart2.USART_StopBits = USART_StopBits_1;
	  husart2.USART_Parity = USART_Parity_No;
	  husart2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  husart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  
	  USART_Init(USART2,&husart2);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART2_IRQn);
		USART_Cmd(USART2,ENABLE);	
}

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
			angle = USART_ReceiveData(USART2);
				for(int j = 0; j <1000; j++);
			//Usart_Transmit_uint8_t(angle);
			speed = USART_ReceiveData(USART2);
			//Usart_Transmit_uint8_t(speed);
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    } 
}

void SendToRaspberryPi(uint8_t* data, uint8_t count)
{
	USART_SendData(USART2, 244);
	//Usart_Transmit_uint8_t(244);
	for(int i = 0; i < count; i++){
			for(int j = 0; j <1000; j++);
		USART_SendData(USART2, *(data+i));
		//Usart_Transmit_uint8_t(*(data+i));
	}
}

signed int getNeededAngle()
{
	return angle-90;
}

signed int getNeededSpeed()
{
	return speed;
}	

/*void SendToRaspberryPi(char* fmt, ...)
{
	char buffer[50];
	int size = 0;//size +=sprintf(buffer, "%i\n\r", data);
	va_list ap;
	char *p, *sval;
	
	va_start(ap,fmt);
	for(p = fmt; *p; p++){
		if(*p != '%'){
			size += sprintf(buffer, "%c", *p);
			continue;
		}
		switch(*++p){
			case 'd':
				size += sprintf(buffer, "%d", va_arg(ap,int));
				break;
			case 'f':
				size += sprintf(buffer, "%f", va_arg(ap,double));
				break;
			case 's':
				for(sval = va_arg(ap,char*); *sval; sval++)
				size += sprintf(buffer, "%c", *sval);
				break;
			default:
				size += sprintf(buffer, "%c", *p);
				break;
		}
	}
	va_end(ap);
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j <1000; j++);
		USART_SendData(USART2,buffer[i]);
	}
}*/
