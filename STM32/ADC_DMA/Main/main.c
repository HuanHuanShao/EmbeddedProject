#include "string.h"

#include "main.h"
#include "system_clk.h"
#include "driver_adc.h"
#include "driver_gpio.h"
#include "driver_dma.h"

#include "math.h"

#define SAMPLE_NUM			(5120U)

__IO uint16_t BUFF_1_2[2][SAMPLE_NUM] 	__attribute__ ( (at(0x24070000)) );
__IO uint16_t BUFF_3[2][SAMPLE_NUM] 	__attribute__ ( (at(0x24075000)) );

static volatile bool fadc = false;
static volatile bool fdeal = true;
static volatile bool ping_pong = true;

static void SCB_CacheEnable(void);
static void MPU_Config(void);
static bool f_deal(uint16_t *pdata);


uint16_t ChipId = 0;
uint16_t peak_num = 0;
static uint16_t *pThreshold = (uint16_t*)(0x2405EC00);
volatile uint8_t ADC_State = 0;

int main(void)
{
	uint16_t i = 0;
	bool retVal = false;
	uint8_t errCode = 0;
	
	memset((uint8_t*)BUFF_1_2, 0, sizeof(BUFF_1_2));
	memset((uint8_t*)BUFF_3, 0, sizeof(BUFF_3));
	SCB_CacheEnable();
	MPU_Config();
	HAL_Init();
	
	SystemClock_Config();	
	MX_DMA_Init();
	MX_GPIO_Init();
	errCode = MX_ADC1_Init();
		
	if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&BUFF_1_2[0][0], SAMPLE_NUM) != HAL_OK)
	{
		Error_Handler();
	}
	
	while(fadc==false);
	fadc = false;
	memset((uint8_t*)&BUFF_1_2[0][0], 0, sizeof(uint16_t)*SAMPLE_NUM);
	StartAdc((uint32_t*)&BUFF_1_2[0][0], SAMPLE_NUM);
	HAL_ADC_Start(&hadc1);

	while(1)
	{
		if(fadc==true)
		{
			fadc = false;
			
			if(fdeal==true)
			{
				fdeal = false;
				ping_pong = !ping_pong;
				memset((uint8_t*)&BUFF_1_2[ping_pong][0], 0, sizeof(uint16_t)*SAMPLE_NUM);
				StartAdc((uint32_t*)&BUFF_1_2[ping_pong][0], SAMPLE_NUM);
				HAL_ADC_Start(&hadc1);				
			}
			if(fdeal == false)
			{
				retVal = f_deal((uint16_t*)&BUFF_1_2[!ping_pong][0]);
				if(retVal==true)
				{
					memcpy((uint16_t*)&BUFF_3[!ping_pong][0], (uint16_t*)&BUFF_1_2[!ping_pong][0], sizeof(uint16_t)*SAMPLE_NUM);
				}
				fdeal = true;
			}
		}
	}	
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	fadc = true;
}

static bool f_deal(uint16_t *pdata)
{
	uint16_t i = 0;
	uint32_t sum = 0;
	
	for(i=0;i<SAMPLE_NUM;i++)
	{
		sum = sum + pdata[i];
	}
	
	if(sum>10000)
	{
		return true;
	}
	
	return false;
}

void Error_Handler(void)
{
	while(1)
	{
	}
}

static void SCB_CacheEnable(void)
{
	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();
	
	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();
}

static void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU attributes as WT for SRAM */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x24070000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

