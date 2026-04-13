#include "mecanum.h"
#include "stm32f4xx_hal_gpio.h"

extern TIM_HandleTypeDef htim3;

#define PWM_MAX   999
#define CMD_MAX   999

typedef struct {
    GPIO_TypeDef *in1_port; uint16_t in1_pin;
    GPIO_TypeDef *in2_port; uint16_t in2_pin;
    uint32_t      pwm_ch;
} MotorCfg;

static MotorCfg motors[4] = {
    /* M_FL (M1) */ { GPIOB, GPIO_PIN_12, GPIOB, GPIO_PIN_13, TIM_CHANNEL_1 },
    /* M_FR (M2) */ { GPIOE, GPIO_PIN_3,  GPIOE, GPIO_PIN_2,  TIM_CHANNEL_2 },
    /* M_BL (M3) */ { GPIOD, GPIO_PIN_2,  GPIOD, GPIO_PIN_3,  TIM_CHANNEL_3 },
    /* M_BR (M4) */ { GPIOD, GPIO_PIN_7,  GPIOD, GPIO_PIN_4,  TIM_CHANNEL_4 },
 
};

static inline int16_t clamp(int32_t v, int32_t lo, int32_t hi) {
    return (int16_t)(v < lo ? lo : (v > hi ? hi : v));
}
static inline int32_t iabs(int32_t v) { return v < 0 ? -v : v; }

void Mecanum_Init(void)
{
    
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    Mecanum_Stop();
}

void Motor_Set(MotorId id, int16_t speed)
{
    if (id > M_BR) return;
    MotorCfg *m = &motors[id];
    speed = clamp(speed, -PWM_MAX, PWM_MAX);

    if (speed > 0) {
        HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
    } else if (speed < 0) {
        HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
    }
    __HAL_TIM_SET_COMPARE(&htim3, m->pwm_ch, (uint32_t)iabs(speed));
}

void Mecanum_Drive(int16_t vx, int16_t vy, int16_t wz)
{
    vx = clamp(vx, -CMD_MAX, CMD_MAX);
    vy = clamp(vy, -CMD_MAX, CMD_MAX);
    wz = clamp(wz, -CMD_MAX, CMD_MAX);

    int32_t w[4];
    w[M_FL] = vx + vy + wz;
    w[M_FR] = vx - vy - wz;
    w[M_BL] = vx - vy + wz;
    w[M_BR] = vx + vy - wz;

    int32_t peak = 0;
    for (int i = 0; i < 4; i++) if (iabs(w[i]) > peak) peak = iabs(w[i]);
    if (peak > PWM_MAX) {
        for (int i = 0; i < 4; i++) w[i] = w[i] * PWM_MAX / peak;
    }
    for (int i = 0; i < 4; i++) Motor_Set((MotorId)i, (int16_t)w[i]);
}

void Mecanum_Stop(void)
{
    for (int i = 0; i < 4; i++) Motor_Set((MotorId)i, 0);
}

void Mecanum_test(void)
{
    Mecanum_Init();
    HAL_Delay(1000);
    
    // right
    Mecanum_Drive(0, 400, 0);  
    HAL_Delay(2000);
    Mecanum_Stop();             
    HAL_Delay(1000);

    // 
    Mecanum_Drive(0, 0, 400);  HAL_Delay(2000);
    Mecanum_Stop();
    
    Motor_Set(4,-500);
}

/*HAL_Delay(1000);

Mecanum_Drive(400, 0, 0);   HAL_Delay(1500);  // 前進
Mecanum_Stop();              HAL_Delay(500);
Mecanum_Drive(-400, 0, 0);  HAL_Delay(1500);  // 後退
Mecanum_Stop();              HAL_Delay(500);
Mecanum_Drive(0, 400, 0);   HAL_Delay(1500);  // 右平移
Mecanum_Stop();              HAL_Delay(500);
Mecanum_Drive(0, -400, 0);  HAL_Delay(1500);  // 左平移
Mecanum_Stop();              HAL_Delay(500);
Mecanum_Drive(0, 0, 400);   HAL_Delay(1500);  // 原地右轉
Mecanum_Stop();*/