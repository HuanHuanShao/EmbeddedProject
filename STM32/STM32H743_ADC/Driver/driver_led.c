#include "driver_led.h"

void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = BLUE_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(BLUE_LED_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = RED_LED_PIN;
	HAL_GPIO_Init(RED_LED_PORT, &GPIO_InitStruct);
}

void blue_led_light(bool f)
{
	HAL_GPIO_WritePin(BLUE_LED_PORT, BLUE_LED_PIN, f);
}

void red_led_light(bool f)
{
	HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, f);
}