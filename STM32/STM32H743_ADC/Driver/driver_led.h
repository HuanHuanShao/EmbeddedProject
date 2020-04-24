#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include <stdbool.h>

#define BLUE_LED_PIN		GPIO_PIN_7
#define BLUE_LED_PORT		GPIOB

#define RED_LED_PIN			GPIO_PIN_14
#define RED_LED_PORT		GPIOB

enum{
	LED_OFF = 0,
	LED_ON  = 1
};

extern void LED_GPIO_Init(void);
extern void blue_led_light(bool f);
extern void red_led_light(bool f);

#endif