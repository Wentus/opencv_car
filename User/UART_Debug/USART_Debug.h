#ifndef DEBUG
#define DEBUG

#include <stdio.h>
#include <stdint.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void Usart_Init(void);
void Usart_Transmit_uint8_t(uint8_t data);
void Usart_Transmit_uint16_t(uint16_t data);
void Usart_Transmit_uint32_t(uint32_t data);
void Usart_Transmit_uint64_t(uint64_t data);
void Usart_Transmit_double(double data);
void Usart_Transmit_string(char* buffer,uint8_t size);

#endif /* DEBUG */
