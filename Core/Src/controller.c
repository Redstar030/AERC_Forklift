/*#include "controller.h"
#include "mecanum.h"
#include "fork.h"

extern UART_HandleTypeDef huart1;

#define SPEED_DRIVE   500
#define SPEED_STRAFE  500
#define SPEED_TURN    400

static volatile uint8_t rx_byte;   
static volatile uint8_t new_cmd = 0;
static volatile char    latest = 'S';

void Controller_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_byte, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        latest = (char)rx_byte;
        new_cmd = 1;
        HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_byte, 1);  
}

void Controller_Update(void)
{
    if (!new_cmd) return;
    new_cmd = 0;
    
    switch (latest) {
        case 'w': case 'W':  Mecanum_Drive( SPEED_DRIVE,  0, 0); break;  // 前
        case 's': case 'S':  Mecanum_Drive(-SPEED_DRIVE,  0, 0); break;  // 後
        case 'a': case 'A':  Mecanum_Drive(0, -SPEED_STRAFE, 0); break;  // 左平移
        case 'd': case 'D':  Mecanum_Drive(0,  SPEED_STRAFE, 0); break;  // 右平移
        case 'q': case 'Q':  Mecanum_Drive(0, 0, -SPEED_TURN);  break;  // 左轉
        case 'e': case 'E':  Mecanum_Drive(0, 0,  SPEED_TURN);  break;  // 右轉
        case 'x': case 'X':  Mecanum_Stop();                     break;  // 停

        case 'i': case 'I':  Fork_Up();   break;
        case 'k': case 'K':  Fork_Down(); break;
        case 'j': case 'J':  Fork_Stop(); break;

        default: break;
    }
}*/

#include "controller.h"
#include "receiver.h"
#include "mecanum.h"
#include "fork.h"

extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;

static Receiver rx_ly;  
static Receiver rx_lx;  
static Receiver rx_rx;  
static Receiver rx_ry;  

#define FORK_THRESHOLD  200  

void Controller_Init(void)
{
    Receiver_Init(&rx_ly, &htim8,  TIM_CHANNEL_1);   // PC6
    Receiver_Init(&rx_lx, &htim8,  TIM_CHANNEL_2);   // PC7
    Receiver_Init(&rx_ry, &htim12, TIM_CHANNEL_1);   // PB14
    Receiver_Init(&rx_rx, &htim12, TIM_CHANNEL_2);   // PB15
}

void Controller_Update(void)
{
    if (!Receiver_IsAlive(&rx_lx)
        || !Receiver_IsAlive(&rx_ly)
        || !Receiver_IsAlive(&rx_rx))
    {
        Mecanum_Stop();
        Fork_Stop();
        return;
    }

    int16_t vx = Receiver_GetScaled(&rx_ly, 1000);
    int16_t vy = Receiver_GetScaled(&rx_lx, 1000);
    int16_t wz = Receiver_GetScaled(&rx_rx, 1000);
    Mecanum_Drive(vx, vy, wz);

    // 鏟斗
    int16_t fork_input = Receiver_GetScaled(&rx_ry, 1000);
    if      (fork_input >  FORK_THRESHOLD) Fork_Up();
    else if (fork_input < -FORK_THRESHOLD) Fork_Down();
    else                                   Fork_Stop();
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim8) {
        switch (htim->Channel) {
            case HAL_TIM_ACTIVE_CHANNEL_1: Receiver_HandleCapture(&rx_ly); break;
            case HAL_TIM_ACTIVE_CHANNEL_2: Receiver_HandleCapture(&rx_lx); break;
            default: break;
        }
    } else if (htim == &htim12) {
        switch (htim->Channel) {
            case HAL_TIM_ACTIVE_CHANNEL_1: Receiver_HandleCapture(&rx_ry); break;
            case HAL_TIM_ACTIVE_CHANNEL_2: Receiver_HandleCapture(&rx_rx); break;
            default: break;
        }
    }
}