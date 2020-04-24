#ifndef __MAIN_H
#define __MAIN_H

#include "stm32h7xx_hal.h"

#define SAMPLE_NUMS			(280)
#define RANGE_BIN			(256)
#define DOPPLER_BIN			(128)
#define SAMPLE_OFFSET		(SAMPLE_NUMS - RANGE_BIN)

extern __IO uint16_t IF1_DATA[256][256];
extern __IO uint16_t IF2_DATA[256][256];
extern __IO uint16_t IF3_DATA[256][256];
extern __IO uint16_t gaAdcData[3][SAMPLE_NUMS];

void Error_Handler(void);

#endif