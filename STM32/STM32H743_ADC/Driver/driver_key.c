#include "driver_key.h"

void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = KEY_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(KEY_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(KEY_IRQn);
}

static volatile uint8_t t_f = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_11)
  {
    t_f = 1;
  }
}