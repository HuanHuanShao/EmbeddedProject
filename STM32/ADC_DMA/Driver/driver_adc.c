#include "driver_adc.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
uint8_t MX_ADC1_Init(void)
{
	ADC_MultiModeTypeDef multimode = {0};
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Common config 
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV128;
	hadc1.Init.Resolution = ADC_RESOLUTION_16B;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc1.Init.LowPowerAutoWait = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.NbrOfDiscConversion = 1;
	
	hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_EXT_IT11;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	
	hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_ONESHOT;
	hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
	hadc1.Init.OversamplingMode = DISABLE;
	ADC_ConfigureBoostMode(&hadc1);
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		return 1;
	}
	
	
	/** Configure the ADC multi-mode 
	*/
	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
	{
		return 1;
	}
	/** Configure Regular Channel 
	*/
	sConfig.Channel = ADC_CHANNEL_16;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		return 1;
	}
	
	return 0;
}

static uint32_t HAL_RCC_ADC12_CLK_ENABLED=0;
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(adcHandle->Instance==ADC1)
	{
		HAL_RCC_ADC12_CLK_ENABLED++;
		if(HAL_RCC_ADC12_CLK_ENABLED==1){
			__HAL_RCC_ADC12_CLK_ENABLE();
		}

		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = ADC1_PIN_N;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(ADC1_DIF_PORT, &GPIO_InitStruct);
		
		/* ADC1 DMA Init */
		/* ADC1 Init */
		hdma_adc1.Instance = DMA1_Stream1;
		hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode = DMA_NORMAL;
		hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{
			//Error_Handler();
		}

		__HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);
		/* DMA1_Stream1_IRQn interrupt configuration */
		HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
	if(adcHandle->Instance==ADC1)
	{
		HAL_RCC_ADC12_CLK_ENABLED--;
		if(HAL_RCC_ADC12_CLK_ENABLED==0){
			__HAL_RCC_ADC12_CLK_DISABLE();
		}
		HAL_GPIO_DeInit(ADC1_DIF_PORT, ADC1_PIN_N);
	}
	
	HAL_DMA_DeInit(adcHandle->DMA_Handle);
} 

void StartAdc(uint32_t *addrADC1, uint16_t length)
{
	HAL_DMA_Start_IT(&hdma_adc1, (uint32_t)(&ADC1->DR), (uint32_t)addrADC1, length);
}