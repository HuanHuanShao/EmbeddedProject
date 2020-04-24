#include "driver_dma.h"

void MX_DMA_Init(void)
{
	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();
//	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

}