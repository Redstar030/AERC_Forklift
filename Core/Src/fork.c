#include "fork.h"
#include "stm32f4xx_hal_gpio.h"

void Fork_Init(void)
{
    Fork1_Stop();
    Fork2_Stop();
}

void Fork1_Up(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);   
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_SET);   
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET); 
}

void Fork1_Down(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_SET);
}

void Fork1_Stop(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, GPIO_PIN_RESET);
}

void Fork2_Up(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);   
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);  
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET); 
}

void Fork2_Down(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);
}

void Fork2_Stop(void)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
}