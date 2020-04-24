#ifndef __DRIVER_ADC_H
#define __DRIVER_ADC_H

#include "stm32h7xx_hal.h"

/* ADC Handle */
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

/* ADC GPIO Set */
#define ADC1_PIN_N		GPIO_PIN_0		// IF3_P
#define ADC1_PIN_P		GPIO_PIN_1		// IF3_N
#define ADC1_DIF_PORT	GPIOA

/* ADC API */
extern uint8_t MX_ADC1_Init(void);

extern void StartAdc(uint32_t *addrADC1, uint16_t length);
extern void StopAdc(void);
#endif


