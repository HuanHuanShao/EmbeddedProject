#include "tim2_delay.h"

void TIM2_Init(void)
{
    TIM_HandleTypeDef htim;
    
    htim.Instance = TIM2;
    
    htim.Init.Period = 240-1;
    htim.Init.Prescaler = 0;
    htim.Init.ClockDivision = 0;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.AutoReloadPreload = 0;
    
    if(HAL_TIM_Base_Init(&htim) != HAL_OK)
    {
        while(1)
        {
            
        }
    }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    __HAL_RCC_TIM2_CLK_ENABLE();
}

void usSleep(uint16_t us)
{
    TIM2->CNT = 0;
    TIM2->ARR = 240 * us;
    TIM2->CR1 |= TIM_CR1_CEN;
    while((TIM2->SR & TIM_SR_UIF) == RESET);
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->SR &= ~TIM_SR_UIF;
}