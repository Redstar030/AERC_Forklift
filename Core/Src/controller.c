#include "controller.h"
#include "ps4.h"    
#include "mecanum.h"
#include "fork.h"
#include "stm32f4xx_hal.h"
#include <string.h>

extern UART_HandleTypeDef huart1;

#define RX_TIMEOUT_MS   200
#define STICK_DEADZONE  10
#define FORK_THRESHOLD  200

static uint8_t  rx_byte;
static char     line_buf[CONTROLLER_BUFFER_SIZE];
static volatile uint8_t  line_idx   = 0;
static volatile uint8_t  line_ready = 0;
static char     line_complete[CONTROLLER_BUFFER_SIZE];

static uint32_t last_rx_tick = 0;

static int16_t scale_stick(int8_t v)
{
    if (v > -STICK_DEADZONE && v < STICK_DEADZONE) return 0;
    return (int16_t)((int32_t)v * 1000 / 127);
}

void Controller_Init(void)
{
    line_idx   = 0;
    line_ready = 0;
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        if (rx_byte == '\n' || rx_byte == '\r') {
            if (line_idx > 0) {
                line_buf[line_idx] = '\0';
                memcpy(line_complete, line_buf, line_idx + 1);
                line_ready = 1;
            }
            line_idx = 0;
        } else if (line_idx < CONTROLLER_BUFFER_SIZE - 1) {
            line_buf[line_idx++] = (char)rx_byte;
        } else {
            line_idx = 0;   
        }
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}

void Controller_Update(void)
{
    if (line_ready) {
        line_ready = 0;
        if (parse_controller_data(line_complete, &controller_state) == 0) {
            last_rx_tick = HAL_GetTick();
        }
    }

    if (HAL_GetTick() - last_rx_tick > RX_TIMEOUT_MS) {
        Mecanum_Stop();
        Fork_Stop();
        return;
    }

    int16_t vx = -scale_stick(controller_state.l_stick_y); 
    int16_t vy =  scale_stick(controller_state.l_stick_x); 
    int16_t wz =  scale_stick(controller_state.r_stick_x); 
    Mecanum_Drive(vx, vy, wz);

}