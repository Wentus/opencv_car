#include "Sharp.h"

static uint8_t voltToDistance(float data);

static float sharps[3][5];
static uint8_t times = 0;

void InitSharp(void)
{	
	RCC_ADCCLKConfig (RCC_PCLK2_Div6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitTypeDef gpioSharps;
	
	gpioSharps.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	gpioSharps.GPIO_Mode = GPIO_Mode_AIN;
	gpioSharps.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioSharps);
	
	ADC_InitTypeDef adcSharps;
	
	adcSharps.ADC_Mode = ADC_Mode_Independent;
	adcSharps.ADC_ScanConvMode = ENABLE;
	adcSharps.ADC_ContinuousConvMode = ENABLE;
	adcSharps.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adcSharps.ADC_DataAlign = ADC_DataAlign_Right;
	adcSharps.ADC_NbrOfChannel = 3;
	
	ADC_Init(ADC1, &adcSharps);

	ADC_InjectedSequencerLengthConfig(ADC1, 3);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
	
	ADC_ExternalTrigInjectedConvConfig( ADC1, ADC_ExternalTrigInjecConv_None );
 
  ADC_Cmd ( ADC1 , ENABLE ) ;
 
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1)){};
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1)){};
		
  ADC_AutoInjectedConvCmd(ADC1, ENABLE );
  ADC_SoftwareStartInjectedConvCmd ( ADC1 , ENABLE );
	
}

void readSharp(uint8_t* proximitySensors)
{
	sharps[0][times] = (float)(ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1)*3.3)/4096/4;
	sharps[1][times] = (float)(ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2)*3.3)/4096/4;
	sharps[2][times] = (float)(ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3)*3.3)/4096/4;
	if(times < 4) times++;
	else {
		times = 0;
		for(int i = 0; i < 3; i++)
		*(proximitySensors+2*i) = voltToDistance(sharps[i][0] + sharps[i][1] + sharps[i][2] + sharps[i][3]);
	}
}

static uint8_t voltToDistance(float data)
{
	 if(data <=2.5 && data >2)
		 return 10;
	 else if(data <= 2 && data > 1.5)
		 return 15;
	 else if(data <= 1.5 && data > 1.25)
		 return 20;
	 else if(data <= 1.25 && data > 1)
		 return 25;
	 else if(data <= 1 && data > 0.9)
		 return 30;
	 else if(data <= 0.9 && data > 0.85)
		 return 35;
	 else if(data <= 0.85 && data > 0.8)
		 return 40;
	 else if(data <= 0.8 && data > 0.7)
		 return 45;
	 else if(data <= 0.7 && data > 0.65)
		 return 50;
	 else if(data <= 0.65 && data > 0.55)
		 return 55;
	 else if(data <= 0.55 && data > 0.5)
		 return 60;
	 else if(data <= 0.5 && data > 0.47)
		 return 65;
	 else if(data <= 0.47 && data > 0.45)
		 return 70;
	 else if(data <= 0.45 && data > 0.43)
		 return 75;
	 else return 80;
}
