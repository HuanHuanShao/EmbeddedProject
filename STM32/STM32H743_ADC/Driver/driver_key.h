#ifndef __DRIVER_KEY_H
#define __DRIVER_KEY_H

#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"

#define KEY_PIN			GPIO_PIN_13
#define KEY_PORT		GPIOC
#define KEY_IRQn		EXTI15_10_IRQn

#endif
