#ifndef __KEY_H
#define __KEY_H
#include "stm32f4xx.h"
#include "system.h"


#define KEY0_PRESS  1
#define KEY1_PRESS  2
#define KEYUP_PRESS 3

void KeyInit(void);
u8 KeyScan(void);

#endif
