#include "main.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "driver_led.h"
#include "system_clk.h"

static void GPIO_CLK_ENABLE(void);
static void SCB_CacheEnable(void);

int main(void)
{
	SCB_CacheEnable();
	HAL_Init();
	SystemClock_Config();	
	
	GPIO_CLK_ENABLE();
	LED_GPIO_Init();
	blue_led_light(LED_ON);
	red_led_light(LED_ON);
	return 0;
}

static void GPIO_CLK_ENABLE(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
}

static void SCB_CacheEnable(void)
{
	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();
	
	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();
}

void Error_Handler(void)
{
	while(1)
	{
	}
}