/* DELAY function module */
// TIM6 used for timer. Required SPL work working.

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_PL_DELAY_H
#define __STM32F4xx_PL_DELAY_H

/* Includes from SPL library */
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

/* Prototypes */

// initialization of timer. Should be executed before timer will be used
void init_timer(void);

//make delay. Parameter is microseconds
void delay(uint16_t us);

#endif /*__STM32F4xx_PL_DELAY_H */
