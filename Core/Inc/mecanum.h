#ifndef MECANUM_H
#define MECANUM_H
 
#include "main.h"

typedef enum { M_FL = 0, M_FR = 1, M_BL = 2, M_BR = 3 } MotorId;
 
void Mecanum_Init(void);
 
void Motor_Set(MotorId id, int16_t speed);
 
/* High-level chassis control. All inputs in [-1000, 1000].
 *   vx  = forward  (+) / backward (-)
 *   vy  = strafe right (+) / left (-)
 *   wz  = rotate CW (+) / CCW (-)
 */

void Mecanum_Drive(int16_t vx, int16_t vy, int16_t wz);
 
void Mecanum_Stop(void);
 
#endif
 