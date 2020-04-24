#ifndef __DRIVER_GPIO_H
#define __DRIVER_GPIO_H

#include <stdbool.h>
#include "stm32h7xx_hal.h"

/* CAL RESETN GPIO Set */
#define CAL_RESETN_PIN		GPIO_PIN_1
#define CAL_RESETN_PORT		GPIOE

/* EXTI Lines 11 GPIO Set */
#define EXTI_11_GPIO_PIN	GPIO_PIN_11
#define EXTI_11_PORT		GPIOB

/* Green Led GPIO */
#define GREEN_LED_PIN		GPIO_PIN_5
#define RED_LED_PIN			GPIO_PIN_4
#define LED_PORT			GPIOD

/* GPIO API */
extern void MX_GPIO_Init(void);
extern void green_led_on_off(bool f);
extern void red_led_on_off(bool f);

#endif
