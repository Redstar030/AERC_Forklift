#include "encoder.h"
#include "stm32f4xx_hal_tim.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;

volatile int32_t enc_ticks[4] = {0, 0, 0, 0};
volatile int test = 0;

void Encoder_Init(void)
{
    HAL_TIM_IC_Start_IT(&htim2,  TIM_CHANNEL_1);  
    HAL_TIM_IC_Start_IT(&htim8,  TIM_CHANNEL_1);  
    HAL_TIM_IC_Start_IT(&htim1,  TIM_CHANNEL_1);  
    HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1); 
}

void Encoder_Reset(void)
{
    enc_ticks[0] = enc_ticks[1] = enc_ticks[2] = enc_ticks[3] = 0;
}

int32_t Encoder_Get(uint8_t id)
{
    if (id > 3) return 0;
    return enc_ticks[id];
}

int32_t Encoder_GetAverage(void)
{
    return (enc_ticks[0] + enc_ticks[1] + enc_ticks[2] + enc_ticks[3]) / 4;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
   
}