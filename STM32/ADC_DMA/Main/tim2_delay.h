#ifndef __TIM2_DELAY_H
#define __TIM2_DELAY_H

#include "stm32h7xx_hal.h"

extern void TIM2_Init(void);
extern void usSleep(uint16_t us);

#endif