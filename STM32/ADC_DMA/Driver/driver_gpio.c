#include "driver_gpio.h"

static void GPIO_CLK_ENABLE(void);
static void GPIO_NVIC_Cfg(void);
static void MX_EXTI_11_GPIO_Init(void);


void MX_GPIO_Init(void)
{
	GPIO_CLK_ENABLE();
	
	MX_EXTI_11_GPIO_Init();
	GPIO_NVIC_Cfg();
}

static void MX_EXTI_11_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin : PB11 */
	GPIO_InitStruct.Pin = EXTI_11_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(EXTI_11_PORT, &GPIO_InitStruct);
}

static void GPIO_CLK_ENABLE(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
}

static void GPIO_NVIC_Cfg(void)
{
	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

static volatile uint8_t t_f = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_11)
  {
    t_f = 1;
  }
}