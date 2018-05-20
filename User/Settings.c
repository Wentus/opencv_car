#include "Settings.h"

void SetSysClockTo72(void)
{
    ErrorStatus HSEStartUpStatus;

    RCC_DeInit();
    RCC_HSEConfig( RCC_HSE_ON);
	
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        RCC_HCLKConfig( RCC_SYSCLK_Div1);
        RCC_PCLK2Config( RCC_HCLK_Div1);
        RCC_PCLK1Config( RCC_HCLK_Div2);
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        RCC_PLLCmd( ENABLE);
 
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }
				
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
 
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
}

void SysTick_setting(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

static unsigned int delay_ms_count = 0;

void SysTick_Handler(void)
{
	if (delay_ms_count != 0)
		delay_ms_count--;
}

void delay_ms(__IO unsigned int msec)
{
	delay_ms_count = msec;
	SysTick_Config(SystemCoreClock / 1000);

	while (delay_ms_count != 0);

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_s(__IO unsigned int sec)
{
	delay_ms(sec * 1000);
}

void inform_error(void){}

