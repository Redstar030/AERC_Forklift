#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"

#define ENC_FL  0
#define ENC_FR  1
#define ENC_BL  2
#define ENC_BR  3

void Encoder_Init(void);
void Encoder_Reset(void);
int32_t Encoder_Get(uint8_t id);
int32_t Encoder_GetAverage(void);

#endif